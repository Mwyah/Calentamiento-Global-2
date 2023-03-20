//
// Range.cpp
//

#include "Range.hpp"

#include <climits>


Range::Range(int _start, int _end) {
	if (_start < 0 || _start >= _end) {
		this->_start = 0;
		this->_end = 0;
	}
	else {
		this->_start = _start;
		this->_end = _end;
	}
}

int Range::size() const { return _end - _start; }
bool Range::empty() const { return this->size() == 0; }

int Range::start() const { return _start; }
int Range::end() const { return _end; }

Range Range::all() { return Range(0, INT_MAX); }