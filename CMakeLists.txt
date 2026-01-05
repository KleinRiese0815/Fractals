cmake_minimum_required(VERSION 3.28)
project(openglProject)



#dependencies:
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)

#target:
add_subdirectory(src)

#Libraries linken

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glfw
    glad
)