#include "vk_initializers.h"
#include <vulkan/vulkan_core.h>

VkCommandPoolCreateInfo
vkinit::command_pool_create_info(uint32_t queueFamilyIndex,
                                 VkCommandPoolCreateFlags flags) {
  VkCommandPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  info.pNext = nullptr;
  info.queueFamilyIndex = queueFamilyIndex;
  info.flags = flags;
  return info;
}

VkCommandBufferAllocateInfo
vkinit::command_buffer_allocate_info(VkCommandPool pool, uint32_t count) {

  VkCommandBufferAllocateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.pNext = nullptr;

  info.commandPool = pool;
  info.commandBufferCount = count;
  info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  return info;
}

VkFenceCreateInfo vkinit::fence_create_info(VkFenceCreateFlags flags) {
  VkFenceCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.pNext = nullptr;

  info.flags = flags;

  return info;
}

VkSemaphoreCreateInfo
vkinit::semaphore_create_info(VkSemaphoreCreateFlags flags) {

  VkSemaphoreCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  info.pNext = nullptr;
  info.flags = flags;

  return info;
}

VkCommandBufferBeginInfo
vkinit::command_buffer_begin_info(VkCommandBufferUsageFlags flags) {

  VkCommandBufferBeginInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.pNext = nullptr;

  info.pInheritanceInfo = nullptr;
  info.flags = flags;

  return info;
}

VkImageSubresourceRange
vkinit::image_subresources_range(VkImageAspectFlags aspectMask) {
  VkImageSubresourceRange subImage{};
  subImage.aspectMask = aspectMask;
  subImage.baseMipLevel = 0;
  subImage.levelCount = VK_REMAINING_MIP_LEVELS;
  subImage.baseArrayLayer = 0;
  subImage.layerCount = VK_REMAINING_ARRAY_LAYERS;

  return subImage;
}

VkSemaphoreSubmitInfo
vkinit::semaphore_submit_info(VkPipelineStageFlags2 stageMask,
                              VkSemaphore semaphore) {
  VkSemaphoreSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
  submitInfo.pNext = nullptr;
  submitInfo.semaphore = semaphore;
  submitInfo.stageMask = stageMask;
  submitInfo.deviceIndex = 0;
  submitInfo.value = 1;

  return submitInfo;
}

VkCommandBufferSubmitInfo
vkinit::command_buffer_submit_info(VkCommandBuffer cmd) {
  VkCommandBufferSubmitInfo info{};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
  info.pNext = nullptr;
  info.commandBuffer = cmd;
  info.deviceMask = 0;

  return info;
}

VkSubmitInfo2 vkinit::submit_info(VkCommandBufferSubmitInfo *cmd,
                                  VkSemaphoreSubmitInfo *signalSemaphoreInfo,
                                  VkSemaphoreSubmitInfo *waitSemaphoreInfo) {
  VkSubmitInfo2 info = {};
  info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
  info.pNext = nullptr;

  info.waitSemaphoreInfoCount = waitSemaphoreInfo == nullptr ? 0 : 1;
  info.pWaitSemaphoreInfos = waitSemaphoreInfo;

  info.signalSemaphoreInfoCount = signalSemaphoreInfo == nullptr ? 0 : 1;
  info.pSignalSemaphoreInfos = signalSemaphoreInfo;

  info.commandBufferInfoCount = 1;
  info.pCommandBufferInfos = cmd;

  return info;
}

VkImageCreateInfo vkinit::image_create_info(VkFormat format,
                                            VkImageUsageFlags usageFlags,
                                            VkExtent3D extent) {

  VkImageCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  info.pNext = nullptr;

  info.imageType = VK_IMAGE_TYPE_2D;

  info.format = format;
  info.extent = extent;

  info.mipLevels = 1;
  info.arrayLayers = 1;

  info.samples = VK_SAMPLE_COUNT_1_BIT;

  info.tiling = VK_IMAGE_TILING_OPTIMAL;
  info.usage = usageFlags;

  return info;
}

VkImageViewCreateInfo
vkinit::imageview_create_info(VkFormat format, VkImage image,
                              VkImageAspectFlags aspectFlags) {

  VkImageViewCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  info.pNext = nullptr;

  info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  info.image = image;
  info.format = format;
  info.subresourceRange.baseMipLevel = 0;
  info.subresourceRange.levelCount = 1;
  info.subresourceRange.baseArrayLayer = 0;
  info.subresourceRange.layerCount = 1;
  info.subresourceRange.aspectMask = aspectFlags;

  return info;
}

VkRenderingAttachmentInfo vkinit::attachment_info(VkImageView view,
                                                  VkClearValue *clear,
                                                  VkImageLayout layout) {

  VkRenderingAttachmentInfo colorAttachment{};
  colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
  colorAttachment.pNext = nullptr;

  colorAttachment.imageView = view;
  colorAttachment.imageLayout = layout;
  colorAttachment.loadOp =
      clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

  if (clear) {
    colorAttachment.clearValue = *clear;
  }

  return colorAttachment;
}

VkRenderingInfo
vkinit::rendering_info(VkExtent2D renderExtent,
                       VkRenderingAttachmentInfo *colorAttachment,
                       VkRenderingAttachmentInfo *depthAttachment) {

  VkRenderingInfo renderInfo{};
  renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
  renderInfo.pNext = nullptr;

  renderInfo.renderArea = VkRect2D{VkOffset2D{0, 0}, renderExtent};
  renderInfo.layerCount = 1;
  renderInfo.colorAttachmentCount = 1;
  renderInfo.pColorAttachments = colorAttachment;
  renderInfo.pDepthAttachment = depthAttachment;
  renderInfo.pStencilAttachment = nullptr;

  return renderInfo;
}

VkPipelineShaderStageCreateInfo
vkinit::pipeline_shader_stage_create_info(VkShaderStageFlagBits stage,
                                          VkShaderModule shaderModule,
                                          const char *entry) {

  VkPipelineShaderStageCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info.pNext = nullptr;
  info.stage = stage;
  info.module = shaderModule;
  info.pName = entry;

  return info;
}

VkPipelineLayoutCreateInfo vkinit::pipeline_layout_create_info() {
  VkPipelineLayoutCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  info.pNext = nullptr;

  info.flags = 0;
  info.setLayoutCount = 0;
  info.pSetLayouts = nullptr;
  info.pushConstantRangeCount = 0;
  info.pPushConstantRanges = nullptr;

  return info;
}

VkRenderingAttachmentInfo vkinit::depth_attachment_info(VkImageView view,
                                                        VkImageLayout layout) {

  VkRenderingAttachmentInfo depthAttachment{};
  depthAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
  depthAttachment.pNext = nullptr;

  depthAttachment.imageView = view;
  depthAttachment.imageLayout = layout;
  depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  depthAttachment.clearValue.depthStencil.depth = 0.f;

  return depthAttachment;
}
