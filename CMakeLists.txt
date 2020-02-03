CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(tile_puzzle)

SET(EXEC_NAME tile_puzzle)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_BUILD_TYPE RelWithDebInfo)

FILE(GLOB classes_DIR "src/classes/*.h" "src/classes/*.cpp")
SET(PROG_SOURCES src/main.cpp ${classes_DIR})

ADD_EXECUTABLE(${EXEC_NAME} ${PROG_SOURCES})

