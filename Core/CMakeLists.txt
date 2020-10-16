include(../cmake/utils.cmake)

add_executable(app "")
target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f3xx_hal_msp.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f3xx_it.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/syscalls.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/sysmem.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/system_stm32f3xx.c
  ${CMAKE_CURRENT_LIST_DIR}/Startup/startup_stm32f334r8tx.s)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Inc)


target_link_libraries(app stm32_drivers)
target_link_libraries(app shell)


target_compile_options(app PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(app PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(app PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(app PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(app PRIVATE $<$<COMPILE_LANGUAGE:C>:STM32F334x8 USE_HAL_DRIVER DEBUG>)

target_link_directories(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../)
target_link_options(app PRIVATE -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group -static --specs=nano.specs -TSTM32F334R8TX_FLASH.ld)


firmware_size(app)
generate_object(app .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(app .hex ihex)
endif()
