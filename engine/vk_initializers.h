#pragma once
#include "vk_types.h"

namespace vkinit {

VkCommandPoolCreateInfo
command_pool_create_info(uint32_t queueFamilyIndex,
                         VkCommandPoolCreateFlags flags);

VkCommandBufferAllocateInfo command_buffer_allocate_info(VkCommandPool pool,
                                                         uint32_t count);

}; // namespace vkinit
