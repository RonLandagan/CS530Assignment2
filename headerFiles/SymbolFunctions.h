/********************************************************************
Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: SymbolFunctions.h
Notes: This header file contains the declaration of functions that
        are necessary to analyze and use information found in the
        symbol table.

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
function: isLiteral
Notes: Checks to see if a passed in address is a literal found in the .sym file
        and returns a boolean value of whether or not it is found

@param currentAddress A string of the current Address
@param filename A string of the name of the sym file
@return A boolean value of whether the current address holds a literal
*******************************************************************************/
bool isLiteral(string currentAddress, string filename);

/*******************************************************************************
function: getLiteral
Notes: Takes in a full instruction, the current address, and the filename of 
        the sym file, and returns the full statement to insert into the lis 
        file.

@param textRecord A string of the full instruction
@param currentAddress A string of the current Address
@param filename A string of the name of the sym file
@return A string of the full statement to be inserted
*******************************************************************************/
string getLiteral(string textRecord, string currentAddress, string filename);

/*******************************************************************************
function: getLiteralLength
Notes: Takes in a full instruction, the current address, and the filename of 
        the sym file, and returns the length of the literal

@param textRecord A string of the full instruction
@param currentAddress A string of the current Address
@param filename A string of the name of the sym file
@return The size of the literal
*******************************************************************************/
int getLiteralLength(string textRecord, string currentAddress, string filename);

/*******************************************************************************
function: createMapOfSymbols
Notes: Takes in the name of the sym file and returns an ordered map of each 
        symbol and its value.

@param filename A string of the name of the sym file
@return An ordered map of each symbol and their values
*******************************************************************************/
map<string,string> createMapOfSymbols(string filename);

/*******************************************************************************
function: removeWrittenSymbols
Notes: Takes in a map of symbols and the name of the sym file and returns an 
        ordered map of symbols and values that haven't already been written
        into the lis file.

@param sym An ordered map of all of the symbols in the sym file
@param filename A string of the name of the lis file
@return An ordered map of new symbols and their values
*******************************************************************************/
map<string,string> removeWrittenSymbols(map<string,string> sym, string filename);

/*******************************************************************************
function: insertSymbol
Notes: Takes in the address and label of a specific symbol and inserts it 
        into a lis file

@param address A string of the address of the symbol
@param label A string of the name of the symbol
@param filename A string of the name of the lis file
*******************************************************************************/
void insertSymbol(string address, string label, string filename);

/*******************************************************************************
function: addRemainingSymbols
Notes: Takes in the name of the lis and sym files and writes in the symbols
        that are missing in the lis file

@param filename A string of the name of the lis and sym files
*******************************************************************************/
void addRemainingSymbols(string filename);
