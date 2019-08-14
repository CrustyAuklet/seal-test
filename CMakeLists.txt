cmake_minimum_required(VERSION 3.13)
project(TestSeal
        LANGUAGES C CXX )

# add the CMSIS module to this project.
# this module provided CMSIS headers and startup code, based on the cache variable DEVICE_TYPE
# currently valid device types are SAML21, SAMD21, SAMD51.
# Provide the entire device name ex: SAML21G18B (the default)
add_subdirectory(seal-device)

# create this project as a binary
add_executable(${PROJECT_NAME} main.cpp)

## All the following is PUBLIC. This isn't really necessary since that is the default
## but I like to be explicit. In reality it doesn't matter since this is an executable not a library

# This project shoudl use C++17 features
target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

# consume the PUBLIC and INTERFACE properties, includes, and sources from seal-device
# seal-device is actually two layers of INTERFACE libraries, to mimic CMSIS layers
# all properties are transitive though, so our project gets everything it needs
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        seal-device
)

# declare this projects sources (none right now). main.cpp could go here, but some
# CMake parsers don't like an add_executable() call with no sources.
target_sources(${PROJECT_NAME}
    PUBLIC
)

# change the extension of the executable to elf
set_target_properties(${PROJECT_NAME}
        PROPERTIES
            SUFFIX ".elf"
)

# create a HEX and BIN file from the ELF file each time we compile
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.bin
        COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}"
)
