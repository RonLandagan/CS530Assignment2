#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>
#include "InstructionSet.h"

using namespace std;

/*******************************************************************************
function: formatAddress
Notes: Takes in a string of an address in HEX and formats it for writing into
        the LIS file.

@param address The address to format
@return Formatted address
*******************************************************************************/
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

/*******************************************************************************
function: formatInstructionName
Notes: Takes in a string of an instruction mnemonic and formats it for writing 
        into the LIS file by making the total string length 6 characters.

@param instructionName The name to format
@return Formatted instruction mnemonic
*******************************************************************************/
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

/*******************************************************************************
function: formatOperand
Notes: Takes in a string of an operand and formats it for writing into the  LIS
        file by making the total string length 9 characters.

@param operand The operand to format
@return Formatted operand
*******************************************************************************/
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

/*******************************************************************************
function: toUpper
Notes: Returns a string with all capital letters.

@param hexValue The string to turn into uppercase
@return The uppercase form of the string
*******************************************************************************/
string toUpper(string str){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/*******************************************************************************
function: hexToDecimal
Notes: Takes in a hex value and returns its integer equivalent

@param hexValue The string to turn into a decimal
@return Decimal form of the passed-in number
*******************************************************************************/
int hexToDecimal(string hexValue){
    unsigned int x;
    stringstream ss;
    ss << std::hex << hexValue;
    ss >> x;
    return x;
}

/*******************************************************************************
function: decimalToHex
Notes: Takes in an integer and returns its HEX equivalent

@param decimalValue Integer number to turn into hex
@return Hex form of the passed-in number
*******************************************************************************/
string decimalToHex(int decimalValue){
    string result;
    stringstream ss;
    ss << std::hex << decimalValue;
    ss >> result;
    result = toUpper(result);
    return result;
}

/*******************************************************************************
function: findProperLine
Notes: Takes in a string of an address in HEX and searches the lis file of the 
        filename and finds and resturns the correct line to insert the statement

@param address The address of the statement to insert
@param filename The name of the LIS file to read
@return The line number to insert at
*******************************************************************************/
int findProperLine(string symAddress, string filename){
    ifstream readLisFile;
    readLisFile.open(filename + ".lis");
    string line;
    int lineCounter = 1;
    int currentAddress;
    int currentSymAddress;
    while(getline(readLisFile, line)){
        currentAddress = hexToDecimal(line.substr(0,4));
        currentSymAddress = hexToDecimal(symAddress);

        if(currentAddress > currentSymAddress)
            break;
        lineCounter++;
        
    }
    readLisFile.close();
    return lineCounter;
}


void setBaseRegister(string value){
    ofstream writeBaseRegisterFile;
    writeBaseRegisterFile.open("baseRegister.txt");
    writeBaseRegisterFile << value;
}


string getBaseRegister(){
    ifstream readbaseRegisterFile;
    readbaseRegisterFile.open("baseRegister.txt");
    string line;
    getline(readbaseRegisterFile, line);
    return line;
}


/*******************************************************************************
function: insertLineInLisFile
Notes: Inserts a given string into the passed in location of the passed in LIS 
        file.

@param properLine The line location to insert newLine
@param newLine The statement to insert into the LIS file
@param filename The name of the LIS file to write into
*******************************************************************************/
void insertLineInLisFile(int properLine, string newLine, string filename){
    ifstream readLisFile;
    readLisFile.open(filename + ".lis");
    string line;    
    vector<string> lisFileVector;
    
    // Read the lis file and get to the proper line
    for(int i=1; i<properLine; i++){
        getline(readLisFile, line);
        lisFileVector.push_back(line + "\n");
    }
    // Insert the new line
    lisFileVector.push_back(newLine + "\n");

    // Read the rest of the lis file
    while(getline(readLisFile, line)){
        lisFileVector.push_back(line + "\n");
    }

    // Read entire lis file into vector
    while(getline(readLisFile, line)){
        lisFileVector.push_back(line + "\n");
    }
    readLisFile.close();

    
    // Write the vector back into the lis file
    ofstream writeLisFile;
    writeLisFile.open(filename + ".lis");
    
    string test;
    while(!lisFileVector.empty()){
        writeLisFile << lisFileVector.front();
        lisFileVector.erase(lisFileVector.begin());
    }
    writeLisFile.close();
}

/*******************************************************************************
function: insertLine
Notes: Inserts the full passed in statement into the passed in LIS file

@param newLine The full statement to pass into the LIS file
@param filename The name of the LIS file to write into
*******************************************************************************/
void insertLine(string newLine, string filename){
    
    string newLineAddress = newLine.substr(0,4);
    int properLine = findProperLine(newLineAddress, filename);
    
    insertLineInLisFile(properLine, newLine, filename);

}

/*******************************************************************************
function: findDeleteLine
Notes: Finds and returns the number line that matches the passed in address in 
        the passed in LIS file

@param addressToDelete The address of the line to delete
@param filename The name of the LIS file to read through
@return The line number of the matched address
*******************************************************************************/
int findDeleteLine(string addressToDelete, string filename){
    ifstream readLisFile;
    readLisFile.open(filename + ".lis");
    string line;
    int lineCounter = 1;
    string currentAddress;
    while(getline(readLisFile, line)){
        currentAddress = line.substr(0,4);

        if(currentAddress == addressToDelete)
            break;
        lineCounter++;
        
    }
    readLisFile.close();
    return lineCounter;
}

/*******************************************************************************
function: deleteLineInLisFile
Notes: Deletes the line found in the passed in line number in the passed in
        LIS file.

@param deleteLine The line number of the line to be deleted
@param filename The LIS file to delete the line
*******************************************************************************/
void deleteLineInLisFile(int deleteLine, string filename){
    ifstream readLisFile;
    readLisFile.open(filename + ".lis");
    string line;    
    vector<string> lisFileVector;
    
    // Read the lis file and get to the proper line
    for(int i=1; i<deleteLine; i++){
        getline(readLisFile, line);
        lisFileVector.push_back(line + "\n");
    }
    // Ignore the line to be deleted
    getline(readLisFile, line);

    // Read the rest of the lis file
    while(getline(readLisFile, line)){
        lisFileVector.push_back(line + "\n");
    }

    // Read entire lis file into vector
    while(getline(readLisFile, line)){
        lisFileVector.push_back(line + "\n");
    }
    readLisFile.close();

    
    // Write the vector back into the lis file
    ofstream writeLisFile;
    writeLisFile.open(filename + ".lis");
    
    string test;
    while(!lisFileVector.empty()){
        writeLisFile << lisFileVector.front();
        lisFileVector.erase(lisFileVector.begin());
    }
    writeLisFile.close();
}

/*******************************************************************************
function: deleteLine
Notes: Deletes the line found in the passed in address from the passed in LIS
        file.

@param addressToDelete The address found at the beginn of the line to delete
@param filename The name of the LIS file to delete from
*******************************************************************************/
void deleteLine(string addressToDelete, string filename){
    //Find the line to delete by address
    int deletedLine = findDeleteLine(addressToDelete, filename);

    //Delete the line
   deleteLineInLisFile(deletedLine, filename);
}

/*******************************************************************************
function: ReadHeaderRecord
Notes: Takes in the header record as a string and the filename. Then the 
    header record is parsed, analyzed, and its LIS equivalent is written
    in the LIS file.

@param headerRecord Full header record to parse and analyze
@param filename Filename of LIS file to write into
*******************************************************************************/
void ReadHeaderRecord(string headerRecord, string filename){
    //Gets Control Section Name
        //1. Read Program name in col 2-7
    string controlSectionName = headerRecord.substr(1,6);
    
    //2. Read starting address in col 8-13
    string startingAddress = headerRecord.substr(7, 6);

    // Write title of source code
    string firstLine = formatAddress(startingAddress) + "  .  SOURCE CODE FOR ";
    firstLine += controlSectionName;

    insertLine(firstLine, filename);
 
    // Write start line
    string secondLine = formatAddress(startingAddress) + "  ";

    secondLine += formatOperand(controlSectionName);

    secondLine += "START   " + to_string(stoi(startingAddress));
    
    insertLine(secondLine, filename);
    
    //Initialize counter variable  
    int currentAddress = stoi(startingAddress); 
 
    // Read length of object program in col 14-19
    string controlSectionLength = headerRecord.substr(13, 6);
    
    // Set max length for counter
    int fullSectionLength = hexToDecimal(controlSectionLength);

    string hexValue = decimalToHex(fullSectionLength);
}  

/*******************************************************************************
function: findLabel
Notes: Opens symbol table and looks for a label that matches the passed-in 
    address. If found, it returns the Symbol. Else, it returns a string of 
    6 spaces.

@param address The address to find in the symbol table
@param filename The name of the symbol table to open
@return Symbol being searched for
*******************************************************************************/
string findLabel(int address, string filename){
    ifstream symTable;
    symTable.open(filename + ".sym");

    string currentAddress = "00" + formatAddress(decimalToHex(address));
    
    //Open the symbol table, turn its contents into a string
    string str((std::istreambuf_iterator<char>(symTable)),
                std::istreambuf_iterator<char>());
    
    //Search the string for the current address
    int found = str.find(currentAddress);
    
    //If found return the Symbol found 8 characters before and return
        //The substring 6 characters in length and delete the current line in LIS file
    string foundAddress;    
    if (found != std::string::npos){
        foundAddress = str.substr(found-8, 6);
        //If the found label is in the literal table
        if(foundAddress[0] == ' ')
            foundAddress = str.substr(found-24, 6);
    }
    else
        //If not, return a blank space
        foundAddress = "      ";
    return foundAddress;
};

/*******************************************************************************
function: strToBin
Notes: Takes in a string in a hex format, and returns its binary 
    equivalent.

@param str A string in hex format
@return The equivalent in binary format
*******************************************************************************/
string strToBin(string str){
    string binaryString = "";   
    char target; 
    while(!str.empty()){
        target = str[0];
        switch (target){
            case '0': binaryString += "0000";
                break;
            case '1': binaryString += "0001";
                break;
            case '2': binaryString += "0010";
                break;
            case '3': binaryString += "0011";
                break;
            case '4': binaryString += "0100";
                break;
            case '5': binaryString += "0101";
                break;
            case '6': binaryString += "0110";
                break;
            case '7': binaryString += "0111";
                break;
            case '8': binaryString += "1000";
                break;
            case '9': binaryString += "1001";
                break;
            case 'A': binaryString += "1010";
                break;
            case 'B': binaryString += "1011";
                break;
            case 'C': binaryString += "1100";
                break;
            case 'D': binaryString += "1101";
                break;
            case 'E': binaryString += "1110";
                break;
            case 'F': binaryString += "1111";
                break;
        }
        str.erase(0,1);
    }
    return binaryString;
}

/*******************************************************************************
function: binToStr
Notes: Takes in a string in a binary format, and returns its hex 
    equivalent.

@param str A string in binary format
@return The equivalent in hex format
*******************************************************************************/
string binToStr(string bin){
    string str = "";
    string target = "";
    while(!bin.empty()){
        target = bin.substr(0,4);

        if(target == "0000") {str += "0";}
        else if(target == "0001") {str += "1";}
        else if(target == "0010") {str += "2";}
        else if(target == "0011") {str += "3";}
        else if(target == "0100") {str += "4";}
        else if(target == "0101") {str += "5";}
        else if(target == "0110") {str += "6";}
        else if(target == "0111") {str += "7";}
        else if(target == "1000") {str += "8";}
        else if(target == "1001") {str += "9";}
        else if(target == "1010") {str += "A";}
        else if(target == "1011") {str += "B";}
        else if(target == "1100") {str += "C";}
        else if(target == "1101") {str += "D";}
        else if(target == "1110") {str += "E";}
        else if(target == "1111") {str += "F";}
    
        bin.erase(0,4);
    }
    return str;

}

/*******************************************************************************
function: getInstructionLength
Notes: Takes in a string of a textRecord and returns the length of the 
    first instruction.

@param textRecord A line of a textRecord
@return The length of the first instruction
*******************************************************************************/
int getInstructionLength(string textRecord){
    int numberOfCharacters = 0;

    //Read first 3 characters of textRecord
    string first3Chars = textRecord.substr(0,3);
    string first3CharsBin = strToBin(first3Chars);

    // Set the n and i flags to 0
    first3CharsBin[6] = '0';
    first3CharsBin[7] = '0';

    // Get the OPCode of the instruction
    string opCode = binToStr(first3CharsBin.substr(0,8));

    // Get the instruction format
    InstructionSet instr;
    string instructionFormat = instr.getFormat(opCode);
    
    if(instructionFormat == "1")
        numberOfCharacters = 2;
    else if(instructionFormat == "2")
        numberOfCharacters = 4;
    else if((instructionFormat == "3/4") && (first3CharsBin[11] == '0'))
        numberOfCharacters = 6;
    else if((instructionFormat == "3/4") && (first3CharsBin[11] == '1'))
        numberOfCharacters = 8;
    else
        cout << "ERROR. INCORRECT FORMAT READING" << endl;

    return numberOfCharacters;
}

/*******************************************************************************
function: getInstructionName
Notes: Takes in a string of a full instruction and returns its mnemonic.

@param str A string of a full instruction
@return The instruction's mnemonic
*******************************************************************************/
string getInstructionName(string fullObjectCode){
    string fullObjectCodeBin = strToBin(fullObjectCode);

    // Set the n and i flags to 0
    fullObjectCodeBin[6] = '0';
    fullObjectCodeBin[7] = '0';

    // Get the OPCode of the instruction
    string opCode = binToStr(fullObjectCodeBin.substr(0,8));

    // Get the instruction name
    InstructionSet instr;
    string instructionName = instr.getInstruction(opCode);
    
    return instructionName;
}

/*******************************************************************************
function: getRegister
Notes: Takes in a register number and returns it's name

@param registerNumber The number of register
@return The equivalent register name
*******************************************************************************/
string getRegister(char registerNumber){
    if(registerNumber == '0')
        return "A";
    if(registerNumber == '1')
        return "X";
    if(registerNumber == '2')
        return "L";
    if(registerNumber == '3')
        return "B";
    if(registerNumber == '4')
        return "S";
    if(registerNumber == '5')
        return "T";
    if(registerNumber == '6')
        return "F";
    if(registerNumber == '8')
        return "PC";
    if(registerNumber == '9')
        return "SW";
    else
        return "ERROR: INCORRECT REGISTER CODE";
}

/*******************************************************************************
function: getOperandFormat2
Notes: Takes in a string of the full object code of an instruction
    in format 2 and returns its operand.

@param str A string of a full format 2 instruction
@return The operand of the instruction
*******************************************************************************/
string getOperandFormat2(string fullObjectCode){
    char r1 = fullObjectCode[2];
    char r2 = fullObjectCode[3];

    string reg1;
    string reg2;

    string instructionName = getInstructionName(fullObjectCode);
  
    if((instructionName == "CLEAR")||(instructionName == "SVC")||(instructionName=="TIXR")){
        reg1 = getRegister(r1);
        reg2 = "     ";
    }
    else{
        reg1 = getRegister(r1);
        reg2 = "," + getRegister(r2);
    }
    return " " + reg1 + reg2;
}

/*******************************************************************************
function: getInstructionFlags
Notes: Takes in a string of the full object code of an instruction
    in format 3/4 and returns a string of its set flags.

@param str A string of a full format 3/4 instruction
@return A string of flags and their setting
*******************************************************************************/
string getInstructionFlags(string fullObjectCode){
    string fullObjectCodeBin = strToBin(fullObjectCode);

    // instructionFlags[0] is the n flag
    // instructionFlags[1] is the i flag
    // instructionFlags[2] is the x flag
    // instructionFlags[3] is the b flag
    // instructionFlags[4] is the p flag
    // instructionFlags[5] is the e flag
    string instructionFlags = fullObjectCodeBin.substr(6,6);
    return instructionFlags;    
}

/*******************************************************************************
function: hexToDec
Notes: Takes in a string of a value in HEX and returns its decimal equivalent.

@param disp The HEX value to convert
@return The converted decimal value
*******************************************************************************/
int hexToDec(string disp){
    int length = disp.length();

    int base = 1;
    int dispDecimal = 0;

    for(int i = length-1; i >= 0; i--){
        if((disp[i] >= '0') && (disp[i] <= '9')){
            dispDecimal += (disp[i] - 48) * base;
            base *= 16;
        }
        else if((disp[i] >= 'A' ) && (disp[i] <= 'F')){
            dispDecimal += (disp[i] - 55) * base;
            base *= 16;
        }
    }
    return dispDecimal;
}

/*******************************************************************************
function: twosCompliment
Notes: Performs a 2s compliment conversion of passed in HEX value, and returns
        the result.

@param hexNum The value to convert in a HEX format
@return Converted HEX value
*******************************************************************************/
string twosCompliment(string hexNum){
    string binNum = strToBin(hexNum);

    //Flip all the 1's into 0s and vice versa
    for(int i = 0; i < binNum.length(); i++){
        if(binNum[i] == '0')
            binNum[i] = '1';
        else
            binNum[i] = '0';
    }

    // add 1 to result
    string newHexNum = binToStr(binNum);
    int decNum = hexToDecimal(newHexNum);
    decNum++;
    newHexNum = decimalToHex(decNum);
    return newHexNum;
}

/*******************************************************************************
function: getOperandPC
Notes: Takes in a string of a full instruction and its address and returns the 
        appropriate operand through the Program-counter addressing mode.

@param fullObjectCode The full instruction in the form of object code
@param currentAddress The instruction's address
@param filename The name of the symbol table to read through
@return The name of the appropriate operand
*******************************************************************************/
string getOperandPC(string fullObjectCode, string currentAddress, string filename){
    int displacement;
    string dispInBin = strToBin(fullObjectCode.substr(3,3));
    //Checks to see if displacement is positive
    if(dispInBin[0] == '0')
       displacement = hexToDecimal(fullObjectCode.substr(3,3));
    else
       displacement = (-1) * hexToDecimal(twosCompliment(fullObjectCode.substr(3,3)));

    int programCounter = hexToDecimal(currentAddress) + 3;

    int targetAddress = programCounter + displacement;    

    string operand = findLabel(targetAddress, filename);

    return operand;
}

/*******************************************************************************
function: getOperandBase
Notes: Takes in a string of the full object code and filename and finds the 
    operand using base relative addressing

@param fullObjectCode The full instruction in the form of object code
@param filename The name of the base register file to read
@return The name of the appropriate operand
*******************************************************************************/
string getOperandBase(string fullObjectCode, string filename){
    string operand = "";
    int displacement;
    string dispInBin;
    int targetAddressDec;
    int baseValue = hexToDecimal(getBaseRegister());

    dispInBin = strToBin(fullObjectCode.substr(3,3));
    //Checks to see if displacement is positive
    if(dispInBin[0] == '0')
       displacement = hexToDecimal(fullObjectCode.substr(3,3));
    else
       displacement = (-1) * hexToDecimal(twosCompliment(fullObjectCode.substr(3,3)));

    targetAddressDec = baseValue + displacement;
    operand = findLabel(targetAddressDec, filename);

    return operand;
}

/*******************************************************************************
function: getOperandDirect
Notes: Takes in a string of a full instruction and its address and returns the 
        appropriate operand through the direct addressing mode.

@param fullObjectCode The full instruction in the form of object code
@return The name of the appropriate operand
*******************************************************************************/
string getOperandDirect(string fullObjectCode){
    string operand = "";
    string displacement = fullObjectCode.substr(3,3);
    int dispDecimal = hexToDec(displacement);

    operand += to_string(dispDecimal);

    return operand;
}

/*******************************************************************************
function: getOperandFormat4
Notes: Takes in a string of a full, format 4 instruction and returns the 
        appropriate operand 

@param fullObjectCode The full instruction in the form of object code
@param filename The name of the symbol table to read through
@return The name of the appropriate operand
*******************************************************************************/
string getOperandFormat4(string fullObjectCode, string filename){
    string operand = "";
    int targetAddress;

    string instructionFlags = getInstructionFlags(fullObjectCode);
    //If instruction is immediate
    if((instructionFlags[0] == '0')&&(instructionFlags[1] == '1')){
        operand = "#" + to_string(hexToDecimal(fullObjectCode.substr(3,5)));
    }
    else{
        targetAddress = hexToDecimal(fullObjectCode.substr(4,4));
        operand = " " + findLabel(targetAddress, filename);
    }
    return operand;
}

/*******************************************************************************
function: getOperandFormat3
Notes: Takes in a string of the full object code of an instruction
        in format 3 and returns its operand.

@param fullObjectCode A string of a full format 3 instruction
@param currentAddress A string of the current address
@param filename The name of the sym file
@return The operand of the instruction
*******************************************************************************/
string getOperandFormat3(string fullObjectCode, string currentAddress, string filename)
{
    string operand = "";
    // Get the instruction flags 
    string instructionFlags = getInstructionFlags(fullObjectCode);

    // if Indirect flag is set
    if((instructionFlags[0] == '1')&&(instructionFlags[1] == '0')){
        operand = "@";
        // If base flag is set
        if(instructionFlags[3] == '1')
            operand += getOperandBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1'){
            operand += getOperandPC(fullObjectCode, currentAddress, filename);
        }
        // If neither base nor pc flags are set 
        else
            operand += getOperandDirect(fullObjectCode);
    }

    // if Immediate flag is set
    else if((instructionFlags[0] == '0')&&(instructionFlags[1] == '1')){
        operand = "#";
        // If b flag is set
        if(instructionFlags[3] == '1')
            operand += getOperandBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1'){
            operand += getOperandPC(fullObjectCode, currentAddress, filename);
        }
        // If neither base nor pc flags are set 
        else{
            operand += getOperandDirect(fullObjectCode);
        }
    }
    // if both Indirect and Immediate flags are set
    else{
        operand = " ";
        if(instructionFlags[3] == '1')
            operand += getOperandBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1')
            operand += getOperandPC(fullObjectCode, currentAddress, filename);
        // If neither base nor pc flags are set 
        else
            operand += getOperandDirect(fullObjectCode);
    }

    // Check x flag
    if(instructionFlags[2] == '1')
        operand += ",X";
    
    return operand;
}

