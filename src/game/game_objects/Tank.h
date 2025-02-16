#pragma once
#include <memory>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "../../renderer/SpriteAnimator.h"
#include "../../utils/Timer.h"
#include "../../physics/collision/ICollidable.h"
#include "../Level.h"
namespace renderer { class Sprite; }
class Tank: public GameObject, public std::enable_shared_from_this<Tank>
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};
	enum class ETankType
	{
		Yellow1,
		Yellow2,
		Yellow3,
		Yellow4,
		White1,
		White2,
		White3,
		White4,
		Green1,
		Green2,
		Green3,
		Green4,
		DarkGreen1,
		DarkGreen2,
		DarkGreen3,
		DarkGreen4,
		Red1,
		Red2,
		Red3,
		Red4
	};
	Tank(const ETankType eTankType,
		 const double maxVelocity,
		 const glm::vec2& position,
		 const glm::vec2& size,
	  	 const float rotation = 0,
		 const float layer = 0,
		 const double hitPoints = 100.0);
	

	void render() const override;
	void setOrientation(const EOrientation eOrientation);
	EOrientation getOrientation() const { return m_eOrientation; }
	void update(const double delta) override;
	double getMaxVelocity() const { return m_maxVelocity; }
	virtual void setVelocity(const double velocity) override;
	virtual void shoot();
	virtual void OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint) override;
	virtual void takeDamage(const double damage);
	void setParentLevel(std::shared_ptr<Level> parentLevel);
	virtual void initAI() override;
	virtual void setTarget(std::shared_ptr<GameObject> target);
	virtual void setHasAI(bool hasAI);
	virtual ~Tank() override;


private:
	EOrientation m_eOrientation;
	std::shared_ptr<renderer::Sprite> m_pSprite_top;
	std::shared_ptr<renderer::Sprite> m_pSprite_bottom;
	std::shared_ptr<renderer::Sprite> m_pSprite_left;
	std::shared_ptr<renderer::Sprite> m_pSprite_right;

	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_top;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_bottom;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_left;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_right;

	std::shared_ptr<renderer::Sprite> m_pSprite_respawn;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_respawn;

	std::shared_ptr<renderer::Sprite> m_pSprite_shield;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_shield;

	Timer m_respawnTimer;
	Timer m_shieldTimer;
	Timer m_reloadingTimer;

	double m_maxVelocity;
	bool m_isSpawning;
	bool m_hasShield;
	bool m_isReloading;
	double m_reloadingDuration;
	double m_hitPoints;
	std::shared_ptr<Level> m_parentLevel;
	bool m_hasAI;
};