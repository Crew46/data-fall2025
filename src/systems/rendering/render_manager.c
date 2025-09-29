#ifndef RENDER_MANAGER_C
#define RENDER_MANAGER_C
#include "render_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../architecture/object/object_manager.h"
#include "../../systems/transform/transform_manager.h"
#include "video.h"
#include "../../tools/debugger.c"

RenderManager* renderManager;

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER INITIALIZATION//////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeRenderManager()
{
    renderManager = (RenderManager*)malloc(sizeof(RenderManager));
    renderManager->renderComponents = ConstructDoublyLinkedList();
}

void DeinitializeRenderManager()
{
    //deconstruct doubly linekd list
    free(renderManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT CONSTRUCTION & DECONSTRUCTION/////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture)
{
    InitializeComponent((Component*)renderComponent, RENDER_COMPONENT);  
    SetObjectName((Object*)renderComponent, "Render_Component"); 
    renderComponent->regionID = region;
    renderComponent->textureID = texture;
    renderComponent->renderPriority = 0;
    DoublyLinkedListInsertToTail(renderManager->renderComponents, (Object*)renderComponent);
}

RenderComponent* ConstructRenderComponent()
{
    RenderComponent* renderComponent = (RenderComponent*)malloc(sizeof(RenderComponent));
    InitializeRenderComponent(renderComponent, 0, 0);
    return renderComponent;
}

void DeconstructRenderComponent(RenderComponent* renderComponent)
{
    DeconstructComponent(&renderComponent->base);
    free(renderComponent);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateRenderComponent(RenderComponent* renderComponent)
{
    TransformComponent* transformComponent = (TransformComponent*)GetComponentFromComponent((Component*)renderComponent, TRANSFORM_COMPONENT);

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

RenderManager* GetRenderManager()
{
    return renderManager;
}

void SetRenderComponentRegion(RenderComponent* renderComponent, int region)
{
    renderComponent->regionID = region;
}

void SetRenderComponentTexture(RenderComponent* renderComponent, int texture)
{
    renderComponent->textureID = texture;
}

#endif //RENDER_MANAGER_C