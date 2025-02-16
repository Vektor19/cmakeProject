#pragma once
#include <memory>
#include <glm/vec2.hpp>
class GameObject;
class AIComponent
{
public:
	enum class EActionType {
		None,
		Chase,
		Patrol
	};
	AIComponent(const float detectionDistance, const EActionType eActionType);
	virtual void update(const double delta) = 0;
	virtual void setTarget(std::shared_ptr<GameObject> target) = 0;
	virtual bool isTargetClose(const glm::vec2& targetPos) = 0;
protected:
	float m_detectionDistance;
	EActionType m_actionType;
};