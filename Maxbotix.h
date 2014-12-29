#ifndef Maxbotix_h
#define Maxbotix_h

// Configuration
//#define MAXBOTIX_WITH_SOFTWARE_SERIAL 1

#include <Arduino.h>
#ifdef MAXBOTIX_WITH_SOFTWARE_SERIAL
#include "RxSoftwareSerial.h"
#endif

class Maxbotix
{
public:
    // models
    typedef enum {
        LV,
        XL,
        HRLV
    }
    MAXBOTIX_MODEL_t;

    // inputs
    typedef enum {
        PW,
        AN,
#ifdef MAXBOTIX_WITH_SOFTWARE_SERIAL
        TX
#endif
    }
    MAXBOTIX_INPUT_t;

    // filters
    typedef enum {
        NONE,
        MEDIAN,
        HIGHEST_MODE,
        LOWEST_MODE,
        BEST,
        SIMPLE
    }
    MAXBOTIX_FILTER_t;

    // init/delete
    Maxbotix(uint8_t pin, MAXBOTIX_INPUT_t input, MAXBOTIX_MODEL_t model, MAXBOTIX_FILTER_t filter = NONE,
             uint8_t sample_size = 0);
#ifdef MAXBOTIX_WITH_SOFTWARE_SERIAL
    Maxbotix(Stream* serial, MAXBOTIX_MODEL_t model, MAXBOTIX_FILTER_t filter = NONE, uint8_t sample_size = 0);
#endif
    ~Maxbotix();

    // simple api
    float getRange();
    uint8_t getSampleSize()
    {
        return sample_size;
    };

    // advanced api
    void readSample();
    float* getSample()
    {
        return sample;
    };
    float getSampleMedian();
    float getSampleMode(bool highest = true);
    float getSampleBest();

    // getters
    MAXBOTIX_MODEL_t getModel()
    {
        return model;
    }
    MAXBOTIX_INPUT_t getInput()
    {
        return input;
    }
    MAXBOTIX_FILTER_t getFilter()
    {
        return filter;
    }

    // setters
    void setADSampleDelay(uint8_t delay)
    {
        ad_sample_delay = delay;
    }

    // utilities
    static float toCentimeters(float inches)
    {
        return 2.54 * inches;
    };
    static float toInches(float centimeters)
    {
        return centimeters / 2.54;
    };

private:
    // config variables
    uint8_t pin;
    MAXBOTIX_INPUT_t input;
    MAXBOTIX_MODEL_t model;
    MAXBOTIX_FILTER_t filter;
    uint8_t sample_size;
    uint8_t ad_sample_delay;
    Stream* serial;

    // core
    float* sample;
    void init();
    float readSensor();
    unsigned short readSensorSerial(uint8_t length);
    void pushToSample(float value);
    void sortSample();
};

#endif
