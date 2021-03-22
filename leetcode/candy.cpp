#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
int max(int &a,int &b){
    return (a>b)?a:b;
}
class Solution
{ 
public:
    int findContentChildren(vector<int> &g)
    {   
        int size=g.size();
        if(size<2) return size;
        vector<int> num(size,1);
        for(int i=1;i<size;i++){
            if(g[i]>g[i-1]) num[i]=num[i-1]+1;
        }
        for(int i=size-1;i>0;i--){
            if(g[i]<g[i-1]) num[i-1]=max(num[i-1],num[i]+1);
        }
        return accumulate(num.begin(),num.end(),0);
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
    string str1;
    while (1)
    {
        cin >> str1;
        vector<int> child(s1.GetStringByNumArr(str1));
        cout<<s1.findContentChildren(child)<<endl;
    }
    return 0;
}