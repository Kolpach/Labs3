#include <iostream>
#include <string>
#define N 26
using namespace std;
string encript(const string& text,const string& key)
{
	int16_t d = key.size();
	int32_t k = 0, m = 0;
	char V;
	string encripted_text;
	for (size_t i = 0; i < text.size(); ++i)
	{
		k = static_cast<int32_t>(key[i%d]) - 'A';
		m = static_cast<int32_t>(text[i]) - 'A';
		V = static_cast<char>((m + k) % N) + 'A';
		encripted_text += V;
	}
	return encripted_text;
}
string decript(const string& text, const string& key)
{
	int16_t d = key.size();
	int16_t k = 0, m = 0;
	char V;
	string decripted_text;
	for (size_t i = 0; i < text.size(); ++i)
	{
		k = static_cast<int16_t>(key[i%d]) - 'A';
		m = static_cast<int16_t>(text[i]) - 'A';
		V = static_cast<char>((m - k + N) % N) + 'A';//+N Потому что сумма первых двух может быть отрицательна
		decripted_text += V;
	}
	return decripted_text;
}
void check(const string& text)
{
	for (char a : text)
	{
		if (a < 'A' || a > 'Z')
		{
			throw 1;
		}
	}
}
int main()
{
	cout << "Supported letters: A-Z" << endl;
	string text, key;
IF_WRONG_TEXT:
	try
	{
		cout << "Type message: " << endl;
		cin >> text;
		check(text);
	}
	catch (int)
	{
		cout << "Unsupported symbol detected!" << endl;
		cout << "Supported letters: A-Z" << endl;
		goto IF_WRONG_TEXT;
	}

IF_WRONG_KEY:
	try
	{
		cout << "Type code: " << endl;
		cin >> key;
		check(key);
	}
	catch (int)
	{
		cout << "Unsupported symbol detected!" << endl;
		cout << "Supported letters: A-Z" << endl;
		goto IF_WRONG_KEY;
	}

	string result = encript(text, key);
	cout << result << endl;
	result = decript(result, key);
	cout << result << endl;
	system("pause");
	return 0;
}
