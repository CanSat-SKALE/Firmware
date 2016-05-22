#include <math.h>
#include "air_data.h"

static const float sea_level_pressure = 101325; // [Pa]
static const float vertical_pressure_decrease = 0.0833f; // [m/Pa]
static const float air_density = 1.225f; // [kg/m3]

float air_data_compute_altitude(float pressure)
{
    return (sea_level_pressure - pressure) * vertical_pressure_decrease;
}

float air_data_compute_airspeed(float dynamic_pressure)
{
    if (dynamic_pressure > 0) {
        return sqrtf(2 * dynamic_pressure / air_density);
    } else {
        return 0;
    }
}
