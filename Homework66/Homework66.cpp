#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//1
//int main() 
//{
//    string inputFileName = "input.txt";
//    string outputFileName = "output.txt";
//
//    ifstream inputFile(inputFileName);
//    ofstream outputFile(outputFileName);
//
//    if (!inputFile.is_open())
//    {
//        cout << "Не удалось открыть файл " << inputFileName << endl;
//        return 1;
//    }
//
//    if (!outputFile.is_open())
//    {
//        cout << "Не удалось создать файл " << outputFileName << endl;
//        return 1;
//    }
//
//    string line;
//    while (getline(inputFile, line))
//    {
//        istringstream iss(line);
//        string word;
//        while (iss >> word) 
//        {
//            if (word.length() >= 7)
//            { 
//                outputFile << word << " ";
//            }
//        }
//        outputFile << "\n";
//    }
//
//    cout << "Слова, длиной не менее семи символов, были записаны в файл " << outputFileName << endl;
//
//    inputFile.close();
//    outputFile.close();
//}
// 
// 
//2

class MyString
{
	friend ostream& operator<<(ostream& os, const MyString& x);
	friend istream& operator>>(istream& is, MyString& x);

	friend MyString operator +(int delta, MyString right)
	{
		char mas[1000];
		for (int i = 0; i < delta; i++)
		{
			mas[i] = 'x';
		}
		for (int i = 0; i < right.size; i++)
		{
			mas[delta + i] = right.str[i];
		}
		mas[delta + right.size] = 0;
		return MyString(mas);
	}
	int size = 0;
	char* str = nullptr;
public:

	static int count;
	MyString()
	{
		Clear();
		str = new char[80];
		size = 80;
		for (int i = 0; i < size; i++) str[i] = '*';
		str[size - 1] = 0;
		count++;
	}
	MyString(const MyString& r)
	{
		SetStr(r.str);
		count++;
	}
	MyString(int size)
	{
		Clear();
		str = new char[size + 1];
		this->size = size;
		str[size - 1] = 0;
		for (int i = 0; i < size; i++) str[i] = '*';
		count++;
	}
	MyString(const char* str)
	{
		SetStr(str);
		count++;
	}
	MyString(MyString&& other) noexcept
	{
		str = other.str;
		size = other.size;
		other.str = nullptr;
		other.size = 0;
	}
	~MyString()
	{
		Clear();
		count--;
	}
	void SetStr(const char* str)
	{
		Clear();
		int length = strlen(str);
		this->str = new char[length + 1];
		this->size = length;
		for (int i = 0; i <= length; i++)
		{
			this->str[i] = str[i];
		}
	}
	char* GetStr()
	{
		return str;
	}
	void Clear()
	{
		if (str != nullptr)
		{
			delete[] str;
		}
	}
	void Print()
	{
		cout << str << endl;
	}
	static int GetCount()
	{
		return count;
	}
	void Read(const char* mesagge)
	{
		char mas[250];
		cout << mesagge << ": ";
		cin.getline(mas, 250);
		SetStr(mas);
	}
	MyString operator +(int delta)
	{
		if (delta < 0) return *this - (-delta);
		char mas[1000];
		for (int i = 0; i < size; i++)
			mas[i] = str[i];
		for (int i = 0; i < delta; i++)
			mas[size + i] = 'x';
		mas[size + delta] = 0;
		return MyString(mas);
	}
	MyString operator -(int delta)
	{
		if (delta < 0) return *this + (-delta);
		char mas[1000];
		int newsize = size - delta;
		if (newsize < 0) newsize = 0;
		for (int i = 0; i < newsize; i++)
			mas[i] = str[i];
		mas[newsize] = 0;
		return MyString(mas);
	}
	void Plus(int delta)
	{
		if (delta < 0) return Minus(-delta);
		char mas[1000];
		for (int i = 0; i < size; i++)
			mas[i] = str[i];
		for (int i = 0; i < delta; i++)
			mas[size + i] = 'x';
		mas[size + delta] = 0;
		SetStr(mas);
	}
	void Minus(int delta)
	{
		if (delta < 0) return Plus(-delta);
		char mas[1000];
		int newsize = size - delta;
		if (newsize < 0) newsize = 0;
		for (int i = 0; i < newsize; i++)
			mas[i] = str[i];
		mas[newsize] = 0;
		SetStr(mas);
	}
	//2
	MyString operator++(int)
	{
		MyString x(*this);
		x.Plus(1);
		return x;
	}

	MyString operator--(int)
	{
		MyString x(*this);
		x.Minus(1);
		return x;
	}

	MyString operator ++()
	{
		Plus(1);
		return MyString(*this);

	}

	MyString operator --()
	{
		Minus(1);
		return MyString(*this);
	}

	MyString operator =(MyString& x)
	{
		SetStr(x.GetStr());
		return *this;
	}

	MyString& operator=(MyString&& x) noexcept
	{
		if (this != &x) {
			Clear();
			str = x.str;
			size = x.size;
			x.str = nullptr;
			x.size = 0;
		}
		return *this;
	}
};
istream& operator >>(istream& is, MyString& x)
{
	char mas[250];
	is.getline(mas, 250);
	x.SetStr(mas);
	return is;
}
ostream& operator <<(ostream& os, const MyString& x)
{
	os << x.str << "\n" << x.size;
	return os;
}

int MyString::count = 0;

int main()
{

	int k = 2;

	MyString str5("fds");
	cin >> str5;
	cout << str5;
}