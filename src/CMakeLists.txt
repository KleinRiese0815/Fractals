add_executable(${PROJECT_NAME} 
main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rendering)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    gui
    renderer
)