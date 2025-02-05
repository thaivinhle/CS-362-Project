#ifndef VULKANENGINE_H
#define VULKANENGINE_H

#include <memory>

namespace VkEngine {
class Instance;
class DebugMessenger;
class Window;
class PhysicalDevice;

class VulkanEngine {
public:
  VulkanEngine();
  ~VulkanEngine();

  [[nodiscard]] bool isActive() const;

  void render();

private:
  std::unique_ptr<Instance> instance;
  std::unique_ptr<DebugMessenger> debugMessenger;
  std::shared_ptr<Window> window;
  std::shared_ptr<PhysicalDevice> physicalDevice;
};

} // VkEngine

#endif //VULKANENGINE_H
