# YAMLParser
This project is developed as part of the master's thesis **YAML Based Input File Format For Finite Element Analysis**
at the Norwegian University of Science and Technology (NTNU). It contains a prototype program for parsing and emitting YAML based
input files for Finite Element Analysis (FEA). Additionally, it contains a converter from Bjørn Haugen's input file format for FEA to 
the YAML based format.


## Getting started
YAMLParser is based on *yaml-cpp*. To build yaml-cpp, go to the [yaml-cpp Github repository](https://github.com/jbeder/yaml-cpp) and
follow the How to Build instructions. After the build, *yaml-cpp* must be linked to this project. In Visual Studio, this is done by
adding the file path to the local *yaml-cpp* library both under **C/C++** and **Link** in the project property pages. When the project
is successfully linked to the *yaml-cpp* library, YAMLParser is ready to be built in Visual Studio.

## Built With
* C++
* [yaml-cpp](https://github.com/jbeder/yaml-cpp) - A parser and emitter for YAML files

## Acknowledgements
* Associate Professor Bjørn Haugen at NTNU. My supervisor for the master's thesis.
* Jesse Beder - Author of yaml-cpp
