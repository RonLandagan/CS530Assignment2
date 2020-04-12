/********************************************************************
Names: Ron Landagan, cssc1917 (Team Lead),
       Will Rodriguez, cssc1922 (Developer),
       Isaiah Dorado, cssc1973 (Developer),
       Joshua Vargas, cssc1929 (Developer)
Project: CS530 Assignment 2
File: LISFunctions.cpp
Notes: This header file contains the definitions of functions that
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
}

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

void insertLine(string newLine, string filename){
    
    string newLineAddress = newLine.substr(0,4);
    int properLine = findProperLine(newLineAddress, filename);
    
    insertLineInLisFile(properLine, newLine, filename);

}

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

void deleteLine(string addressToDelete, string filename){
    //Find the line to delete by address
    int deletedLine = findDeleteLine(addressToDelete, filename);

    //Delete the line
   deleteLineInLisFile(deletedLine, filename);
}

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

string getOperandDirect(string fullObjectCode){
    string operand = "";
    string displacement = fullObjectCode.substr(3,3);
    int dispDecimal = hexToDec(displacement);

    operand += to_string(dispDecimal);

    return operand;
}

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

string getOperandFormat3(string fullObjectCode, string currentAddress, string filename){
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
