//
// main.cpp
//

#include "..\HTML Colorizer Lib\HTMLRuleParser.hpp"
#include "..\HTML Colorizer Lib\HTMLColorizer.hpp"
#include <fstream>
#include <iostream>


// Debug argument line: "ruleFile.txt" "inputFile.txt" "outputFile.html"

int main(int argc, char* argv[]) {

	if (argc == 4) {

		std::ifstream ruleFile(argv[1]);
		std::ifstream inputFile(argv[2]);
		std::ofstream outputFile(argv[3]);

		if (ruleFile.is_open() && inputFile.is_open() && outputFile.is_open()) {
			outputFile.clear();

			HTMLColorizer colorizer;
			HTMLRule rule = HTMLRuleParser::parse(ruleFile);
			for (;!rule.empty(); rule = HTMLRuleParser::parse(ruleFile))
				colorizer.addRule(rule);

			colorizer.colorize(inputFile, outputFile);
		}

		if (ruleFile.is_open()) ruleFile.close();
		if (inputFile.is_open()) inputFile.close();
		if (outputFile.is_open()) outputFile.close();
	}

	return EXIT_SUCCESS;
}