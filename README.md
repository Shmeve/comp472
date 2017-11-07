# COMP 472 - Deliverable 2

Team #4 - ProjectArmadillo

Authors:

Christopher Paslawski, 27445164  
Anita Haurie, 27498063  
Thomas Vaudry-Read, 27516517  
Steve Ferreira, 27477546  

Section: Fall 2017 - F

Date: November 6, 2017

We certify that this submission is the original work of members of the group and meets the Faculty's Expectations of Originality.

## Compilation instructions

**This project uses the C++11 standard, and you will need a recent compiler capable of supporting these features.**

This project uses CMake >=3.5 (https://cmake.org/) to generate build files for any platform. It can be installed on Linux or macOS using a package manager, or Windows using the official installer. Ensure it is added to your system PATH and accessible via command line.

Then, CMake can be used in the command line to generate build files for any environment desired.

1. `cd [path to assignment]`
2. `mkdir build`
3. `cd build`
4. `cmake -G "your generator here" ..`
    - Run `cmake -G` to see a list of possible generators, eg. `Xcode`, `Unix Makefiles`, versions of Visual Studio, etc.
5. Build the project using whichever build system you chose.
