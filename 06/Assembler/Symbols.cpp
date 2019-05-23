#include "Symbols.h"

void Symbols::FindLabels() {

	while (getline(asmFile, currentCommand)) {
		int i = 0;
		while (currentCommand[i] == ' ' || currentCommand[i] == '\t') {
			i++;
		}
		if (currentCommand[i] != '/' && currentCommand[i] !='(' && i < currentCommand.size()) {
			currentROMNum++;
		}
		if (currentCommand[i] == '(') {
			HandleLabel(i+1);
		}
		
	}
}

void Symbols::FindSymbols() {
	while (getline(asmFile, currentCommand)) {
		int i = 0;
		while (currentCommand[i] == ' ' || currentCommand[i] == '\t') {
			i++;
		}
		
		if (currentCommand[i] == '@' && (currentCommand[i + 1] < '0' || currentCommand[i + 1] > '9')) {
			HandleAssign(i + 1);
		}
	}
	
}

void Symbols::HandleAssign(int i) {
	std::string shortCommand = currentCommand.substr(i, std::string::npos);
	int x = shortCommand.find(' ');
	std::string assign = shortCommand.substr(0, x);
	if (!Contains(assign)) {
		AddEntry(assign, std::to_string(++currentRAMNum));
	}
}

void Symbols::HandleLabel(int i) {

	int x = currentCommand.find(')');
	std::string label = currentCommand.substr(i, x - i);
	int labelVal = currentROMNum + 1;
	symbolTable.insert(std::pair<std::string, std::string>(label, std::to_string(labelVal) ));

}

void Symbols::AddEntry(std::string name, std::string address) {
	symbolTable.insert(std::pair<std::string, std::string>(name, address));
}

bool Symbols::Contains(std::string symbol) {
	std::map<std::string, std::string>::iterator itr;
	for (itr = symbolTable.begin(); itr != symbolTable.end(); itr++) {
		if (itr->first == symbol) {
			return(true);
		}
	}
	return(false);
}

Symbols::Symbols(std::string filePath) {
	currentROMNum = -1;
	currentRAMNum = 1023;
	asmFile.open(filePath);

	HandleFixed();
	FindLabels();
	asmFile.clear();
	asmFile.seekg(0, std::ios::beg);
	FindSymbols();
}

void Symbols::printTable() {
	std::map<std::string, std::string>::iterator itr;
	std::cout << "Name" << "\tValue" << std::endl;
	for (itr = symbolTable.begin(); itr != symbolTable.end(); itr++) {
		std::cout << itr->first << "\t" << itr->second << std::endl;
	}
}

std::map<std::string, std::string> Symbols::ReturnTable() {
	return(symbolTable);
}


void Symbols::HandleFixed(){
	symbolTable.insert(std::pair<std::string, std::string>("SP", "0"));
	symbolTable.insert(std::pair<std::string, std::string>("LCL", "1"));
	symbolTable.insert(std::pair<std::string, std::string>("ARG", "2"));
	symbolTable.insert(std::pair<std::string, std::string>("THIS", "3"));
	symbolTable.insert(std::pair<std::string, std::string>("THAT", "4"));
	symbolTable.insert(std::pair<std::string, std::string>("R0", "0"));
	symbolTable.insert(std::pair<std::string, std::string>("R1", "1"));
	symbolTable.insert(std::pair<std::string, std::string>("R2", "2"));
	symbolTable.insert(std::pair<std::string, std::string>("R3", "3"));
	symbolTable.insert(std::pair<std::string, std::string>("R4", "4"));
	symbolTable.insert(std::pair<std::string, std::string>("R5", "5"));
	symbolTable.insert(std::pair<std::string, std::string>("R6", "6"));
	symbolTable.insert(std::pair<std::string, std::string>("R7", "7"));
	symbolTable.insert(std::pair<std::string, std::string>("R8", "8"));
	symbolTable.insert(std::pair<std::string, std::string>("R9", "9"));
	symbolTable.insert(std::pair<std::string, std::string>("R10", "10"));
	symbolTable.insert(std::pair<std::string, std::string>("R11", "11"));
	symbolTable.insert(std::pair<std::string, std::string>("R12", "12"));
	symbolTable.insert(std::pair<std::string, std::string>("R13", "13"));
	symbolTable.insert(std::pair<std::string, std::string>("R14", "14"));
	symbolTable.insert(std::pair<std::string, std::string>("R15", "15"));
	symbolTable.insert(std::pair<std::string, std::string>("SCREEN", "16384"));
	symbolTable.insert(std::pair<std::string, std::string>("KBD", "24576"));
}