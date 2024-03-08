#pragma once
#include "0Include.h"

template <typename T>
class HASH
{
public:
	HASH(const std::size_t sample);
	HASH(const HASH<T> &sample);
	HASH(const T &original);

	HASH<T> &operator=(const HASH<T> &other);
	HASH<T> &operator+=(const HASH<T> &other);

	HASH<T> operator+(const HASH<T> &other) const;


	bool operator==(const HASH<T> &other) const;
	//bool operator==(const std::size_t other);

	bool operator!=(const HASH<T> &other) const;

	bool operator<(const HASH<T> &other) const;
	//bool operator<(const std::size_t other);

	bool operator<=(const HASH<T> &other) const;
	//bool operator<=(const std::size_t other);

	bool operator>(const HASH<T> &other) const;
	//bool operator>(const std::size_t other);

	bool operator>=(const HASH<T> &other) const;
	//bool operator>=(const std::size_t other);
private:
	std::size_t Hash;
};


#include "HASH.cpp"


