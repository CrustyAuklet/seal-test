## Bare Bones Seal example project

This project demonstrates a blinky project on a SAML21G18B using the Seal-device cmsis package.

## Why CMake

Many IDEs will use CMake as a source for projects. This allows the benifits of an IDE, while still allowing a developer to quickly drop into the command line for manual building and Continous Integration / testing. Since the CMakeLists.txt files serves as a single source of truth for the project structure developers can make thier own decision on what to use for development: IDE, editor, command line based on preference, the given task, or how they feel that day.

CMake also allows for a modular project design. This project, for example, consumes another CMake project (as a git submodule) to get CMSIS headers and startup files. This project does not need to know the implementation, it simply provides the device name it is using and the proper linker files, startup files, and headers are provided. This should allow for a project to be cross compiled across many devices (several differnt Arm cortex-M devices), as well as on a completely different architecture (windows/linux simulator). Implementations need to be provided in the CMSIS module, but the project itself shouldn't care.

## Purpose

This is a very simple project that aims to show how CMake can be used to acomplish the promise of CMake. It is also meant to test different development environments to see how well they handle a CMake based embedded project, and debugging that project.

Editor files for the following IDEs are commited to this repo to show how the varies IDEs that have been tested so far are set up.
Edior files included:
  * VSCode
  * Visual Studio 2019 (with CMake Support)
  * Clion

The branch `noConfig` mirrors this branch but with no config files, to allow setting up an environment from scratch.
