
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(pio_bluetooth_test pio_bluetooth_test.cpp)
target_link_libraries(pio_bluetooth_test
                      PRIVATE
                      GTest::GTest
                      ${LIBNAME}
                      )
add_test(pio_bluetooth_test pio_bluetooth_test)