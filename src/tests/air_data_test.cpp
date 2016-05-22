#include "air_data.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(AirDataTests)
{

};

TEST(AirDataTests, pressureToAltitude)
{
    DOUBLES_EQUAL(0, air_data_compute_altitude(101325), 1);
    DOUBLES_EQUAL(110.9, air_data_compute_altitude(100000), 1);
}


TEST(AirDataTests, dynamicPressureToAirspeed)
{
    DOUBLES_EQUAL(0, air_data_compute_airspeed(0), 0.01);
    DOUBLES_EQUAL(1.41, air_data_compute_airspeed(1.225), 1);
    DOUBLES_EQUAL(0, air_data_compute_airspeed(-1), 1);
}
