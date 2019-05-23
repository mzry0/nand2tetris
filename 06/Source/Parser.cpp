#include "Parser.h"
#include <string>
#include <fstream>
#include <iostream>

Parser::Parser(std::string filePath, std::map<std::string, std::string> table) {
	asmFile.open(filePath);
	symbolTable = table;

}

bool Parser::HasMoreCommands() {
	if (getline(asmFile, currentCommand))
		return(true);
	else
		return(false);
}
std::string Parser::Symbol() {
	if (currentCommand[0] == '@')
		return(currentCommand.substr(1, currentCommand.size() - 1));
	else 
		return(currentCommand.substr(1, currentCommand.size() - 2));
}
std::string Parser::Dest() {
	int pos = currentCommand.find("=");
	if (pos == std::string::npos)
		return(std::string(""));
	else
		return(currentCommand.substr(0, pos));
}

std::string Parser::Comp()
{
	int pos = currentCommand.find("=");
	if (pos == std::string::npos)
		pos = -1;
	int semcol;
	semcol = currentCommand.find(";");
	if (semcol == std::string::npos)
		semcol = currentCommand.size();
	return(currentCommand.substr(pos + 1, semcol - pos - 1));
}

std::string Parser::Jump()
{
	int semcol = currentCommand.find(";");
	if (semcol == std::string::npos)
		return(std::string(""));
	else
		return(currentCommand.substr(semcol + 1, 3));
	
}

commandType Parser::ACLType() {
	int i = 0;
	while (currentCommand[i] == ' ' || currentCommand[i] == '\t') {
		i++;
	}
	if ((i >= currentCommand.size()) || (currentCommand[i] == '/')) {
		//std::cout << "ignored " << currentCommand << " where i = " << i<<std::endl;
		return (commandType::IGNORE);
	}
	else if (currentCommand[i] == '@')	return (commandType::A_COMMAND);
	else if (currentCommand[i] == '(') return (commandType::L_COMMAND);
	else return (commandType::C_COMMAND);
}

std::string Parser::ACommand() {
	int i = 0;
	while (currentCommand[i] != '@') {
		i++;
	}
	i++;
	std::string shortCommand = currentCommand.substr(i, std::string::npos);
	int x = shortCommand.find(' ');

	if (currentCommand[i] >= '0' && currentCommand[i] <= '9') {
		return(shortCommand.substr(0, x));
	}

	else {
		std::map<std::string, std::string>::iterator itr;
		for (itr = symbolTable.begin(); itr != symbolTable.end(); itr++) {
			std::string cmp = shortCommand.substr(0, x);
			if (itr->first == cmp) {
				std::string x = itr->second;
				return(x);
			}
		}
	}
}

Parser::~Parser() {
	asmFile.close();
}
