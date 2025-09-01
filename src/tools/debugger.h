#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "string.h"
#include "video.h"
#include "../object.h"
#include "../vector/vector2.h"
#include "math.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

void PrintIntAt(int x, int y, int value)
{
    //cannot convert negative values, must find absolute value, and add negative after
    int* stringValue = (int*)malloc(sizeof(int) * 25);
    itoa(abs(value), stringValue, 10);
    
    int* stringToPrint = (int*)malloc(sizeof(int) * (strlen(stringValue) + 2));

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
    free(stringToPrint);
}

void DrawLine(int startingX, int startingY, int endX, int endY, int* character)
{
    //find the change in x and y
    int deltaX = endX - startingX;
    int deltaY = endY - startingY;

    //distance between the visual dots
    int distanceBetweenDots = 6;
    //distance betweent he two passed in vectors
    float distance = GetDistanceBetweenVector2s(startingX, startingY, endX, endY);
    //number of dots that will fit into distance
    int numberOfDots = floor(distance / distanceBetweenDots);
    //if they are actually apart from eachother
    if(distance != 0)
    {
        //how does does the height related to the hypotenuse
        float cosineRatio = deltaY / distance;
        int deltaXNegative = 1;
        if(deltaX < 0)
        {
            deltaXNegative = -1;
        }

        //for every dot starting at 1st, rather than 0st 
        for(int i = 1; i < (numberOfDots); i++)
        {
            //find the x of that dot
            float newY = startingY + (cosineRatio * (i * distanceBetweenDots)); 
            //find the y of that dot
            float newX = startingX + (deltaXNegative * sqrt(pow(distanceBetweenDots * i, 2) - pow(startingY - newY, 2))); 
            print_at(round(newX), round(newY), character);
        }
    }
}

void PrintObjectDataAt(int x, int y, Object* object)
{
    int leading = 20;
    int tracking = 20;

    print_at(x, y + leading, "Position: ");

    //x and y
    print_at(x + tracking * 1, y + leading * 2, "X: ");
    PrintIntAt(x + tracking * 5, y + leading * 2, object->x);

    print_at(x + tracking * 1, y + leading * 3, "Y: ");
    PrintIntAt(x + tracking * 5, y + leading * 3, object->y);



    //x and y dir
    print_at(x, y + leading * 4, "Dir: ");

    print_at(x + tracking * 1, y + leading * 5, "xdir: ");
    PrintIntAt(x + tracking * 5, y + leading * 5, object->xdir);

    print_at(x + tracking * 1, y + leading * 6, "ydir: ");
    PrintIntAt(x + tracking * 5, y + leading * 6, object->ydir);


    //sprite region and texture
    print_at(x, y + leading * 7, "Sprite: ");

    print_at(x + tracking * 1, y + leading * 8, "rID: ");
    PrintIntAt(x + tracking * 5, y + leading * 8, object->regionID);
    
    print_at(x + tracking * 1, y + leading * 9, "tID: ");
    PrintIntAt(x + tracking * 5, y + leading * 9, object->textureID);



    //misc
    print_at(x, y + leading * 10, "Misc: ");

    print_at(x + tracking * 1, y + leading * 11, "active: ");
    PrintIntAt(x + tracking * 5, y + leading * 11, object->isActive);
    print_at(x + tracking * 1, y + leading * 12, "id: ");
    PrintIntAt(x + tracking * 5, y + leading * 12, object->id);

    print_at(x + tracking * 1, y + leading * 13, "name: ");
    print_at(x + tracking * 5, y + leading * 13, object->name);

    print_at(x + tracking * 1, y + leading * 14, "speed: ");
    PrintIntAt(x + tracking * 5, y + leading * 14, object->speed);
}

 void VisualizeLinkedList(DoublyLinkedList* list)
 {
    DoublyNode* previousNode = NULL;
    DoublyNode* currentNode = list->head;
    Object* currentData = NULL;
    while(currentNode != NULL)
    {
        currentData = currentNode->data;
        PrintIntAt(currentData->x, currentData->y, currentData->id);
        //draw line from current node to previous node
        if(currentNode->previous == previousNode)
        {
            if(previousNode == NULL)
            {

            }
            else
            {
                DrawLine(currentNode->data->x, currentNode->data->y - 10, previousNode->data->x, previousNode->data->y - 10, ".");
            }
        }
        //draw line from previous node to current node
        if(previousNode != NULL)
        {
            DrawLine(previousNode->data->x, previousNode->data->y + 10, currentNode->data->x, currentNode->data->y + 10, ",");
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
}

#endif //DEBUGGER_H