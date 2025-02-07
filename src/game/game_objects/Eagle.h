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
		const float rotation = 0);
	void render() const override;
	void update(const uint64_t delta) override;

private:
	std::array<std::shared_ptr<renderer::Sprite>, 2> m_sprites;
	EEagleState m_eCurrentEagleState;
};