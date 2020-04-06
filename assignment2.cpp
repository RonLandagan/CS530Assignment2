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
    cout << "HEADER RECORD" << endl;
    
    //Gets Control Section Name
        //1. Read Program name in col 2-7
    string controlSectionName = headerRecord.substr(1,6);
    cout << "Control section name: " << controlSectionName << endl;
    
    //2. Read starting address in col 8-13
    string startingAddress = headerRecord.substr(7, 6);
    cout << "Starting Address: " << startingAddress << endl;

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
    cout << "Current Address: " << currentAddress << endl;
 
    //3. Read length of object program in col 14-19
    string controlSectionLength = headerRecord.substr(13, 6);
    cout << "Control Section length: " << controlSectionLength << endl;
    
    //1. Set max length for counter
    
    int fullSectionLength = hexToDecimal(controlSectionLength);
    cout << "Full section length: " << fullSectionLength << endl;

    string hexValue = decimalToHex(fullSectionLength);
    cout << "HEX VALUE: " << hexValue << endl;
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
    return reg1 + reg2;
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
        operand = findLabel(targetAddress, filename);
    }
    return operand;
}

/*******************************************************************************
function: getOperandFormat3
Notes: Takes in a string of the full object code of an instruction
    in format 3 and returns its operand.

@param str A string of a full format 3 instruction
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
        if(instructionFlags[3] == '1')
            operand = getOperandBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1')
            operand = getOperandPC(fullObjectCode, currentAddress, filename);
        // If neither base nor pc flags are set 
        else
            operand = getOperandDirect(fullObjectCode);
    }

    // Check x flag
    if(instructionFlags[2] == '1')
        operand += ",X";
    
    return operand;
}

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
    //If direct addressing
    else{
        targetAddress += fullObjectCode.substr(3,3);
    }
    return targetAddress;
}

string getInstructionAndOperand(string textRecord, string currentAddress, string filename){
    
    int instructionLength = getInstructionLength(textRecord);

    string fullObjectCode = textRecord.substr(0, instructionLength);

    cout << "FULL OBJECT CODE: " << fullObjectCode << endl;
    
    // Get the instruction name
    string instructionName = formatInstructionName(getInstructionName(fullObjectCode));
    cout << "INSTRUCTION NAME: " << instructionName << endl;

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
    }
    // Format 4
    else if(instructionLength == 8){
        instructionName.insert(0,"+");
        operand = getOperandFormat4(fullObjectCode, filename);
    }
    string fullStatement = "";
    fullStatement = "  " + instructionName + "  " + operand + "   " + fullObjectCode; 
    
    cout << instructionName + "|" << endl;
    if(instructionName == " LDB   "){
        fullStatement += "\n               BASE    " + operand.substr(1,6);
        //Sets base register to TargetAddress
        setBaseRegister(getTargetAddress(fullObjectCode, currentAddress));
    }

    return fullStatement;
}

//Checks to see if a passed in address is a literal found in the .sym file
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
    cout << "CURRENT ADDRESS: " << currentAddress << endl;
    cout << "LITERAL LoCATIN: " << literalLocation << endl;
    cout << "FOunD: "<<found << endl;
    bool isLiteral = false;
    if(found > literalLocation){
        cout << "THIS IS A LITERAL" << endl;
        isLiteral = true;
    }

    return isLiteral;
}

string getLiteral(string textRecord, string currentAddress, string filename){
    ifstream symTable;
    symTable.open(filename + ".sym");
    string fullStatement = "";
    
    //Open the symbol table, turn its contents into a string
    string str((std::istreambuf_iterator<char>(symTable)),
                std::istreambuf_iterator<char>());

    int found = str.rfind(currentAddress);
    fullStatement += "BYTE    ";
    fullStatement += str.substr(found-17,6) + "   ";
    int length = stoi(str.substr(found-9,1));

    fullStatement += textRecord.substr(0,length);
    return fullStatement;
    
}

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

void ReadTextRecord(string textRecord, string filename){
    cout << "TEXT RECORD : " << textRecord << endl;
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
        cout << "GETTING CURRENT ADDRESS" << endl;
        fullStatement += currentAddress + "  ";
        
        //Writes the label if exists in col 7-12
        cout << "WRITING LABEL" << endl;
        fullStatement += findLabel(hexToDecimal(currentAddress), filename);
        
        //If the address belongs to a literal, write appropriate statement
        cout << "CHECKING IF LITERAL" << endl;
        if(isLiteral(currentAddress, filename)){
            fullStatement += getLiteral(textRecord, currentAddress, filename);
            instructionLength = getLiteralLength(textRecord, currentAddress, filename);
        }
        else{
        //Writes the instruction, operand, and object code in col 15-40
        cout << "WRITING INSTRUCTION AND OPERAND" << endl;
        fullStatement += getInstructionAndOperand(textRecord, currentAddress, filename);
        instructionLength = getInstructionLength(textRecord);
        }
        cout << "FULL STATEMENT: " << fullStatement << endl;

        insertLine(fullStatement, filename);
        
        //Increments the address
        int newAddress = hexToDecimal(currentAddress) + instructionLength/2;
        currentAddress = formatAddress(decimalToHex(newAddress));
        textRecord.erase(0,instructionLength);
        cout << "TEXTRECORD LENGTH: " << textRecord.length() << endl;
    }
}


void ReadModRecord(string modRecord, string filename){
    cout << "MOD RECORD" << endl;
}

void writeEndStatement(string fullStatement, string filename){
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);

    lisFile << fullStatement;
    lisFile.close();
}

void ReadEndRecord(string endRecord, string filename){
    cout << "END RECORD" << endl;

    string fullStatement = "";
    //1. Write blank address and label 
    fullStatement += "               ";
    //2. Write “END” instruction
    fullStatement += "END     ";
    //3. Write program name
    fullStatement += findLabel(hexToDec(endRecord.substr(1,6)), filename);
    cout << fullStatement << endl;

    //write end record to end of lis file
    writeEndStatement(fullStatement, filename);
}



// TODO: rewrite to use after text records are read and fill in missing symbols
void analyzeAndWriteSymbolTable(string filename){
    ifstream symFile;   
    string line;

    //Read and analyze symbol table
    // open symbol table
    symFile.open (filename + ".sym");

    // skip a couple lines
    getline(symFile, line);
    getline(symFile, line);
    getline(symFile, line);

    // loop through file reading each line 
    string symbolName = "";
    string symbolAddress = "";
    string delimiter = " ";

    while(line != ""){
    symbolName = line.substr(0, 6);
    symbolAddress = formatAddress(line.substr(8, 6));
    
    // write symbol and address in function
    insertLine(symbolAddress + "  " + symbolName, filename);
    //insertSymbol(symbolName, symbolAddress, filename);
    // end when you read a blank line
    getline(symFile, line);

    }
}

void analyzeAndWriteObjectFile(string filename){
    ifstream objFile;
    string line;

    //Read and analyze object file
    objFile.open (filename + ".obj");
    while(getline(objFile, line)){

        if(line[0] == 'H'){
            cout << line << endl;
            ReadHeaderRecord(line, filename);
            cout << "\n \n";
        }
        
        if(line[0] == 'T'){
            cout << line << endl;
    //TODO: WORK ON THIS PART NEXT
            ReadTextRecord(line, filename);
            cout << "\n \n";
        }

        if(line[0] == 'M'){
            cout << line << endl;
            ReadModRecord(line, filename);
            cout << "\n \n";
        }

        if(line[0] == 'E'){
            cout << line << endl;
            ReadEndRecord(line, filename);
            cout << "\n \n";
        }
    }
    objFile.close();
}

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

void addRemainingSymbols(string filename){
    
    map<string,string> symbols = createMapOfSymbols(filename);

    //Read through lis file and remove already written symbols from the map
    symbols = removeWrittenSymbols(symbols, filename);
    
    
    for(auto i = symbols.rbegin(); i != symbols.rend(); ++i){
        insertSymbol(i->first, i->second, filename);
    }
}

//TODO: When writing .make file remember in clean: rm "baseRegister.txt"
//TODO: Formatting the .lis file columns

void buildLISFile(string filename){
    
    //Initialize LIS file
    ofstream lisFile(filename + ".lis", std::ofstream::trunc);
    lisFile.close();

    // analyzeAndWriteSymbolTable(filename);
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
