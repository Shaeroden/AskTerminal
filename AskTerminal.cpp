#include <Arduino.h>
#include <limits.h>
#include <climits>

#include "AskTerminal.h"

// a set of tools for stopping a program and prompting a user for a response through a terminal.
// a sketch can only be resumed with a valid input from the user or a defineable exit keyword that forces the askTerminal function to return a specific value.  
// responses can be constrained in a variety of ways within the function call.

// this code was drafted by ChatGPT and edited by the author.

// this is my first library.  thank you for your patience with any errors.

void clearSerialBuffer(Stream &terminal) {
    while (terminal.available()) {
        terminal.read(); // Discard characters
    }
}

bool askTerminalForBool(Stream &terminal, const String &prompt, bool exitValue, const String &exitKeyword) {
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        userInput = terminal.readStringUntil('\n');
        userInput.trim();
        userInput.toLowerCase();

        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }

        // Check for true values
        if (userInput == "1" || userInput == "y" || userInput == "t") {
            return true;
        }

        // Check for false values
        if (userInput == "0" || userInput == "n" || userInput == "f") {
            return false;
        }

        // If input is invalid, print error message and retry
        terminal.println("Invalid input. 1/y/t = yes/true, 0/n/f = no/false");
        terminal.println();
    }
}

// ---- NUMERICALS ---- //
byte askTerminalForByte(Stream &terminal, const String &prompt, byte minValue, byte maxValue, byte exitValue, const String &exitKeyword) {
    byte input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        // Read user input
        userInput = terminal.readStringUntil('\n');
        userInput.trim();  // Remove any leading/trailing spaces
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        int temp = userInput.toInt();  // Convert to int first
		if (temp < 0 || temp > 255) {  
			terminal.println("Value out of range for byte (0-255).");
			continue;
		}
		byte userValue = (byte)temp;  // Safe conversion after range check
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = (byte)userValue;
            return input;  // Return the valid byte input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

int askTerminalForInt(Stream &terminal, const String &prompt, int minValue, int maxValue, int exitValue, const String &exitKeyword) {
    int input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        // Read user input
        userInput = terminal.readStringUntil('\n');
        userInput.trim();  // Remove any leading/trailing spaces
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to an integer
        int userValue = userInput.toInt();
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid integer input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

unsigned int askTerminalForUInt(Stream &terminal, const String &prompt, unsigned int minValue, unsigned int maxValue, unsigned int exitValue, const String &exitKeyword) {
    unsigned int input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        // Read user input
        userInput = terminal.readStringUntil('\n');
        userInput.trim();  // Remove any leading/trailing spaces
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to an unsigned integer
        unsigned int userValue = userInput.toInt();
        
        if (userValue >= 0 && userValue >= minValue && userValue <= maxValue) {
            input = (unsigned int)userValue;
            return input;  // Return the valid unsigned integer input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a positive number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

long askTerminalForLong(Stream &terminal, const String &prompt, long minValue, long maxValue, long exitValue, const String &exitKeyword) {
    long input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to a long integer
        long userValue = userInput.toInt();
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid long integer input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

unsigned long askTerminalForULong(Stream &terminal, const String &prompt, unsigned long minValue, unsigned long maxValue, unsigned long exitValue, const String &exitKeyword) {
    unsigned long input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to an unsigned long
        unsigned long userValue = strtoul(userInput.c_str(), NULL, 10);
        
        if (userValue >= 0 && userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid unsigned long input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a positive number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

float askTerminalForFloat(Stream &terminal, const String &prompt, float minValue, float maxValue, float exitValue, const String &exitKeyword) {
    float input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to a float
        float userValue = userInput.toFloat();
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid float input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

double askTerminalForDouble(Stream &terminal, const String &prompt, double minValue, double maxValue, double exitValue, const String &exitKeyword) {
    double input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to a double
        double userValue = strtod(userInput.c_str(), NULL);  // Correct
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid double input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

long long askTerminalForLongLong(Stream &terminal, const String &prompt, long long minValue, long long maxValue, long long exitValue, const String &exitKeyword) {
    long long input;
    String userInput;
    byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Try to convert the input to a long long
        long long userValue = strtoll(userInput.c_str(), NULL, 10);
        
        if (userValue >= minValue && userValue <= maxValue) {
            input = userValue;
            return input;  // Return the valid long long input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

short askTerminalForShort(Stream &terminal, const String &prompt, short minValue, short maxValue, short exitValue, const String &exitKeyword) {
    String userInput;
    byte reprompt = 0;

    while (true) {
        if (reprompt == 0) {
            terminal.print(prompt);
            terminal.println("");
        }
        // Reprint the main prompt every 5 attempts.
        reprompt = (reprompt + 1) % 5;

        // Reset serial buffer and any holdover input from the last loop
        clearSerialBuffer(terminal);
        userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }

        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }

        // Convert input to integer
        int temp = userInput.toInt();

        // Validate range for short (-32,768 to 32,767)
        if (temp < -32768 || temp > 32767) {
            terminal.println("Value out of range for short (-32,768 to 32,767).");
            continue;
        }

        // Validate user-defined min/max range
        if (temp < minValue || temp > maxValue) {
            terminal.print("Invalid input. Please enter a number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
            continue;
        }

        return (short)temp;  // Safe conversion and return
    }
}


unsigned short askTerminalForUShort(Stream &terminal, const String &prompt, unsigned short minValue, unsigned short maxValue, unsigned short exitValue, const String &exitKeyword) {
    unsigned short input;
    String userInput;
	byte reprompt = 0;
    
    while (true) {
        if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
        
        //reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		userInput = "";

        // Wait for user input and proceed when there is nonblank input
        while (userInput == "") {
            userInput = terminal.readStringUntil('\n');
            userInput.trim();
        }
        
        // Check if the input matches the exit keyword
        if (userInput.equals(exitKeyword)) {
            return exitValue;
        }
        
        // Convert user input to an integer
        long temp = userInput.toInt();

        // Validate if it's within the range of an unsigned short
        if (temp < 0 || temp > 65535) {
            terminal.println("Value out of range for unsigned short (0 to 65535).");
            continue;
        }
        input = (unsigned short)temp;
        
        if (input >= minValue && input <= maxValue) {
            return input;  // Return the valid unsigned short input
        } else {
            // If invalid, print the valid range and prompt again
            terminal.print("Invalid input. Please enter a positive number between ");
            terminal.print(minValue);
            terminal.print(" and ");
            terminal.print(maxValue);
            terminal.print(", or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

// ---- ALPHABETICS ---- //
char askTerminalForChar(Stream &terminal, const String &prompt, const String &validChars, char exitValue, const String &exitKeyword) {
    String input;
	byte reprompt = 0;
    
    while (true) {
		if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
		
        // Read user input (single character)
        while (input == "") {
            input = terminal.readStringUntil('\n');
            input.trim();
        }
        
        // Check if the input matches the exit keyword
        if (input.equals(exitKeyword)) {
            return exitValue;
        }
        
        // If validChars is empty, any character is allowed
        if (validChars.length() == 0 || validChars.indexOf(input.charAt(0)) >= 0) {
            return input.charAt(0);  // Return the valid character
        } else {
            // If invalid, print the valid characters and prompt again
            terminal.print("Invalid input. Please enter a valid character");
            if (validChars.length() > 0) {
                terminal.print(" from: ");
                terminal.println(validChars);
            } else {
                terminal.println(".");
            }
            terminal.print("Or type ");
            terminal.print(exitKeyword);
            terminal.println(" to exit.");
        }
    }
}

String askTerminalForString(Stream &terminal, const String &prompt, size_t minLength, size_t maxLength, const String &requiredChars, const String &restrictedChars, const String &exitKeyword) {
    String input;
	byte reprompt = 0;
    
    while (true) {
		if (reprompt == 0){
			terminal.print(prompt);
			terminal.println("");
		}
		//re-print the main prompt every 5 attempts.
		reprompt = (reprompt + 1) % 5;
		
		//reset serial buffer and any holdover input from last loop
		clearSerialBuffer(terminal);
		input = "";

        // Wait for user input and proceed when there is nonblank input
        while (input == "") {
            input = terminal.readStringUntil('\n');
            input.trim();
        }

        // Check if the input matches the exit keyword
        if (input.equals(exitKeyword)) {
            return "";
        }

        // Check the length of the input
        if (input.length() < minLength || input.length() > maxLength) {
            terminal.print("Invalid input. Please enter a string between ");
            terminal.print(minLength);
            terminal.print(" and ");
            terminal.print(maxLength);
            terminal.println(" characters.");
            continue;
        }

        // Check for required characters
        if (requiredChars.length() > 0) {
            bool hasRequiredChar = false;
            for (size_t i = 0; i < requiredChars.length(); i++) {
                if (input.indexOf(requiredChars.charAt(i)) == -1) {
                    terminal.print("Input must include at least one of the following characters: ");
                    terminal.println(requiredChars);
                    hasRequiredChar = true;
                    break;
                }
            }
            if (hasRequiredChar) {
                continue;
            }
        }

        // Check for restricted characters
        if (restrictedChars.length() > 0) {
            bool hasRestrictedChar = false;
            for (size_t i = 0; i < restrictedChars.length(); i++) {
                if (input.indexOf(restrictedChars.charAt(i)) != -1) {
                    terminal.print("Input cannot contain any of the following characters: ");
                    terminal.println(restrictedChars);
                    hasRestrictedChar = true;
                    break;
                }
            }
            if (hasRestrictedChar) {
                continue;
            }
        }
		
        // If valid, return the input
        return input;
    }
}

