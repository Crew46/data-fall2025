#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

List *titleList                 = NULL;

void title_screen (bool *begin)
{
    Object *otmp                = NULL;
    Node   *ntmp                = NULL; 

    if (*begin                 == false)
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        //  We only run this section once
        //
        *begin                  = true;

        ////////////////////////////////////////////////////////////////////////////
        //
        //  Create list to store title screen elements
        //
        titleList               = createList ();

        ////////////////////////////////////////////////////////////////////////////
        //
        //  Initialize LOGO node, appending to list
        //
        otmp                    = createObject (TITLE_TEXTURE, TITLE_LOGO,
                                                640,           180,
                                                IS_ACTIVE_FLAG);
        ntmp                    = createNode (otmp);
        ntmp -> data.vx         = -10;
        ntmp -> data.vy         = 0;
        ntmp -> data.dx         = 60;     // destination X
        ntmp -> data.dy         = 180;    // destination Y
        titleList               = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize SUBTITLE node, appending to list
        //
        otmp                    = createObject (TITLE_TEXTURE, TITLE_SUBTITLE,
                                                100,           -360,
                                                IS_ACTIVE_FLAG);
        ntmp                    = createNode (otmp);
        ntmp -> data.vx         = 0;
        ntmp -> data.vy         = 5;
        ntmp -> data.dx         = 100;    // destination X
        ntmp -> data.dy         = 180;    // destination Y
        titleList               = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize MESSAGE node, appending to list
        //
        otmp                    = createObject (TITLE_TEXTURE, TITLE_MESSAGE,
                                                -640,          240,
                                                IS_ACTIVE_FLAG);
        ntmp                    = createNode (otmp);
        ntmp -> data.vx         = 10;
        ntmp -> data.vy         = 0;
        ntmp -> data.dx         = 100;    // destination X
        ntmp -> data.dy         = 240;    // destination Y
        titleList               = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize START node, appending to list
        //
        otmp                    = createObject (TITLE_TEXTURE, TITLE_START,
                                                300,           360,
                                                IS_ACTIVE_FLAG);
        ntmp                    = createNode (otmp);
        ntmp -> data.vx         = 0;
        ntmp -> data.vy         = -5;
        ntmp -> data.dx         = 300;    // destination X
        ntmp -> data.dy         = 240;    // destination Y
        titleList               = append (titleList, titleList -> tail, ntmp);
    }
    else
    {
        ////////////////////////////////////////////////////////////////////////////
        //
        // Iterate through each node in the list for adjustment and display
        //
        ntmp                    = titleList -> head;
        while (ntmp            != NULL)
        {
            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node X position, comparing to desired destination X
            //
            if (ntmp -> data.x != ntmp -> data.dx)
            {
                ntmp -> data.x  = ntmp -> data.x + ntmp -> data.vx;
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Adjust node Y position, comparing to desired destination Y
            //
            if (ntmp -> data.y != ntmp -> data.dy)
            {
                ntmp -> data.y  = ntmp -> data.y + ntmp -> data.vy;
            }

            ////////////////////////////////////////////////////////////////////////
            //
            // Display node to screen
            //
            select_texture (ntmp -> data.textureID);
            select_region (ntmp  -> data.regionID);
            draw_region_at (ntmp -> data.x, ntmp -> data.y);

            ntmp                = ntmp -> next;
        }
    }
}

#endif // _TITLE_SCREEN_H
