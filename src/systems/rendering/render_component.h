#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

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

#endif // RENDER_COMPONENT_H