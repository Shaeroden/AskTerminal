#include <AskTerminal.h>
#include <WiFi.h>
#include <time.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;  // Adjust based on your timezone (e.g., -18000 for EST)
const int daylightOffset_sec = 0;  // Adjust if daylight savings applies

void getWiFiCredentials(String &ssid, String &password) {
    ssid = askTerminalForString(Serial, "Enter Wi-Fi SSID (1-32 characters):", 1, 32);
    password = askTerminalForString(Serial, "Enter Wi-Fi Password (8-63 characters):", 8, 63);
}

void connectToWiFi() {
    String ssid, password;

    while (true) {  // Keep prompting until connected
        getWiFiCredentials(ssid, password);

        Serial.print("Connecting to Wi-Fi...");
        WiFi.begin(ssid.c_str(), password.c_str());

        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 10) {  
            delay(1000);
            Serial.print(".");
            attempts++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\nConnected to Wi-Fi!");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
            break;  // Exit loop when connected
        } else {
            Serial.println("\nFailed to connect. Please try again.");
        }
    }
}

void printNetworkTime() {
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.print("Current Time: ");
    Serial.print(asctime(&timeInfo));  // Prints time in human-readable format
}

void setup() {
    Serial.begin(115200);
    connectToWiFi();
}

void loop() {
    printNetworkTime();
    delay(10000);  // Print time every 10 seconds
}
