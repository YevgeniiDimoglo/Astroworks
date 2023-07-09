#pragma once

#include "../Graphics/Sprite.h"

#include "UIUtilities.h"

class Image : public Widget
{
public:
	Image() {}
	Image(std::string name);

	void setImageValues(float positionX, float positionY, float positionZ, float width, float height, float angle, float r, float g, float b, float a) override;

	void updateSpriteValues() override;

	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) override;

	void update(float elapsedTime, GLFWwindow* window) override;

private:

	float positionX;
	float positionY;
	float positionZ;
	float width;
	float height;
	float angle;
	float r;
	float g;
	float b;
	float a;

	std::shared_ptr<Sprite> image;
};