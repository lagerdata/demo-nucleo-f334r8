cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(demo-nucleo-f334r8 VERSION 1.0 LANGUAGES C ASM)


# Location of application specific code
add_subdirectory(Core)
# Location of test code. These will be run on deploys
add_subdirectory(Unit-tests)

# Location of STM32 Drivers
add_subdirectory(Drivers)

#Location of standalone/reusable modules
add_subdirectory(modules)
