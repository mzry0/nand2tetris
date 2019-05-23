#include "Code.h"

Code::Code(std::string outPath) {
	binaryFile.open(outPath);
	destConversion[0] = { "", "000" };
	destConversion[1] = { "M", "001" };
	destConversion[2] = { "D","010" };
	destConversion[3] = { "MD", "011" };
	destConversion[4] = { "A", "100" };
	destConversion[5] = { "AM", "101" };
	destConversion[6] = { "AD", "110" };
	destConversion[7] = { "AMD", "111"};

	compConversion[0] =  { "0", "0101010"};    compConversion[1] =  { "1", "0111111"};
	compConversion[2] =  { "-1", "0111010" };  compConversion[3] =  { "D", "0001100" };
	compConversion[4] =  { "A", "0110000" };   compConversion[5] =  { "!D", "0001101" };
	compConversion[6] =  { "!A", "0110001" };  compConversion[7] =  { "-D", "0001111" };
	compConversion[8] =  { "-A", "0110011" };  compConversion[9] =  { "D+1", "0011111" };
	compConversion[10] = { "A+1", "0110111" }; compConversion[11] = { "D-1", "0001110" };
	compConversion[12] = { "A-1", "0110010" }; compConversion[13] = { "D+A", "0000010" };
	compConversion[14] = { "D-A", "0010011" }; compConversion[15] = { "A-D", "0000111" };
	compConversion[16] = { "D&A", "0000000" }; compConversion[17] = { "D|A", "0010101" };
	compConversion[18] = { "M", "1110000" };   compConversion[19] = { "!M", "1110001" };
	compConversion[20] = { "-M", "1110011" };  compConversion[21] = { "M+1", "1110111" };
	compConversion[22] = { "M-1", "1110010" }; compConversion[23] = { "D+M", "1000010" };
	compConversion[24] = { "D-M", "1010011" }; compConversion[25] = { "M-D", "1000111" };
	compConversion[26] = { "D&M", "1000000" }; compConversion[27] = { "D|M", "1010101" };

	jumpConversion[0] = {"", "000"};
	jumpConversion[1] = {"JGT", "001"};
	jumpConversion[2] = {"JGE", "011"};
	jumpConversion[3] = {"JEQ", "010"};
	jumpConversion[4] = {"JLT", "100"};
	jumpConversion[5] = {"JNE", "101"};
	jumpConversion[6] = {"JLE", "110"};
	jumpConversion[7] = {"JMP", "111"};
}

void Code::Convert(std::string command, subsection sect) {

	std::string shortCommand;
	int n = 0;
	
	for (int i = 0; i < command.size(); i++) {
		if (command[i] != ' ') {
			shortCommand.resize(n + 1);
			shortCommand[n++] = command[i];
		}
	}
	if (sect == subsection::DEST) {
		//std::cout << "DESTshortCommand: " << shortCommand << std::endl;
		for (int i = 0; i < 8; i++) {
			if (destConversion[i].in == shortCommand) {
				binaryFile << destConversion[i].out;
				break;
			}
		}
	}
	else if (sect == subsection::COMP) {
		//std::cout << "COMPshortCommand: " << shortCommand << std::endl;
		for (int i = 0; i < 28; i++) {
			if (compConversion[i].in == shortCommand) {
				binaryFile << "111" << compConversion[i].out;
				break;
			}
		}
	}
	else if (sect == subsection::JMP) {
		//std::cout << "JMPshortCommand: " << shortCommand << std::endl;
		//std::cout << " jmp shortCommand len = " << shortCommand.size() << std::endl;
		for (int i = 0; i < 8; i++) {
			if (jumpConversion[i].in == shortCommand) {
				binaryFile << jumpConversion[i].out;
				break;
			}
		}
	}
}
void Code::Dec2bin(std::string command) {
	std::string x("0000000000000000");
	//std::cout << "x(before) = " << x << std::endl;
	int dec = std::stoi(command);
	if (dec == 0) {
		binaryFile << x;
		return;
	}
	int i = 15;
	while (dec >= 2) {
		x[i] = 48 + (dec % 2);
		dec /= 2;
		i--;
	}
	x[i] = 49;
	binaryFile << x;
}

void Code::Endline() {
	binaryFile << "\n";
}

Code::~Code() {
	binaryFile.close();
}



