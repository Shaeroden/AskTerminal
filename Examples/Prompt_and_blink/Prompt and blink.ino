#include <AskTerminal.h>

const int LED_PIN = LED_BUILTIN;  // Use the onboard LED

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    while (!Serial);  // Wait for the serial connection to open
}

void loop() {
    // Ask the user for the number of blinks (0-255)
    byte blinkCount = AskTerminal::askTerminalForByte(Serial, "Enter number of blinks (0-255):", 0, 255);

    // Ask the user for blink duration (100-1000 ms)
    int blinkDuration = AskTerminal::askTerminalForInt(Serial, "Enter blink duration (100-1000 ms):", 100, 1000);

    Serial.println("Starting blink sequence...");

    for (byte i = 0; i < blinkCount; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(blinkDuration / 2);
        digitalWrite(LED_PIN, LOW);
        delay(blinkDuration / 2);
    }

    Serial.println("Blink sequence complete.\n");
}