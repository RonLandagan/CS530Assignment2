#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
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

    // Write starting address in first line
    ofstream lisFile;
    lisFile.open(filename + ".lis");
    lisFile << formatAddress(startingAddress);
    //1. Write program name in first line
    lisFile << "  .  SOURCE CODE FOR " << controlSectionName << endl;
    
    //Write Starting line of Control Structure code
    lisFile << formatAddress(startingAddress);
    lisFile << setfill(' ') << "  " << setw(6) << controlSectionName;
    lisFile << "  " << " START" << "  " << " 0" << endl;

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
        //The substring 6 characters in length
    if (found != std::string::npos)
        return str.substr(found-8, 6);
    else
        //If not, return a blank space
        return "      ";
};

/*******************************************************************************
function: writeCurrentAddress
Notes: Takes in the current address as an int and the filename. Then the 
    address is turned into a 4 column string in hex and is written in the 
    LIS file.

@param currentAddress Current address of the instruction to write
@param filename Filename of LIS file to write into
*******************************************************************************/
void writeCurrentAddress(int currentAddress, string filename){
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);

    lisFile << formatAddress(decimalToHex(currentAddress));
    lisFile << "  ";

    lisFile.close();
}

/*******************************************************************************
function: writeLabel
Notes: Takes in the current address as an int and the filename. Then a  
    label with the same address is searched for and if found, it is 
    written in the LIS file.

@param currentAddress Current address of the instruction to write
@param filename Filename of LIS file to write into
*******************************************************************************/
void writeLabel(int currentAddress, string filename){
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);

    lisFile << findLabel(currentAddress, filename);
    lisFile << "  ";    

    lisFile.close();
}

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

    string reg1 = getRegister(r1);
    string reg2 = getRegister(r2);

    return reg1 + "," + reg2;
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

string getOperandIndirectBase(string fullObjectCode, string filename){
    string operand = "INDIRECT,BASE";

    return operand;
}

string getOperandIndirectPC(string fullObjectCode, string filename){
    string operand = "INDIRECT,PC";

    return operand;
}

string getOperandIndirectDirect(string fullObjectCode, string filename){
    string operand = "INDIRECT,DIRECT";

    return operand;
}

string getOperandImmediateBase(string fullObjectCode, string filename){
    string operand = "IMMEDIATE,BASE";

    return operand;
}

string getOperandImmediatePC(string fullObjectCode, string filename){
    string operand = "IMMEDIATE,PC";

    return operand;
}



string getOperandImmediateDirect(string fullObjectCode, string filename){
    string operand = "#";
    string displacement = fullObjectCode.substr(3,3);
    int dispDecimal = hexToDec(displacement);

    operand += to_string(dispDecimal);

    return operand;
}

string getOperandSimpleBase(string fullObjectCode, string filename){
    string operand = "SIMPLE,BASE";

    return operand;
}

string getOperandSimplePC(string fullObjectCode, string filename){
    string operand = "SIMPLE,PC";

    return operand;
}

string getOperandSimpleDirect(string fullObjectCode, string filename){
    string operand = "SIMPLE,DIRECT";

    return operand;
}

