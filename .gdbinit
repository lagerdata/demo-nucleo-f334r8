#
#
########################################
# This connects to a GDB Server listening
# for commands on localhost at tcp port 3333
target remote localhost:3333
########################################


########################################

########################################





########################################
# Reset the chip to get to a known state.
monitor reset halt



########################################


# Load the program executable called "image.elf"
#####If building with STM32Cube
#file Test/demo-nucleo-f334r8_test.elf

#####If building with cmake+ninja
file _build/Core/app
load
break main
