#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "render_component.h"

struct RenderManager
{
    DoublyLinkedList* renderComponents;
};

//manager
void InitializeRenderManager();

void DeinitializeRenderManager();

RenderManager* GetRenderManager();

//render component
void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture);

void DeinitializeRenderComponent(RenderComponent* renderComponent);

void UpdateRenderComponent(RenderComponent* renderComponent);

RenderComponent* ConstructRenderComponent();

void DeconstructRenderComponent(RenderComponent* renderComponent);

void SetRenderComponentRegion(RenderComponent* renderComponent, int region);

void SetRenderComponentTexture(RenderComponent* renderComponent, int texture);


#endif //RENDER_MANAGER_H