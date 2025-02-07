#pragma once
#include "GameObject.h"
#include <memory>
#include <array>
namespace renderer
{
	class Sprite;
}
class Border : public GameObject
{
public:
	Border(const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0,
		const float layer = 0);
	void render() const override;
	void update(const uint64_t delta) override;
private:
	std::shared_ptr<renderer::Sprite> m_sprite;
};