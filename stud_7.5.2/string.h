#pragma once

#include<assert.h>

namespace luow
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		/*	string()
				:_str(new char[1])
				, _size(0)
				, _capacity(0)
				{
				_str[0] = '\0';
				}*/

				//string(const char* str = nullptr)  不可以
				//string(const char* str = '\0')
				//string(const char* str = "\0")
		string(const char* str = "")
			:_size(strlen(str))
		{
			_capacity = _size == 0 ? 3 : _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// s3(s2)
		string(const string& s)
			:_size(s._size)
			, _capacity(s._capacity)
		{
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
		}

		// s1 = s3;
		// s1 = s1;
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				/*delete[] _str;
				_str = new char[s._capacity + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._capacity;*/

				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;

				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		const char* c_str()
		{
			return _str;
		}

		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		// 不修改成员变量数据的函数，最好都加上const
		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}

		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}

		bool operator>=(const string& s) const
		{
			//return *this > s || *this == s;
			return *this > s || s == *this;
		}

		bool operator<(const string& s) const
		{
			return !(*this >= s);
		}

		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}

		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}

		void resize(size_t n, char ch = '\0')
		{
			if (n < _size)
			{
				// 删除数据--保留前n个
				_size = n;
				_str[_size] = '\0';
			}
			else if (n > _size)
			{
				if (n > _capacity)
				{
					reserve(n);
				}

				size_t i = _size;
				while (i < n)
				{
					_str[i] = ch;
					++i;
				}

				_size = n;
				_str[_size] = '\0';
			}
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;

				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			/*if (_size + 1 > _capacity)
			{
				reserve(_capacity * 2);
			}

			_str[_size] = ch;
			++_size;

			_str[_size] = '\0';*/
			insert(_size, ch);
		}

		void append(const char* str)
		{
			//size_t len = strlen(str);
			//if (_size+len > _capacity)
			//{
			//	reserve(_size + len);
			//}

			//strcpy(_str + _size, str);
			////strcat(_str, str);
			//_size += len;
			insert(_size, str);
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size + 1 > _capacity)
			{
				reserve(2 * _capacity);
			}

			// 问题代码
			/*	size_t end = _size;
				while (end >= pos)
				{
				_str[end+1] = _str[end];
				--end;
				}*/

			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}

			_str[pos] = ch;
			++_size;

			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t len = strlen(str);

			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			// 挪动数据
			size_t end = _size + len;
			while (end > pos + len - 1)
			{
				_str[end] = _str[end - len];
				--end;
			}

			/*size_t end = _size;
			for (size_t i = 0; i < _size + 1; ++i)
			{
				_str[end + len] = _str[end];
				--end;
			}*/

			// 拷贝插入
			strncpy(_str + pos, str, len);
			_size += len;

			return *this;

		}

		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);

			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}

			return *this;
		}

		//swap(s1, s2);
		//s1.swap(s2);
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_capacity, s._capacity);
			std::swap(_size, s._size);
		}

		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);

			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}

			return npos;
		}

		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < _size);

			// kmp
			char* p = strstr(_str + pos, str);
			if (p == nullptr)
			{
				return npos;
			}
			else
			{
				return p - _str;
			}
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

	private:
		char* _str;
		size_t _capacity;
		size_t _size;

		static const size_t npos;
		// 可以
		//static const size_t npos = -1;

		/*	static const size_t N = 10;
			int _a[N];*/

			// 不可以
			//static const double dpos = 1.1;
	};

	const size_t string::npos = -1;

	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	// 21:13继续
	istream& operator>>(istream& in, string& s)
	{
		s.clear();

		char ch = in.get();
		char buff[128];
		size_t i = 0;
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[127] = '\0';
				s += buff;
				i = 0;
			}

			ch = in.get();
		}

		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in;
	}

	void test_string1()
	{
		string s1;
		string s2("hello world");

		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;

		s2[0]++;

		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
	}

	void test_string2()
	{
		string s1;
		string s2("hello world");

		string s3(s2);
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;

		s2[0]++;
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;

		s1 = s3;
		cout << s1.c_str() << endl;
		cout << s3.c_str() << endl;

		s1 = s1;
		cout << s1.c_str() << endl;
		cout << s3.c_str() << endl;
	}

	void Print(const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			cout << s[i] << " ";
		}
		cout << endl;

		string::const_iterator it = s.begin();
		while (it != s.end())
		{
			//*it = 'x';
			++it;
		}
		cout << endl;

		for (auto ch : s)
		{
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string3()
	{
		string s1("hello world");
		for (size_t i = 0; i < s1.size(); ++i)
		{
			s1[i]++;
		}
		cout << endl;

		for (size_t i = 0; i < s1.size(); ++i)
		{
			cout << s1[i] << " ";
		}
		cout << endl;

		Print(s1);

		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			(*it)--;
			++it;
		}
		cout << endl;

		it = s1.begin();
		while (it != s1.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto ch : s1)
		{
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string4()
	{
		string s1("hello world");
		string s2("hello world");
		string s3("xx");

		cout << (s1 < s2) << endl;
		cout << (s1 == s2) << endl;
		cout << (s1 >= s2) << endl;
	}

	void test_string5()
	{
		string s1("hello world");
		/*s1.push_back(' ');
		s1.append("xxxxxxxxxxxxxxxxxxxx");*/

		s1 += ' ';
		s1 += "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

		cout << s1.c_str() << endl;

		string s2;
		s2 += 'a';
		//s2 += 'b';
		//s2 += 'c';
		cout << s2.c_str() << endl;

		s1.insert(5, 'x');
		cout << s1.c_str() << endl;

		s1.insert(0, 'x');
		cout << s1.c_str() << endl;
	}

	void test_string6()
	{
		string s1("hello world11111111111111111111111");
		cout << s1.capacity() << endl;
		s1.reserve(10);
		cout << s1.capacity() << endl;
	}

	void test_string7()
	{
		string s1;
		s1.resize(20, 'x');
		cout << s1.c_str() << endl;
		s1.resize(30, 'y');
		cout << s1.c_str() << endl;

		s1.resize(10);
		cout << s1.c_str() << endl;
	}

	void test_string8()
	{
		string s1("11111111");
		s1.insert(0, 'x');
		cout << s1.c_str() << endl;

		s1.insert(3, 'x');
		cout << s1.c_str() << endl;

		s1.insert(3, "yyy");
		cout << s1.c_str() << endl;

		s1.insert(0, "yyy");
		cout << s1.c_str() << endl;
	}

	void test_string9()
	{
		string s1("0123456789");
		cout << s1.c_str() << endl;

		s1.erase(4, 3);
		cout << s1.c_str() << endl;

		s1.erase(4, 30);
		cout << s1.c_str() << endl;

		s1.erase(2);
		cout << s1.c_str() << endl;
	}

	// 流插入重载必须实现成友元函数？ 不对
	void test_string10()
	{
		std::string s1("0123456789");
		s1 += '\0';
		s1 += "xxxxxxxx";

		cout << s1 << endl;
		cout << s1.c_str() << endl;

		string s2;
		cin >> s2;
		cout << s2 << endl;

		cin >> s1;
		cout << s1 << endl;
	}
}
