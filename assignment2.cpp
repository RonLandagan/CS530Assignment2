#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>
#include "headerFiles/InstructionSet.h"
#include "headerFiles/formattingFunctions.h"
#include "headerFiles/formattingFunctions.cpp"
#include "headerFiles/conversionFunctions.h"
#include "headerFiles/conversionFunctions.cpp"
#include "headerFiles/LISFunctions.h"
#include "headerFiles/LISFunctions.cpp"
#include "headerFiles/SymbolFunctions.h"
#include "headerFiles/SymbolFunctions.cpp"

using namespace std;

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

/*******************************************************************************
function: fileExists
Notes: Takes in a filename and checks to see if it exists and returns results.

@param filename A string of the name of the file to check
@return The results of the check
*******************************************************************************/
bool fileExists(string filename){
    // Try opening file to read
    ifstream tempFile;
    tempFile.open(filename);
    if(tempFile)
        return true;
    else
        return false;
}

//TODO: make to check for obj and sym file existence before building lis file
int main(int argc, char **argv){
//1. Build LIS File
    if (argc == 2){
        //Check if both <filename>.obj and <filename>.sym exists
        string objFilename = argv[1];
        objFilename += ".obj";
        string symFilename = argv[1];
        symFilename += ".sym";

        if(fileExists(objFilename) && fileExists(symFilename))
            buildLISFile(argv[1]);
        else
            cout << "Error: missing .obj or .sym file" << endl;
    }
    else{
        cout << "ERROR: Incorrect numebr of arguments!" << endl;
    }
    remove("baseRegister.txt");
    return 0;
}
