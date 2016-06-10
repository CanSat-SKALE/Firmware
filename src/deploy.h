#ifndef DEPLOY_H
#define DEPLOY_H

#include <stdbool.h>

#define NB_SAMPLES_REFERENCE 10
#define READY_ALTITUDE 300 // [m]
#define DEPLOYMENT_ALTITUDE 400 // [m]
#define CLIMB_RATE_FILTER_TIME 5 // [nb samples @10Hz]

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float altitude_buffer[CLIMB_RATE_FILTER_TIME];
    int altitude_buffer_pos;
} climb_rate_filter_t;

void climb_rate_filter_init(climb_rate_filter_t *f);
float climb_rate_update_10Hz(climb_rate_filter_t *f, float altitude);


typedef struct {
    float altitude_reference;
    float altitude_reference_acc;
    bool altitude_reference_set;
    int nb_zero_reference_samples_needed;
    bool ready;
    climb_rate_filter_t climb_rate_filter;
} deployment_trigger_t;

void deployment_init(deployment_trigger_t *t);
void deployment_set_reference(deployment_trigger_t *t, float altitude_above_sea_level);
float deployment_get_altitude_reference(deployment_trigger_t *t);
float deployment_get_altitude_above_ground(deployment_trigger_t *t, float altitude_above_sea_level);
bool deployment_trigger_should_activate_update_10Hz(deployment_trigger_t *t, float altitude_above_sea_level);


#ifdef __cplusplus
}
#endif

#endif /* DEPLOY_H */
