#include <AskTerminal.h>

const int ledPin = 9; // PWM pin for LED brightness

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
	serial.print("Waveform controller");
}

void loop() {
    // Prompt user for waveform type
    char waveform = askTerminalForChar(Serial, 
        "Select waveform type: (s)ine, (t)riangle, s(q)uare, sa(w)tooth:", 
        "stqw");

    // Prompt user for period (1-10 seconds)
    byte period = askTerminalForByte(Serial, "Enter period in seconds (1-10):", 1, 10);
    unsigned long interval = (period * 1000) / 256; // Time per step in milliseconds

    Serial.print("Waveform: ");
    Serial.print(waveform);
    Serial.print(", Period: ");
    Serial.print(period);
    Serial.println(" sec");
    Serial.println("Type anything in Serial Monitor to stop waveform cycle.");

    // Generate waveform until user sends any input
    while (!Serial.available()) {
        unsigned long elapsed = millis() % (period * 1000);
        byte brightness = 0;

        switch (waveform) {
            case 's': // Sine wave
                brightness = (sin(2 * PI * (elapsed / (float)(period * 1000))) + 1) * 127.5;
                break;

            case 't': // Triangle wave
                if ((elapsed % (period * 500)) < (period * 250)) {
                    brightness = map(elapsed % (period * 500), 0, (period * 250), 0, 255);
                } else {
                    brightness = map(elapsed % (period * 500), (period * 250), (period * 500), 255, 0);
                }
                break;

            case 'q': // Square wave
                brightness = (elapsed % (period * 1000) < (period * 500)) ? 255 : 0;
                break;

            case 'w': // Sawtooth wave
                brightness = map(elapsed % (period * 1000), 0, (period * 1000), 0, 255);
                break;
        }

        analogWrite(ledPin, brightness);
        delay(interval);
    }

    // Clear input buffer
    while (Serial.available()) {
        Serial.read();
    }

    Serial.println("Waveform stopped. Restarting parameter selection...\n");
}
