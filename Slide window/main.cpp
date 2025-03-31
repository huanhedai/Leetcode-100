#include<iostream>
#include<vector>
#include<algorithm>		//  max函数
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;

class solution {
public:
	/* 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。 */
	int lengthOfLongestSubstring1(string s) {
		vector<int> m(128, 0);
		int ans = 0;
		int i = 0;
		for (int j = 0; j < s.size(); j++)
		{
			i = max(i, m[s[j]]);	// i 记录的是当前滑动窗口的起始位置索引
			/*
				s[j]	返回的是s字符串中的第j+1个字符
				m[s[j]]	返回的是该字符的ASCII码索引对应的数组m中的元素值，
						这个位置初始值为0，当访问过该位置后，会将该位置的值赋值为 j + 1，
						表示的是该字符下一个字符的索引位置，即滑动窗口的末尾位置索引
			*/
			m[s[j]] = j + 1;
			ans = max(ans, j - i + 1);
		}
		return ans;
	}

	int lengthOfLongestSubstring(string s) {
		unordered_set<char> curr;
		int n = s.size();
		int ans = 0;
		int rk = 0;	// 右指针的索引位置

		for (int i = 0; i < n; i++) {
			if (i != 0)
			{
				curr.erase(s[i - 1]);
			}
			while (rk < n && !curr.count(s[rk])) {	// 从第 i 个元素开始遍历
				curr.insert(s[rk]);
				++rk;
			}
			ans = max(ans, rk - i);
		}
		return ans;
	}
	int lengthOfLongestSubstring2(string s) {
		// 哈希集合，记录每个字符是否出现过
		unordered_set<char> occ;
		int n = s.size();
		// 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
		int rk = -1, ans = 0;
		// 枚举左指针的位置，初始值隐性地表示为 -1
		for (int i = 0; i < n; ++i) {
			if (i != 0) {
				// 左指针向右移动一格，移除一个字符
				occ.erase(s[i - 1]);
			}
			while (rk + 1 < n && !occ.count(s[rk + 1])) {
				// 不断地移动右指针
				occ.insert(s[rk + 1]);
				++rk;
			}
			// 第 i 到 rk 个字符是一个极长的无重复字符子串
			ans = max(ans, rk - i + 1);
		}
		return ans;
	}

	/*
	给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。


	示例 1:

	输入: s = "cbaebabacd", p = "abc"
	输出: [0,6]
	解释:
	起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
	起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
	 示例 2:

	输入: s = "abab", p = "ab"
	输出: [0,1,2]
	解释:
	起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
	起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
	起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

	*/
	// 我的方法：
	// 缺点：使用排序来查找异位词并不是最高效的方法，特别是对于长字符串。更优的方法是使用滑动窗口结合字符计数。
	vector<int> findAnagrams(string s, string p) {
		int window_size = p.size();
		int ssize = s.size();
		sort(p.begin(), p.end());
		vector<int> ans;
		/*
		没有预先分配任何空间或调整其大小。这意味着 ans 是一个空的向量。
		当尝试通过 ans[j] = i; 赋值时，由于 ans 为空，访问任何索引（包括 j = 0）都会导致未定义行为。
		故一般用 push_back() 函数
		*/
		if (window_size > ssize)return {};
		for (int i = 0; i < ssize - window_size + 1; i++)
		{
			string test = s.substr(i, window_size);
			/*
				str.substr(int startIndex, int length);
				代表从字符串 str 的索引为 startIndex 的位置开始向后取 length 个字符，组成新的字符串。
			*/
			sort(test.begin(), test.end());		
			/*
			对于 s 中的每一个长度为 window_size 的子串，代码都调用了 sort 函数进行排序。
			假设 s 的长度为 n，p 的长度为 k，那么整体的时间复杂度大约为 O(n * k log k)。
			对于较大的 n 和 k，这会导致性能显著下降。
			*/
			if (test == p)
			{
				ans.push_back(i);
			}
		}

		return ans;
	}

	// 滑动窗口的方法, 使用了哈希表进行索引
	/*
	无关目标字符串顺序的问题，只需要考虑出现次数问题/出现与否，用哈希
	*/
	vector<int> findAnagrams(string s, string p, string ss) {
		vector<int> result;
		if (p.size() > s.size()) return result;

		unordered_map<char, int> pCount, sCount;
		for (char c : p) {
			pCount[c]++;		// 给目标哈希表的键赋值，值的多少与对应字符出现的个数有关
		}
		int window_size = p.size();
		for (int i = 0; i < s.size(); ++i) {	// i 指向窗口内部的右侧，i - window_size + 1 指向窗口内部的左侧，i - window_size 指向窗口外部的左侧
			// 添加当前字符到窗口
			sCount[s[i]]++;			// sCount 哈希表用来存放每次在 s 上移动时得到的窗口

			// 移除窗口左侧超出范围的字符，保证每次移动一个，窗口内字符数不变
			if (i >= window_size) {
				if (sCount[s[i - window_size]] == 1) {
					sCount.erase(s[i - window_size]);		// 如果窗口左侧的字符在窗口内没有出现，那么就将其移除即可
				}
				else {
					sCount[s[i - window_size]]--;	// 如果窗口左侧的字符在窗口内有出现，那么就将出现次数减一即可
				}
			}

			// 比较两个哈希表
			if (i >= window_size - 1 && sCount == pCount) {
				result.push_back(i - window_size + 1);
			}
		}

		return result;
	}

};

int main() {
	solution sol;
	string test = "abcda";
	int ans = sol.lengthOfLongestSubstring(test);
	cout << "ans = " << ans << endl;


	string s = "abdabba";
	string p = "ab";
	vector<int> ans2 = sol.findAnagrams(s, p, "s");
	cout << "[";
	for (int i = 0; i < ans2.size(); i++)
	{
		cout << ans2[i];
	}
	cout << "]" << endl;

	return 0;
}