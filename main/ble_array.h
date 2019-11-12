#pragma once

#include <array>
#include <stdexcept>


namespace ble {


struct ArrayTag {};

template<size_t Size>
class Array
	: public std::array<uint8_t, Size>
	, private ArrayTag
{
private:
	using Base = std::array<uint8_t, Size>;

public:
	Array& operator=(std::initializer_list<uint8_t> ilist) {
		if (ilist.size() > Size) {
			throw std::out_of_range("arr = list");
		}
		std::copy(ilist.begin(), ilist.end(), Base::begin());
		usedSize = ilist.size();
		return *this;
	}

	void SetUsedSize(size_t used) {
		if (used > Size) {
			throw std::out_of_range("arr.SetUsedSize");
		}
		usedSize = used;
	}

	size_t GetUsedSize() const noexcept { return usedSize; }

private:
	size_t usedSize = 0;
};


} // namespace ble
