add_executable(${PROJECT_NAME} main.cpp)

file(GLOB PROJECTGUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cpp)
add_library(project_gui STATIC ${PROJECTGUI_SRC})

target_include_directories(project_gui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)

target_link_libraries(project_gui
    PUBLIC
    imgui)
