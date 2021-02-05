cmake_minimum_required(VERSION 3.7.0)
project("png_manager")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/commonoptions.cmake)

conan_basic_setup()

include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_BOOST})

include_directories("include")

#add_executable(tests
#    ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/main.cpp
#)
#target_link_libraries( tests
#    ${CONAN_LIBS}
#)
#add_test(
#    NAME tests
#    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/tests
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
#)