#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
#include "../Level.h"
namespace renderer
{
	class Sprite;
}
class Ice : public GameObject, public std::enable_shared_from_this<Ice>
{
public:
	enum class EBlockLocation {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	Ice(const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0,
		const float layer = 0
	);
	void render() const override;
	void update(const double delta) override;
	virtual void OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint) override;
	virtual void takeDamage();
	void setParentLevel(std::shared_ptr<Level> parentLevel);

private:
	void renderBlock(EBlockLocation eBlockLocation) const;
	std::shared_ptr<renderer::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
	std::shared_ptr<Level> m_parentLevel;
};