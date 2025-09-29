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

void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture)
{
    InitializeComponent((Component*)renderComponent, RENDER_COMPONENT);  
    SetObjectName((Object*)renderComponent, "Render_Component"); 
    renderComponent->regionID = region;
    renderComponent->textureID = texture;
    DoublyLinkedListInsertToTail(renderManager->renderComponents, (Object*)renderComponent);
}

void DeinitializeRenderComponent(RenderComponent* renderComponent)
{
    DeconstructComponent(&renderComponent->base);
    free(renderComponent);
}

RenderComponent* ConstructRenderComponent()
{
    RenderComponent* renderComponent = (RenderComponent*)malloc(sizeof(RenderComponent));
    InitializeRenderComponent(renderComponent, 0, 0);
    return renderComponent;
}

void DeconstructRenderComponent(RenderComponent* renderComponent)
{

}

void UpdateRenderComponent(RenderComponent* renderComponent)
{
    //GETCOMPONENT FROM COMPONENT NOT WORKING, NEED TO FIX

    //if this gameobject has a transform
    //if(transformComponent != NULL)
    //{
     //   print_at(screen_width / 2, screen_height / 2 + 150, "rendering");
        //select_texture(renderComponent->textureID);
        //select_region(renderComponent->regionID);
        //draw_region_at(transformComponent->position.x, transformComponent->position.y);
    //}
    //else
    //{
     //   print_at(screen_width / 2, screen_height / 2 + 150, "NULL");
    //}

}

RenderManager* GetRenderManager()
{
    return renderManager;
}

#endif //RENDER_MANAGER_C