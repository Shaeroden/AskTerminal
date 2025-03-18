#ifndef ASK_TERMINAL_H
#define ASK_TERMINAL_H

#include <Arduino.h>
#include <limits.h>
#include <climits>
#include <float.h>

byte askTerminalForByte(Stream &terminal, const String &prompt, byte minValue = 0, byte maxValue = 255, byte exitValue = 0, const String &exitKeyword = "exit");
int askTerminalForInt(Stream &terminal, const String &prompt, int minValue = INT_MIN, int maxValue = INT_MAX, int exitValue = 0, const String &exitKeyword = "exit");
unsigned int askTerminalForUInt(Stream &terminal, const String &prompt, unsigned int minValue = 0, unsigned int maxValue = UINT_MAX, unsigned int exitValue = 0, const String &exitKeyword = "exit");
long askTerminalForLong(Stream &terminal, const String &prompt, long minValue = LONG_MIN, long maxValue = LONG_MAX, long exitValue = 0, const String &exitKeyword = "exit");
unsigned long askTerminalForULong(Stream &terminal, const String &prompt, unsigned long minValue = 0, unsigned long maxValue = ULONG_MAX, unsigned long exitValue = 0, const String &exitKeyword = "exit");
float askTerminalForFloat(Stream &terminal, const String &prompt, float minValue = -FLT_MAX, float maxValue = FLT_MAX, float exitValue = 0.0, const String &exitKeyword = "exit");
double askTerminalForDouble(Stream &terminal, const String &prompt, double minValue = -DBL_MAX, double maxValue = DBL_MAX, double exitValue = 0.0, const String &exitKeyword = "exit");
long long askTerminalForLongLong(Stream &terminal, const String &prompt, long long minValue = LLONG_MIN, long long maxValue = LLONG_MAX, long long exitValue = 0, const String &exitKeyword = "exit");
short askTerminalForShort(Stream &terminal, const String &prompt, short minValue = SHRT_MIN, short maxValue = SHRT_MAX, short exitValue = 0, const String &exitKeyword = "exit");
unsigned short askTerminalForUShort(Stream &terminal, const String &prompt, unsigned short minValue = 0, unsigned short maxValue = USHRT_MAX, unsigned short exitValue = 0, const String &exitKeyword = "exit");
char askTerminalForChar(Stream &terminal, const String &prompt, const String &validChars = "", const String &exitKeyword = "exit", char exitValue = '\0');
String askTerminalForString(Stream &terminal, const String &prompt, size_t minLength = 1, size_t maxLength = 255, const String &requiredChars = "", const String &restrictedChars = "", const String &exitKeyword = "exit");
bool askTerminalForBool(Stream &terminal, const String &prompt, bool exitValue = false, const String &exitKeyword = "exit");

#endif