/*******************************************************************************
function: getTargetAddress
Notes: Takes in a string of the full object code of an instruction
         in format 3 and returns target address.

@param fullObjectCode A string of a full instruction
@param currentAddress A string of the current address
@return The target address of the instruction
*******************************************************************************/
string getTargetAddress(string fullObjectCode, string currentAddress){
    string targetAddress = "";

    int displacement;
    string dispInBin;
    int programCounter;
    int targetAddressDec;

    // Get the instruction flags 
    string instructionFlags = getInstructionFlags(fullObjectCode);

    // If base relative
    if(instructionFlags[3] == '1'){
        int baseValue = hexToDecimal(getBaseRegister());

        dispInBin = strToBin(fullObjectCode.substr(3,3));
        //Checks to see if displacement is positive
        if(dispInBin[0] == '0')
           displacement = hexToDecimal(fullObjectCode.substr(3,3));
        else
           displacement = (-1) * hexToDecimal(twosCompliment(fullObjectCode.substr(3,3)));

        targetAddressDec = baseValue + displacement;
        targetAddress += decimalToHex(targetAddressDec);
    
    }
    //If PC relative
    else if(instructionFlags[4] == '1'){
        dispInBin = strToBin(fullObjectCode.substr(3,3));
        //Checks to see if displacement is positive
        if(dispInBin[0] == '0')
           displacement = hexToDecimal(fullObjectCode.substr(3,3));
        else
           displacement = (-1) * hexToDecimal(twosCompliment(fullObjectCode.substr(3,3)));

        programCounter = hexToDecimal(currentAddress) + 3;

        targetAddressDec = programCounter + displacement;
        targetAddress += decimalToHex(targetAddressDec);
    
    }
    //If format 4
    else if(instructionFlags[5] == '1'){
        targetAddress += fullObjectCode.substr(3,5);
    }
    //If direct addressing
    else{
        targetAddress += fullObjectCode.substr(3,3);
    }
    return targetAddress;
}

