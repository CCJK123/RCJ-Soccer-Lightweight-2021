#include "rgb.h"

RGB::RGB(uint8_t address, int channel, int threshold) {
    _channel = channel;
    _threshold = threshold;

    select(_channel);

    // the integration and gain times can be configured 
    sensor = Adafruit_TCS34725(tcs34725IntegrationTime_t = TCS34725_INTEGRATIONTIME_2_4MS, tcs34725Gain_t = TCS34725_GAIN_1X);
    sensor.begin();
}

int RGB::calcLux() {
    select(_channel);
    uint16_t c = sensor.read16(TCS34725_CDATAL);
    uint16_t r = sensor.read16(TCS34725_RDATAL);
    uint16_t g = sensor.read16(TCS34725_GDATAL);
    uint16_t b = sensor.read16(TCS34725_BDATAL);
    // use low-level calls to read values
    // instead of using `sensor.getRawData(&r, &g, &b, &c);` so as to prevent waiting for the intgeration time
    // thus remember to wait at least the integration time until you read the next data

    return (int) sensor.calculateLux(r, g, b);
}

double RGB::getPercent() {
    select(_channel);
    return double(RGB::calcLux())/_threshold;
}

int RGB::getThreshold() {
    select(_channel);
    return _threshold;
}

bool RGB::isOnLine() {
    select(_channel);
    return (RGB::calcLux() > _threshold);
}