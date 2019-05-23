#pragma once
#include <string>
#include <fstream>
#include <map>

enum class commandType { A_COMMAND, C_COMMAND, L_COMMAND, IGNORE };

class Parser {
private:
	std::string currentCommand;
	std::ifstream asmFile;
	std::map<std::string, std::string> symbolTable;
public:
	Parser(std::string filePath, std::map<std::string, std::string> table);
	bool HasMoreCommands();
	commandType ACLType();
	std::string ACommand();
	std::string Symbol();
	std::string Dest();
	std::string Comp();
	std::string Jump();
	~Parser();
};