#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
}
class BrickWall : public GameObject
{
public:
	enum class EBrickWallType {
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
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};
	enum class EBrickLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BrickWall(const EBrickWallType eBrickWallType,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0);
	void render() const override;
	void update(const uint64_t delta) override;

private:
	void renderBrick(EBrickLocation eBrickLocation) const;
	std::array<std::shared_ptr<renderer::Sprite>, 15> m_sprites;
	std::array<EBrickState, 4> m_eBrickStates;
};