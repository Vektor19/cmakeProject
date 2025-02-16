#pragma once
#include "AIComponent.h"
#include <memory>
#include "../../utils/Timer.h"
class GameObject;
class Tank;
class TankAIComponent :public AIComponent
{
public:
	TankAIComponent(std::shared_ptr<Tank> owner, const float detectionDistance = 50, const EActionType eActionType = EActionType::None);
	virtual void setTarget(std::shared_ptr<GameObject> target) override;
	virtual void update(const double delta) override;
	virtual bool isTargetClose(const glm::vec2& targetPos) override;
private:
	std::shared_ptr<Tank> m_owner;
	std::weak_ptr<GameObject> m_target;
	Timer m_changeDirrectionTimer;
};