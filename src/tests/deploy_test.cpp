#include "deploy.h"
#include "math.h"
#include "CppUTest/TestHarness.h"


TEST_GROUP(ClimbRateFilter)
{
};

TEST(ClimbRateFilter, Constant)
{
    climb_rate_filter_t f;
    climb_rate_filter_init(&f);
    climb_rate_update_10Hz(&f, 0);
    CHECK_EQUAL(0, climb_rate_update_10Hz(&f, 0));
}

TEST(ClimbRateFilter, StepUp)
{
    climb_rate_filter_t f;
    climb_rate_filter_init(&f);
    for (int i = 0; i < CLIMB_RATE_FILTER_TIME; i++) {
        // step from 0 to 1 over 0.5s (filter time=5 at 10Hz) is 2
        CHECK_EQUAL(2, climb_rate_update_10Hz(&f, 1));
    }
    CHECK_EQUAL(0, climb_rate_update_10Hz(&f, 1));
}

TEST(ClimbRateFilter, StepDown)
{
    climb_rate_filter_t f;
    climb_rate_filter_init(&f);
    for (int i = 0; i < CLIMB_RATE_FILTER_TIME; i++) {
        climb_rate_update_10Hz(&f, 1);
    }
    for (int i = 0; i < CLIMB_RATE_FILTER_TIME; i++) {
        // step from 0 to 1 (filter time=5 at 10Hz -> 0.5s average) is 2
        CHECK_EQUAL(-2, climb_rate_update_10Hz(&f, 0));
    }
    CHECK_EQUAL(0, climb_rate_update_10Hz(&f, 0));
}


TEST_GROUP(DeployTest)
{
};

TEST(DeployTest, AltitudeReference)
{
    deployment_trigger_t t;
    deployment_init(&t);
    CHECK_EQUAL(0, deployment_get_altitude_reference(&t));
    deployment_set_reference(&t, 42);
    CHECK_EQUAL(42, deployment_get_altitude_reference(&t));
    CHECK_EQUAL(58, deployment_get_altitude_above_ground(&t, 100));
}

TEST(DeployTest, UpdateTakesAltitudeReferenceOnFirstSamples)
{
    deployment_trigger_t t;
    deployment_init(&t);
    int i;
    for (i = 1; i <= 10; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t, i));
    }
    float sum_of_1_to_10 = 10*(10+1)/2;
    CHECK_EQUAL(sum_of_1_to_10/10, deployment_get_altitude_reference(&t))

    // further samples are ignored
    deployment_trigger_should_activate_update_10Hz(&t, 1000);
    CHECK_EQUAL(sum_of_1_to_10/10, deployment_get_altitude_reference(&t))
}

TEST(DeployTest, ReadyAt300meters)
{
    deployment_trigger_t t;
    deployment_init(&t);
    float reference_altitude = 600;
    for (int i = 0; i < 10; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t, reference_altitude));
    }
    CHECK_FALSE(t.ready);
    deployment_trigger_should_activate_update_10Hz(&t, reference_altitude + 300);
    CHECK_TRUE(t.ready); // activate after 300
    deployment_trigger_should_activate_update_10Hz(&t, reference_altitude + 290);
    CHECK_TRUE(t.ready); // stay active
}

TEST(DeployTest, Deploy)
{
    deployment_trigger_t t;
    deployment_init(&t);
    float reference_altitude = 600;

    // init at ground level
    for (int i = 0; i < 10; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t, reference_altitude));
    }

    // go up a little
    for (int i = 0; i < 10; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t,
                    reference_altitude + 10));
    }

    // go back down
    for (int i = 0; i < 10; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t,
                    reference_altitude + 5));
    }

    // climb to 450m
    for (int i = 0; i < 450; i++) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t,
                    reference_altitude + i));
    }

    // glide down to 401m
    for (float alt = 450; alt > 401; alt-=0.1) {
        CHECK_FALSE(deployment_trigger_should_activate_update_10Hz(&t,
                    reference_altitude + alt ));
    }

    // and activate at 400m
    CHECK_TRUE(deployment_trigger_should_activate_update_10Hz(&t,
               reference_altitude + 400));
}

