/********************************************************************
Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: formattingFunctions.h
Notes: This header file contains the declaration of functions that
        are necessary to format different data types used in the 
        dissassembler.

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
function: formatAddress
Notes: Takes in a string of an address in HEX and formats it for writing into
        the LIS file.

@param address The address to format
@return Formatted address
*******************************************************************************/
string formatAddress(string address);

/*******************************************************************************
function: formatInstructionName
Notes: Takes in a string of an instruction mnemonic and formats it for writing 
        into the LIS file by making the total string length 6 characters.

@param instructionName The name to format
@return Formatted instruction mnemonic
*******************************************************************************/
string formatInstructionName(string instructionName);

/*******************************************************************************
function: formatOperand
Notes: Takes in a string of an operand and formats it for writing into the  LIS
        file by making the total string length 9 characters.

@param operand The operand to format
@return Formatted operand
*******************************************************************************/
string formatOperand(string operand);
