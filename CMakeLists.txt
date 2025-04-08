cmake_minimum_required(VERSION 3.15)
project(VulkanSDLApp)

set(CMAKE_CXX_STANDARD 17)


file(GLOB SRC_FILES "./engine/*.cpp")

# Find Vulkan
find_package(Vulkan REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)

add_subdirectory(vk-bootstrap)
file(GLOB VK_BOOTSTRAP_SRC "./vk-bootstrap/src/*.cpp")


# Include directories
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    vk-bootstrap/src
)

# Add the executable
add_executable(VulkanSDLApp
    ${SRC_FILES}
)


target_link_libraries(VulkanSDLApp
    ${Vulkan_LIBRARIES}
    ${SDL2_LIBRARIES}
    vk-bootstrap::vk-bootstrap
)
