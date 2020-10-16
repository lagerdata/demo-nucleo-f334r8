include(../../../cmake/utils.cmake)

add_executable(test-example "")
target_sources(test-example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main_test.c
  ${CMAKE_CURRENT_LIST_DIR}/test_example.c)
target_include_directories(test-example PRIVATE ${CMAKE_CURRENT_LIST_DIR})

set(CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../Core)
target_sources(test-example PRIVATE ${CORE_DIR}/Src/stm32f3xx_hal_msp.c
  ${CORE_DIR}/Src/stm32f3xx_it.c
  ${CORE_DIR}/Src/syscalls.c
  ${CORE_DIR}/Src/sysmem.c
  ${CORE_DIR}/Src/system_stm32f3xx.c
  ${CORE_DIR}/Startup/startup_stm32f334r8tx.s)

target_include_directories(test-example PRIVATE ${CORE_DIR}/Inc)


target_link_libraries(test-example stm32_drivers)


set(UNITY_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Unity/src)
target_sources(test-example PRIVATE ${UNITY_SRC_DIR}/unity.c
  ${CMAKE_CURRENT_LIST_DIR}/../../unity_config.c)
target_include_directories(test-example PRIVATE ${UNITY_SRC_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../)



target_compile_options(test-example PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(test-example PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(test-example PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(test-example PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(test-example PRIVATE $<$<COMPILE_LANGUAGE:C>:STM32F334x8 USE_HAL_DRIVER UNITY_INCLUDE_CONFIG_H DEBUG>)

target_link_directories(test-example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../../)
target_link_options(test-example PRIVATE -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group -static --specs=nano.specs -TSTM32F334R8TX_FLASH.ld)


firmware_size(test-example)
generate_object(test-example .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(test-example .hex ihex)
endif()
