#pragma once
#include "AIComponent.h"
#include <memory>
class GameObject;
class Tank;
class TankAIComponent :public AIComponent
{
public:
	TankAIComponent(std::shared_ptr<Tank> owner);
	virtual void setTarget(std::shared_ptr<GameObject> target) override;
	virtual void update(const double delta) override;
private:
	std::shared_ptr<Tank> m_owner;
	std::weak_ptr<GameObject> m_target;
};