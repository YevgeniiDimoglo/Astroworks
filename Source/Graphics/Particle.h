#pragma once

#include "Utilities.h"

class Particle {
public:

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bingingDescription{};
			bingingDescription.binding = 0;
			bingingDescription.stride = sizeof(Vertex);
			bingingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bingingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color;
		}
	};

	glm::vec2 GetPosition() const { return position; }
	float GetPositionX() const { return position.x; }
	float GetPositionY() const { return position.y; }
	void SetPosition(glm::vec2 position) { this->position = position; }

	glm::vec2 GetVelocity() const { return velocity; }
	void SetVelocity(glm::vec2 velocity) { this->velocity = velocity; }

	glm::vec4 GetColor() const { return color; }
	float GetRColor() const { return color.r; }
	float GetBColor() const { return color.g; }
	float GetGColor() const { return color.b; }
	float GetAColor() const { return color.a; }
	void SetColor(glm::vec4 color) { this->color = color; }

private:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec4 color;
};