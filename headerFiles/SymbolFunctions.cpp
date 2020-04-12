#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>

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

