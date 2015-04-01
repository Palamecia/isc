project(Process)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(${PROJECT_NAME}_HDR
    dictionary.h
    iscparser.h
    module.h
    processmanager.h
    step.h
    stepmanager.h
)

set(${PROJECT_NAME}_SRC
    dictionary.cpp
    iscparser.cpp
    module.cpp
    processmanager.cpp
    step.cpp
    stepfunctions.cpp
    stepmanager.cpp
)

set(${PROJECT_NAME}_LIB
    Util
    Calcul
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}
    ${${PROJECT_NAME}_LIB}
)
