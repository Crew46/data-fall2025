#ifndef NODE_H
#define NODE_H

// This will make a node for either enemy or enemy (more will be added.)
Object *mkNode ()
{
    Object *enemy           = NULL;
    int     pickVariant     = 0;
    int     xpos            = 0;
    int     ypos            = 0;

    pickVariant             = rand () % (100 + 1);
    xpos                    = rand () % (639 + 1);

    enemy                   = (Object *) malloc (sizeof (Object));

    enemy -> next           = NULL;
    enemy -> prev           = NULL;
    enemy -> x              = xpos;
    enemy -> y              = ypos;
    enemy -> isActive       = true;

    if (pickVariant        <= 80)
    {
        enemy -> height     = 10;
        enemy -> width      = 10;
        enemy -> hp         = 1;
        enemy -> texture    = ENEMYA_TEXTURE;
        enemy -> region     = ENEMYA_REGION;
        enemy -> points     = 10;
    }
    else
    {
        enemy -> height     = 20;
        enemy -> width      = 20;
        enemy -> hp         = 3;
        enemy -> texture    = ENEMYB_TEXTURE;
        enemy -> region     = ENEMYB_REGION1;
        enemy -> points     = 20;
    }

    return (enemy);
}

#endif // NODE_H
