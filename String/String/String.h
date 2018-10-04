#ifndef STRING_H
#define STRING_H

#include <string.h>

class String
{
public:

	String() :
		str(nullptr),
		num_chars(0)
	{ }


	String(const char *string) :

		num_chars(strlen(string)),
		str(new char[num_chars + 1])
	{
		strcpy_s(str, num_chars + 1, string);
	}


	String(const String &string) :

		num_chars(string.num_chars),
		str(new char[num_chars + 1])
	{
		strcpy_s(str, num_chars + 1, string.str);
	}

	~String()
	{
		delete[] str;
	}

	bool empty() const
	{
		return num_chars == 0;
	}

	unsigned int size() const
	{
		return num_chars;
	}

	void clear()
	{
		delete[] str;
		str = nullptr;
		num_chars = 0;
	}

	const char *returnstr() const
	{
		return str;
	}

	void operator=(const String &string)
	{
		// si string cap al objecte en el que estic treballant, no cal fer new
		//sinó sobreescriure Check this everywhere

		delete[] str;
		num_chars = string.num_chars;
		str = new char[num_chars + 1];
		strcpy_s(str, num_chars + 1, string.str);
	}

	String operator+=(const String &string)
	{
		unsigned int new_num_chars = num_chars + string.num_chars;
		char *new_str = new char[new_num_chars + 1];

		strcpy_s(new_str, new_num_chars + 1, str);
		strcat_s(new_str, new_num_chars + 1, string.str);

		delete[] str;
		num_chars = new_num_chars;
		str = new_str;

		return *this;
	}

	String operator+(const String &string) const
	{
		String stringsum(str);
		stringsum += string;
		return stringsum;
	}

	bool operator==(const String &string)
	{
		return strcmp(str, string.str) == 0;
	}

	bool operator!=(const String &string)
	{
		return strcmp(str, string.str) != 0;
	}

	//create method prefix (if we have world and we put world as prefix we get helloworld)

private:

	unsigned int num_chars;
	char *str;
};

#endif // STRING_H