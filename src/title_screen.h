#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

List       *titleList                 = NULL;

////////////////////////////////////////////////////////////////////////////////////
//
// title_screen() handles the display of title screen elements
//
void title_screen (bool *begin)
{
    ////////////////////////////////////////////////////////////////////////////////
    //
    // Declare variables
    //
    int     index                     = 0;
    int     pick                      = 0;
    int     x                         = 0;
    int     y                         = 0;
    Node   *ntmp                      = NULL; 
    Object *otmp                      = NULL;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize title screen elements: this only runs once per state
    //
    if (*begin                       == false)
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Toggle begin to ensure this does not run again
        //
        *begin                        = true;

        ////////////////////////////////////////////////////////////////////////////
        //
        // Create list to store title screen elements
        //
        titleList                     = createList ();

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize LOGO node, inserting into list
        //
        otmp                          = createObject (TITLE_TEXTURE, TITLE_LOGO,
                                                      640,           120,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = -10;
        otmp -> vy                    = 0;
        otmp -> dx                    = 110;    // destination X
        otmp -> dy                    = 120;    // destination Y
        titleList                     = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize SUBTITLE node, inserting into list
        //
        otmp                          = createObject (TITLE_TEXTURE, TITLE_SUBTITLE,
                                                      150,           -60,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = 0;
        otmp -> vy                    = 1;
        otmp -> dx                    = 150;    // destination X
        otmp -> dy                    = 160;    // destination Y
        titleList                     = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize MESSAGE node, inserting into list
        //
        otmp                          = createObject (TITLE_TEXTURE, TITLE_MESSAGE,
                                                      -640,          240,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = 5;
        otmp -> vy                    = 0;
        otmp -> dx                    = 145;    // destination X
        otmp -> dy                    = 240;    // destination Y
        titleList                     = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize celestial object nodes, inserting into list
        //
        for (index = 0; index < 64; index++)
        {
            pick                      = rand () % 6   + CELESTIAL_SMALL;
            x                         = rand () % 630 + 0;
            y                         = rand () % 350 + 0;

            otmp                      = createObject (CELESTIAL_TEXTURES, pick,
                                                      x,                  y,
                                                      IS_ACTIVE_FLAG);
            ntmp                      = createNode (otmp);
        otmp                          = ntmp -> data;
            otmp -> id                = seconds;
            otmp -> frame             = pick - (CELESTIAL_SMALL - 1);
            otmp -> status            = IS_ACTIVE_FLAG;
            otmp -> vx                = rand () % 5 - 2;
            otmp -> vy                = rand () % 8 + 1;
            otmp -> dx                = -1000;  // destination X
            otmp -> dy                = -1000;  // destination Y
            titleList                 = insert (titleList, titleList -> head, ntmp);
        }

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize START node, inserting into list
        //
        otmp                          = createObject (TITLE_TEXTURE, TITLE_START,
                                                      255,           360,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> id                    = seconds;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = 0;
        otmp -> vy                    = -1;
        otmp -> dx                    = 255;    // destination X
        otmp -> dy                    = 240;    // destination Y
        titleList                     = insert (titleList, titleList -> head, ntmp);
    }
    else
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Determine if enough time has passed to toggle the START
        //
        ntmp                          = titleList -> head;
        otmp                          = ntmp -> data;
        if (seconds                  >  otmp -> id + 1)
        {
            otmp -> id                = seconds;
            if (otmp -> status       != 0)
            {
                otmp -> status        = INACTIVE_FLAG;
            }
            else
            {
                otmp -> status        = IS_ACTIVE_FLAG;
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        //
        // Iterate through each node in the list for adjustment and display
        //
        ntmp                          = titleList -> head;
        while (ntmp                  != NULL)
        {
            otmp                      = ntmp -> data;
/*
            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust celestial objects
            //
            if (otmp -> frame        >  0)
            {
                if (seconds          >  otmp -> id + (otmp -> frame - 1))
                {
                    pick              = (otmp -> frame + 1) % 6 + 1;
                    otmp -> id        = seconds;
                    otmp -> frame     = pick;
                    otmp -> regionID  = pick + (CELESTIAL_SMALL - 1);
                }
            }
*/

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node X position, comparing to desired destination X
            //
            if (otmp -> x            != otmp -> dx)
            {
                otmp -> x             = otmp -> x + otmp -> vx;
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node Y position, comparing to desired destination Y
            //
            if (otmp -> y            != otmp -> dy)
            {
                otmp -> y             = otmp -> y + otmp -> vy;
                if (otmp -> y        >  360)
                {
                    otmp -> x         = rand () % 630;
                    otmp -> vx        = rand () % 5 - 2;
                    otmp -> y         = -1 * (rand () % 40 + 20);
                    otmp -> vy        = rand () % 8 + 1;
                    otmp -> regionID  = rand () % 6 + CELESTIAL_SMALL;
                }
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Display node to screen
            //
            if (otmp -> status       == IS_ACTIVE_FLAG)
            {
                select_texture (otmp -> textureID);
                select_region  (otmp -> regionID);
                draw_region_at (otmp -> x, otmp -> y);
            }

            ntmp                      = ntmp -> next;
        }
    }
}

#endif // _TITLE_SCREEN_H
