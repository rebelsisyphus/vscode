#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

vector<int> GetStringByNumArr(string str);


int main()
{
    cout << "请输入字符串" << endl;
    string str;
    cin >> str;
    vector<int> nums(GetStringByNumArr(str));

    for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        cout << *it << endl;
    }

    system("pause");
    return 0;
}

vector<int> strtoint(string str){
    size_t i=0;
    vector<char> tempnum;
    vector<int> numlist;
    while(i<str.length()){
        while((str[i]-48)>=0&&(str[i]-48)<=9) tempnum.push_back(str[i]);
        if(!tempnum.empty()){
            numlist.push_back(stoi(string(tempnum.begin(),tempnum.end())));
            tempnum.clear();
        }
        i++;
    }
    return numlist;
}
