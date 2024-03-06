#pragma once
#include "Main.h"

TextField::TextField()
{
	this->NumberColumns = 0;
}

TextField::TextField(const std::string &path) : TextField()
{
	this->TextLenth.clear();
	this->NumberColumns = 0;

	std::ifstream fin(path);

	if (fin.fail() || fin.is_open() == false) {
		throw "Не удалось открыть файл";
	}

	std::string s;
	std::size_t size;
	while (!fin.eof()) {
		std::getline(fin, s);

		size = 0;
		for (char ch : s) {
			size += (ch == '\t' ? tab_len : 1);
		}
		this->TextLenth.push_back(TextField::TextLenthRow { s, size });
		this->NumberColumns = (std::max)(this->NumberColumns, size);
	}
	fin.close();

	this->CreateHashes();

	this->updateNumberColumns();
}

TextField::~TextField()
{
}


void TextField::CreateHashes()
{
	this->MyHASH = { "" };
	this->Hash.clear();
	this->HashWord.clear();
	for (TextField::TextLenthRow &row : this->TextLenth) {
		HASH<std::string> hash(row.text);
		this->MyHASH += hash;

		this->Hash.push_back(hash);

		this->HashWord.push_back({});
		std::size_t start = 0;
		for (std::size_t fin = 0; fin < row.text.size(); fin++)
		{
			if (row.text[fin] == ' ') {
				std::string word = row.text.substr(start, fin + 1 - start);
				this->HashWord[this->HashWord.size() - 1].push_back({ HASH<std::string>{word}, word.size() });
				start = fin + 1;
			}
		}
		std::string word = row.text.substr(start);
		this->HashWord[this->HashWord.size() - 1].push_back({ HASH<std::string>{word}, word.size() });
	}

	//std::sort(this->SortedHash.begin(), this->SortedHash.end());
}



const HASH<std::string> &TextField::getMyHASH() const
{
	return this->MyHASH;
}


std::size_t TextField::getNumberColumns() const
{
	return this->NumberColumns;
}

void TextField::updateNumberColumns()
{
	this->NumberColumns = this->TextLenth[0].lenth;
	for (std::size_t i = 1; i < this->TextLenth.size(); i++)
	{
		this->NumberColumns = (std::max)(this->NumberColumns, this->TextLenth[i].lenth);
	}
	//this->updateNumberPixelColumns();
}



bool TextField::operator==(const TextField &other) const
{
	return this->MyHASH == other.MyHASH;
}

bool TextField::operator!=(const TextField &other) const
{
	return !(this->operator==(other));
}

bool TextField::operator<(const TextField &other) const
{
	return this->MyHASH < other.MyHASH;
}
