#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

struct RenderComponent
{
    Component component; //base component
    int textureID; //texture id
    int regionID; //region id
}

#endif // RENDER_COMPONENT_H