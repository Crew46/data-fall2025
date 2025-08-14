#include "gamemanager.h"

struct object  
{
	int region;
	int x;
	int y;
	int alive;
};

GameManager* CreateGameManager() 
{
    // Allocate memory for the GameManager structure
    GameManager* gameManager = (GameManager*)malloc(sizeof(GameManager));
    return gameManager;
}

void InitializeGameManager(GameManager* gameManager) 
{
    if(gameManager != NULL) 
    {
        //initialize things managed by game manager

        //temporary location for shooter initialization 
        //int         chance              = 0;
        int         index               = 0;
        int         xpos                = 320;
        int         ypos                = 300;
        int         pewpews             = 0;
        object [12] enemy;
        object [4]  pewpew;

        srand (get_cycle_counter ());

        for (index = 0; index < 12; index++)
        {
            enemy[index].region         = 'v' - (rand () % 2 * 32);
            enemy[index].x              = index * 57;
            enemy[index].y              = 20 - (index * 20);
		    enemy[index].alive          = 1;
        }

        for (index = 0; index < 4; index++)
        {
            pewpew[index].region        = '.';
            pewpew[index].x             = 0;
            pewpew[index].y             = 0;
            pewpew[index].alive         = 0;
        }

	    select_gamepad (0);
	    select_texture (-1);
    }
}

void DeinitializeGameManager(GameManager* gameManager) 
{
    if (gameManager != NULL) 
    {
        free(gameManager);
    }
}

void UpdateGameManager(GameManager* gameManager) 
{
    if(gameManager != NULL) 
    {
        //temporary location for input handling, drawing, and object specific game logic, will be moved to appropriate systems later
        if (gamepad_left()         >  0)
        {
            xpos                    = xpos - 1;
        }

        if (gamepad_right()        >  0)
        {
            xpos                    = xpos + 1;
        }

        if (gamepad_up()           >  0)
        {
            ypos                    = ypos - 1;
        }

        if (gamepad_down()         >  0)
        {
            ypos                    = ypos + 1;
        }

        if (gamepad_button_a()     >  0)
        {
            if (pewpews            <  4)
            {
                pewpew[pewpews].x      = xpos;
                pewpew[pewpews].y      = ypos;
                pewpew[pewpews].alive  = 1;
                pewpews                = pewpews + 1;
            }
        }

        if (xpos                   <  0)
        {
            xpos                    = 0;
        }

        if (xpos                   >  630)
        {
            xpos                    = 630;
        }

        if (ypos                   >  350)
        {
            ypos                    = 350;
        }

        if (ypos                   <  0)
        {
            ypos                    = 0;
        }

        select_region ('^');
        set_drawing_point (xpos, ypos);
        draw_region ();

        for (index = 0; index < 12; index++)
        {
            if (enemy[index].alive == 1)
            {
                select_region (enemy[index].region);
                set_drawing_point (enemy[index].x, enemy[index].y);
                draw_region ();

                enemy[index].x      = rand () % 3 - 1;
                enemy[index].y      = enemy[index].y + 1;

                if (enemy[index].x <  0)
                {
                    enemy[index].x  = 0;
                }

                if (enemy[index].x >  630)
                {
                    enemy[index].x  = 630;
                }

                if (enemy[index].y >  630)
                {
                    enemy[index].y  = rand () % 40 - 30;
                }
            }
        }

        if (pewpews                >  0)
        {
            for (index = 0; index < pewpews; index++)
            {
                select_region (pewpew[index].region);
                set_drawing_point (pewpew[index].x, pewpew[index].y);
                draw_region ();

                pewpew[index].y     = pewpew[index].y - 1;

                if (pewpew[index].y <  0)
                {
                    pewpew[index].alive  = 0;
                    pewpews              = pewpews - 1;
                }
            }
        }
    }
}


