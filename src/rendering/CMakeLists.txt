file(GLOB RENDERER_SRC ./*.cpp)

add_library(renderer 
    STATIC
    ${RENDERER_SRC}
)

target_include_directories(renderer
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(renderer
    PUBLIC
    glfw
    glad
    glm
)