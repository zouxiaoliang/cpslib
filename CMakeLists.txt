cmake_minimum_required(VERSION 2.8)

project(pslib-cpp)
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall")
set(CMAKE_CXX_STANDARD 11)
set(LIB_VERSION 1.0.0)

include_directories(/usr/local/include)

include_directories(.)
include_directories(utils)

aux_source_directory(utils SRC_LIST)
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    aux_source_directory(osx SRC_LIST)
else(CMAKE_SYSTEM_NAME MATCHES "Linux")
    aux_source_directory(linux SRC_LIST)
endif()

link_directories(/usr/local/lib)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

SET(LIBRARY_OUTPUT_PATH lib)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION ${LIB_VERSION})
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} "-dynamiclib --coverage -framework CoreFoundation -framework IOKit")
else(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} "-shared --coverage")
endif()

