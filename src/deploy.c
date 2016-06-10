#include "deploy.h"


void climb_rate_filter_init(climb_rate_filter_t *f)
{
    int i;
    for (i = 0; i < CLIMB_RATE_FILTER_TIME; i++) {
        f->altitude_buffer[i] = 0;
    }
    f->altitude_buffer_pos = 0;
}

float climb_rate_update_10Hz(climb_rate_filter_t *f, float altitude)
{
    float diff = altitude - f->altitude_buffer[f->altitude_buffer_pos];
    f->altitude_buffer[f->altitude_buffer_pos] = altitude;

    // increment buffer pointer
    f->altitude_buffer_pos++;
    if (f->altitude_buffer_pos >= CLIMB_RATE_FILTER_TIME) {
        f->altitude_buffer_pos = 0;
    }

    float rate = diff / ((float)CLIMB_RATE_FILTER_TIME / 10); // for 10Hz
    return rate;
}


void deployment_init(deployment_trigger_t *t)
{
    t->altitude_reference = 0;
    t->altitude_reference_acc = 0;
    t->altitude_reference_set = false;
    t->nb_zero_reference_samples_needed = NB_SAMPLES_REFERENCE;
    t->ready = false;
    climb_rate_filter_init(&t->climb_rate_filter);
}

void deployment_set_reference(deployment_trigger_t *t, float altitude_above_sea_level)
{
    t->altitude_reference = altitude_above_sea_level;
}

float deployment_get_altitude_reference(deployment_trigger_t *t)
{
    return t->altitude_reference;
}

float deployment_get_altitude_above_ground(deployment_trigger_t *t, float altitude_above_sea_level)
{
    return altitude_above_sea_level - t->altitude_reference;
}

bool deployment_trigger_should_activate_update_10Hz(deployment_trigger_t *t, float altitude_above_sea_level)
{
    // initial calibration of zero level
    if (t->nb_zero_reference_samples_needed > 0) {
        t->altitude_reference_acc += altitude_above_sea_level;
        t->nb_zero_reference_samples_needed--;
        if (t->nb_zero_reference_samples_needed == 0) {
            deployment_set_reference(t, t->altitude_reference_acc / NB_SAMPLES_REFERENCE);
            t->altitude_reference_set = true;
        }
    }

    // first stage: reach READY_ALTITUDE
    float altitude_above_ground = deployment_get_altitude_above_ground(t, altitude_above_sea_level);
    if (t->altitude_reference_set && altitude_above_ground >= READY_ALTITUDE) {
        t->ready = true;
    }

    // second stage: below DEPLOYMENT_ALTITUDE with a negative climb rate
    float climb_rate = climb_rate_update_10Hz(&t->climb_rate_filter, altitude_above_sea_level);
    if (t->ready && climb_rate < 0 && altitude_above_ground <= DEPLOYMENT_ALTITUDE) {
        return true;
    }
    return false;
}

