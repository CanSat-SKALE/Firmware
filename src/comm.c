#include <ch.h>
#include <hal.h>
#include "thread_prio.h"
#include <string.h>
#include "air_data.h"
#include "sensor_readout.h"
#include "telemetry_protocol.h"
#include "log.h"

#include "comm.h"


static mutex_t telemetry_lock;
static telemetry_state_t telemetry;
static char telemetry_frame_buffer[TELEMETRY_FRAME_BUFFER_SIZE];

static THD_WORKING_AREA(comm_tx_wa, 1024);
static THD_FUNCTION(comm_tx, arg)
{
    BaseSequentialStream *comm_port = (BaseSequentialStream*)arg;
    chRegSetThreadName("comm_tx");

    log_info("tx thrad started");

    while (true) {
        chMtxLock(&telemetry_lock);
        if (should_resend_last_telemetry_frame(&telemetry)) {
            chSequentialStreamWrite(comm_port,
                                    (const uint8_t *)telemetry_frame_buffer,
                                    strlen(telemetry_frame_buffer));
            log_info("sending telemetry frame: %s", telemetry_frame_buffer);
        }
        chMtxUnlock(&telemetry_lock);
        chThdSleepMilliseconds(50);
    }
}

static THD_WORKING_AREA(comm_rx_wa, 1024);
static THD_FUNCTION(comm_rx, arg)
{
    BaseSequentialStream *comm_port = (BaseSequentialStream*)arg;
    chRegSetThreadName("comm_rx");

    log_info("rx thrad started");

    static char resp_buf[TELEMETRY_FRAME_BUFFER_SIZE];
    static telemetry_rx_buffer_t b;
    telemetry_rx_buffer_init(&b);
    while (true) {
        char c = chSequentialStreamGet(comm_port);
        (void)c;
        chMtxLock(&telemetry_lock);
        char *buf = telemetry_rx_buffer_input_char(&b, c);
        if (buf != NULL) {
            log_info("rx frame: %s", buf);
            telemetry_parse_frame(&telemetry, buf, resp_buf);
            if (strlen(resp_buf) != 0) {
                chSequentialStreamWrite(comm_port,
                                        (const uint8_t *)resp_buf,
                                        strlen(resp_buf));
                log_info("sending response: &s", resp_buf);
            }
        }
        chMtxUnlock(&telemetry_lock);
    }
}

static THD_WORKING_AREA(periodic_telemetry_wa, 1024);
static THD_FUNCTION(periodic_telemetry, arg)
{
    (void)arg;
    chRegSetThreadName("periodic_telemetry");

    log_info("telemetry thrad started");

    static struct telemetry_data_s data;
    while (true) {
        chThdSleepMilliseconds(1000);

        float pressure, temperature;
        float dynamic_pressure = 0; // TODO read differential pressure sensor
        sensor_get_ms5611(&pressure, &temperature);
        data.altitude = air_data_compute_altitude(pressure);
        data.pressure = pressure;
        data.speed = air_data_compute_airspeed(dynamic_pressure);
        data.temperature = temperature;
        data.bus_voltage = 0; // TODO read battery voltage
        data.gps_latitude = 0; // TODO GPS
        data.gps_longitude = 0;
        data.gps_altitude = 0;
        data.gps_satellite_nbr = 0;
        data.gps_speed = 0;

        chMtxLock(&telemetry_lock);
        telemetry_assemble_frame(&telemetry, &data, telemetry_frame_buffer);
        chMtxUnlock(&telemetry_lock);
    }
}


static THD_WORKING_AREA(comm_relay_force_deploy_wa, 1024);
static THD_FUNCTION(comm_relay_force_deploy, arg)
{
    (void) arg;
    chRegSetThreadName("comm_relay_force_deploy");
    int last_deploy = 0;
    while (true) {
        chMtxLock(&telemetry_lock);
        if (telemetry.force_deploy > last_deploy) {
            last_deploy = telemetry.force_deploy;

            log_info("sending force deploy to container");
            // send force deploy over IR
            IR_pwm(true);
            chThdSleepMilliseconds(2000);
            IR_pwm(false);
        }
        chMtxUnlock(&telemetry_lock);
        chThdSleepMilliseconds(100);
    }
}

void comm_start(BaseSequentialStream *port)
{
    chMtxObjectInit(&telemetry_lock);
    telemetry_init(&telemetry);
    chThdCreateStatic(comm_tx_wa, sizeof(comm_tx_wa), THD_PRIO_COMM, comm_tx, port);
    chThdCreateStatic(comm_rx_wa, sizeof(comm_rx_wa), THD_PRIO_COMM, comm_rx, port);
    chThdCreateStatic(periodic_telemetry_wa, sizeof(periodic_telemetry_wa), THD_PRIO_COMM, periodic_telemetry, NULL);
    chThdCreateStatic(comm_relay_force_deploy_wa, sizeof(comm_relay_force_deploy_wa), THD_PRIO_COMM, comm_relay_force_deploy, port);
}
