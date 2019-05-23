#pragma once
#include<fstream>
#include<iostream>
#include<string>

enum class subsection {
	DEST = 1, COMP = 2, JMP = 3
};

struct conversion {
	std::string in;
	std::string out;
};

class Code {
private:
	
	conversion destConversion[8];
	conversion compConversion[28];
	conversion jumpConversion[8];

	std::ofstream binaryFile;
	

public:
	Code(std::string outPath);
	void Convert(std::string command, subsection sect);
	void Endline();
	void Dec2bin(std::string command);
	~Code();
	
};