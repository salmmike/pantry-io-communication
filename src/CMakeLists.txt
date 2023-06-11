
set(SOURCES
    main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBNAME})

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
