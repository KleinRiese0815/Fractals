cmake_minimum_required(VERSION 3.10)
project(imgui)

# alle Quell-Dateien

file(GLOB IMGUI_SOURCES "./*.cpp" "./backends/*.cpp")

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

# Abhängigkeiten
target_link_libraries(imgui
    PUBLIC
    glfw        # muss vorher als Target existieren
)
