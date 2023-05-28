
find_package(PkgConfig REQUIRED)
pkg_check_modules(glib REQUIRED IMPORTED_TARGET glib-2.0 gio-2.0)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::glib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