/*******************************************************************************
function: getOperandFormat3
Notes: Takes in a string of the full object code of an instruction
    in format 3 and returns its operand.

@param str A string of a full format 3 instruction
@return The operand of the instruction
*******************************************************************************/
string getOperandFormat3(string fullObjectCode, string filename)
{   //TODO: continue to work on instruction name and operand
    string operand = "";
    // Get the instruction flags 
    string instructionFlags = getInstructionFlags(fullObjectCode);

    // if Indirect flag is set
    if((instructionFlags[0] == '1')&&(instructionFlags[1] == '0')){
        // If base flag is set
        if(instructionFlags[3] == '1')
            //TODO: FINISH this method
            operand = getOperandIndirectBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1')
            //TODO: FINISH this method
            operand = getOperandIndirectPC(fullObjectCode, filename);
        // If neither base nor pc flags are set 
        else
            //TODO: FINISH this method
            operand = getOperandIndirectDirect(fullObjectCode, filename);
    }

    // if Immediate flag is set
    else if((instructionFlags[0] == '0')&&(instructionFlags[1] == '1')){
        // If b flag is set
        if(instructionFlags[3] == '1')
            //TODO: FINISH this method
            operand = getOperandImmediateBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1')
            //TODO: FINISH this method
            operand = getOperandImmediatePC(fullObjectCode, filename);
        // If neither base nor pc flags are set 
        else
            operand = getOperandImmediateDirect(fullObjectCode, filename);
    }
    // if neither Indirect nor Immediate flags are net
    else{
        if(instructionFlags[3] == '1')
            //TODO: FINISH this method
            operand = getOperandSimpleBase(fullObjectCode, filename);
        // If pc flag is set
        else if(instructionFlags[4] == '1')
            //TODO: FINISH this method NEXT!!!!
            operand = getOperandSimplePC(fullObjectCode, filename);
        // If neither base nor pc flags are set 
        else
            //TODO: FINISH this method
            operand = getOperandSimpleDirect(fullObjectCode, filename);
    }

    // Check x flag
    if(instructionFlags[2] == '1')
        operand += ",X";
    
    return operand;
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

void writeInstructionAndOperand(string textRecord, string filename){
    
    int instructionLength = getInstructionLength(textRecord);

    string fullObjectCode = textRecord.substr(0, instructionLength);

    cout << "FULL OBJECT CODE: " << fullObjectCode << endl;
    
    // Get the instruction name
    string instructionName = getInstructionName(fullObjectCode);
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
        operand = getOperandFormat2(fullObjectCode);
    }
    // Format 3
    else if(instructionLength == 6){
        instructionName.insert(0," ");  
        operand = getOperandFormat3(fullObjectCode, filename);
    }
    // Format 4
    else if(instructionLength == 8){
        instructionName.insert(0,"+");
        //operand = getOperandFormat4(fullObjectCode);
    }

    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);
    // Write instruction into LIS file
    lisFile << formatInstructionName(instructionName) << "  ";
    // Write operand into LIS file
    lisFile << formatOperand(operand) << " ";
    // Write full object code into LIS file
    lisFile << fullObjectCode << endl;
    lisFile.close();
}

void ReadTextRecord(string textRecord, string filename){
    cout << "TEXT RECORD" << endl;
    textRecord.erase(0,1);
    
    // Open output file
    ofstream lisFile;
    lisFile.open(filename + ".lis", ios::out | ios::app);
    lisFile.close();
    
    //1. Read first address in col 2-7
    int currentAddress = stoi(textRecord.substr(0, 6));
    textRecord.erase(0,6);

    //2. Read length of object code in record in col 8-9
    int textRecordLength = hexToDecimal(textRecord.substr(0, 2));
    textRecord.erase(0,2);
    
    int instructionLength = 0;
    //3. Read Object Code in col 10-69
    //while(!textRecord.empty()){
    for(int i = 0; i < 2; i++){
        //Writes current address in LIS file in col 1-4
        writeCurrentAddress(currentAddress, filename);
        
        //Writes the label if exists in col 7-12
        writeLabel(currentAddress, filename);

        //Writes the instruction, operand, and object code in col 15-40
        writeInstructionAndOperand(textRecord,filename);

        instructionLength = getInstructionLength(textRecord);
        
        //Increments the address
        currentAddress += instructionLength/2;
        textRecord.erase(0,instructionLength);
    }
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

// TODO: WORK ON THIS PART NEXT!!
void insertSymbol(string symName, string symAddress, string filename){
    // read lis file into vector
    // find the proper position
    // insert symbol and address
    // write vector out into new file
}

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
    // parse each line using ' ' as a delimiter 
    symbolName = line.substr(0, 6);
    symbolAddress = line.substr(8, 6);
    cout << "SYMBOL NAME: " << symbolName << endl;
    cout << "SYMBOL ADDRESS: " << symbolAddress << endl;
    // write symbol and address in function
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

//TODO: might have to do two passes to write the assembler directives
void buildLISFile(string filename){
    
    analyzeAndWriteSymbolTable(filename);
    analyzeAndWriteObjectFile(filename);
    
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
