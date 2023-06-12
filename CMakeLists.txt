project(pantry-io-communication)
cmake_minimum_required(VERSION 3.22)

set(LIBNAME pio-communicator)

enable_testing()

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)
