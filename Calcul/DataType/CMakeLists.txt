project(DataType)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB files "SystemInterface/ISCSI/*")
foreach(file ${files})
    add_subdirectory(${file})
endforeach()

set(${PROJECT_NAME}_HDR
    Boolean/booleandescriptor.h
    Boolean/booleanvalue.h
    Class/classdescriptor.h
    Class/uservalue.h
    Color/colordescriptor.h
    Float/floatdescriptor.h
    Function/builtinfunction.h
    Function/functionvalue.h
    Function/userfunction.h
    Integer/integerdescriptor.h
    Integer/integeroperator.h
    Integer/integervalue.h
    None/voiddescriptor.h
    None/voidvalue.h
    String/stringdescriptor.h
    String/stringvalue.h
    SystemInterface/iscsi.h
    SystemInterface/iscsidescriptror.h
    Variant/vardescriptor.h
    builtinvalue.h
    iscvalue.h
    memberdescriptor.h
    objectdescriptor.h
    typedescriptor.h
    typeinfo.h
)

set(${PROJECT_NAME}_SRC
    Boolean/booleandescriptor.cpp
    Boolean/booleanvalue.cpp
    Class/classdescriptor.cpp
    Class/uservalue.cpp
    Color/colordescriptor.cpp
    Float/floatdescriptor.cpp
    Function/builtinfunction.cpp
    Function/functionvalue.cpp
    Function/userfunction.cpp
    Integer/integerdescriptor.cpp
    Integer/integervalue.cpp
    None/voiddescriptor.cpp
    None/voidvalue.cpp
    String/stringdescriptor.cpp
    String/stringvalue.cpp
    SystemInterface/iscsi.cpp
    SystemInterface/iscsidescriptror.cpp
    Variant/vardescriptor.cpp
    builtinvalue.cpp
    iscvalue.cpp
    memberdescriptor.cpp
    objectdescriptor.cpp
    typedescriptor.cpp
    typeinfo.cpp
)

set(${PROJECT_NAME}_LIB
    Util
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HDR}
    ${${PROJECT_NAME}_SRC}
)

target_link_libraries(${PROJECT_NAME}
    ${${PROJECT_NAME}_LIB}
)
