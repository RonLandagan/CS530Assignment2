#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <streambuf>
#include <vector>

string toUpper(string str){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
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
    result = toUpper(result);
    return result;
}

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

