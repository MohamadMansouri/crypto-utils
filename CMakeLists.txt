cmake_minimum_required(VERSION 3.10)

project(VerifiableSA)

enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

include_directories(includes)


find_library(GMP_LIBRARY NAMES gmp)
find_library(GMPXX_LIBRARY NAMES gmpxx)

link_libraries(${GMP_LIBRARY} ${GMPXX_LIBRARY})


add_subdirectory(src)
add_subdirectory(testsuit)