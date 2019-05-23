#include "Parser.h"
#include "Code.h"
#include "Symbols.h"


int main(int argc, char *argv[]) {

	std::string input(argv[1]);
	std::string output(argv[2]);
	std::string dest, comp, jump;
	std::string address;
	Symbols symbols(input);
	Parser parser(input, symbols.ReturnTable());
	Code code(output);
	
	while (parser.HasMoreCommands()) {
		commandType type = parser.ACLType();
		if (type == commandType::C_COMMAND) {

			comp = parser.Comp();
			dest = parser.Dest();
			jump = parser.Jump();

			code.Convert(comp, subsection::COMP);
			code.Convert(dest, subsection::DEST);
			code.Convert(jump, subsection::JMP);
			code.Endline();
		}
		else if (type == commandType::A_COMMAND) {
			address = parser.ACommand();
			code.Dec2bin(address);
			code.Endline();
		}

	}
	return 0;

}
/*void main() {
	Symbols symbols("fill.asm");
	symbols.printTable();
	std::cin.get();
}*/