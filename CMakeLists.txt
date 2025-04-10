cmake_minimum_required(VERSION 3.15)
project(VulkanSDLApp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB SRC_FILES "./engine/*.cpp")

# Find Vulkan
find_package(Vulkan REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add vk-bootstrap
add_subdirectory(vk-bootstrap)
file(GLOB VK_BOOTSTRAP_SRC "./vk-bootstrap/src/*.cpp")

# Include directories
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    vk-bootstrap/src
    /usr/include  # ImGui headers
)

# Add the executable
add_executable(VulkanSDLApp
    ${SRC_FILES}
)

# Now that target exists, link ImGui
target_link_libraries(VulkanSDLApp
    ${Vulkan_LIBRARIES}
    ${SDL2_LIBRARIES}
    vk-bootstrap::vk-bootstrap
    imgui  # Link ImGui library
)

# Shader compilation
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(COMPILED_SHADER_DIR "${CMAKE_BINARY_DIR}/shaders")
file(MAKE_DIRECTORY ${COMPILED_SHADER_DIR})

add_custom_command(
    OUTPUT ${COMPILED_SHADER_DIR}/gradient.comp.spv 
    COMMAND glslc ${SHADER_DIR}/gradient.comp -o ${COMPILED_SHADER_DIR}/gradient.comp.spv
    DEPENDS ${SHADER_DIR}/gradient.comp
    COMMENT "compiling gradient.comp shader"
)

add_custom_command(                                                                                  
    OUTPUT ${COMPILED_SHADER_DIR}/sky.comp.spv                                                  
    COMMAND glslc ${SHADER_DIR}/sky.comp -o ${COMPILED_SHADER_DIR}/sky.comp.spv            
    DEPENDS ${SHADER_DIR}/sky.comp                                                              
    COMMENT "compiling sky.comp shader"                                                         
)                                                                                                    

add_custom_command(                                                                                              
    OUTPUT ${COMPILED_SHADER_DIR}/color_triangle.vert.spv                                                        
    COMMAND glslc ${SHADER_DIR}/color_triangle.vert -o ${COMPILED_SHADER_DIR}/color_triangle.vert.spv               
    DEPENDS ${SHADER_DIR}/color_triangle.vert                                                                         
    COMMENT "compiling color_triangle.vert shader"                                                                     
)                                                                                                                
                                                                                                                 
add_custom_command(                                                                                              
    OUTPUT ${COMPILED_SHADER_DIR}/color_triangle.frag.spv                                                                  
    COMMAND glslc ${SHADER_DIR}/color_triangle.frag -o ${COMPILED_SHADER_DIR}/color_triangle.frag.spv                                 
    DEPENDS ${SHADER_DIR}/color_triangle.frag                                                                               
    COMMENT "compiling color_triangle.frag shader"                                                                          
)                                                                                                                

add_custom_target(CompileShaders ALL
    DEPENDS
    ${COMPILED_SHADER_DIR}/gradient.comp.spv
    ${COMPILED_SHADER_DIR}/sky.comp.spv
    ${COMPILED_SHADER_DIR}/color_triangle.vert.spv
    ${COMPILED_SHADER_DIR}/color_triangle.frag.spv
)

add_dependencies(VulkanSDLApp CompileShaders)
