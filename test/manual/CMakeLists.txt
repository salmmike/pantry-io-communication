find_package(PkgConfig REQUIRED)
pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquitto REQUIRED)

set(MANUALTEST mqtt_publisher)

set(SOURCES
    mqtt_publisher.c)

add_executable(${MANUALTEST} ${SOURCES})

target_link_libraries(${MANUALTEST} PRIVATE PkgConfig::Mosquitto)
