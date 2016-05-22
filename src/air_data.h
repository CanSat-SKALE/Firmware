#ifndef AIR_DATA_H
#define AIR_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

float air_data_compute_altitude(float pressure);
float air_data_compute_airspeed(float dynamic_pressure);

#ifdef __cplusplus
}
#endif

#endif /* AIR_DATA_H */
