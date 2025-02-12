#ifndef BUFFERS_H
#define BUFFERS_H

#include <vulkan/vulkan.h>
#include <memory>

namespace VkEngine {

class LogicalDevice;
class PhysicalDevice;

namespace Buffers {
  void createBuffer(const std::shared_ptr<LogicalDevice>& logicalDevice,
                    const std::shared_ptr<PhysicalDevice>& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

  void copyBuffer(const std::shared_ptr<LogicalDevice>& logicalDevice, const VkCommandPool& commandPool,
                  const VkQueue& queue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  void destroyBuffer(const std::shared_ptr<LogicalDevice>& logicalDevice, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

  VkCommandBuffer beginSingleTimeCommands(const std::shared_ptr<LogicalDevice>& logicalDevice, VkCommandPool commandPool);

  void endSingleTimeCommands(const std::shared_ptr<LogicalDevice>& logicalDevice, VkCommandPool commandPool,
                             VkQueue queue, VkCommandBuffer commandBuffer);
}

} // VkEngine

#endif //BUFFERS_H
