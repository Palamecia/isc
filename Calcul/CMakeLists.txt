project(Calcul)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(DataType)

set(${PROJECT_NAME}_HDR
    calcul.h
    contexte.h
    contextestack.h
    iscobject.h
    memorymanager.h
)

set(${PROJECT_NAME}_SRC
    calcul.cpp
    contexte.cpp
    contextestack.cpp
    iscobject.cpp
    memorymanager.cpp
)

set(${PROJECT_NAME}_LIB
    Util
    DataType
    Process
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}
    ${${PROJECT_NAME}_LIB}
)
