//
// Image.hpp
//

#ifndef _CMG2_IMAGE_HPP_
#define _CMG2_IMAGE_HPP_

#include "Range.hpp"


class Image {
public:
	Image();
	Image(int rows, int cols, int channels);
	Image(int rows, int cols, int channels, unsigned char* data);

	Image(const Image& image);
	Image(const Image& image, const Range& rowRange, const Range& colRange);

	virtual ~Image();

	Image& operator=(const Image& image);
	Image operator()(const Range& rowRange, const Range& colRange) const;

	Image clone() const;
	void cloneTo(Image& image) const;
	void create(int rows, int cols, int channels);
	bool empty() const;

	void release();

	Image col(int x) const;
	Image colRange(const Range& range) const;

	Image row(int y) const;
	Image rowRange(const Range& range) const;

	const unsigned char* data() const;
	unsigned char* data();

	int rows() const;
	int cols() const;
	int total() const;
	int channels() const;

	unsigned char& at(int index);
	const unsigned char& at(int index) const;

	static Image zeros(int rows, int cols, int channels);
	static Image values(int rows, int cols, int channels, unsigned char value);

	size_t countRef() const;

private:
	Range _rowRange = Range();
	Range _colRange = Range();
	int totalColLen = 0;
	int _channels = 0;
	unsigned char* _data = nullptr;
	size_t* _countRef = nullptr;
	bool isOuterData = false;

	unsigned char* copyData() const;

};


#endif