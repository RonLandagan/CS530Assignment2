# CS530Assignment2
A disassembler program for a SIC/XE machine
Overview & Goals:

The goal of this project is to develop, test, and deliver a disassembler program for the XE variant of the SIC/XE family of machines. This process will take place over the course of seven weeks, and should include C++ source files, header files, a Makefile, and a README file.

Project Description:

The disassembler program will take in two files: an XE object file and its accompanying symbol file. From these two files, the disassembler will reverse-engineer the software such that it generates two additional files: an XE source file and an XE listing file. If the required files aren’t available, then the program will exit. 

The main program will consist of a reader that will read the XE object file, and translate each instruction, step-by-step, writing the XE listing file and referring to the symbol file when necessary. After the listing file has been fully written, it will be modified to create the XE source file.
