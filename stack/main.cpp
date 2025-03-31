#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<unordered_map>
using namespace std;

class Solution {
public:
	bool isValid(string s, int a) {
		int n = s.size();
		char front = s.at(0);
		char back = s.at(n - 1);	
		if (!s.empty() &&  n % 2 != 0)
		{
			cout << "++++++" << endl;
			return false;
		}
		for (int i = 0; i < n/2; i++)	
		{
			switch (s[i])
			{
			case '[':
				if (s[n - 1 - i] != ']')
				{
					return false;
				}
				break;
			case '{':
				if (s[n - 1 - i] != '}')
				{
					return false;
				}
				break;
			case '(':
				if (s[n - 1 - i] != ')')
				{
					return false;
				}
				break;
			default:
				break;
			}
		}
		return true;
	}

	bool isValid(string s) {
		int n = s.size();
		if (n%2!=0)
		{
			return false;
		}
		unordered_map<char, char> pairs = {
			{')','('},{'{','}'},{'[',']'}
		};
		stack<char> stk;
		for (char ch:s)
		{
			if (pairs.count(ch))
			{
				if (stk.top()==pairs[ch])	
				{
					stk.pop();
				}
			}
			else {
				stk.push(ch);
			}
		}
		return stk.empty();

	}
};


int main() {
	Solution sol;
	bool ans = sol.isValid("{[()]}");
		cout << "ans = " << ans << endl;
		return 0;
}