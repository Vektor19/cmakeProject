#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
}
class Trees : public GameObject
{
public:
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	enum class ETreesState {
		All,
		Destroyed
	};
	Trees(const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0,
		const float layer = 0);
	void render() const override;
	void update(const double delta) override;
	virtual void OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint) override;
	virtual void takeDamage();

private:
	void renderBlock(EBlockLocation eBlockLocation) const;
	std::shared_ptr<renderer::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
	ETreesState m_eTreesState;
};