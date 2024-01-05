#pragma once
#include "Main.h"



std::set<TextField::PairTextFieldComparisonResult>::iterator TextField::PairTextFieldComparisonResult::CompareTextField(const TextField &basic, const TextField &secondary)
{
	const std::vector<TextField::TextLenthRow> &bas_TextLenth = basic.TextLenth, &sec_TextLenth = secondary.TextLenth;
	const std::vector<HASH<std::string>> &bas_Hash = basic.Hash, &sec_Hash = secondary.Hash;
	

	std::vector<TextField::ComparisonResultRow> bas_result = {}, sec_result = {};
	
	std::vector<std::pair<std::size_t, std::size_t>> matched = TextField::PairTextFieldComparisonResult::DiffAlgorithm(bas_Hash, sec_Hash);
	std::size_t bas_start = 0, sec_start = 0;
	for (std::pair<std::size_t, std::size_t> fin : matched) {
		std::size_t &bas_fin = fin.first, &sec_fin = fin.second;

		if (bas_fin > bas_start || sec_fin > sec_start) {
			TextField::PairTextFieldComparisonResult::CompareWord(bas_result, sec_result, basic, secondary, bas_start, bas_fin, sec_start, sec_fin);
		}
		bas_start = bas_fin + 1;
		sec_start = sec_fin + 1;
		bas_result.push_back({ std::vector<COLOUR>{COLOUR::NOT_CHANGED}, &bas_TextLenth[bas_fin] });
		sec_result.push_back({ std::vector<COLOUR>{COLOUR::NOT_CHANGED}, &sec_TextLenth[sec_fin] });
	}
	TextField::PairTextFieldComparisonResult::CompareWord(bas_result, sec_result, basic, secondary, bas_start, bas_TextLenth.size(), sec_start, sec_TextLenth.size());


	return AllPairTextFieldComparisonResult.insert(TextField::PairTextFieldComparisonResult{ {basic.getMyHASH(), bas_result}, { secondary.getMyHASH(), sec_result }}).first;
}