/*******************************************************************************
function: getInstructionAndOperand
Notes: Takes in a string of the text record, current address, and file name
        and returns the full formatted line to go into the LIS file

@param textRecord A string of a full format 3 instruction
@param currentAddress A string of the current address
@param filename A string of the file name of the sym file
@return The full line to insert into the lis file
*******************************************************************************/
string getInstructionAndOperand(string textRecord, string currentAddress, string filename){
    
    int instructionLength = getInstructionLength(textRecord);

    string fullObjectCode = textRecord.substr(0, instructionLength);
    
    // Get the instruction name
    string instructionName = formatInstructionName(getInstructionName(fullObjectCode));

    // Get the instruction operand depending on format
    string operand = "";
    string instructionFlags = "";

    // Format 1 (1 Byte)
    if(instructionLength == 2){  
        instructionName.insert(0," ");  
        operand = "         ";
    }
    // Format 2 (2 Bytes)
    else if(instructionLength == 4){
        instructionName.insert(0," ");  
        operand = formatOperand(getOperandFormat2(fullObjectCode));
    }
    // Format 3
    else if(instructionLength == 6){
        instructionName.insert(0," ");  
        operand = getOperandFormat3(fullObjectCode, currentAddress, filename);
        operand = formatOperand(operand);
    }
    // Format 4
    else if(instructionLength == 8){
        instructionName.insert(0,"+");
        operand = getOperandFormat4(fullObjectCode, filename);
        operand = formatOperand(operand);
    }
    string fullStatement = "";
    fullStatement = "  " + instructionName + " " + operand + " " + fullObjectCode; 
    
    if(instructionName == " LDB   "){
        fullStatement += "\n               BASE    " + operand.substr(1,6);
        //Sets base register to TargetAddress
        setBaseRegister(getTargetAddress(fullObjectCode, currentAddress));
    }
    else if(instructionName == "+LDB   "){
        fullStatement += "\n               BASE    " + operand.substr(1,6);
        //Sets base register to TargetAddress
        setBaseRegister(getTargetAddress(fullObjectCode, currentAddress));
    }

    return fullStatement;
}

