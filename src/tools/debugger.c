#ifndef DEBUGGER_C
#define DEBUGGER_C
#include "string.h"
#include "video.h"
#include "../architecture/object/object.h"
#include "../vector/vector2.h"
#include "../architecture/game_object/game_object.h"
#include "math.h"
#include "../architecture/component/component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

void PrintIntAt (int x, int y, int value)
{
    //cannot convert negative values, must find absolute value, and add negative after
    int* stringValue = (int*) malloc (sizeof (int) * 25);
    itoa (abs (value), stringValue, 10);
    
    int* stringToPrint = (int*) malloc (sizeof (int) * (strlen (stringValue) + 2));

    if (value < 0)
    {
        strcpy (stringToPrint, "-");
    }
    strcpy (stringToPrint, stringValue);
    print_at (x, y, stringToPrint);
    free (stringToPrint);
    free (stringValue);
}

void DrawLine(Vector2* starting, Vector2* ending, int* character)
{
    //find the change in x and y
    int deltaX = ending->x - starting->x;
    int deltaY = ending->y - starting->y;

    //distance between the visual dots
    int distanceBetweenDots = 6;
    //distance betweent he two passed in vectors
    float distance = GetDistanceBetweenVector2s(starting, ending);
    //number of dots that will fit into distance
    int numberOfDots = floor(distance / distanceBetweenDots);
    //if they are actually apart from eachother
    if(distance != 0)
    {
        //how does does the height relate to the hypotenuse
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
            float newY = starting->y + (cosineRatio * (i * distanceBetweenDots)); 
            //find the y of that dot
            float newX = starting->x + (deltaXNegative * sqrt(pow(distanceBetweenDots * i, 2) - pow(starting->y - newY, 2))); 
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
    //print_at(x + tracking * 1, y + leading * 2, "X: ");
    //PrintIntAt(x + tracking * 5, y + leading * 2, object->x);

    //print_at(x + tracking * 1, y + leading * 3, "Y: ");
    //PrintIntAt(x + tracking * 5, y + leading * 3, object->y);



    //x and y dir
    //print_at(x, y + leading * 4, "Dir: ");

    //print_at(x + tracking * 1, y + leading * 5, "xdir: ");
    //PrintIntAt(x + tracking * 5, y + leading * 5, object->xdir);

    //print_at(x + tracking * 1, y + leading * 6, "ydir: ");
    //PrintIntAt(x + tracking * 5, y + leading * 6, object->ydir);


    //sprite region and texture
    //print_at(x, y + leading * 7, "Sprite: ");

    //print_at(x + tracking * 1, y + leading * 8, "rID: ");
    //PrintIntAt(x + tracking * 5, y + leading * 8, object->regionID);
    
    //print_at(x + tracking * 1, y + leading * 9, "tID: ");
    //PrintIntAt(x + tracking * 5, y + leading * 9, object->textureID);



    //misc
    print_at(x, y + leading * 10, "Misc: ");

    print_at(x + tracking * 1, y + leading * 11, "active: ");
    PrintIntAt(x + tracking * 5, y + leading * 11, object->isActive);
    print_at(x + tracking * 1, y + leading * 12, "id: ");
    PrintIntAt(x + tracking * 5, y + leading * 12, object->objectID);

    print_at(x + tracking * 1, y + leading * 13, "name: ");
    print_at(x + tracking * 5, y + leading * 13, object->name);

}
/*
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
    */

void PrintGameObjectDataAt(int x, int y, GameObject* gameObject)
{
    int leading = 20;
    int tracking = 20;

    print_at(x, y + leading, "GameObject: ");

    print_at(x + tracking * 1, y + leading * 2, "gID: ");
    PrintIntAt(x + tracking * 5, y + leading * 2, gameObject->gameObjectID);
    
    print_at(x + tracking, y + leading * 3, "components: ");
    DoublyNode* currentNode = gameObject->components->head;
    Component* currentComponent = NULL;
    int index = 0;
    while(currentNode != NULL)
    {
        currentComponent = (Component*)currentNode->data;
        if(currentComponent != NULL)
        {
            print_at(x + tracking * 2, y + leading * 4, "type: ");
            if(index > 0)
            {
                print_at(x + (tracking * (5 + (2 * (index - 1)))) + 7, y + leading * 4, ",");
                print_at(x + (tracking * (5 + (2 * (index - 1)))) + 7, y + leading * 5, ",");
            }
            PrintIntAt(x + tracking * (5 + (2 * index)), y + leading * 4, currentComponent->type);

            print_at(x + tracking * 2, y + leading * 5, "cID: ");
            PrintIntAt(x + tracking * (5 + (2 * index)), y + leading * 5, currentComponent->componentID);
        }
        currentNode = currentNode->next;
        index++;
    }
    print_at(x + tracking * 1, y + leading * 6, "children:");
    print_at(x + tracking * 2, y + leading * 7, "gID:");
    DoublyNode* currentChildNode = gameObject->children->head;
    GameObject* currentGameObject = NULL;
    int gameObjectIndex = 0;
    while(currentChildNode != NULL)
    {
        currentGameObject = (GameObject*)currentChildNode->data;
        currentChildNode = currentChildNode->next;
        if(currentGameObject != NULL)
        {
            PrintIntAt(x + tracking * (5 + (2 * gameObjectIndex)), y + leading * 7, currentGameObject->gameObjectID);
        }
        gameObjectIndex++;
    }
    print_at(x + tracking, y + leading * 8, "ParentCID");
    PrintIntAt(x + tracking * 6, y + leading * 8, gameObject->parent->gameObjectID);
    print_at(x + tracking, y + leading * 9, "Object: ");
    print_at(x + tracking * 2, y + leading * 10, "active: ");
    PrintIntAt(x + tracking * 6, y + leading * 10, gameObject->base.isActive);
    print_at(x + tracking * 2, y + leading * 11, "name: ");
    print_at(x + tracking * 6, y + leading * 11, gameObject->base.name);
    print_at(x + tracking * 2, y + leading * 12, "oID: ");
    PrintIntAt(x + tracking * 6, y + leading * 12, gameObject->base.objectID);

}

#endif //DEBUGGER_C