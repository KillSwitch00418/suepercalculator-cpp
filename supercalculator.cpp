#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>
#define maximum 10000
using namespace std;

class BigInt
{
 	public:
		string number;
		long long remainder;
		bool sign;

	BigInt()
  	{
		number = "0";
		sign = false;
		remainder = 0;
	}

	BigInt(string s)
	{
		if( isdigit(s[0]) )
		{
			number = s;
			sign = false;
		}
		else
		{
			number = s.substr(1) ;
			sign = (s[0] == '-');
		}
		remainder = 0;
	}

	BigInt(string s , bool goal)
	{
		number = s;
		sign = goal;
	}

	BigInt(string s, long long r)
	{
		if( isdigit(s[0]) )
		{
			number = s;
			sign = false;
		}
		else
		{
			number = s.substr(1) ;
			sign = (s[0] == '-');
		}
		remainder = r;
	}

	BigInt add(BigInt b1, BigInt b2)
	{
		string add = (b1.number.length() > b2.number.length()) ? b1.number : b2.number;
		char carry = '0';
		int length_dif = abs((int)(b1.number.size() - b2.number.size()));
		if(b1.number.size() > b2.number.size())
 			b2.number.insert(0, length_dif, '0');
		else
			b1.number.insert(0, length_dif, '0');
		for(int i=b1.number.size() - 1; i >= 0; --i)
		{
			add[i] = ((carry - '0') + (b1.number[i] - '0') + (b2.number[i] - '0')) + '0';
			if(i != 0)
			{
				if(add[i] > '9')
				{
					add[i] -= 10;
					carry = '1';
				}
				else
  					carry = '0';
			}
		}
		if(add[0] > '9')
		{
			add[0] -= 10;
			add.insert(0, 1, '1');
		}
		BigInt b3(add);
		return b3;
	}
	BigInt subtract(BigInt b1, BigInt b2)
	{
		string sub;
		bool goal = 0;
		if(b1.number.length() < b2.number.length())
		{
			sub = b1.number;
			b1.number = b2.number;
			b2.number = sub;
			goal = 1;
		}
		int length_dif = abs((int)(b1.number.size() - b2.number.size()));
		b2.number.insert(0, length_dif, '0');
		sub=b1.number;
		for(int i = b1.number.length() - 1; i >= 0; --i)
		{
			if(b1.number[i] < b2.number[i])
			{
				b1.number[i] += 10;
				b1.number[i - 1]--;
				if(i == 0)
					goal = 1;
			}
			sub[i] = ((b1.number[i] - '0') - (b2.number[i] - '0')) + '0';
		}
		while(sub[0] == '0' && sub.length() != 1)
			sub.erase(0, 1);
		BigInt b3(sub, goal);
		return b3;
	}

	BigInt multiply(BigInt b1, BigInt b2)
	{
		if(b1.number.length() > b2.number.length())
			b1.number.swap(b2.number);
		BigInt res("0");
		for(int i=b1.number.length() - 1; i >= 0; --i)
 		{
			string temp = b2.number;
			int current_digit = b1.number[i]-'0';
			int carry = 0;
			for(int j=temp.length() - 1; j >= 0; --j)
			{
				temp[j] = ((temp[j] - '0') * current_digit) + carry;
				if(temp[j] > 9)
				{
					carry = (temp[j]/10);
					temp[j] -= (carry*10);
				}
				else
					carry = 0;
			temp[j] += '0';
			}

			if(carry > 0)
				temp.insert(0, 1, (carry+'0'));
			temp.append((b1.number.length() - i - 1), '0');
			BigInt tempOb(temp);
			res = add(res, tempOb);
		}

		while(res.number[0] == '0' && res.number.length() != 1)
		res.number.erase(0 , 1);
		return res;
	}

	BigInt divide(BigInt b1, BigInt b2)
	{
	const char * c = b2.number.c_str();
	long long den = strtoll (c, NULL, 10); 
	long long remainder = 0;
	string result; result.resize(maximum);
	for(int index = 0, len = b1.number.length(); index < len; ++index)
	{
		remainder = (remainder * 10) + (b1.number[index] - '0');
		result[index] = remainder / den + '0';
		remainder %= den;
	}
	result.resize(b1.number.length());
	while(result[0] == '0' && result.length() != 1)
		result.erase(0, 1);
	if(result.length() == 0)
		result = "0";

	BigInt b3(result, remainder);
	return b3;
	}

	BigInt factorial(BigInt b)
	{
		BigInt sub(b.number);
		BigInt res(b.number);
		while (sub.number != "1")
		{
			sub=subtract(sub, BigInt("1"));
			res=multiply(res, sub);
		}
		return res;
	}
};

int main()
{
	string s;
	BigInt operation1; 
	BigInt operation2; 
	BigInt operation3;
	BigInt m;
	char operation;

	cout << "\nHere are the operations available to you: + - * / !";
	cout << "\nWhich would you like to use? ";
	cin >> operation;
	cout << "\nIf factorial, enter \"0\" for operand 2" << "\n";
	cout << "Operand 1: ";
	cin >> s;
	operation1.number = s;
	cout << "Operand 2: ";
	cin >> s;
	operation2.number = s;

	switch(operation)
	{
		case '+' : operation3 = m.add(operation1, operation2);
			break;
		case '-' : operation3 = m.subtract(operation1, operation2);
			break;
		case '*' : operation3 = m.multiply(operation1, operation2);
			break;
		case '/' : operation3 = m.divide(operation1, operation2); 
			break;
		case '!' : operation3 = m.factorial(operation1);
			break;
	}

	if(operation == '/')
		cout<<"Final answer: " << operation3.number << " with remainder: " << operation3.remainder << "\n";
	else
		cout<<"Final answer: " << operation3.number << "\n";
	return 0;
}

