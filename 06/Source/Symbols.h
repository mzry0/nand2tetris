#pragma once

#include<string>
#include<fstream>
#include<map>
#include<iostream>

class Symbols {

private:

	std::ifstream asmFile;
	std::map<std::string, std::string> symbolTable;
	std::string currentCommand;
	int currentROMNum, currentRAMNum;

public:

	Symbols(std::string filePath);
	void FindLabels();
	void FindSymbols();
	void HandleLabel(int i);
	void HandleAssign(int i);
	void HandleFixed();
	bool Contains(std::string symbol);
	void AddEntry(std::string name, std::string address);
	void printTable();
	std::map<std::string, std::string> ReturnTable();

};