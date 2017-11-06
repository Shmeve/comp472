# COMP 472 - Deliverable 2

Team #4 - ProjectArmadillo

Authors:

Thomas Vaudry-Read, 27516517  
Christopher Paslawski, 27445164  
Steve Ferreira, 27477546  
Anita Haurie, 27498063  

Section: Fall 2017 - F

Date: November 6, 2017

## Usage

```
Team 11 - Bonzee
Usage:
  Armadillo [OPTION...]

  -h, --help            Help
  -w, --wait            Wait for debugger to attach
  -g, --green arg       Green player type
  -r, --red arg         Red player type
  -d, --depth arg       Tree search depth for both players (shortcut)
  -G, --greendepth arg  Tree search depth for Red player
  -R, --reddepth arg    Tree search depth for Green player
```

## Compilation instructions

**This project uses the C++11 standard, and you will need a recent compiler capable of supporting these features.**

This project uses CMake >=3.6 (https://cmake.org/) to generate build files for any platform. It can be installed on Linux or macOS using a package manager, or Windows using the official installer. Ensure it is added to your system PATH and accessible via command line.

Then, CMake can be used in the command line to generate build files for any environment desired.

1. `cd [path to assignment]`
2. `mkdir build`
3. `cd build`
4. `cmake -G "your generator here" ..`
    - Run `cmake -G` to see a list of possible generators, eg. `Xcode`, `Unix Makefiles`, versions of Visual Studio, etc.
5. Build the project using whichever build system you chose.
