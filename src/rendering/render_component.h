#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
#include "../component/component.h"

struct RenderComponent
{
    Component component; //base component
    int textureID; //texture id
    int regionID; //region id
}

void DrawRenderComponent(RenderComponent* renderComponent)
{
    select_texture(renderComponent->textureID);
    select_region(renderComponent->regionID);
}

#endif // RENDEROBJECT_H