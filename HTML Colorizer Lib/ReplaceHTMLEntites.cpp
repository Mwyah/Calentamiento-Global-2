//
// ReplaceHTMLEntities.cpp
//

#include "ReplaceHTMLEntities.hpp"


namespace {

class EntityPair final {
public:
	EntityPair(std::string entity, std::string replacer) {
		_entity = entity;
		_replacer = replacer;
	}

	inline const std::string& entity() const { return _entity; };
	inline const std::string& replacer() const { return _replacer; };

private:
	std::string _entity, _replacer;
};


std::array<EntityPair, 3> pairs = {EntityPair("&", "&amp;"), 
								   EntityPair("<", "&lt;"), 
								   EntityPair(">", "&gt;")};

}

void replace_HTML_entities(std::string& str) {
	for (const auto& item : pairs) {

		size_t pos = 0;
		while (true) {
			pos = str.find(item.entity(), pos);

			if (pos == str.npos) break;

			str.replace(pos, 1, item.replacer());

			pos += item.replacer().length();
		}
	}
}