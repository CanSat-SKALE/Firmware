#ifndef TELEMETRY_PROTOCOL_H
#define TELEMETRY_PROTOCOL_H

/*
protocol:

SENSOR - <TEAM ID>, .. \n
ACK    - ACK-SENSOR, PACKET COUNT \n

IMG    - IMG, FRAME NUMBER, DATA (HEX/BASE64) \n
ACK    - ACKI, FRAME NUMBER \n

--------

CMD    - CMD, CMD NUMBER, NAME, ARGS, ... \n
ACK    - ACKC,  CMD NUMBER \n

*/


#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define TELEMETRY_FRAME_BUFFER_SIZE 100+1

typedef struct {
    int telemetry_frame_count;
    int last_telemetry_ack;
} telemetry_state_t;

typedef struct {
    char buffer[TELEMETRY_FRAME_BUFFER_SIZE];
    int idx;
} telemetry_rx_buffer_t;

struct telemetry_data_s {
    int32_t altitude; // [m] from barometer
    int32_t pressure; // [Pa]
    float speed; // [m/s] from pitot tube
    int32_t temperature; // [degC]
    float bus_voltage; // [V] from battery
    float gps_latitude; // [deg]
    float gps_longitude; // [deg]
    float gps_altitude; // [m]
    int gps_satellite_nbr;
    float gps_speed; // [m/s]
};

void telemetry_init(telemetry_state_t *t);
void telemetry_assemble_frame(telemetry_state_t *t, const struct telemetry_data_s *data, char *frame);
void telemetry_parse_frame(telemetry_state_t *t, const char *frame);
bool should_resend_last_telemetry_frame(telemetry_state_t *t);

void telemetry_rx_buffer_init(telemetry_rx_buffer_t *b);
char *telemetry_rx_buffer_input_char(telemetry_rx_buffer_t *b, char c);

#ifdef __cplusplus
}
#endif

#endif /* TELEMETRY_PROTOCOL_H */