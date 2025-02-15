#pragma once
#include <memory>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "../../renderer/SpriteAnimator.h"
#include "../../utils/Timer.h"
#include "../../physics/collision/ICollidable.h"
namespace renderer { class Sprite; }
class Bullet: public GameObject, public std::enable_shared_from_this<Bullet>
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};
	Bullet(const EOrientation eOrientation,
		 const double maxVelocity,
		 const glm::vec2& position,
		 const glm::vec2& size,
		 const float layer = 0);
	

	void render() const override;
	void update(const double delta) override;
	double getMaxVelocity() const { return m_maxVelocity; }
	virtual void setVelocity(const double velocity) override;
	virtual ~Bullet() override;
	virtual void OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint) override;


private:
	EOrientation m_eOrientation;
	std::shared_ptr<renderer::Sprite> m_pSprite;

	double m_maxVelocity;
};