/*******************************************************************************
function: isLiteral
Notes: Checks to see if a passed in address is a literal found in the .sym file
        and returns a boolean value of whether or not it is found

@param currentAddress A string of the current Address
@param filename A string of the name of the sym file
@return A boolean value of whether the current address holds a literal
*******************************************************************************/
bool isLiteral(string currentAddress, string filename){
    ifstream symTable;
    symTable.open(filename + ".sym");
    
    //Open the symbol table, turn its contents into a string
    string str((std::istreambuf_iterator<char>(symTable)),
                std::istreambuf_iterator<char>());
    
    //Search the string for the phrase "Literal"
    int literalLocation = str.find("Literal");
    //Search the string for the current address
    int found = str.rfind("00" + currentAddress);

    bool isLiteral = false;
    if(found > literalLocation){
        isLiteral = true;
    }

    return isLiteral;
}

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
string getLiteral(string textRecord, string currentAddress, string filename){
    ifstream symTable;
    symTable.open(filename + ".sym");
    string fullStatement = "";
    
    //Open the symbol table, turn its contents into a string
    string str((std::istreambuf_iterator<char>(symTable)),
                std::istreambuf_iterator<char>());

    int found = str.rfind(currentAddress);
    fullStatement += "   BYTE    ";
    fullStatement += str.substr(found-17,6) + "   ";
    int length = stoi(str.substr(found-9,1));

    fullStatement += textRecord.substr(0,length);
    return fullStatement;
    
}

