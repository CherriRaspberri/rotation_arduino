#include <Arduino.h>
#include <Wire.h>
#include <M5_Encoder.h>
#include <microOscSlip.h>

M5_Encoder encoder;
MicroOscSlip<128> osc(&Serial);

void setup()
{
    // Initialize I2C communication, encoder, and serial communication
    Wire.begin();
    encoder.begin();
    Serial.begin(115200);
}

void loop()
{
    encoder.update(); // Update encoder state

    int encoderChange = encoder.getEncoderChange(); // Get the current rotation value

    // Check if there is a change in rotation and send it via OSC
    if ( encoderChange != 0 ) // Check if there is a change in rotation
    {
        osc.sendInt("/enc/rot", encoderChange); // Send the rotation value via OSC
    }

    // Check for button press and release events
    if (encoder.wasPressed()) // Check if the button was pressed
    {
        osc.sendInt("/enc/press", 1); // Send a button press event via OSC
    }
    if (encoder.wasReleased()) // Check if the button was released
    {
        osc.sendInt("/enc/press", 0); // Send a button release event via OSC
    }
}