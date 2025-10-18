#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

List       *titleList                 = NULL;

////////////////////////////////////////////////////////////////////////////////////
//
// title_screen() handles the display of title screen elements
//
void title_screen (bool *alreadyrun)
{
    ////////////////////////////////////////////////////////////////////////////////
    //
    // Declare variables
    //
    int     index                     = 0;
    int     pick                      = 0;
    int     position                  = 0;
    int     x                         = 0;
    int     y                         = 0;
    Node   *ntmp                      = NULL; 
    Object *otmp                      = NULL;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize title screen elements: this only runs once per state
    //
    if (*alreadyrun                  == false)
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Toggle begin to ensure this does not run again
        //
        *alreadyrun                   = true;

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
                                                      110,           360,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = 0;
        otmp -> vy                    = -1;
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
                                                      -500,          240,
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
        // Initialize celestial starfield nodes, inserting into list
        //
        for (index = 0; index < 128; index++)
        {
            pick                      = rand () % 6   + CELESTIAL_LARGE;
            x                         = rand () % 630 + 0;
            y                         = rand () % 350 + 0;

            otmp                      = createObject (CELESTIAL_TEXTURES, pick,
                                                      x,                  y,
                                                      IS_ACTIVE_FLAG | ZOOM_FLAG);
            ntmp                      = createNode (otmp);
            otmp                      = ntmp -> data;
            otmp -> id                = half_seconds;
            otmp -> frame             = pick - (CELESTIAL_LARGE - 1);
            otmp -> vx                = 0;
            otmp -> vy                = 0;
            otmp -> dx                = -1000;  // destination X
            otmp -> dy                = -1000;  // destination Y
            titleList                 = insert (titleList, titleList -> head, ntmp);
        }

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize START node, inserting into list
        //
        otmp                          = createObject (TITLE_TEXTURE, TITLE_START,
                                                      640,           240,
                                                      IS_ACTIVE_FLAG);
        ntmp                          = createNode (otmp);
        otmp                          = ntmp -> data;
        otmp -> id                    = half_seconds;
        otmp -> status                = IS_ACTIVE_FLAG;
        otmp -> vx                    = -3;
        otmp -> vy                    = 0;
        otmp -> dx                    = 260;    // destination X
        otmp -> dy                    = 240;    // destination Y
        titleList                     = insert (titleList, titleList -> head, ntmp);
    }
    else
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Determine if enough time has passed to toggle the START
        //
        position                      = get_channel_position (0);
        if (position                 >  200000)
        {
            ntmp                          = titleList -> head;
            otmp                          = ntmp -> data;
            if (half_seconds             >  otmp -> id)
            {
                otmp -> id                = half_seconds + 1;
                if (IS_ACTIVE_FLAG       == (otmp -> status & IS_ACTIVE_FLAG))
                {
                    otmp -> status        = INACTIVE_FLAG;
                    otmp -> id            = otmp -> id   - 1;
                }
                else
                {
                    otmp -> status        = IS_ACTIVE_FLAG;
                }
            }
        }
    }
}

#endif // _TITLE_SCREEN_H