/*******************************************************************************
function: getLiteralLength
Notes: Takes in a full instruction, the current address, and the filename of 
        the sym file, and returns the length of the literal

@param textRecord A string of the full instruction
@param currentAddress A string of the current Address
@param filename A string of the name of the sym file
@return The size of the literal
*******************************************************************************/
int getLiteralLength(string textRecord, string currentAddress, string filename){
    ifstream symTable;
    symTable.open(filename + ".sym");
    string fullStatement = "";
    
    //Open the symbol table, turn its contents into a string
    string str((std::istreambuf_iterator<char>(symTable)),
                std::istreambuf_iterator<char>());

    int found = str.rfind(currentAddress);

    int length = stoi(str.substr(found-9, 1));
    return length;
}

/*******************************************************************************
function: ReadTextRecord
Notes: Takes in a full text record and writes each instruction into the lis 
        file.

@param textRecord A string of the full text record
@param filename A string of the name of the lis and sym files
*******************************************************************************/
void ReadTextRecord(string textRecord, string filename){
    textRecord.erase(0,1);
    
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);
    lisFile.close();
    
    //1. Read first address in col 2-7
    string currentAddress = formatAddress(textRecord.substr(0, 6));
    textRecord.erase(0,6);

    //2. Read length of object code in record in col 8-9
    int textRecordLength = hexToDecimal(textRecord.substr(0, 2));
    textRecord.erase(0,2);
    
    int instructionLength = 0;
    string fullStatement;
    //3. Read Object Code in col 10-69
    while(textRecord.length() > 1){
    //for(int i = 0; i < 9; i++){
        fullStatement = "";
        //Writes current address in LIS file in col 1-4
        fullStatement += currentAddress + "  ";
        
        //Writes the label if exists in col 7-12
        fullStatement += findLabel(hexToDecimal(currentAddress), filename);
        
        //If the address belongs to a literal, write appropriate statement
        if(isLiteral(currentAddress, filename)){
            fullStatement += getLiteral(textRecord, currentAddress, filename);
            instructionLength = getLiteralLength(textRecord, currentAddress, filename);
        }
        else{
        //Writes the instruction, operand, and object code in col 15-40
        fullStatement += getInstructionAndOperand(textRecord, currentAddress, filename);
        instructionLength = getInstructionLength(textRecord);
        }

        insertLine(fullStatement, filename);
        
        //Increments the address
        int newAddress = hexToDecimal(currentAddress) + instructionLength/2;
        currentAddress = formatAddress(decimalToHex(newAddress));
        textRecord.erase(0,instructionLength);
    }
}

