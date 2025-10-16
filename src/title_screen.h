#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

List *titleList                         = NULL;

void title_screen (bool *begin)
{
    Object *otmp                        = NULL;
    Node   *ntmp                        = NULL; 

    if (*begin                         == false)
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        //  We only run this section once
        //
        *begin                          = true;

        ////////////////////////////////////////////////////////////////////////////
        //
        //  Create list to store title screen elements
        //
        titleList                       = createList ();

        ////////////////////////////////////////////////////////////////////////////
        //
        //  Initialize LOGO node, inserting into list
        //
        otmp                            = createObject (TITLE_TEXTURE, TITLE_LOGO,
                                                        640,           120,
                                                        IS_ACTIVE_FLAG);
        ntmp                            = createNode (otmp);
        ntmp -> data -> status          = IS_ACTIVE_FLAG;
        ntmp -> data -> vx              = -10;
        ntmp -> data -> vy              = 0;
        ntmp -> data -> dx              = 110;    // destination X
        ntmp -> data -> dy              = 120;    // destination Y
        titleList                       = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize SUBTITLE node, inserting into list
        //
        otmp                            = createObject (TITLE_TEXTURE, TITLE_SUBTITLE,
                                                        150,           -60,
                                                        IS_ACTIVE_FLAG);
        ntmp                            = createNode (otmp);
        ntmp -> data -> status          = IS_ACTIVE_FLAG;
        ntmp -> data -> vx              = 0;
        ntmp -> data -> vy              = 1;
        ntmp -> data -> dx              = 150;    // destination X
        ntmp -> data -> dy              = 160;    // destination Y
        titleList                       = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize MESSAGE node, inserting into list
        //
        otmp                            = createObject (TITLE_TEXTURE, TITLE_MESSAGE,
                                                        -640,          240,
                                                        IS_ACTIVE_FLAG);
        ntmp                            = createNode (otmp);
        ntmp -> data -> status          = IS_ACTIVE_FLAG;
        ntmp -> data -> vx              = 5;
        ntmp -> data -> vy              = 0;
        ntmp -> data -> dx              = 145;    // destination X
        ntmp -> data -> dy              = 240;    // destination Y
        titleList                       = insert (titleList, titleList -> head, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize START node, inserting into list
        //
        otmp                            = createObject (TITLE_TEXTURE, TITLE_START,
                                                        255,           360,
                                                        IS_ACTIVE_FLAG);
        ntmp                            = createNode (otmp);
        ntmp -> data -> id              = seconds;
        ntmp -> data -> status          = IS_ACTIVE_FLAG;
        ntmp -> data -> vx              = 0;
        ntmp -> data -> vy              = -1;
        ntmp -> data -> dx              = 255;    // destination X
        ntmp -> data -> dy              = 240;    // destination Y
        titleList                       = insert (titleList, titleList -> head, ntmp);
    }
    else
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Determine if enough time has passed to toggle the START
        //
        ntmp                            = titleList -> head;
        if (seconds                    >  ntmp -> data -> id)
        {
            ntmp -> data -> id          = seconds;
            if (ntmp -> data -> status != 0)
            {
                ntmp -> data -> status  = 0;
            }
            else
            {
                ntmp -> data -> status  = IS_ACTIVE_FLAG;
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        //
        // Iterate through each node in the list for adjustment and display
        //
        ntmp                            = titleList -> head;
        while (ntmp                    != NULL)
        {
            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node X position, comparing to desired destination X
            //
            if (ntmp -> data -> x      != ntmp -> data -> dx)
            {
                ntmp -> data -> x       = ntmp -> data -> x + ntmp -> data -> vx;
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node Y position, comparing to desired destination Y
            //
            if (ntmp -> data -> y      != ntmp -> data -> dy)
            {
                ntmp -> data -> y       = ntmp -> data -> y + ntmp -> data -> vy;
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Display node to screen
            //
            if (ntmp -> data -> status == IS_ACTIVE_FLAG)
            {
                select_texture (ntmp -> data -> textureID);
                select_region (ntmp  -> data -> regionID);
                draw_region_at (ntmp -> data -> x, ntmp -> data -> y);
            }

            ntmp                        = ntmp -> next;
        }
    }
}

#endif // _TITLE_SCREEN_H
