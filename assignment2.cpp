#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include "InstructionSet.h"

using namespace std;

string writeAddress(string address){
    stringstream ss;
    string result;
    if(address.length() > 4)
        address = address.substr(address.length()-4,4);
    ss << setfill('0') << setw(4) << address;
    ss >> result;
    return result;
}

string formatHexValue(string hexValue){
    transform(hexValue.begin(), hexValue.end(), hexValue.begin(), ::toupper);
    return hexValue;
}

int hexToDecimal(string hexValue){
    unsigned int x;
    stringstream ss;
    ss << std::hex << hexValue;
    ss >> x;
    return x;
}

string decimalToHex(int decimalValue){
    string result;
    stringstream ss;
    ss << std::hex << decimalValue;
    ss >> result;
    result = formatHexValue(result);
    return result;
}

void ReadHeaderRecord(string headerRecord, string filename){
    cout << "HEADER RECORD" << endl;
    
    //Gets Control Section Name
        //1. Read Program name in col 2-7
    string controlSectionName = headerRecord.substr(1,6);
    cout << "Control section name: " << controlSectionName << endl;
    
    //2. Read starting address in col 8-13
    string startingAddress = headerRecord.substr(7, 6);
    cout << "Starting Address: " << startingAddress << endl;

    // Write starting address in first line
    ofstream lisFile;
    lisFile.open(filename + ".lis");
    lisFile << writeAddress(startingAddress);
    //1. Write program name in first line
    lisFile << "  .  SOURCE CODE FOR " << controlSectionName << endl;
    
    //Write Starting line of Control Structure code
    lisFile << writeAddress(startingAddress);
    lisFile << setfill(' ') << "  " << setw(6) << controlSectionName;
    lisFile << "  " << "START" << "  " << " 0" << endl;

    lisFile.close();
    
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


void ReadTextRecord(string textRecord, string filename){
    cout << "TEXT RECORD" << endl;
    //1. Read first address in col 2-7
    //2. Read length of object code in record in col 8-9
        //1. Save into a variable
    //3. Read Object Code in col 10-69
        //1. Write current address to LIS file in col 1-4
            //1. If current address matches a label in the SYM table, write label in col 7-12
        //2. Read first 3 characters
        //3. Convert 3 characters to binary
        //4. Read first 6 bits
            //1. Get Opcode from the OBJ file
            //2. Get format from Opcode
            //3. If format is 3 or 4, use the bits 7 to 12 tho find the nixbpe flags
            //4. Return instructions format
        //5. Read full instruction
            //1. Get all nixbpe flags
                //1. Find operand using flags
            //2. Write Instruction and operand
                //1. Write instruction in col 15-20
                //2. Write operand in col 23-31
            //3. Write Object code in col 33-end
        //6. Increment counter variable by instruction size
        //7. Repeat until text record is finished
}


void ReadModRecord(string modRecord, string filename){
    cout << "MOD RECORD" << endl;
}

void ReadEndRecord(string endRecord, string filename){
    cout << "END RECORD" << endl;
    //1. Write address
    //2. Write “END” instruction
    //3. Write program name
}

void buildLISFile(string filename){
    ifstream objFile;
   
    objFile.open (filename + ".obj");
    string line;
    while(getline(objFile, line)){

        if(line[0] == 'H'){
            cout << line << endl;
            ReadHeaderRecord(line, filename);
            cout << "\n \n";
        }
        
        if(line[0] == 'T'){
            cout << line << endl;
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

int main(int argc, char **argv){
//1. Build LIS File
    if (argc == 2){
        buildLISFile(argv[1]);
    

    //1. Open OBJ file + Open SYM file
    //2. Read Header Record (Read col 1 “H”)
        //1. Read Program name in col 2-7
            //1. Write program name in first line
        //2. Read starting address in col 8-13
            //1. Initialize counter variable
        //3. Read length of object program in col 14-19
            //1. Set max length for counter
        //4. Begin writing LIS file
    //3. Read Text Record (Read col 1 “T”)
        //1. Read first address in col 2-7
        //2. Read length of object code in record in col 8-9
            //1. Save into a variable
        //3. Read Object Code in col 10-69
            //1. Write current address to LIS file in col 1-4
                //1. If current address matches a label in the SYM table, write label in col 7-12
            //2. Read first 3 characters
            //3. Convert 3 characters to binary
            //4. Read first 6 bits
                //1. Get Opcode from the OBJ file
                //2. Get format from Opcode
                //3. If format is 3 or 4, use the bits 7 to 12 tho find the nixbpe flags
                //4. Return instructions format
            //5. Read full instruction
                //1. Get all nixbpe flags
                    //1. Find operand using flags
                //2. Write Instruction and operand
                    //1. Write instruction in col 15-20
                    //2. Write operand in col 23-31
                //3. Write Object code in col 33-end
            //6. Increment counter variable by instruction size
            //7. Repeat until text record is finished
        //4. Go to next line
    //4. Read Modification Record (Read col 1 “M”)
    //5. Read End record (Read col 1 “E”)
        //1. Write address
        //2. Write “END” instruction
        //3. Write program name
//2. Build SIC File
    //buildSICFile(argv[1]);
    //1. Open LIS file
    //2. Begin writing SIC file
        //1. Read through character-by-character
        //2.Write only source statements into SIC file 
    }
    else{
        cout << "ERROR: Incorrect numebr of arguments!" << endl;
    }
    return 0;
}
