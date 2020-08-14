add_library (ledctrl STATIC "")
target_sources(ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Src/ledctrl.c)
target_include_directories(ledctrl PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Inc)

target_link_libraries(ledctrl stm32_drivers)

target_compile_options(ledctrl PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(ledctrl PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:STM32F334x8 USE_HAL_DRIVER DEBUG>)
