#include "telemetry_protocol.h"
#include "CppUTest/TestHarness.h"
#include <string.h>


const struct telemetry_data_s telem_data = {
    .altitude = 300,
    .pressure = 97772,
    .speed = 10,
    .temperature = 15,
    .bus_voltage = 1.18,
    .gps_latitude = 46.532162,
    .gps_longitude = 6.591388,
    .gps_altitude = 314,
    .gps_satellite_nbr = 4,
    .gps_speed = 9,
};

TEST_GROUP(TelemetryTest)
{

};

TEST(TelemetryTest, TelemetryFrameEndsWithNewline)
{
    char framebuffer[TELEMETRY_FRAME_BUFFER_SIZE];
    telemetry_state_t t;
    telemetry_init(&t);
    telemetry_assemble_frame(&t, &telem_data, framebuffer);
    CHECK_EQUAL('\n', framebuffer[strlen(framebuffer) - 1])
}

TEST(TelemetryTest, Framenumber)
{
    char framebuffer[TELEMETRY_FRAME_BUFFER_SIZE];
    telemetry_state_t t;
    telemetry_init(&t);
    telemetry_assemble_frame(&t, &telem_data, framebuffer);
    STRNCMP_EQUAL("8099,1", framebuffer, 6);
    telemetry_assemble_frame(&t, &telem_data, framebuffer);
    STRNCMP_EQUAL("8099,2", framebuffer, 6);
}

TEST(TelemetryTest, telemetryData)
{
    char framebuffer[TELEMETRY_FRAME_BUFFER_SIZE];
    telemetry_state_t t;
    telemetry_init(&t);
    telemetry_assemble_frame(&t, &telem_data, framebuffer);
    STRCMP_EQUAL("8099,1,1,300,97772,10.0,15,1.18,46.532162,6.591388,314.0,4,9.0,0,0\n", framebuffer);
}

TEST(TelemetryTest, parseTelemAck)
{
    char parse_resp_buffer[TELEMETRY_FRAME_BUFFER_SIZE];
    telemetry_state_t t;
    telemetry_init(&t);
    CHECK_EQUAL(0, t.last_telemetry_ack);

    const char frame[] = "ACK-SENSOR, 3\n";
    telemetry_parse_frame(&t, frame, parse_resp_buffer);
    CHECK_EQUAL(3, t.last_telemetry_ack);
}

TEST(TelemetryTest, parseInvalidAckIgnored)
{
    telemetry_state_t t;
    telemetry_init(&t);
    char parse_resp_buffer[TELEMETRY_FRAME_BUFFER_SIZE];
    t.last_telemetry_ack = 5;

    const char frame1[] = "ACK, 3\n";
    telemetry_parse_frame(&t, frame1, parse_resp_buffer);
    CHECK_EQUAL(5, t.last_telemetry_ack);
    const char frame2[] = "ACK-SENSOR, ??\n";
    telemetry_parse_frame(&t, frame2, parse_resp_buffer);
    CHECK_EQUAL(5, t.last_telemetry_ack);
}

TEST(TelemetryTest, shouldResendTelemetry)
{
    char framebuffer[TELEMETRY_FRAME_BUFFER_SIZE];
    char parse_resp_buffer[TELEMETRY_FRAME_BUFFER_SIZE];
    telemetry_state_t t;
    telemetry_init(&t);
    // no frame sent, cannot resend
    CHECK_FALSE(should_resend_last_telemetry_frame(&t))

    telemetry_assemble_frame(&t, &telem_data, framebuffer);

    // frame 1 sent, no ack -> resend
    CHECK_TRUE(should_resend_last_telemetry_frame(&t))

    const char frame1[] = "ACK-SENSOR, 1\n";
    telemetry_parse_frame(&t, frame1, parse_resp_buffer);  // got ack
    CHECK_FALSE(should_resend_last_telemetry_frame(&t)) // don't resend
}


TEST(TelemetryTest, rxBuffer)
{
    telemetry_rx_buffer_t b;
    telemetry_rx_buffer_init(&b);
    POINTERS_EQUAL(NULL, telemetry_rx_buffer_input_char(&b, 'a'));
    POINTERS_EQUAL(NULL, telemetry_rx_buffer_input_char(&b, 'b'));
    POINTERS_EQUAL(NULL, telemetry_rx_buffer_input_char(&b, 'c'));
    char *buf = telemetry_rx_buffer_input_char(&b, '\n');
    STRCMP_EQUAL("abc\n", buf);
    POINTERS_EQUAL(NULL, telemetry_rx_buffer_input_char(&b, '1'));
    POINTERS_EQUAL(NULL, telemetry_rx_buffer_input_char(&b, '2'));
    buf = telemetry_rx_buffer_input_char(&b, '\n');
    STRCMP_EQUAL("12\n", buf);
}
