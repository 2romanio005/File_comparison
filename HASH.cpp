#pragma once
#include "Main.h"

template class HASH<std::string>;

template<typename T>
HASH<T>::HASH(const std::size_t sample)
{
	this->Hash = sample;
}

template<typename T>
HASH<T>::HASH(const HASH<T> &sample) : HASH(sample.Hash)
{
}

template<typename T>
HASH<T>::HASH(const T &original)
{
	this->Hash = std::hash<T> {}(original);
}


template<typename T>
HASH<T> &HASH<T>::operator=(const HASH<T> &other)
{
	this->Hash = other.Hash;

	return *this;
}

template<typename T>
HASH<T> &HASH<T>::operator+=(const HASH<T> &other)
{
	this->Hash ^= other.Hash + 0x9e3779b9 + (this->Hash << 6) + (this->Hash >> 2);

	return *this;
}


template<typename T>
HASH<T> HASH<T>::operator+(const HASH<T> &other) const
{
	HASH res(this->Hash ^ (other.Hash + 0x9e3779b9 + (this->Hash << 6) + (this->Hash >> 2)));
	return res;
}



template<typename T>
bool HASH<T>::operator==(const HASH<T> &other) const
{
	return this->Hash == other.Hash;
}

template<typename T>
bool HASH<T>::operator!=(const HASH<T> &other) const
{
	return !(this->operator==(other));
}

template<typename T>
bool HASH<T>::operator<(const HASH<T> &other) const
{
	return this->Hash < other.Hash;
}

template<typename T>
bool HASH<T>::operator<=(const HASH<T> &other) const
{
	return !(this->operator>(other));
}

template<typename T>
bool HASH<T>::operator>(const HASH<T> &other) const
{
	return this->Hash > other.Hash;
}

template<typename T>
bool HASH<T>::operator>=(const HASH<T> &other) const
{
	return !(this->operator<(other));
}


