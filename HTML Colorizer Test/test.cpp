//
// test.cpp
//

#include "gtest/gtest.h"
#include "../HTML Colorizer Lib/HTMLRuleParser.hpp"
#include "../HTML Colorizer Lib/HTMLColorizer.hpp"


TEST(HTMLRuleParser, parseEmpty) {
	std::istringstream iss;

	HTMLRule rule = HTMLRuleParser::parse(iss);
	EXPECT_EQ(rule.empty(), true);
}

TEST(HTMLRuleParser, parseValid) {
	std::istringstream iss("a : 000000\n    \nb&c : 1f0ae3\n\
vector<string> : ff00cc\n<< : ffffff\n<< : 000000");

	HTMLRule arr[5] = {HTMLRuleParser::parse(iss), HTMLRuleParser::parse(iss),
					   HTMLRuleParser::parse(iss), HTMLRuleParser::parse(iss), 
		               HTMLRuleParser::parse(iss)};

	EXPECT_EQ(HTMLRuleParser::parse(iss).empty(), true);

	EXPECT_EQ(arr[0].word(), "a");
	EXPECT_EQ(arr[0].color(), "000000");
	EXPECT_EQ(arr[1].word(), "b&amp;c");
	EXPECT_EQ(arr[1].color(), "1f0ae3");
	EXPECT_EQ(arr[2].word(), "vector&lt;string&gt;");
	EXPECT_EQ(arr[2].color(), "ff00cc");
	EXPECT_EQ(arr[3].word(), "&lt;&lt;");
	EXPECT_EQ(arr[3].color(), "ffffff");
	EXPECT_EQ(arr[4].word(), "&lt;&lt;");
	EXPECT_EQ(arr[4].color(), "000000");
}

TEST(HTMLRuleParser, parseInvalidAndSemiValid) {
	std::istringstream iss("a :: 000000\n f f f : 111111\nt : 3\n\
vector<string> :    \n : 000000");

	HTMLRule arr[2] = {HTMLRuleParser::parse(iss), HTMLRuleParser::parse(iss)};

	EXPECT_EQ(arr[0].word(), "a");
	EXPECT_EQ(arr[0].color(), "000000");
	EXPECT_EQ(arr[1].word(), "f");
	EXPECT_EQ(arr[1].color(), "111111");
}


TEST(HTMLColorizer, emptyColorize) {
	HTMLColorizer colorizer;

	std::istringstream iss("template<class T, class... Args>\n\
constexpr T* construct_at(T* p, Args&&... args); ");

	std::ostringstream oss;

	colorizer.colorize(iss, oss);
	EXPECT_EQ(oss.str(), "template&lt;class T, class... Args&gt;\n\
constexpr T* construct_at(T* p, Args&amp;&amp;... args); ");
}

TEST(HTMLColorizer, NonEmptyColorize) {
	HTMLColorizer colorizer;
	colorizer.addRule({"Sepulka", "e8b520"});
	colorizer.addRule({"Enteropia", "51bcfc"});
	colorizer.addRule({"Ardrites", "28a718"});
	colorizer.addRule({"Sepulkaria", "fc6d46"});
	colorizer.addRule({"Sepuling", "950266"});
	colorizer.addRule({"sepuling", "950266"});
	colorizer.addRule({"pl", "1d8c6e"});
	colorizer.addRule({"sing", "1d8c6e"});
	colorizer.addRule({"see", "1d8c6e"});

	std::istringstream iss("Sepulka - pl.: sepulkas, a prominent element of the civilization of Ardrites from the planet of Enteropia; see \"Sepulkaria\"\n\
Sepulkaria - sing: sepulkarium, establishments used for sepuling; see \"Sepuling\"\n\
Sepuling - an activity of Ardrites from the planet of Enteropia; see \"Sepulka\"");

	std::ostringstream oss;

	colorizer.colorize(iss, oss);
	EXPECT_EQ(oss.str(), R"(<span style="color: #e8b520;">Sepulka</span> - <span style="color: #1d8c6e;">pl</span>.: sepulkas, a prominent element of the civilization of <span style="color: #28a718;">Ardrites</span> from the planet of <span style="color: #51bcfc;">Enteropia</span>; <span style="color: #1d8c6e;">see</span> "<span style="color: #fc6d46;">Sepulkaria</span>"
<span style="color: #fc6d46;">Sepulkaria</span> - <span style="color: #1d8c6e;">sing</span>: sepulkarium, establishments used for <span style="color: #950266;">sepuling</span>; <span style="color: #1d8c6e;">see</span> "<span style="color: #950266;">Sepuling</span>"
<span style="color: #950266;">Sepuling</span> - an activity of <span style="color: #28a718;">Ardrites</span> from the planet of <span style="color: #51bcfc;">Enteropia</span>; <span style="color: #1d8c6e;">see</span> "<span style="color: #e8b520;">Sepulka</span>")");
}