void TextField::PairTextFieldComparisonResult::CompareWord(std::vector<TextField::ComparisonResultRow>& bas_result, std::vector<TextField::ComparisonResultRow> &sec_result, const TextField &basic, const TextField &secondary, std::size_t bas_start, std::size_t bas_fin, std::size_t sec_start, std::size_t sec_fin)
{
	const std::vector<TextField::TextLenthRow> &bas_TextLenth = basic.TextLenth, &sec_TextLenth = secondary.TextLenth;

	std::string bas, sec;
	for (std::size_t i = bas_start; i < bas_fin; i++)
	{
		bas += basic.TextLenth[i].text;// +'\n';
	}
	for (std::size_t i = sec_start; i < sec_fin; i++)
	{
		sec += secondary.TextLenth[i].text;// +'\n';
	}

	std::vector<std::pair<std::size_t, std::size_t>> matched = TextField::PairTextFieldComparisonResult::DiffAlgorithm(bas, sec);

	//std::size_t row = 0, sum_prev_row = 0;
	//for (std::pair<std::size_t, std::size_t> &fin : matched) {
	//	std::size_t &bas_fin = fin.first, &sec_fin = fin.second;

	//	if(sum_prev_row + )
	//}

	std::size_t row_margin = 0, matched_iter = 0;
	for (std::size_t i = bas_start; i < bas_fin; i++)
	{
		std::size_t col_red = 0;

		bas_result.push_back({ std::vector<COLOUR>{COLOUR::CHANGED}, &bas_TextLenth[i] });
		std::vector<COLOUR>& row_col = bas_result[bas_result.size() - 1].ColourRow;
		for (std::size_t j = 0; j < bas_TextLenth[i].text.size(); j++)
		{
			std::size_t step = bas_TextLenth[i].text[j] == '\t' ? tab_len : 1;
			
			if (matched_iter < matched.size() && row_margin + j == matched[matched_iter].first) {
				matched_iter++;
				for (std::size_t s = 0; s < step; s++)
				{
					row_col.push_back(COLOUR::NOT_CHANGED);
				}
			}
			else {
				for (std::size_t s = 0; s < step; s++)
				{
					row_col.push_back(COLOUR::ERASED);
					col_red++;
				}
			}
		}
		row_margin += bas_TextLenth[i].text.size();

/*		if (col_red == 0) {
			row_col.clear();
			row_col.push_back(COLOUR::NOT_CHANGED);
		}else*/ 
		if (col_red * 4 >= bas_TextLenth[i].lenth * 3) {
			row_col.clear();
			row_col.push_back(COLOUR::ERASED);
		}
	}

	for (std::size_t i = bas_fin - bas_start; i < sec_fin - sec_start; i++)
	{
		bas_result.push_back({ std::vector<COLOUR>{COLOUR::EMPTY}, nullptr });
	}

	row_margin = 0, matched_iter = 0;;
	for (std::size_t i = sec_start; i < sec_fin; i++)
	{
		sec_result.push_back({ std::vector<COLOUR>{COLOUR::CHANGED}, &sec_TextLenth[i] });
		std::vector<COLOUR> &row_col = sec_result[sec_result.size() - 1].ColourRow;
		for (std::size_t j = 0; j < sec_TextLenth[i].text.size(); j++)
		{
			std::size_t step = sec_TextLenth[i].text[j] == '\t' ? tab_len : 1;

			if (matched_iter < matched.size() && row_margin + j == matched[matched_iter].second) {
				matched_iter++;
				for (std::size_t s = 0; s < step; s++)
				{
					row_col.push_back(COLOUR::NOT_CHANGED);
				}
			}
			else {
				for (std::size_t s = 0; s < step; s++)
				{
					row_col.push_back(COLOUR::ADDED);
				}
			}
		}
		row_margin += sec_TextLenth[i].text.size();

		//switch(bas_result[sec_result.size() - 1].ColourRow[0]) {
		////case COLOUR::NOT_CHANGED:
		////	row_col.clear();
		////	row_col.push_back(COLOUR::NOT_CHANGED);
		////	break;
		//case COLOUR::ERASED:
		//case COLOUR::EMPTY:
		//	row_col.clear();
		//	row_col.push_back(COLOUR::ADDED);
		//	break;
		//}
		if (bas_result[sec_result.size() - 1].ColourRow[0] == COLOUR::ERASED || bas_result[sec_result.size() - 1].ColourRow[0] == COLOUR::EMPTY) {
			row_col.clear();
			row_col.push_back(COLOUR::ADDED);
		}

	}

	for (std::size_t i = sec_fin - sec_start; i < bas_fin - bas_start; i++)
	{
		sec_result.push_back({ std::vector<COLOUR>{COLOUR::EMPTY}, nullptr });
	}


	//std::vector<std::vector<std::size_t>> previous(bas_fin - bas_start + 1, std::vector<std::size_t>(sec_fin - sec_start + 1, 0));

	//for (int i = bas_fin - bas_start - 1; i >= 0; --i)  // !!!!!!!!!!!! int 
	//{
	//	for (int j = sec_fin - sec_start - 1; j >= 0; --j)
	//	{
	//		std::size_t tmp = TextField::PairTextFieldComparisonResult::DiffLenAlgorithm(basic.HashWord[i], secondary.HashWord[j]);
	//		previous[i][j] = (std::max)(tmp + previous[i + 1][j + 1], (std::max)(previous[i + 1][j], previous[i][j + 1]));
	//	}
	//}

	//std::vector<std::pair<std::size_t, std::size_t>> result;  // какая строка соединяется с какой
	//result.reserve(previous[0][0]);

	//std::size_t i = 0, j = 0;

	//while (i < bas_fin - bas_start - 1 && j < sec_fin - sec_start - 1) {
	//	if (basic[i] == secondary[j]) {
	//		result.push_back({ i++, j++ });
	//	}
	//	else if (previous[i + 1][j] > previous[i][j + 1]) {
	//		++i;
	//	}
	//	else {
	//		++j;
	//	}
	//}
}


