#pragma once
#include <string>
#include <algorithm>
#include "generator.h"

struct PasswordOptions
{
	int passLenght;
	int uppercase;
	int numbers;
	int symbols;
	bool excludeAmbiguius;
	bool excludeSimilar;

	struct StringSets
	{
		std::string ambiguous = "{}[]()/\\'`~,;:.<>\"";
		std::string symbols = "!@#$%^&*-_+=|?";
		std::string similar = "iIl10oO";
	}strSets;

	std::string GetRestricted()
	{
		std::string restricted = "";
		if (excludeAmbiguius) restricted += strSets.ambiguous;
		if (excludeSimilar) restricted += strSets.similar;
		return restricted;
	}

	bool CheckChar(std::string str, char toCheck)
	{
		return (str.find(toCheck) != std::string::npos) ? true : false;
	}

	std::string GetChars(int opt, char min, char max)
	{
		Generator rndNo;
		std::string str = "";
		int i = 0;
		while (i < opt)
		{
			char nextChar = char(rndNo());
			if (((nextChar >= min && nextChar <= max) || CheckChar(strSets.ambiguous, nextChar)) && !CheckChar(GetRestricted(), nextChar))
			{
				str += nextChar;
				i++;
			}
		}
		return str;
	}

	std::string GetSymbols()
	{
		Generator rndNo;
		std::string str = "";
		int i = 0;
		while (i < symbols)
		{
			char nextChar = char(rndNo());
			if (CheckChar(strSets.symbols, nextChar) && !CheckChar(GetRestricted(), nextChar))
			{
				str += nextChar;
				i++;
			}
		}
		return str;
	}

	std::string ShufflePassword(std::string str)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(str.begin(), str.end(), g);
		return str;
	}

	std::string GeneratePassword()
	{
		return ShufflePassword(GetChars(uppercase, 'A', 'Z') + GetChars(numbers, '0', '9') + GetSymbols() + GetChars(passLenght - uppercase - numbers - symbols, 'a', 'z'));
	}
};
