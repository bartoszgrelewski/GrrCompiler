# Grrompilator, compilator of a simple imperative language

## How to run the project
1. You have to write in terminal: `make`, which will compile the project.
2. When compilation is done the `compiler` run-file will be created in the `GrrCompiler` folder. Outside `build` and `src` folders of course.
3. Then type in `./compiler <file_name> <file_output>` -> the output of the program will be in the file which name you have given in the second argument. It would be an assembly code of the program after compilation.
4. You have to compile virtual machine as well.
5. Finally, type in `./vm <file_output>` to run the program in virtual machine. The output of the program will be in the terminal.

## MAKEFILE
I have also other makefile commands, which are: 
* `make` - it will compile the project and run the program in virtual machine.
* `make debug` - it will compile the project with debug mode.
* `make clean` - it will remove all the files which are created during the compilation process.

## Utils
* bison (GNU Bison) 3.8.2
* flex 2.6.4
* GNU Make 4.3
* g++ 11.3.0

## Quick overview of files and folders structure

### Src
It has all the source files of the project.

### Build
It has all the files which are being created during the compilation of the project. It won't createe automatically so you have to create it manually if you already don't have it, but I included it so you don't have to create it. It is necessary to have this folder, otherwise the project won't compile, since the compilation process creates some files in this folder and then links them with the rest of the project files and makefile will throw that there is no folder like `build`.

## Overview of the project logic
The project is divided into two parts:
* Compiler - it reads the program written in the language and creates an assembly code of the program.
* Virtual machine - it reads the assembly code and runs the program. 




## Authors
* [Bartosz Grelewski](https://github.com/bartoszgrelewski) - compiler 
* [Dr Maciej Gębala](https://cs.pwr.edu.pl/gebala/) - virtual machine and assignment