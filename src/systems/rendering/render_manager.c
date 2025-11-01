#ifndef RENDER_MANAGER_C
#define RENDER_MANAGER_C
#include "render_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../architecture/object/object_manager.h"
#include "../../systems/transform/transform_manager.h"
#include "video.h"
#include "../../tools/debugger.c"

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT CONSTRUCTION & DECONSTRUCTION/////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture)
{
    CM_InitializeComponent((Component*)renderComponent, RENDER_COMPONENT);  
    OM_ObjectSet_Name((Object*)renderComponent, "Render_Component"); 
    renderComponent->regionID = region;
    renderComponent->textureID = texture;
    renderComponent->renderPriority = 0;
}

RenderComponent* ConstructRenderComponent()
{
    RenderComponent* renderComponent = (RenderComponent*)malloc(sizeof(RenderComponent));
    InitializeRenderComponent(renderComponent, 0, 0);
    return renderComponent;
}

void DeconstructRenderComponent(RenderComponent* renderComponent)
{
    CM_DeconstructComponent(&renderComponent->base);
    free(renderComponent);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateRenderComponent(RenderComponent* renderComponent)
{
    TransformComponent* transformComponent = (TransformComponent*)GOM_GetComponentFromComponent((Component*)renderComponent, TRANSFORM_COMPONENT);

    //if able to get transform component
    if(transformComponent != NULL)
    {
        select_texture(renderComponent->textureID);
        select_region(renderComponent->regionID);
        draw_region_at(transformComponent->position.x, transformComponent->position.y);
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS & SETTERS///////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void SetRenderComponentRegion(RenderComponent* renderComponent, int region)
{
    renderComponent->regionID = region;
}

void SetRenderComponentTexture(RenderComponent* renderComponent, int texture)
{
    renderComponent->textureID = texture;
}

void SetRenderComponentDescriptiveData(RenderComponent* renderComponent, int region, int texture, int renderPriority)
{
    renderComponent->regionID = region;
    renderComponent->textureID = texture;
    renderComponent->renderPriority = renderPriority;
}

#endif //RENDER_MANAGER_C