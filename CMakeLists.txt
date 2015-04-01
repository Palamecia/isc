cmake_minimum_required(VERSION 2.8)

project(isc)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(Util)
add_subdirectory(System)
add_subdirectory(Process)
add_subdirectory(Calcul)

set(${PROJECT_NAME}_HDR
    Syntax.h
)

set(${PROJECT_NAME}_SRC
    main.cpp
)

set(${PROJECT_NAME}_LIB
    Util
    System
    Process
    Calcul
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}
    ${${PROJECT_NAME}_LIB}
)

add_executable(${PROJECT_NAME}-debug
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}-debug
    ${${PROJECT_NAME}_LIB}
)

# target_compile_definitions(${PROJECT_NAME}-debug
#     -DISC_DEBUG
# )
