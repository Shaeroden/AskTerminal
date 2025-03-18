AskTerminal - Arduino Library for User Input Handling

//Overview

AskTerminal is a lightweight Arduino library that simplifies user input handling through serial (or other terminal) communication. It provides functions for prompting users to enter various data types, including integers, floating-point numbers, characters, and strings, with validation and optional constraints.

//Features

Supports multiple data types: byte, int, long, float, double, char, string, and more.
Allows input validation (min/max values, required/restricted characters).
Supports exit keywords for terminating input.
Clears serial buffer before reading new input.
Reprompts users if they enter invalid or out of range data.
Works with all terminal types.  USB, bluetooth, WiFi, etc.

//Installation

Using the Arduino Library Manager
Open the Arduino IDE.
Go to Sketch → Include Library → Manage Libraries...
Search for AskTerminal.
Click Install.

//Manual Installation

Download the AskTerminal.zip file from the GitHub Releases.
Open the Arduino IDE.
Go to Sketch → Include Library → Add .ZIP Library...
Select the downloaded ZIP file.

//Usage

Basic Example

#include <AskTerminal.h>

void setup() {
    Serial.begin(115200);
    
    // Ask for an integer between 1 and 100
    int number = askTerminalForInt(Serial, "Enter a number:", 1, 100, -1, "exit");
    
    // Ask for a character from a predefined set
    char choice = askTerminalForChar(Serial, "Choose a letter (A, B, C):", "ABC", 'X', "quit");
    
    Serial.print("You entered: ");
    Serial.println(number);
    Serial.print("Your choice: ");
    Serial.println(choice);
}

void loop() {
    // Your main program loop
}

//Function Reference

1. Asking for an Integer

int askTerminalForInt(Stream &terminal, const String &prompt, int minValue, int maxValue, int exitValue, const String &exitKeyword);
terminal – The stream to use (Serial or another Stream object).
prompt – The message to display.
minValue / maxValue – The valid input range.
exitValue – The value to return if the exit keyword is entered.
exitKeyword – A string that allows the user to exit.

2. Asking for a String with Constraints

String askTerminalForString(Stream &terminal, const String &prompt, size_t minLength, size_t maxLength, const String &requiredChars, const String &restrictedChars, const String &exitKeyword);
minLength / maxLength – Limits on input length.
requiredChars – String must contain at least one of these characters.
restrictedChars – String must NOT contain any of these characters.
(Include more function descriptions as needed.)

License
This library is licensed under the MIT License. See LICENSE for details.

Contributing
Contributions are welcome! If you find a bug or have a suggestion, open an issue or submit a pull request.
