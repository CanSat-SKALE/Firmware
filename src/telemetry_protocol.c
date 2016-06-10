#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "telemetry_protocol.h"

#define TEAM_ID 8099


void telemetry_init(telemetry_state_t *t)
{
    t->telemetry_frame_count = 1;
    t->last_telemetry_ack = 0;
    t->force_deploy = 0;
}

void telemetry_assemble_frame(telemetry_state_t *t, const struct telemetry_data_s *data, char *frame)
{
    snprintf(frame, TELEMETRY_FRAME_BUFFER_SIZE,
             "%d,%d,%d,%"PRId32",%"PRId32",%.1f,%"PRId32",%.2f,%f,%f,%.1f,%d,%.1f,%"PRId32",%" PRId32 "\n",
             TEAM_ID,
             t->telemetry_frame_count, // TODO this should be mission time
             t->telemetry_frame_count,
             data->altitude,
             data->pressure,
             data->speed,
             data->temperature,
             data->bus_voltage,
             data->gps_latitude,
             data->gps_longitude,
             data->gps_altitude,
             data->gps_satellite_nbr,
             data->gps_speed,
             (uint32_t)0,
             (uint32_t)0);
    t->telemetry_frame_count++;
}

void telemetry_parse_frame(telemetry_state_t *t, const char *frame,
                           char *response)
{
    response[0] = '\0'; // by default don't send response
    if (strncmp("ACK-SENSOR", frame, strlen("ACK-SENSOR")) == 0) {
        const char *arg1 = strchr(frame, ',');
        if (arg1 != NULL) {
            long int ack_nbr = strtol(++arg1, NULL, 10);
            if (ack_nbr != 0) {
                t->last_telemetry_ack = ack_nbr;
            }
        }
    }
    if (strncmp("COMMAND", frame, strlen("COMMAND")) == 0) {
        const char *arg1 = strchr(frame, ',');
        if (arg1 != NULL) {
            long int cmd_seq_nbr = strtol(++arg1, NULL, 10);
            if (cmd_seq_nbr != 0) {
                const char *arg2 = strchr(arg1, ',');
                arg2++;
                if (arg2 != NULL) {
                    if (strncmp("FORCE-DEPLOY", arg2, strlen("FORCE-DEPLOY"))) {
                        t->force_deploy = cmd_seq_nbr;
                        snprintf(response, TELEMETRY_FRAME_BUFFER_SIZE,
                                 "ACK-COMMAND, %ld\n", cmd_seq_nbr);
                    }
                }
            }
        }
    }
}

bool should_resend_last_telemetry_frame(telemetry_state_t *t)
{
    if (t->last_telemetry_ack < t->telemetry_frame_count - 1) {
        return true;
    } else {
        return false;
    }
}


void telemetry_rx_buffer_init(telemetry_rx_buffer_t *b)
{
    b->idx = 0;
}

char *telemetry_rx_buffer_input_char(telemetry_rx_buffer_t *b, char c)
{
    b->buffer[b->idx++] = c;
    if (c == '\n') {
        b->buffer[b->idx] = '\0';
        b->idx = 0;
        return b->buffer;
    }
    return NULL;
}
