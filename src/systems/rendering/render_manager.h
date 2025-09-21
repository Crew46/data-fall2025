#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "render_component.h"

struct RenderManager
{
    DoublyLinkedList* renderComponents;
};

void InitializeRenderManager();

void DeinitializeRenderManager();

void UpdateRenderComponent(RenderComponent* renderComponent);

void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture);

void DeinitializeRenderComponent(RenderComponent* renderComponent);

RenderComponent* ConstructRenderComponent();

void DeconstructRenderComponent(RenderComponent* renderComponent);

RenderManager* GetRenderManager();

#endif //RENDER_MANAGER_H