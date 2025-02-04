#include "Instance.h"
#include "DebugMessenger.h"
#include <stdexcept>
#include <unordered_set>
#include <GLFW/glfw3.h>

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

namespace VkEngine {
  Instance::Instance()
  {
    if (enableValidationLayers && !checkValidationLayerSupport())
    {
      throw std::runtime_error("validation layers requested, but not available!");
    }

    constexpr VkApplicationInfo appInfo {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = "Vulkan Engine",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_0
    };

    const auto extensions = getRequiredExtensions();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers)
    {
      DebugMessenger::populateCreateInfo(debugCreateInfo);
    }

    const VkInstanceCreateInfo createInfo {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = enableValidationLayers ? &debugCreateInfo : nullptr,
      .pApplicationInfo = &appInfo,
      .enabledLayerCount = enableValidationLayers ? static_cast<uint32_t>(validationLayers.size()) : 0,
      .ppEnabledLayerNames = enableValidationLayers ? validationLayers.data() : nullptr,
      .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data()
    };

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
      throw std::runtime_error("failed to create instance!");
    }
  }

  Instance::~Instance()
  {
    vkDestroyInstance(instance, nullptr);
  }

  VkInstance& Instance::getInstance()
  {
    return instance;
  }

  bool Instance::checkValidationLayerSupport()
  {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Use a hash set for quick lookups
    std::unordered_set<std::string> availableLayerNames;
    for (const auto& layer : availableLayers)
    {
      availableLayerNames.insert(layer.layerName);
    }

    for (const char* layerName : validationLayers)
    {
      if (!availableLayerNames.contains(layerName))
      {
        return false;
      }
    }

    return true;
  }

  std::vector<const char *> Instance::getRequiredExtensions()
  {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
    {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }
} // VkEngine