/*******************************************************************************
function: writeEndStatement
Notes: Takes in a full statement and the filename of the lis file, and writes
        the full end statement into the lis file.

@param textRecord A string of the end statement
@param filename A string of the name of the lis file
*******************************************************************************/
void writeEndStatement(string fullStatement, string filename){
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);

    lisFile << fullStatement;
    lisFile.close();
}

/*******************************************************************************
function: ReadEndRecord
Notes: Takes in the full end record and the name of the lis file and writes 
        last statement in the lis file.

@param textRecord A string of the full end record
@param filename A string of the name of the lis file
*******************************************************************************/
void ReadEndRecord(string endRecord, string filename){
    string fullStatement = "";
    //1. Write blank address and label 
    fullStatement += "               ";
    //2. Write “END” instruction
    fullStatement += "END     ";
    //3. Write program name
    fullStatement += findLabel(hexToDec(endRecord.substr(1,6)), filename);

    //write end record to end of lis file
    writeEndStatement(fullStatement, filename);
}

/*******************************************************************************
function: analyzeAndWriteObjectFile
Notes: Takes in the name of the obj file and reads each line and take the
        appropriate action at each record.

@param filename A string of the name of the obj file
*******************************************************************************/
void analyzeAndWriteObjectFile(string filename){
    ifstream objFile;
    string line;

    //Read and analyze object file
    objFile.open (filename + ".obj");
    while(getline(objFile, line)){

        if(line[0] == 'H'){
            ReadHeaderRecord(line, filename);
        }
        
        if(line[0] == 'T'){
            ReadTextRecord(line, filename);
        }

        if(line[0] == 'E'){
            ReadEndRecord(line, filename);
        }
    }
    objFile.close();
}

