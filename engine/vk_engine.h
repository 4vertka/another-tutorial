#pragma once

#include "vk_descriptors.h"
#include "vk_loader.h"
#include "vk_pipelines.h"
#include "vk_types.h"
#include <functional>
#include <memory>

struct DeletionQueue {
  std::deque<std::function<void()>> deletors;

  void push_function(std::function<void()> &&function) {
    deletors.push_back(function);
  }

  void flush() {
    for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
      (*it)();
      deletors.clear();
    }
  }
};

struct ComputePushConstants {
  glm::vec4 data1;
  glm::vec4 data2;
  glm::vec4 data3;
  glm::vec4 data4;
};

struct ComputeEffect {
  const char *name;

  VkPipeline pipeline;
  VkPipelineLayout layout;

  ComputePushConstants data;
};

struct FrameData {
  VkSemaphore _swapchainSemaphore, _renderSemaphore;
  VkFence _renderFence;

  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  DeletionQueue _deletionQueue;
};

constexpr unsigned int FRAME_OVERLAP = 2;

class VulkanEngine {
public:
  bool _isInitialized{false};
  int _frameNumber{0};
  bool stop_rendering{false};
  VkExtent2D _windowExtent{1700, 900};

  struct SDL_Window *_window{nullptr};
  static VulkanEngine &Get();

  void init();

  void cleanup();

  void draw();

  void run();

  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debug_messenger;
  VkPhysicalDevice _chosenGPU;
  VkDevice _device;
  VkSurfaceKHR _surface;

  VkSwapchainKHR _swapchain;
  VkFormat _swapchainImageFormat;

  std::vector<VkImage> _swapchainImages;
  std::vector<VkImageView> _swapchainImageViews;
  VkExtent2D _swapchainExtent;

  FrameData _frames[FRAME_OVERLAP];

  FrameData &get_current_frame() {
    return _frames[_frameNumber % FRAME_OVERLAP];
  };

  VkQueue _graphicsQueue;
  uint32_t _graphicsQueueFamily;
  DeletionQueue _mainDeletionQueue;

  VmaAllocator _allocator;

  AllocatedImage _drawImage;
  VkExtent2D _drawExtent;

  DescriptorAllocator globalDescriptorAllocator;
  VkDescriptorSet _drawImageDescriptors;
  VkDescriptorSetLayout _drawImageDescriptorLayout;

  VkPipeline _gradientPipeline;
  VkPipelineLayout _gradientPipelineLayout;

  VkFence _immFence;
  VkCommandBuffer _immCommandBuffer;
  VkCommandPool _immCommandPool;

  void immediate_submit(std::function<void(VkCommandBuffer cmd)> &&function);

  std::vector<ComputeEffect> backgroundEffects;
  int currentBackgroundEffect{0};

  VkPipelineLayout _trianglePipelineLayout;
  VkPipeline _trianglePipeline;

  void init_triangle_pipeline();

  VkPipelineLayout _meshPipelineLayout;
  VkPipeline _meshPipeline;

  GPUMeshBuffers rectangle;

  void init_mesh_pipeline();

  GPUMeshBuffers uploadMesh(std::span<uint32_t> indices,
                            std::span<Vertex> vertices);

  std::vector<std::shared_ptr<MeshAsset>> testMeshes;

  AllocatedImage _depthImage;

private:
  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();

  void create_swapchain(uint32_t widht, uint32_t height);
  void destroy_swapchain();

  void draw_background(VkCommandBuffer cmd);

  void init_descriptors();

  void init_pipelines();
  void init_background_pipelines();

  void init_imgui();

  void draw_imgui(VkCommandBuffer cmd, VkImageView targetImageView);

  void draw_geometry(VkCommandBuffer cmd);

  AllocatedBuffer create_buffer(size_t allocSize, VkBufferUsageFlags usage,
                                VmaMemoryUsage memoryUsage);

  void destroy_buffer(const AllocatedBuffer &buffer);

  void init_default_data();
};
