Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: README.txt
Notes: This is the README file that comes with the 
	turned-in assignment. This disassembler program 
    will take in two files: an XE object file and 
    its accompanying symbol file. From these two files, 
    the disassembler will reverse-engineer the software 
    such that it generates two additional files: an XE 
    source file and an XE listing file. If the required 
    files aren’t available, then the program will exit.

Files Included:
-assignment2.cpp
-header files:
    -InstructionSet.h
    -conversionFunctions.h
    -conversionFunctions.cpp
    -formattingFunctions.h
    -formattingFunctions.cpp
    -LISFunctions.h
    -LISFunctions.cpp
    -SymbolFunctions.h
    -SymbolFunctions.cpp
-makefile
-README.txt
-SoftwareDesignDocument.docx

To Compile:
1) Open command prompt and navigate to appropriate folder.
	(Should have assignment2.cpp and other included files)
2) Type "make" to run the makefile and compile the program.

To Operate:
1) Include an XE object file, <filename>.obj and its
    accompanying symbol file, <filename>.sym, in the same
    folder as the makefile. 
2) To generate the XE source file and listing file, type 
    "dxe <filename>", without the brackets.

While writing this program I found that my favorite piece
    was writing the "insertLine" function found in the
    LISFunctions.h header file. Being able to write the
    LIS file by simply inserting a full statement beginning
    with its address made the project much easier.

I know that seperating my functions into seperate header
    files wasn't necessary, but I feel that organizing
    them by functionality makes the project easier to
    parse through.

The instruction "RSUB" results in an operand of "0" 
    instead of a blank space. Also, the sample files 
    that were provided didn't work properly, so I used the 
    example found in Figure 2.8 on page 65 of the textbook
    as my test file. I wrote its accompanying SYM file.

This was the largest project I have ever worked on, 
    totaling to over 1800 lines of code! I am very proud
    of the team for being able to pull something like this
    off. The most important lesson that I've learned from
    this project is the value of early organization, and 
    making sure to put in the effort during pre-production.
I should have definitely put more time into perfecting the
    algorithm that this program would run, because halfway
    through, some adjustments had to be made on the fly.
