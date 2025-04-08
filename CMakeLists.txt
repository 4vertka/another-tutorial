cmake_minimum_required(VERSION 3.15)
project(VulkanSDLApp)

set(CMAKE_CXX_STANDARD 17)


file(GLOB SRC_FILES "./engine/*.cpp")

# Find Vulkan
find_package(Vulkan REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)


# Include directories
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

# Add the executable
add_executable(VulkanSDLApp
    ${SRC_FILES}
)


target_link_libraries(VulkanSDLApp
    ${Vulkan_LIBRARIES}
    ${SDL2_LIBRARIES}
)
