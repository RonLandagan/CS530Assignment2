/********************************************************************
Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: LISFunctions.h
Notes: This header file contains the declaration of functions that
        are necessary to build the LIS file from the SYM and OBJ
        files.

********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>

/*******************************************************************************
function: findLabel
Notes: Opens symbol table and looks for a label that matches the passed-in 
    address. If found, it returns the Symbol. Else, it returns a string of 
    6 spaces.

@param address The address to find in the symbol table
@param filename The name of the symbol table to open
@return Symbol being searched for
*******************************************************************************/
string findLabel(int address, string filename);

/*******************************************************************************
function: findProperLine
Notes: Takes in a string of an address in HEX and searches the lis file of the 
        filename and finds and resturns the correct line to insert the statement

@param address The address of the statement to insert
@param filename The name of the LIS file to read
@return The line number to insert at
*******************************************************************************/
int findProperLine(string symAddress, string filename);

/*******************************************************************************
function: setBaseRegister
Notes: Takes in a string of an address in HEX and writes it into the 
        baseRegister.txt file

@param value The value to write into the base register file
*******************************************************************************/
void setBaseRegister(string value);

/*******************************************************************************
function: getBaseRegister
Notes: Reads the baseRegister.txt file and returns its contents.

@param value The value found in the base register file
*******************************************************************************/
string getBaseRegister();

/*******************************************************************************
function: insertLineInLisFile
Notes: Inserts a given string into the passed in location of the passed in LIS 
        file.

@param properLine The line location to insert newLine
@param newLine The statement to insert into the LIS file
@param filename The name of the LIS file to write into
*******************************************************************************/
void insertLineInLisFile(int properLine, string newLine, string filename);

/*******************************************************************************
function: insertLine
Notes: Inserts the full passed in statement into the passed in LIS file

@param newLine The full statement to pass into the LIS file
@param filename The name of the LIS file to write into
*******************************************************************************/
void insertLine(string newLine, string filename);

/*******************************************************************************
function: findDeleteLine
Notes: Finds and returns the number line that matches the passed in address in 
        the passed in LIS file

@param addressToDelete The address of the line to delete
@param filename The name of the LIS file to read through
@return The line number of the matched address
*******************************************************************************/
int findDeleteLine(string addressToDelete, string filename);

/*******************************************************************************
function: deleteLineInLisFile
Notes: Deletes the line found in the passed in line number in the passed in
        LIS file.

@param deleteLine The line number of the line to be deleted
@param filename The LIS file to delete the line
*******************************************************************************/
void deleteLineInLisFile(int deleteLine, string filename);

/*******************************************************************************
function: deleteLine
Notes: Deletes the line found in the passed in address from the passed in LIS
        file.

@param addressToDelete The address found at the beginn of the line to delete
@param filename The name of the LIS file to delete from
*******************************************************************************/
void deleteLine(string addressToDelete, string filename);

/*******************************************************************************
function: ReadHeaderRecord
Notes: Takes in the header record as a string and the filename. Then the 
    header record is parsed, analyzed, and its LIS equivalent is written
    in the LIS file.

@param headerRecord Full header record to parse and analyze
@param filename Filename of LIS file to write into
*******************************************************************************/
void ReadHeaderRecord(string headerRecord, string filename);

/*******************************************************************************
function: getInstructionLength
Notes: Takes in a string of a textRecord and returns the length of the 
    first instruction.

@param textRecord A line of a textRecord
@return The length of the first instruction
*******************************************************************************/
int getInstructionLength(string textRecord);

/*******************************************************************************
function: getInstructionName
Notes: Takes in a string of a full instruction and returns its mnemonic.

@param str A string of a full instruction
@return The instruction's mnemonic
*******************************************************************************/
string getInstructionName(string fullObjectCode);

/*******************************************************************************
function: getRegister
Notes: Takes in a register number and returns it's name

@param registerNumber The number of register
@return The equivalent register name
*******************************************************************************/
string getRegister(char registerNumber);

/*******************************************************************************
function: getOperandFormat2
Notes: Takes in a string of the full object code of an instruction
    in format 2 and returns its operand.

@param str A string of a full format 2 instruction
@return The operand of the instruction
*******************************************************************************/
string getOperandFormat2(string fullObjectCode);

/*******************************************************************************
function: getInstructionFlags
Notes: Takes in a string of the full object code of an instruction
    in format 3/4 and returns a string of its set flags.

@param str A string of a full format 3/4 instruction
@return A string of flags and their setting
*******************************************************************************/
string getInstructionFlags(string fullObjectCode);

/*******************************************************************************
function: getOperandPC
Notes: Takes in a string of a full instruction and its address and returns the 
        appropriate operand through the Program-counter addressing mode.

@param fullObjectCode The full instruction in the form of object code
@param currentAddress The instruction's address
@param filename The name of the symbol table to read through
@return The name of the appropriate operand
*******************************************************************************/
string getOperandPC(string fullObjectCode, string currentAddress, string filename);

/*******************************************************************************
function: getOperandBase
Notes: Takes in a string of the full object code and filename and finds the 
    operand using base relative addressing

@param fullObjectCode The full instruction in the form of object code
@param filename The name of the base register file to read
@return The name of the appropriate operand
*******************************************************************************/
string getOperandBase(string fullObjectCode, string filename);

/*******************************************************************************
function: getOperandDirect
Notes: Takes in a string of a full instruction and its address and returns the 
        appropriate operand through the direct addressing mode.

@param fullObjectCode The full instruction in the form of object code
@return The name of the appropriate operand
*******************************************************************************/
string getOperandDirect(string fullObjectCode);

/*******************************************************************************
function: getOperandFormat4
Notes: Takes in a string of a full, format 4 instruction and returns the 
        appropriate operand 

@param fullObjectCode The full instruction in the form of object code
@param filename The name of the symbol table to read through
@return The name of the appropriate operand
*******************************************************************************/
string getOperandFormat4(string fullObjectCode, string filename);

/*******************************************************************************
function: getOperandFormat3
Notes: Takes in a string of the full object code of an instruction
        in format 3 and returns its operand.

@param fullObjectCode A string of a full format 3 instruction
@param currentAddress A string of the current address
@param filename The name of the sym file
@return The operand of the instruction
*******************************************************************************/
string getOperandFormat3(string fullObjectCode, string currentAddress, string filename);

/*******************************************************************************
function: getTargetAddress
Notes: Takes in a string of the full object code of an instruction
         in format 3 and returns target address.

@param fullObjectCode A string of a full instruction
@param currentAddress A string of the current address
@return The target address of the instruction
*******************************************************************************/
string getTargetAddress(string fullObjectCode, string currentAddress);

/*******************************************************************************
function: getInstructionAndOperand
Notes: Takes in a string of the text record, current address, and file name
        and returns the full formatted line to go into the LIS file

@param textRecord A string of a full format 3 instruction
@param currentAddress A string of the current address
@param filename A string of the file name of the sym file
@return The full line to insert into the lis file
*******************************************************************************/
string getInstructionAndOperand(string textRecord, string currentAddress, string filename);


