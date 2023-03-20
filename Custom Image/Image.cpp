//
// Image.cpp
//

#include "Image.hpp"

#include <algorithm>
#include <iostream>


namespace {
	bool isValid(int rows, int cols, int channels) {
		return (rows > 0 && cols > 0 && channels > 0);
	}

	bool isValid(int rows, int cols, int channels, unsigned char* data) {
		return (rows > 0 && cols > 0 && channels > 0 && data);
	}
}

Image::Image() {
	_countRef = new size_t(1);
}

Image::Image(int rows, int cols, int channels) {

	_countRef = new size_t(1);

	if (isValid(rows, cols, channels)) {
		_rowRange = Range(0, rows);
		_colRange = Range(0, cols);
		totalColLen = _colRange.end();
		_channels = channels;
		_data = new unsigned char[total()*_channels];
	}
}

Image::Image(int rows, int cols, int channels, unsigned char* data) {

	_countRef = new size_t(1);

	if (isValid(rows, cols, channels, data)) {
		_rowRange = Range(0, rows);
		_colRange = Range(0, cols);
		totalColLen = _colRange.end();
		_channels = channels;
		_data = data;
		isOuterData = true;
	}
}

Image::Image(const Image& image) {

	_rowRange = image._rowRange;
	_colRange = image._colRange;
	totalColLen = image.totalColLen;
	_channels = image._channels;
	_data = image._data;
	_countRef = image._countRef;
	isOuterData = image.isOuterData;

	(*_countRef)++;
}
Image::Image(const Image& image, const Range& rowRange, const Range& colRange) {

	_rowRange = Range(image._rowRange.start() + rowRange.start(), 
					  std::min(image._rowRange.end(), image._rowRange.start() + rowRange.end()));
	_colRange = Range(image._colRange.start() + colRange.start(),
					  std::min(image._colRange.end(), image._colRange.start() + colRange.end()));
	totalColLen = image.totalColLen;
	_channels = image._channels;
	_data = image._data;
	_countRef = image._countRef;
	isOuterData = image.isOuterData;

	(*_countRef)++;
}

Image::~Image() {

	release();
}

Image& Image::operator=(const Image& image) {

	if (this == &image) {
		return *this;
	}

	_rowRange = image._rowRange;
	_colRange = image._colRange;
	totalColLen = image.totalColLen;
	_channels = image._channels;
	_data = image._data;
	_countRef = image._countRef;
	isOuterData = image.isOuterData;

	(*_countRef)++;

	return *this;
}
Image Image::operator()(const Range& rowRange, const Range& colRange) const{

	return Image(*this, rowRange, colRange);
}

Image Image::clone() const{

	Image res;
	cloneTo(res);

	return res;
}
void Image::cloneTo(Image& image) const{

	if (this != &image) {
		image._colRange = Range(0, cols());
		image._rowRange = Range(0, rows());
		image.totalColLen = cols();
		image._channels = _channels;
		image.release();
		image._data = copyData();
		image._countRef = new size_t(1);
		image.isOuterData = false;
	}
}
void Image::create(int rows, int cols, int channels) {
	
	unsigned char* tmpData = copyData();

	_colRange = Range(0, std::min(cols, this->cols()));
	_rowRange = Range(0, std::min(rows, this->rows()));
	totalColLen = this->cols();
	_channels = channels;
	release();
	_data = tmpData;
	_countRef = new size_t(1);
	isOuterData = false;
}
bool Image::empty() const {

	return (total() == 0 || _data == nullptr);
}

void Image::release() {
	(*_countRef)--;

	if (*_countRef == 0 && !isOuterData) {
		delete[] _data;
		_data = nullptr;
		delete _countRef;
		_countRef = nullptr;
	}
}

Image Image::col(int x) const{

	if (x >= cols())
		return Image();

	Image res = Image(*this);
	res._colRange = Range(x, x+1);

	return res;
}
Image Image::colRange(const Range& range) const{

	Image res = Image(*this);
	res._colRange = Range(_colRange.start() + range.start(),
						  std::min(_colRange.end(), _colRange.start() + range.end()));

	return res;
}

Image Image::row(int y) const{

	if (y >= rows())
		return Image();

	Image res = Image(*this);
	res._rowRange = Range(y, y+1);

	return res;
}
Image Image::rowRange(const Range& range) const{

	Image res = Image(*this);
	res._rowRange = Range(_rowRange.start() + range.start(),
						  std::min(_rowRange.end(), _rowRange.start() + range.end()));

	return res;
}

const unsigned char* Image::data() const { return _data; }
unsigned char* Image::data() { return _data; }

int Image::rows() const { return _rowRange.size(); }
int Image::cols() const { return _colRange.size(); }
int Image::total() const { return rows()*cols(); }
int Image::channels() const { return _channels; }

unsigned char& Image::at(int index) { 
	return _data[_channels*(totalColLen*(_rowRange.start() + index/cols()) + _colRange.start() + index % cols())];
}
const unsigned char& Image::at(int index) const {
	return _data[_channels*(totalColLen*(_rowRange.start() + index/cols()) + index % cols())];
}

Image Image::zeros(int rows, int cols, int channels) {

	if (rows == 0 || cols == 0 || channels == 0) 
		return Image();

	unsigned char* data = new unsigned char[rows*cols*channels];

	for (size_t i = 0; i < rows*cols*channels; i++) 
		data[i] = 0;

	Image res = Image(rows, cols, channels, data);
	res.isOuterData = false;

	return res;

}
Image Image::values(int rows, int cols, int channels, unsigned char value) {

	if (rows == 0 || cols == 0 || channels == 0)
		return Image();

	unsigned char* data = new unsigned char[rows*cols*channels];

	for (size_t i = 0; i < rows*cols*channels; i++)
		data[i] = value;

	Image res = Image(rows, cols, channels, data);
	res.isOuterData = false;

	return res;
}

size_t Image::countRef() const { return *_countRef; }


unsigned char* Image::copyData() const{
	unsigned char* res = new unsigned char[total()*channels()];

	size_t i = 0;
	for (size_t y = _rowRange.start(); y < _rowRange.end(); y++) {
		for (size_t x = _colRange.start(); x < _colRange.end(); x++) {
			for (size_t z = 0; z < channels(); z++) {
				res[i] = _data[(y*totalColLen + x)*_channels + z];
				i++;
			}
		}
	}

	return res;
}