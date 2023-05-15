//
// ReplaceHTMLEntities.cpp
//

#ifndef _CMG2_REPLACE_HTML_ENTITIES_HPP_
#define _CMG2_REPLACE_HTML_ENTITIES_HPP_

#include <string>


inline void replace_HTML_entities(std::string& str) {
	char entities[] = {'&', '<', '>'};
	std::string replacers[] = {"&amp;", "&lt;", "&gt;"};

	for (int i = 0; i < 3; i++) {

		size_t pos = 0;
		while (true) {
			pos = str.find(entities[i], pos);

			if (pos == str.npos) break;

			str.replace(pos, 1, replacers[i]);

			pos += replacers[i].length();
		}
	}
}


#endif