#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
}
class BetonWall : public GameObject
{
public:
	enum class EBetonWallType {
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};
	enum class EBrickState {
		All,
		Destroyed
	};
	enum class EBrickLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BetonWall(const EBetonWallType eBetonWallType,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0,
		const float layer = 0);
	void render() const override;
	void update(const double delta) override;

private:
	void renderBrick(EBrickLocation eBrickLocation) const;
	std::array<std::shared_ptr<renderer::Sprite>, 1> m_sprites;
	std::array<EBrickState, 4> m_eBrickStates;
	std::array<glm::vec2, 4> m_blockOffsets;
};