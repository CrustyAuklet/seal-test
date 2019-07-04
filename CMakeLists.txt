cmake_minimum_required(VERSION 3.13)
project(TestSeal 
        LANGUAGES C CXX )

add_subdirectory(seal-device)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        seal-device
)

target_sources(${PROJECT_NAME}
    PUBLIC
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
            SUFFIX ".elf"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.bin
        COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}"
)
