#include "manapch.h"
#include "VulkanVertexBuffer.h"

#include "VulkanRenderAPI.h"

namespace Mana {
	const std::vector<VulkanVertexBuffer::Vertex> vertices = {
		{{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		{{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
	};

	void VulkanVertexBuffer::Init()
	{
		auto device = VulkanRenderAPI::GetDevice()->GetVulkanDevice();

		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = sizeof(vertices[0]) * vertices.size();
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(device, &bufferInfo, nullptr, &m_VulkanBuffer) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, m_VulkanBuffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	
		if (vkAllocateMemory(device, &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(device, m_VulkanBuffer, m_VertexBufferMemory, 0);

		void* data;
		vkMapMemory(device, m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferInfo.size);
		vkUnmapMemory(device, m_VertexBufferMemory);
	}
	
	void VulkanVertexBuffer::Clean()
	{
		auto device = VulkanRenderAPI::GetDevice()->GetVulkanDevice();
		vkDestroyBuffer(device, m_VulkanBuffer, nullptr);
		vkFreeMemory(device, m_VertexBufferMemory, nullptr);
	}
	
	uint32_t VulkanVertexBuffer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		auto physicalDevice = VulkanRenderAPI::GetPhysicalDevice()->GetVulkanDevice();

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		MANA_CORE_ASSERT(false, "Failed to find suitable memory type!");
	}
}
