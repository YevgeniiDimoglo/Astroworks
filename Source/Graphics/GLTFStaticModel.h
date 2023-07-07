#pragma once

// GLTF based model resource

#include "Utilities.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#include <tiny_gltf.h>

class GLTFStaticModel
{
public:

	std::string filePath;
	std::string fileName;
	std::string fileType;

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bingingDescription{};
			bingingDescription.binding = 0;
			bingingDescription.stride = sizeof(Vertex);
			bingingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bingingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, normal);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, uv);

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && normal == other.normal && uv == other.uv;
		}
	};

	struct
	{
		int				count;
		VkBuffer		buffer;
		VkDeviceMemory	memory;
	} vertices;

	struct
	{
		int				count;
		VkBuffer		buffer;
		VkDeviceMemory	memory;
	} indices;

	struct Node;

	struct Primitive
	{
		uint32_t	firstIndex;
		uint32_t	indexCount;
		int32_t		materialIndex;
	};

	struct Mesh
	{
		std::vector<Primitive>	primitives;
	};

	struct Node
	{
		Node* parent;
		std::vector<Node*>	children;
		Mesh				mesh;
		glm::mat4			matrix;

		~Node()
		{
			for (auto& child : children)
			{
				delete child;
			}
		}
	};

	glm::mat4 sceneValues = glm::mat4(1.0f);

	struct Material
	{
		glm::vec4	baseColorFactor = glm::vec4(1.0f);
		uint32_t	baseColorTextureIndex;
	};

	struct Image
	{
		VkImage					image;
		VkImageLayout			imageLayout;
		VkDeviceMemory			deviceMemory;
		VkImageView				view;
		uint32_t				width, height;
		VkDescriptorImageInfo	descriptor;
		VkSampler				sampler;
		VkDescriptorSet			descriptorSet;
	};

	struct Texture
	{
		int32_t imageIndex;
	};

	GLTFStaticModel(std::string filePath);
	~GLTFStaticModel() {};

public:

	std::vector<GLTFStaticModel::Image> getImages() const { return images; }
	std::vector<GLTFStaticModel::Image> getDummyImages() const { return dummyTextureImages; }

	void loadImages(tinygltf::Model& input);
	void loadTextures(tinygltf::Model& input);
	void loadMaterials(tinygltf::Model& input);
	void loadNode(const tinygltf::Node& inputNode, const tinygltf::Model& input, GLTFStaticModel::Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<GLTFStaticModel::Vertex>& vertexBuffer);

	void drawNode(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, GLTFStaticModel::Node* node);
	void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

	void setSceneValues(glm::mat4x4 matrixTansform) { sceneValues = matrixTansform; }

	void loadglTFFile(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, VkDescriptorPool samplerDescriptorPool, VkDescriptorSetLayout samplerSetLayout);

	void cleanupResourses(VkDevice newLogicalDevice);

private:

	void createVertexBuffer(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<Vertex>* vertices);
	void createIndexBuffer(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<uint32_t>* indices);
	Image createTextureFromBuffer(void* buffer, VkDeviceSize bufferSize, VkFormat format, uint32_t texWidth, uint32_t texHeight, VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue);
	void createDummyTextures(VkPhysicalDevice newPhysicalDevice, VkDevice newLogicalDevice, VkCommandPool transferCommandPool, VkQueue transferQueue);

	VkPhysicalDevice newPhysicalDevice;
	VkDevice newLogicalDevice;
	VkQueue transferQueue;
	VkCommandPool commandPool;
	VkDescriptorPool samplerDescriptorPool;
	VkDescriptorSetLayout samplerSetLayout;

	// Model Data

	std::vector<Image>		images;
	std::vector<Image>		dummyTextureImages;
	std::vector<Texture>	textures;
	std::vector<Material>	materials;
	std::vector<Node*>		nodes;
};