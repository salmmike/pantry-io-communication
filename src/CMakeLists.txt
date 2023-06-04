
find_package(PkgConfig REQUIRED)
pkg_check_modules(glib REQUIRED IMPORTED_TARGET glib-2.0 gio-2.0)

set(SOURCES
    main.c
    pantryio_dbus_server.c)

set(INCLUDEDIR include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDEDIR})

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::glib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
