include(../cmake/utils.cmake)

add_executable(test-ledctrl "")
target_sources(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main_test.c)
target_include_directories(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR})

set(CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/../Core)
target_sources(test-ledctrl PRIVATE ${CORE_DIR}/Src/stm32f3xx_hal_msp.c
  ${CORE_DIR}/Src/stm32f3xx_it.c
  ${CORE_DIR}/Src/syscalls.c
  ${CORE_DIR}/Src/sysmem.c
  ${CORE_DIR}/Src/system_stm32f3xx.c
  ${CORE_DIR}/Startup/startup_stm32f334r8tx.s)

target_include_directories(test-ledctrl PRIVATE ${CORE_DIR}/Inc)


target_link_libraries(test-ledctrl stm32_drivers)
target_link_libraries(test-ledctrl ledctrl)

set(UNITY_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/Unity/src)
target_sources(test-ledctrl PRIVATE ${UNITY_SRC_DIR}/unity.c
  ${CMAKE_CURRENT_LIST_DIR}/unity_config.c)
target_include_directories(test-ledctrl PRIVATE ${UNITY_SRC_DIR})

set(TEST_LED_SUITE_DIR ${CMAKE_CURRENT_LIST_DIR}/test_suites/test_ledctrl)
target_sources(test-ledctrl PRIVATE ${TEST_LED_SUITE_DIR}/test_ledctrl.c)
target_include_directories(test-ledctrl PRIVATE ${TEST_LED_SUITE_DIR})


target_compile_options(test-ledctrl PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(test-ledctrl PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:STM32F334x8 USE_HAL_DRIVER UNITY_INCLUDE_CONFIG_H DEBUG>)

target_link_directories(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../)
target_link_options(test-ledctrl PRIVATE -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group -static --specs=nano.specs -TSTM32F334R8TX_FLASH.ld)


firmware_size(test-ledctrl)
generate_object(test-ledctrl .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(test-ledctrl .hex ihex)
endif()
