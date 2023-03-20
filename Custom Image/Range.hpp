//
// Range.hpp
//

#ifndef _CMG2_RANGE_HPP_
#define _CMG2_RANGE_HPP_


class Range {
public:
	Range(): _start(0), _end(0) {}
	Range(int _start, int _end);

	int size() const;
	bool empty() const;

	int start() const;
	int end() const;

	static Range all();

private:
	int _start, _end;

};


#endif