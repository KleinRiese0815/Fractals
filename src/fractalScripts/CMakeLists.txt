file(GLOB FRACTALSCRIPTS_SOURCE ./*.cpp)

add_library(fractals
    STATIC 
    ${FRACTALSCRIPTS_SOURCE}    
)

target_include_directories(fractals
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fractals
    PUBLIC
    renderer
)