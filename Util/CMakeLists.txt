project(Util)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(${PROJECT_NAME}_HDR
    file.h
    list.h
    map.h
    set.h
    stack.h
    string.h
    textstream.h
    typedefs.h
)

set(${PROJECT_NAME}_SRC
    file.cpp
    list.cpp
    map.cpp
    set.cpp
    stack.cpp
    string.cpp
    textstream.cpp
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)
