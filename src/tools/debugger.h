#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "string.h"
#include "video.h"

void PrintIntAt(int x, int y, int value)
{
    int* stringToPrint;
    itoa(value, stringToPrint, 10);
    print_at(x, y, stringToPrint);
}

void PrintFloatAt(int x, int y, float value)
{
    int* stringToPrint;
    ftoa(value, stringToPrint);
    print_at(x, y, stringToPrint);
}

#endif //DEBUGGER_H