/*******************************************************************************
function: createMapOfSymbols
Notes: Takes in the name of the sym file and returns an ordered map of each 
        symbol and its value.

@param filename A string of the name of the sym file
@return An ordered map of each symbol and their values
*******************************************************************************/
map<string,string> createMapOfSymbols(string filename){
    //Open sym table for reading
    ifstream symFile;
    string line;
    symFile.open(filename + ".sym");

    //Skip a couple lines
    getline(symFile, line);
    getline(symFile, line);
    getline(symFile, line);
    //Read through each line of sym table and insert each symbol-value pair into a map
    map<string, string> symbols;
    while(line != ""){
        //If symbol doesn't exist in lis file, then insert
        symbols[line.substr(8,6)] = line.substr(0,6);
        getline(symFile, line);
    }
    symFile.close();
    return symbols;
}

/*******************************************************************************
function: removeWrittenSymbols
Notes: Takes in a map of symbols and the name of the sym file and returns an 
        ordered map of symbols and values that haven't already been written
        into the lis file.

@param sym An ordered map of all of the symbols in the sym file
@param filename A string of the name of the lis file
@return An ordered map of new symbols and their values
*******************************************************************************/
map<string,string> removeWrittenSymbols(map<string,string> sym, string filename){
    //Open lis table for reading
    ifstream lisFile;
    string line;
    lisFile.open(filename + ".lis");

    //remove each address in the lis file from the symbol map
    while(getline(lisFile, line)){
        sym.erase("00" + line.substr(0,4));
    }

    lisFile.close();
    return sym;
}

