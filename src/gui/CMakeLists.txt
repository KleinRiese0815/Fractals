file(GLOB GUI_SRC ./*.cpp)

add_library(gui 
    STATIC 
    ${GUI_SRC})

target_include_directories(gui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gui
    PUBLIC
    imgui
    fractals
)