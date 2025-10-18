#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

////////////////////////////////////////////////////////////////////////////////////
//
// Object API
// ======================
// void    CreateCelestials (void)
// List   *GetObjectList    (void);
// void    UpdateAllObjects (List *);
//
////////////////////////////////////////////////////////////////////////////////////

// list of objects in scene
List      *objectList;

void CreateCelestials (void)
{
    int     index                 = 0;
    int     pick                  = 0;
    int     x                     = 0;
    int     y                     = 0;
    List   *ltmp                  = NULL;
    Node   *ntmp                  = NULL;
    Object *otmp                  = NULL;

    if (objectList               == NULL)
    {
        ltmp                      = createList ();
        for (index = 0; index < 96; index++)
        {
            pick                  = rand () % 3   + CELESTIAL_LARGE + 3;
            x                     = rand () % 630 + 0;
            y                     = rand () % 350 - 360;

            otmp                  = createObject (CELESTIAL_TEXTURES, pick,
                                                  x,                  y,
                                                  IS_ACTIVE_FLAG | ZOOM_FLAG);
            ntmp                  = createNode (otmp);
            otmp                  = ntmp -> data;
            otmp -> id            = half_seconds;
            otmp -> frame         = pick - (CELESTIAL_LARGE - 1);
            otmp -> vx            = 0;
            otmp -> vy            = rand () % max_obj_vy + min_obj_vy;
            otmp -> dx            = -1000;  // destination X
            otmp -> dy            = -1000;  // destination Y
            ltmp                  = insert (ltmp, ltmp -> head, ntmp);
        }
        objectList                = ltmp;
    }
}

// return linked list of objects
List *GetObjectList ()
{
    return (objectList);
}

void  UpdateAllObjects (List *myList)
{
    int     pick                      = 0;
    Node   *currentNode               = NULL;
    Object *otmp                      = NULL;  

    if (myList                       != NULL)
    {
        currentNode                   = myList      -> head;
        while (currentNode           != NULL)
        {
            otmp                      = currentNode -> data;

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust celestial objects
            //
            if ((otmp -> frame       >  0) &&
                (otmp -> vy          == 0))
            {
                if (half_seconds     >  otmp -> id + (otmp -> frame - 1))
                {
                    pick              = (otmp -> frame + 1) % 6 + 1;
                    otmp -> id        = half_seconds;
                    otmp -> frame     = pick;
                    otmp -> regionID  = pick + (CELESTIAL_LARGE - 1);
                }
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node X position, comparing to desired destination X
            //
            if (otmp -> vx           <  0)
            {
                if (otmp -> x        >= otmp -> dx)
                {
                    otmp -> x         = otmp -> x + otmp -> vx;
                }
            }
            else if (otmp -> vx      >  0)
            {
                if (otmp -> x        <= otmp -> dx)
                {
                    otmp -> x         = otmp -> x + otmp -> vx;
                }
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust object's Y position, comparing to desired destination Y
            //
            if (otmp -> y            != otmp -> dy)
            {
                otmp -> y             = otmp -> y + (otmp -> vy * vy_obj_factor);
                if (otmp -> y        >  360)
                {
                    otmp -> x         = rand () % 630;
                    otmp -> vx        = 0;
                    otmp -> y         = -1 * (rand () % 40 + 20);
                    otmp -> vy        = rand () % max_obj_vy + min_obj_vy;
                    otmp -> regionID  = rand () % 4 + CELESTIAL_LARGE + 2;
                }
            }
            currentNode               = currentNode -> next;
        }
    }
}

#endif // _OBJECT_MANAGER_H
