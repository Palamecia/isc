project(System)

set(${PROJECT_NAME}_HDR
    iscsourcemanager.h
)

set(${PROJECT_NAME}_SRC
    iscsourcemanager.cpp
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}
    dl
)
