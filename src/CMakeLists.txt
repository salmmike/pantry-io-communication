
set(SOURCES
    main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}lib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
