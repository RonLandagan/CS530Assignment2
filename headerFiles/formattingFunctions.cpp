#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>

string formatAddress(string address){
    stringstream ss;
    string result;
    //Trims down address to 4 least significant bits
    if(address.length() > 4)
        address = address.substr(address.length()-4,4);
    //Formats so that address is 4 characters wide and filled with 0s.
    ss << setfill('0') << setw(4) << address;
    ss >> result;
    return result;
}

string formatInstructionName(string instructionName){
    string formattedInstructionName = "      ";

    for(int i = 0; i < 6; i++){
        if(i < instructionName.length())
            formattedInstructionName[i] = instructionName[i];
        else
            formattedInstructionName[i] = ' ';
    }
    return formattedInstructionName;
}

string formatOperand(string operand){
    string formattedOperand = "         ";

    for(int i = 0; i < 9; i++){
        if(i < operand.length())
            formattedOperand[i] = operand[i];
        else
            formattedOperand[i] = ' ';
    }
    return formattedOperand;
}


