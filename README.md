# Lager Demo Project for NUCLEO-F334R8 Development Kits
## Project Description
This is a demo project for the stm32F3xx MCU that helps users to learn the many different features of the Lager CLI tool.  
With this demo, users can:  
1. Learn how to build a project inside a docker container
2. Remotely flash and run an application on a DUT (in this case the NUCLEO-F334R8 board)
3. See how unit testing can be incorporated into their work flow via the Unity Testing Framework
4. Set up a continuous integration pipeline

## Pre-requisite
Before experimenting with this project there are a couple of pre-requisites  
1. Install docker client for your operating system (https://www.docker.com/products/docker-desktop)
2. Install Lager's CLI tool:  
`pip3 install lager-cli`
  

## Build Instructions
A Lager environment with build instructions is included in this repository.  
To build the project simply run:  
`lager exec build`  
This will build all the targets in this project.  
To see the different build options run:  
`lager devenv commands`  
If you would like to create a development environment from scratch do the following:  
`lager devenv delete` This deletes the current development environment  
`lager devenv create` This creates a new development environment.  
This will instruct users to choose a development environment image (e.g. cortex-m, stm32, ti, etc), where to mount their project in the docker container, and what shell type to use. For this project the default settings are OK. 
 
*Note: In order to use Github Actions you'll need to mount the repo into `/github/workspace` NOT the default `/app`*  
*Note: Go to https://hub.docker.com/u/lagerdata to view other development environments supported by Lager*  
  
To create a new build command run:  
`lager exec --command "user defined build command" --save-as user-defined-shortcut `  

For example, to build this project using CMake + Ninja a user can define the following:  
`lager exec --command "mkdir _build;cd _build;cmake .. -G Ninja;cmake --build ." --save-as build`  
Moving forward a user could then run `lager exec build` 
 
Similarly, to clean this project a user can define the following: 
`lager exec --command "cd _build;ninja -t clean" --save-as clean` 
And then run: 
`lager exec clean` 

Or to build this project using the STM32CUBEIDE's gcc compiler a user can define the following:  
`lager exec --command "headless-build.sh -build demo-nucleo-f334r8 -importAll /app" --save-as build-cube`  
Moving forward a user could then run `lager exec build-cube`  


## Flashing The Board
#### Connect To board
To flash a board first connect the Lager Gateway to the NUCLEO-F334R8 development board.  
There are two options to do this:  
1. USB2.0 - This will allow users to use the ST-Link debug probe built into the NUCLEO-F334R8 development board
2. Cortex-Debug 20 Pin header on Gateway - This allows users to use the built-in FTDI debug probe on the Gateway but will require breaking out the SWD pins on the development board.

  
Then run:  
`lager connect --device stm32f3x --interface stlink --transport hla_swd --speed 480`  
or if using built-in debug probe  
`lager connect --device stm32f3x --interfact ftdi --transport hla_swd --speed 480`  
  
#### Flash Image
To flash the board with the project application run the following:  
`lager flash --hexfile _build/Core/app.hex`  
To execute the program run:  
`lager run`  

## Unit Tests
To run an example unit-test for this project run the following:  
`lager testrun --serial-device /dev/ttyACM0 --hexfile _build/Unit-Tests/test_suites/test_example/test-example.hex`  
The results of the individual tests will be streamed back to the terminal.  
  
## Github Actions
To setup a pipeline using Github Actions you need to have the folder structure `.github/workspace` at the top level of the repository. 
Inside the workspace folder place a .yml file telling github how to build and run your project. 
This demo includes a sample yml file that does the following: 
1) Pull any submodules 
2) Pull the desired docker image 
3) Build the project using a build command defined in the .lager file
4) Run a unit test using 
5) Run a system test using lager python 
