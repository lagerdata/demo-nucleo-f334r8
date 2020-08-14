add_library (stm32_drivers STATIC "")


target_sources(stm32_drivers PRIVATE ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c)


set(CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/../Core)
target_include_directories(stm32_drivers PUBLIC ${CORE_DIR}/Inc)

target_include_directories(stm32_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Inc)
target_include_directories(stm32_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/STM32F3xx_HAL_Driver/Inc/Legacy)

target_include_directories(stm32_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32F3xx/Include)
target_include_directories(stm32_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include)

target_compile_options(stm32_drivers PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(stm32_drivers PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(stm32_drivers PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(stm32_drivers PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(stm32_drivers PRIVATE $<$<COMPILE_LANGUAGE:C>:STM32F334x8 USE_HAL_DRIVER DEBUG>)
