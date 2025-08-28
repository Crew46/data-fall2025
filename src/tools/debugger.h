#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "string.h"
#include "video.h"
#include "../object.h"
#include "math.h"

void PrintIntAt(int x, int y, int value)
{
    //cannot convert negative values, must find absolute value, and add negative after
    int* stringValue = (int*)malloc(sizeof(int) * 40);
    itoa(abs(value), stringValue, 10);
    
    int* stringToPrint = (int*)malloc(sizeof(int) * (strlen(stringValue) + 1));

    if(value < 0)
    {
        strcat(stringToPrint, "-");
    }
    else
    {
        strcat(stringToPrint, "+");
    }
    strcat(stringToPrint, stringValue);
    
    
    print_at(x, y, stringToPrint);
}

void PrintFloatAt(int x, int y, float value)
{
    //cannot convert negative values, must find absolute value, and add negative after
    int* stringValue = (int*)malloc(sizeof(int) * 40);
    ftoa(abs(value), stringValue);
    int* stringToPrint = (int*)malloc(sizeof(int) * (strlen(stringValue) + 1));
    
    if(value < 0)
    {
        strcat(stringToPrint, "-");
    }
    else
    {
        strcat(stringToPrint, "+");
    }
    strcat(stringToPrint, stringValue);
    
    print_at(x, y, stringToPrint);
}

 void PrintObjectDataAt(int x, int y, Object* object, int* label)
 {
    int leading = 20;
    int tracking = 20;

    print_at(x, y, label);

    print_at(x + tracking, y + leading, "Position: ");

    //x and y
    print_at(x + tracking * 2, y + leading * 2, "X: ");
    PrintIntAt(x + tracking * 6, y + leading * 2, object->x);

    print_at(x + tracking * 2, y + leading * 3, "Y: ");
    PrintIntAt(x + tracking * 6, y + leading * 3, object->y);

    //x and y dir
    print_at(x + tracking, y + leading * 4, "Dir: ");

    print_at(x + tracking * 2, y + leading * 5, "xdir: ");
    PrintFloatAt(x + tracking * 6, y + leading * 5, object->xdir);

    print_at(x + tracking * 2, y + leading * 6, "ydir: ");
    PrintFloatAt(x + tracking * 6, y + leading * 6, object->ydir);


    //sprite region and texture
    print_at(x + tracking, y + leading * 7, "Sprite: ");

    print_at(x + tracking * 2, y + leading * 8, "rID: ");
    PrintIntAt(x + tracking * 6, y + leading * 8, object->regionID);
    
    print_at(x + tracking * 2, y + leading * 9, "tID: ");
    PrintIntAt(x + tracking * 6, y + leading * 9, object->textureID);



    //misc
    print_at(x + tracking, y + leading * 10, "Misc: ");

    //active
    print_at(x + tracking * 2, y + leading * 11, "active: ");
    PrintIntAt(x + tracking * 6, y + leading * 11, object->isActive);
    //ID
    print_at(x + tracking * 2, y + leading * 12, "id: ");
    PrintIntAt(x + tracking * 6, y + leading * 12, object->id);
 }

#endif //DEBUGGER_H