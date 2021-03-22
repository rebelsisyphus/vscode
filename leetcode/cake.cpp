#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
using namespace std;
class Solution
{ 
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0, j = 0;
        while (i < g.size() && j < s.size())
        {
            if (s[j] >= g[i])
                i++;
            j++;
        }
        return i;
    }
    vector<int> GetStringByNumArr(string &str) //时间复杂度O(N)
    {
        vector<int> numlist;
        size_t i = 0; //str下标
        vector<char> tempnum;
        while (i < str.length())
        {
            while (int(str[i] - 48) >= 0 && int(str[i] - 48) <= 9)
            {
                tempnum.push_back(str[i++]);
            }
            if (!tempnum.empty())
            {
                numlist.push_back(stoi(string(tempnum.begin(), tempnum.end()))); //将一串数转化成字符串，再用stoi（）转换成int
                tempnum.clear();
            }
            i++;
        }
        return numlist;
    }
   
};

int main()
{   
    Solution s1;
    string str1, str2;
    while (1)
    {
        cin >> str1;
        vector<int> child(s1.GetStringByNumArr(str1));
        cin >> str2;
        vector<int> parent(s1.GetStringByNumArr(str2));
        cout<<s1.findContentChildren(child,parent)<<endl;
    }
    return 0;
}