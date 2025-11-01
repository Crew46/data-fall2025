#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "render_component.h"

//render component
void InitializeRenderComponent(RenderComponent* renderComponent, int region, int texture);

void UpdateRenderComponent(RenderComponent* renderComponent);

RenderComponent* ConstructRenderComponent();

void DeconstructRenderComponent(RenderComponent* renderComponent);

void SetRenderComponentRegion(RenderComponent* renderComponent, int region);

void SetRenderComponentTexture(RenderComponent* renderComponent, int texture);

void SetRenderComponentDescriptiveData(RenderComponent* renderComponent, int region, int texture, int renderPriority);


#endif //RENDER_MANAGER_H