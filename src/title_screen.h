#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

List *titleList  = createList ();

void title_screen (bool *begin)
{
    int     x          = 0;
    int     xdir       = 0;
    int     y          = 0;
    int     ydir       = 0;
    Object *otmp       = NULL;
    Node   *ntmp       = NULL; 

    if (*begin        == false)
    {
        *begin         = true;

        ////////////////////////////////////////////////////////////////////////////
        //
        //  Initialize LOGO node, appending to list
        //
        otmp               = createObject (TITLE_TEXTURE, TITLE_LOGO,
                                           640,           0,
                                           IS_ACTIVE_FLAG);
        ntmp               = createNode (otmp);
        ntmp -> data.dx  = -10;
        ntmp -> data.dy  = 0;
        titleList          = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize SUBTITLE node, appending to list
        //
        otmp               = createObject (TITLE_TEXTURE, TITLE_SUBTITLE,
                                           0,             -360,
                                           IS_ACTIVE_FLAG);
        ntmp               = createNode (otmp);
        ntmp -> data.dx  = 0;
        ntmp -> data.dy  = 5;
        titleList          = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize MESSAGE node, appending to list
        //
        otmp               = createObject (TITLE_TEXTURE, TITLE_MESSAGE,
                                           -640,          0,
                                           IS_ACTIVE_FLAG);
        ntmp               = createNode (otmp);
        ntmp -> data.dx  = 10;
        ntmp -> data.dy  = 0;
        titleList          = append (titleList, titleList -> tail, ntmp);

        ////////////////////////////////////////////////////////////////////////////
        //
        // Initialize START node, appending to list
        //
        otmp               = createObject (TITLE_TEXTURE, TITLE_START,
                                           0,             360,
                                           IS_ACTIVE_FLAG);
        ntmp               = createNode (otmp);
        ntmp -> data.dx  = 0;
        ntmp -> data.dy  = -5;
        titleList          = append (titleList, titleList -> tail, ntmp);
    }
	else
	{
		ntmp               = titleList -> head;
		while (ntmp       != NULL)
		{
			// adjust x and y of current node
			ntmp -> data.x  = ntmp -> data.x + ntmp -> data.dx;
			ntmp -> data.y  = ntmp -> data.y + ntmp -> data.dy;

			// drawing the background
			select_texture (ntmp -> data.textureID);
			select_region (ntmp  -> data.regionID);
			draw_region_at (ntmp -> data.x, ntmp -> data.y);
		}
	}
}

#endif // _TITLE_SCREEN_H
