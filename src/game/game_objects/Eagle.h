#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
}
class Eagle : public GameObject
{
public:
	enum class EEagleState {
		Alive,
		Dead
	};
	Eagle(const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0,
		const float layer = 0,
		const double durability = 100);
	void render() const override;
	virtual void OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint) override;
	virtual void takeDamage(const double damage);
	void update(const double delta) override;

private:
	std::array<std::shared_ptr<renderer::Sprite>, 2> m_sprites;
	EEagleState m_eCurrentEagleState;
	double m_durability;
};