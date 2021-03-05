#include <iostream>
#include <string.h>
using namespace std;
static char *num1[] = {"",        "one",       "two",      "three",
                       "four",    "five",      "six",      "seven",
                       "eight",   "nine",      "ten",      "eleven",
                       "twelve",  "thirteen",  "fourteen", "fifteen",
                       "sixteen", "seventeen", "eighteen", "nineteen"};
static char *num10[] = {"",      "",      "twenty",  "thirty", "forty",
                        "fifty", "sixty", "seventy", "eighty", "ninety"};
static char *num100[] = {"", "thousand", "millon", "billoon", "tirllion"};
class robot {
  private:
    char name[20];
    char type[20];

  public:
    robot() {
        strcpy(name, "xxx");
        strcpy(type, "xxx");
    }
    void set(char n[], char t[]) {
        strcpy(name, n);
        strcpy(type, t);
    }
    void out(int a); //小于1000
    void tran_int(int n, int k);
    void putout(){cout<<name<<endl;}
    ~robot(){cout<<"xiaohu\n";}
};

void robot::out(int a) {
    int b = a % 100;
    if (a / 100 != 0) {
        cout << num1[a / 100] << " hundred "; //百位
        if (b != 0)
            cout << "and ";
    }
    if (b < 20)
        cout << num1[b]; // 20以内
    else {
        cout << num10[b / 10]; //大于20的十位
        if (b % 10 != 0)
            cout << num1[b % 10]; //个位，因为要与十位贴合，加上\b-隐式位置符号
    }
}
void robot::tran_int(int n, int k) {
    if (n / 1000 != 0) {
        tran_int(n / 1000, k + 1);
    }
    out(n % 1000);
    cout << " " << num100[k] << ",";
}
int main() {
    int n;
    cout << "shuru n:" << endl;
    cin >> n;
    
    if (n < 2147483647) {
        cout << n << endl;
        robot brown;
        brown.tran_int(n, 0);
        cout<<"1111"<<endl;
    } 
    else
        cout << "数字太大无法翻译" << endl;
    
    system("pause");
    return 0;
}