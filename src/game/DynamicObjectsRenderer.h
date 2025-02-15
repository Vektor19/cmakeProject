#pragma once
#include <unordered_set>
#include <memory>
#include "game_objects/GameObject.h"

class DynamicObjectsRenderer
{
public:
	DynamicObjectsRenderer() = delete;
	~DynamicObjectsRenderer() = delete;
	DynamicObjectsRenderer(const DynamicObjectsRenderer&) = delete;
	DynamicObjectsRenderer(DynamicObjectsRenderer&&) = delete;
	DynamicObjectsRenderer& operator=(const DynamicObjectsRenderer&) = delete;
	DynamicObjectsRenderer& operator=(DynamicObjectsRenderer&&) = delete;

	static void render();
	static void addDynamicObject(std::shared_ptr<GameObject> pGameObject);
	static void removeDynamicObject(std::shared_ptr<GameObject> pGameObject);
private:

	static std::unordered_set<std::shared_ptr<GameObject>> m_dynamicObjects;
};