//
// main.cpp
//

#include "..\HTML Colorizer Lib\HTMLRuleParser.hpp"
#include "..\HTML Colorizer Lib\HTMLColorizer.hpp"
#include <fstream>


int main(int argc, char* argv[]) {

	if (argc == 4) {
		std::ifstream ruleFile(argv[1]);
		std::ifstream inputFile(argv[2]);
		std::ofstream outputFile(argv[3]);

		if (ruleFile.is_open() && inputFile.is_open() && outputFile.is_open()) {
			outputFile.clear();

			HTMLRuleParser parser;
			parser.parse(ruleFile);

			HTMLColorizer colorizer;
			for (const auto& it : parser)
				colorizer.addRule(it);

			colorizer.colorize(inputFile, outputFile);
		}

		if (ruleFile.is_open()) ruleFile.close();
		if (inputFile.is_open()) inputFile.close();
		if (outputFile.is_open()) outputFile.close();
	}

	return EXIT_SUCCESS;
}