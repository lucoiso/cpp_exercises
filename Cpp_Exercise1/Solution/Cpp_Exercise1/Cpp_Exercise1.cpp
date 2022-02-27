#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cctype>
#include <future>

using namespace std;

template <typename T>
concept IsStr = requires (T)
{
	convertible_to<T, const char[]>;
};

// Filter alphabetic characters from string
template<typename T> requires IsStr<T>
constexpr void FilterAlphabetic(T& InStr)
{
	erase_if(InStr, [](const char ch) -> bool
	{
		const bool IsAlpha = !isalpha(ch) && ch != 'ç' && ch != ' ';
		if (IsAlpha)
		{
			cout << "Removing non-alpha character : " << ch << endl;
		}
		return IsAlpha;
	});
}

// Hide and seek: find each vowel in a string
constexpr char VowelsRef[]{ 'a', 'e', 'i', 'o', 'u' };

template <typename T> 
requires IsStr<T>
constexpr vector<pair<size_t, char>> FindVowelsInStr(const T InVal)
{
	vector<pair<size_t, char>> Output;

	for (const char i : VowelsRef)
	{
		for (string::const_iterator Iterator = InVal.begin(); Iterator != InVal.end(); Iterator++)
		{
			if (*Iterator == i)
			{
				Output.push_back(pair<size_t, char>((Iterator - InVal.begin()), i));
			}
		}
	}

	return Output;
}

bool Loop() 
{
	cout << "\nAnswer: ";
	bool bReturn = true;
	cin >> bReturn;

	return bReturn;
}

int main()
{
	do
	{
		system("cls");

		cout << "Hide and seek: find each vowel in a string" << endl;
		cout << "Type a string: ";

		string Input;
		getline(cin, Input);

		cout << endl;

		FilterAlphabetic(Input);
		cout << endl << "Filtered string: " << Input << endl;

		// Asynchronous function with a future handler
		future<vector<pair<size_t, char>>> AsyncTask = async(launch::async, FindVowelsInStr<string>, Input);
		const auto FoundIndexes = AsyncTask.get();

		// Lambda function to print values
		auto PrintFoundIndexes = [](const auto Container) -> void
		{
			if (Container.size() > 0)
			{
				cout << "Vowels found and their indexes: " << endl;
				for (const auto i : Container)
				{
					cout << "[" << i.first << "]" << ": " << i.second << "; ";
				}

				cout << endl;
			}
			else
			{
				cout << "Not found any vowels" << endl;
			}
		};

		// Calling lambda function
		PrintFoundIndexes(FoundIndexes);

		cout << "\n1 - Repeat\n0 - Exit" << endl;
	} while (Loop());

	return 0;
}