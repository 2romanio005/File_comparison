#pragma once
#include "1Connection.h"

class TextField {
public:
	struct TextLenthRow {
		std::string text;
		std::size_t lenth;
	};

	/*
	struct SortedHashRow {
		HASH<std::string> hash;
		std::size_t index;

		bool operator<(const TextField::SortedHashRow &other) const {
			if (this->hash != other.hash) {
				return this->hash < other.hash;
			}
			return this->index < other.index;
		}
	};
	*/

	struct ComparisonResultRow {
		std::vector<COLOUR> ColourRow = {};    			// цвет строки в [][0] и цвета букв в [][1...] 
		TextField::TextLenthRow const *TextLenthRow = nullptr;
	};

	class PairTextFieldComparisonResult {
	public:
		struct TextFieldComparisonResult {
			~TextFieldComparisonResult() {

			}

			const HASH<std::string> TextFieldHASH;
			const std::vector<TextField::ComparisonResultRow> Result;

			bool operator==(const TextFieldComparisonResult &other) const {
				return this->TextFieldHASH == other.TextFieldHASH;
			}
			bool operator!=(const TextFieldComparisonResult &other) const {
				return !(this->operator==(other));
			}
			bool operator<(const TextFieldComparisonResult &other) const {
				return this->TextFieldHASH < other.TextFieldHASH;
			}
		};

		const TextFieldComparisonResult basic;
		const TextFieldComparisonResult secondary;

		bool operator==(const PairTextFieldComparisonResult &other) const {
			return this->basic == other.basic && this->secondary == other.secondary;
		}
		bool operator!=(const PairTextFieldComparisonResult &other) const {
			return !(this->operator==(other));
		}
		bool operator<(const PairTextFieldComparisonResult &other) const {
			if (this->basic == other.basic) {
				return this->secondary < other.secondary;
			}
			return this->basic < other.basic;
		}


		static std::set<TextField::PairTextFieldComparisonResult>::iterator CompareTextField(const TextField &basic, const TextField &secondary);
	private:
		//static void CompareTextFieldPiece(std::vector<TextField::ComparisonResultRow> &bas_result, std::vector<TextField::ComparisonResultRow> &sec_result, const TextField &basic, const TextField &secondary, std::size_t bas_start, std::size_t bas_fin, std::vector<std::pair<std::size_t *, std::size_t>> &sSimilar);

		template<typename T>
		static std::vector<std::pair<std::size_t, std::size_t>> DiffAlgorithm(const T &basic, const T &secondary);

		template<typename T>
		static std::size_t DiffLenAlgorithm(const T &basic, const T &secondary);



		static void CompareWord(std::vector<TextField::ComparisonResultRow> &bas_result, std::vector<TextField::ComparisonResultRow> &sec_result, const TextField &basic, const TextField &secondary, std::size_t bas_start, std::size_t bas_fin, std::size_t sec_start, std::size_t sec_fin);
		/*
			CompareWord
			CompareWordPiece
			CompareChar
			CompareCharPice
		*/
	};

public:
	TextField();
	TextField(const std::string &path);
	~TextField();

	const HASH<std::string> &getMyHASH() const;
	std::size_t getNumberColumns() const;

	bool operator==(const TextField &other) const;
	bool operator!=(const TextField &other) const;
	bool operator<(const TextField &other) const;

private:
	HASH<std::string> MyHASH = { "" };

	std::vector<TextField::TextLenthRow> TextLenth;
	std::vector<HASH<std::string>> Hash;
	std::vector<std::vector<std::pair<HASH<std::string>, std::size_t>>> HashWord;

	void CreateHashes();


	std::size_t NumberColumns;
	void updateNumberColumns();



	friend class TextField::PairTextFieldComparisonResult;
};








template<typename T>
inline std::vector<std::pair<std::size_t, std::size_t>> TextField::PairTextFieldComparisonResult::DiffAlgorithm(const T &basic, const T &secondary)
{
	std::vector<std::vector<std::size_t>> previous(basic.size() + 1, std::vector<std::size_t>(secondary.size() + 1, 0));

	for (std::size_t i = basic.size(); i > 0; --i) 
	{
		for (std::size_t j = secondary.size(); j > 0; --j)
		{
			if (basic[i - 1] == secondary[j - 1]) {
				previous[i - 1][j - 1] = 1 + previous[i][j];
			}
			else {
				previous[i - 1][j - 1] = (std::max)(previous[i][j - 1], previous[i - 1][j]);
			}
		}
	}

	std::vector<std::pair<std::size_t, std::size_t>> result;
	result.reserve(previous[0][0]);

	std::size_t i = 0, j = 0;

	while (i < basic.size() && j < secondary.size()) {
		if (basic[i] == secondary[j]) {
			result.push_back({ i++, j++ });
		}
		else if (previous[i + 1][j] > previous[i][j + 1]) {
			++i;
		}
		else {
			++j;
		}
	}

	return result;
}




template<typename T>
inline std::size_t TextField::PairTextFieldComparisonResult::DiffLenAlgorithm(const T &basic, const T &secondary)
{
	std::vector<std::vector<std::size_t>> previous(2, std::vector<std::size_t>(secondary.size() + 1, 0));

	for (std::size_t i = basic.size(); i > 0; --i)
	{
		for (std::size_t j = secondary.size(); j > 0; --j)
		{
			if (basic[i - 1] == secondary[j - 1]) {
				previous[(i - 1) % 2][j - 1] = 1 + previous[i % 2][j];
			}
			else {
				previous[(i - 1) % 2][j - 1] = (std::max)(previous[i % 2][j - 1], previous[(i - 1) % 2][j]);
			}
		}
	}

	return previous[0][0];
}














