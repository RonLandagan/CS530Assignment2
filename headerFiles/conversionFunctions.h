/********************************************************************
Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: conversionFunctions.h
Notes: This header file contains the declaration of functions that
        are necessary to convert and manipulate different data types 
        used in the dissassembler.

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
function: toUpper
Notes: Returns a string with all capital letters.

@param hexValue The string to turn into uppercase
@return The uppercase form of the string
*******************************************************************************/
string toUpper(string str);

/*******************************************************************************
function: hexToDecimal
Notes: Takes in a hex value and returns its integer equivalent

@param hexValue The string to turn into a decimal
@return Decimal form of the passed-in number
*******************************************************************************/
int hexToDecimal(string hexValue);

/*******************************************************************************
function: decimalToHex
Notes: Takes in an integer and returns its HEX equivalent

@param decimalValue Integer number to turn into hex
@return Hex form of the passed-in number
*******************************************************************************/
string decimalToHex(int decimalValue);

/*******************************************************************************
function: strToBin
Notes: Takes in a string in a hex format, and returns its binary 
    equivalent.

@param str A string in hex format
@return The equivalent in binary format
*******************************************************************************/
string strToBin(string str);

/*******************************************************************************
function: binToStr
Notes: Takes in a string in a binary format, and returns its hex 
    equivalent.

@param str A string in binary format
@return The equivalent in hex format
*******************************************************************************/
string binToStr(string bin);

/*******************************************************************************
function: hexToDec
Notes: Takes in a string of a value in HEX and returns its decimal equivalent.

@param disp The HEX value to convert
@return The converted decimal value
*******************************************************************************/
int hexToDec(string disp);

/*******************************************************************************
function: twosCompliment
Notes: Performs a 2s compliment conversion of passed in HEX value, and returns
        the result.

@param hexNum The value to convert in a HEX format
@return Converted HEX value
*******************************************************************************/
string twosCompliment(string hexNum);
