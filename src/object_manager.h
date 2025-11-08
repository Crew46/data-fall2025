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

// these constitute the moving starfield
void CreateCelestials (void)
{
    int     index                 = 0;
    int     pick                  = 0;
    int [6] stars;
    int     x                     = 0;
    int     y                     = 0;
    List   *ltmp                  = NULL;
    Node   *ntmp                  = NULL;
    Object *otmp                  = NULL;

    if (objectList               == NULL)
    {
        for (index = 0; index < 3; index++)
        {
            stars[index]          = STAR0 + index;
        }

        ltmp                      = createList ();
        for (index = 0; index < 96; index++)
        {
            pick                  = rand () % 3   + STAR0;
            x                     = rand () % 630 + 0;
            y                     = rand () % 350 - 360;

            otmp                  = createObject (CELESTIAL_TEXTURES, stars, 3,
                                                  x,                  y,
                                                  IS_ACTIVE_FLAG | ZOOM_FLAG);
            otmp -> type          = Object_Type_Celestial;
            ntmp                  = createNode (otmp);
            otmp                  = ntmp -> data;
            otmp -> offset        = half_seconds;
            otmp -> frame         = pick;
            otmp -> delay         = pick;
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
    int     pick                           = 0;
    Node   *currentNode                    = NULL;
    Object *otmp                           = NULL;

    if (myList                            != NULL)
    {
        currentNode                        = myList      -> head;
        while (currentNode                != NULL)
        {
            otmp                           = currentNode -> data;

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust celestial objects
            //
            if (otmp -> vy                == 0)
            {
                if (otmp -> type          == Object_Type_Celestial)
                {
                    if (half_seconds      >  otmp -> offset + otmp -> delay)
                    {
                        otmp -> frame      = otmp -> frame + 1;
                        otmp -> frame     %= otmp -> num_regions;
                        otmp -> offset     = half_seconds;
                        otmp -> delay      = otmp -> frame;
                    }
                }
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node X position, comparing to desired destination X
            //
            if (otmp -> vx                <  0)
            {
                if (otmp -> x             >= otmp -> dx)
                {
                    otmp -> x              = otmp -> x + otmp -> vx;
                }
            }
            else if (otmp -> vx           >  0)
            {
                if (otmp -> x             <= otmp -> dx)
                {
                    otmp -> x              = otmp -> x + otmp -> vx;
                }
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust object's Y position, comparing to desired destination Y
            //
            if (otmp -> y                 != otmp -> dy)
            {
                otmp -> y                 += otmp -> vy * vy_obj_factor;
                if (otmp -> y             >  360)
                {
                    otmp -> x              = rand () % 630;
                    otmp -> vx             = 0;
                    otmp -> y              = -1 * (rand () % 40 + 20);
                    otmp -> vy             = rand () % max_obj_vy + min_obj_vy;
                    if (otmp -> type      == Object_Type_Celestial)
                    {
                        otmp -> frame      = rand () % otmp -> num_regions;
                    }
                }
            }
            currentNode                    = currentNode -> next;
        }
    }
}

#endif // _OBJECT_MANAGER_H
