#pragma once
#include <memory>
class GameObject;
class AIComponent
{
public:
	virtual void update(const double delta) = 0;
	virtual void setTarget(std::shared_ptr<GameObject> target) = 0;
private:
};