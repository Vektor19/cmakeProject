#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
	class SpriteAnimator;
}
class Water : public GameObject
{
public:
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	Water(const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0);
	void render() const override;
	void update(const uint64_t delta) override;

private:
	void renderBlock(EBlockLocation eBlockLocation) const;
	std::shared_ptr<renderer::Sprite> m_sprite;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator;
	std::array<glm::vec2, 4> m_blockOffsets;
};