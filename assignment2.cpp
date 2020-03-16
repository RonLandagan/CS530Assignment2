#include <iostream>
#include <fstream>
#include <string>
#include "InstructionSet.h"

using namespace std;

/*ReadHeaderRecord(ifstream, ifstream){
    //1. Read Program name in col 2-7
        //1. Write program name in first line
    //2. Read starting address in col 8-13
        //1. Initialize counter variable
    //3. Read length of object program in col 14-19
        //1. Set max length for counter
}  
*/

/*ReadTextRecord(ifstream, ifstream){
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
*/

/*ReadModRecord(ifstream){}*/

/*ReadEndRecord(ifstream){
    //1. Write address
    //2. Write “END” instruction
    //3. Write program name
}
*/
void buildLISFile(string filename){
    ifstream objFile;
    objFile.open (filename + ".obj");
    string line;
    getline(objFile, line);
    cout << line << endl;
    objFile.close();
    //Read obj file until "H" character
        //ReadHeaderRecord(ifstream objFile, ifstream symTable);
    //Read obj file until "T" character, repeat until "M"
        //ReadTextRecord(ifstream objFile, ifstream symTable);
    //Read obj file until "M" character
        //ReadModRecord(ifstream objFile);
    //Read obj file until "E" character
        //ReadEndRecord(ifstream objFile);
}

int main(int argc, char **argv){
//1. Build LIS File
buildLISFile(argv[1]);
//buildSICFile(argv[1]);

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
    //1. Open LIS file
    //2. Begin writing SIC file
        //1. Read through character-by-character
        //2.Write only source statements into SIC file 

    return 0;
}
