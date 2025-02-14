#include "DynamicObjectsRenderer.h"

std::unordered_set<std::shared_ptr<GameObject>> DynamicObjectsRenderer::m_dynamicObjects;

void DynamicObjectsRenderer::render()
{
	if (!m_dynamicObjects.empty())
	{
		for (auto& currentGameObject : m_dynamicObjects)
		{
			currentGameObject->render();
		}
	}
}

void DynamicObjectsRenderer::addDynamicObject(std::shared_ptr<GameObject> pGameObject)
{
	m_dynamicObjects.insert(std::move(pGameObject));
}