/*******************************************************************************
function: insertSymbol
Notes: Takes in the address and label of a specific symbol and inserts it 
        into a lis file

@param address A string of the address of the symbol
@param label A string of the name of the symbol
@param filename A string of the name of the lis file
*******************************************************************************/
void insertSymbol(string address, string label, string filename){
    //Create the full statement to be inserted into the LIS file    
    string fullStatement = "";
    //Add the address
    fullStatement += address.substr(2,4) + "  ";
    //Add the label
    fullStatement += label + "   ";

    //Find the amount of reserved bytes
    //Find the address of the next instruction
    ifstream lisFile;
    string line = "";
    lisFile.open(filename + ".lis");
    
    getline(lisFile, line);
    while(line.substr(0,4) < address.substr(2,4)){
        getline(lisFile, line);
    }
    lisFile.close();

    int addressOfNextInstruction = hexToDec(line.substr(0,4));
 
    //Subtract that address from the current address
    int addressDifference = addressOfNextInstruction - hexToDec(address);

    //If difference%3==0, then give mnemonic "RESW", else "RESB"
    if(addressDifference % 3 == 0){
        fullStatement += "RESW    ";
        addressDifference /= 3;
    }
    else
        fullStatement += "RESB    ";
    //Add the difference in addresses as an operand
    fullStatement += to_string(addressDifference);

    insertLine(fullStatement, filename);
}

/*******************************************************************************
function: addRemainingSymbols
Notes: Takes in the name of the lis and sym files and writes in the symbols
        that are missing in the lis file

@param filename A string of the name of the lis and sym files
*******************************************************************************/
void addRemainingSymbols(string filename){
    
    map<string,string> symbols = createMapOfSymbols(filename);

    //Read through lis file and remove already written symbols from the map
    symbols = removeWrittenSymbols(symbols, filename);
    
    
    for(auto i = symbols.rbegin(); i != symbols.rend(); ++i){
        insertSymbol(i->first, i->second, filename);
    }
}

//TODO: When writing .make file remember in clean: rm "baseRegister.txt"

/*******************************************************************************
function: buildLISFile
Notes: Takes in the name of the obj and sym files and writes the lis file.

@param filename A string of the name of the lis file
*******************************************************************************/
void buildLISFile(string filename){
    
    //Initialize LIS file
    ofstream lisFile(filename + ".lis", std::ofstream::trunc);
    lisFile.close();

    analyzeAndWriteObjectFile(filename);

    //Add operands to assembler directives
    addRemainingSymbols(filename);
}

int main(int argc, char **argv){
//1. Build LIS File
    if (argc == 2){
        buildLISFile(argv[1]);
    }
    else{
        cout << "ERROR: Incorrect numebr of arguments!" << endl;
    }
    return 0;
}
