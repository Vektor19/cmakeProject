#pragma once
#include "GameObject.h"
#include <memory>
namespace renderer
{
	class Sprite;
}
class BrickWall : public GameObject
{
public:
	BrickWall(std::shared_ptr<renderer::Sprite> pSprite,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0);
	void render() const override;
	void update(const uint64_t delta) override;

private:
	std::shared_ptr<renderer::Sprite> m_currentSprite;
};