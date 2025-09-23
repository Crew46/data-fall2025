#ifndef RENDER_MANAGER_C
#define RENDER_MANAGER_C
#include "render_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../systems/transform/transform_manager.h"
#include "video.h"

RenderManager* renderManager;

void InitializeRenderManager()
{
    renderManager = (RenderManager*)malloc(sizeof(RenderManager));
    renderManager->renderComponents = CreateDoublyLinkedList();
}

void DeinitializeRenderManager()
{
    //deconstruct doubly linekd list
    free(renderManager);
}

void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture)
{
    ComponentManagerInitializeComponent(&renderComponent->base, RENDER_COMPONENT);  
    renderComponent->regionID = region;
    renderComponent->textureID = texture;
    DoublyLinkedListInsertAtTail(renderManager->renderComponents, (Object*)renderComponent);
}

void DeinitializeRenderComponent(RenderComponent* renderComponent)
{
    ComponentManagerDeconstructComponent(&renderComponent->base);
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
    //transform components of this gameobject
    TransformComponent* transformComponent = (TransformComponent*)GetComponentFromComponent((Component*)renderComponent, TRANSFORM_COMPONENT);

    //GETCOMPONENT FROM COMPONENT NOT WORKING, NEED TO FIX

    //if this gameobject has a transform
    if(transformComponent != NULL)
    {
        print_at(screen_width / 2, screen_height / 2 + 150, "rendering");
        select_texture(renderComponent->textureID);
        select_region(renderComponent->regionID);
        draw_region_at(transformComponent->position.x, transformComponent->position.y);
    }

}

RenderManager* GetRenderManager()
{
    return renderManager;
}

#endif //RENDER_MANAGER_C