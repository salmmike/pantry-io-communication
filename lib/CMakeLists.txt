set(LIBNAME ${PROJECT_NAME}lib)
set(INCDIR ${CMAKE_CURRENT_LIST_DIR}/include/)

set(LIBHEADERS
    ${INCDIR}/pantryio_bluetooth.h
    ${INCDIR}/pantryio_mqtt.h
    ${INCDIR}/pantryio_dbus_server.h
)

set(LIBSOURCES
    ${CMAKE_CURRENT_LIST_DIR}/pantryio_bluetooth.c
    ${CMAKE_CURRENT_LIST_DIR}/pantryio_mqtt.c
    ${CMAKE_CURRENT_LIST_DIR}/pantryio_dbus_server.c
)

include_directories(${INCDIR})
add_library(${LIBNAME} STATIC ${LIBSOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(glib REQUIRED IMPORTED_TARGET glib-2.0 gio-2.0)
pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquitto REQUIRED)

find_path(GLIB_INCLUDE_DIR NAMES glib.h PATH_SUFFIXES glib-2.0)

target_include_directories(${LIBNAME} PUBLIC
                           ${INCDIR}
                           PkgConfig::glib
                           PkgConfig::Mosquitto
                           bluetooth)

target_link_libraries(${LIBNAME} LINK_PUBLIC
                      PkgConfig::glib
                      PkgConfig::Mosquitto
                      bluetooth)

set(PATHNAME ${PROJECT_NAME})

target_compile_definitions(
    ${LIBNAME} PUBLIC
)
