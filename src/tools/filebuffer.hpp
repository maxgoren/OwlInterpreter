#pragma once
#ifndef filebuffer_hpp
#define filebuffer_hpp
#include <iostream>
#include <fstream>
#include <vector>
#include "../tokens/tokens.hpp"
using namespace std;

class FileReader {
    private:
        char readChar;
        int linenum;
        string line;
        vector<string> lines;
        fstream infile;
        std::istream& nextchar() {
            return infile.get(readChar);
        }
    public:
        FileReader() {
            linenum = 0;
        }
        bool readFile(string fname);
        vector<string>& getLines() {
            return lines;
        }
        void reset() {
            lines.clear();
            linenum = 0;
            if (!line.empty()) line.clear();
        }
};



class SourceBuffer {
    private:
        char eofChar;
        char readChar;
        int inPosition;
        int lineNum;
        vector<string> textLines;
        FileReader scanner;
        void initSourceBuffer(vector<string>& tl) {
            textLines = tl;
            inPosition = 0;
            lineNum = 0;
            eofChar = 0x7F;
            readChar = textLines.at(lineNum).at(inPosition);
        }
    public:
        SourceBuffer() {
        
        }
        int lineNumber() {
            return lineNum;
        }
        void loadFile(string filename) {
            scanner.reset();
            if (scanner.readFile(filename)) {
                initSourceBuffer(scanner.getLines());
            } else {
                readChar = eofChar;
            }
        }
        void loadString(string str) {
            scanner.reset();
            vector<string> line;
            line.push_back(str);
            initSourceBuffer(line);
        }
        bool isEOF() {
            return readChar == eofChar;
        }
        char EOFMarker() const {
            return eofChar;
        }
        char Char() const {
            return readChar;
        }
        char GetChar() {
            if (inPosition == textLines[lineNum].size()-1) {
                if (lineNum == textLines.size()-1) {
                    readChar = eofChar;
                    return readChar;
                }
                lineNum++;
                inPosition = 0;
            } else {
                inPosition++;
            }
            readChar = textLines.at(lineNum).at(inPosition);
            return readChar;
        }
        void UnGetChar() {
            if (inPosition - 1 <= 0) {
                inPosition = 0;
                --lineNum;
            } else {
                --inPosition;
            }
            readChar = textLines.at(lineNum).at(inPosition);
        }
};

#endif