project(stdio)

set(${PROJECT_NAME}_HDR
    stdio.h
)

set(${PROJECT_NAME}_SRC
    stdio.cpp
)

add_library(${PROJECT_NAME}
    MODULE
    stdio.h
    stdio.cpp
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    PREFIX ""
)
