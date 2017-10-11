#include "stdafx.h"
#include "CppUnitTest.h"
#include <random>
#include <algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Password
{		
	TEST_CLASS(PasswordTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual("", GeneratePassword({ 7,2,2,1,true,true }).c_str());
		}

		struct PasswordOptions
		{
			int passLenght;
			int uppercase;
			int numbers;
			int symbols;
			bool excludeAmbiguius;
			bool excludeSimilar;
		};

		string GeneratePassword(PasswordOptions options)
		{
			string ambiguous = "{}[]()/\\'\"`~,;:.<>";
			string symbols = "!@#$%^&*-_+=|?";
			string numbers = "1234567890";
			string lowercase = "abcdefghijklmnopqrstuvwxyz";
			string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			string similar = "iIl10oO";
			string password = "";
			int countUpper = 0, countSymbols = 0, countNumbers = 0, countLower = 0;

			static random_device rd;
			static mt19937 generator(rd());
			uniform_int_distribution<int> asciiChar(33, 126);

			while (password.size() < options.passLenght)
			{
				char nextChar = char(asciiChar(generator));
				if (CheckChar(ambiguous, nextChar) && !options.excludeAmbiguius) { password += nextChar; }
				if (CheckChar(similar, nextChar) && !options.excludeSimilar) { password += nextChar; }
				if (CheckChar(symbols, nextChar) && countSymbols < options.symbols) { countSymbols++; password += nextChar; }
				if (CheckChar(lowercase, nextChar) && countLower < (GetLowerCaseLenght(options))) { countLower++; password += nextChar; }
				if (CheckChar(uppercase, nextChar) && countUpper < options.uppercase) { countUpper++; password += nextChar; }
				if (CheckChar(numbers, nextChar) && countNumbers < options.numbers) { countNumbers++; password += nextChar; }
			}

			return password;
		}

		int GetLowerCaseLenght(PasswordOptions options)
		{
			return options.passLenght - options.numbers - options.symbols - options.uppercase;
		}

		bool CheckChar(string str, char toCheck)
		{
			for (int i = 0; i < str.size(); i++)
			{
				if (toCheck == str[i]) return true;
			}
			return false;
		}

	};
}