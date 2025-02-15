#pragma once
#include <memory>
class GameObject;
class AIBehavior
{
public:
	virtual void setTarget(std::shared_ptr<GameObject> target);
	virtual void 
private:
	std::shared_ptr<GameObject> m_pTarget;
};