/********************************************************************
Names: Ron Landagan, cssc1917
       Will Rodriguez, 
       Isaiah Dorado, 
       Joshua Vargas, 
Project: CS530 Assignment 2
File: InstructionSet.h
Notes: This is a header file with a class that contains a hash table 
        holding the information regarding SIC/XE opcodes, their 
        instructions and their formats. This class allows a user to
        get either an instruction's name or format from its

********************************************************************/

#pragma once
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
using namespace std;
class InstructionSet{
    private:
      unordered_map<string, pair<string,string>> map;

    public:
      InstructionSet();
      string getInstruction(string);
      string getFormat(string);
};

InstructionSet::InstructionSet() {
    map["18"] = make_pair("ADD","3/4");
    map["58"] = make_pair("ADDF","3/4");
    map["90"] = make_pair("ADDR","2");
    map["40"] = make_pair("AND","3/4");
    map["B4"] = make_pair("CLEAR","2");
    map["28"] = make_pair("COMP","3/4");
    map["88"] = make_pair("COMPF","3/4");
    map["A0"] = make_pair("COMPR","2");
    map["24"] = make_pair("DIV","3/4");
    map["64"] = make_pair("DIVF","3/4");
    map["9C"] = make_pair("DIVR","2");

    map["C4"] = make_pair("FIX","1");
    map["C0"] = make_pair("FLOAT","1");
    map["F4"] = make_pair("HIO","1");
    map["3C"] = make_pair("J","3/4");
    map["30"] = make_pair("JEQ","3/4");
    map["34"] = make_pair("JGT","3/4");
    map["38"] = make_pair("JLT","3/4");
    map["48"] = make_pair("JSUB","3/4");
    map["00"] = make_pair("LDA","3/4");
    map["68"] = make_pair("LDB","3/4");
    map["50"] = make_pair("LDCH","3/4");

    map["70"] = make_pair("LDF","3/4");
    map["08"] = make_pair("LDL","3/4");
    map["6C"] = make_pair("LDS","3/4");
    map["74"] = make_pair("LDT","3/4");
    map["04"] = make_pair("LDX","3/4");
    map["D0"] = make_pair("LPS","3/4");
    map["20"] = make_pair("MUL","3/4");
    map["60"] = make_pair("MULF","3/4");
    map["98"] = make_pair("MULR","2");
    map["C8"] = make_pair("NORM","1");
    map["44"] = make_pair("OR","3/4");

    map["D8"] = make_pair("RD","3/4");
    map["AC"] = make_pair("RMO","2");
    map["4C"] = make_pair("RSUB","3/4");
    map["A4"] = make_pair("SHIFTL","2");
    map["A8"] = make_pair("SHIFTR","2");
    map["F0"] = make_pair("SIO","1");
    map["EC"] = make_pair("SSK","3/4");
    map["0C"] = make_pair("STA","3/4");
    map["78"] = make_pair("STB","3/4");
    map["54"] = make_pair("STCH","3/4");
    map["80"] = make_pair("STF","3/4");

    map["D4"] = make_pair("STI","3/4");
    map["14"] = make_pair("STL","3/4");
    map["7C"] = make_pair("STS","3/4");
    map["E8"] = make_pair("STSW","3/4");
    map["84"] = make_pair("STT","3/4");
    map["10"] = make_pair("STX","3/4");
    map["1C"] = make_pair("SUB","3/4");
    map["5C"] = make_pair("SUBF","3/4");
    map["94"] = make_pair("SUBR","2");
    map["B0"] = make_pair("SVC","2");
    map["E0"] = make_pair("TD","3/4");

    map["F8"] = make_pair("TIO","1");
    map["2C"] = make_pair("TIX","3/4");
    map["B8"] = make_pair("TIXR","2");
    map["DC"] = make_pair("WD","3/4");
}

string InstructionSet::getInstruction(string opcode){
    return map[opcode].first;
}

string InstructionSet::getFormat(string opcode){
    return map[opcode].second;
}
