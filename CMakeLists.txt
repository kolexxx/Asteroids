cmake_minimum_required(VERSION 3.18.0)
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)
project(Asteroids)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

file(GLOB SOURCE src/*.cpp src/Math/*.cpp)
file(GLOB HEADERS src/*.hpp src/Math/*.hpp)
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})
add_subdirectory(extern)