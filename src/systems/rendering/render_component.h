#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H
#include "../../architecture/component/component.h"

struct RenderComponent
{
    Component base; //base component
    int textureID; //texture id
    int regionID; //region id
    int renderPriority;
};

#endif // RENDER_COMPONENT_H