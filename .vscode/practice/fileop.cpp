#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ofstream out("C:\\Users\\sisyphus\\Desktop\\ccc.txt");
    if (!out) {
        cout << "fail to open" << endl;
        return 1;
    }
    out << "welcome to ";
    char ch[100];
    cin.get(ch, 80, '|');
    out << ch;
    //int i=0;
    //while(ch[i]!='\0') out.put(ch[i++]);
    out.close();

    ifstream in("C:\\Users\\sisyphus\\Desktop\\ccc.txt");
    if(!in){
        cout << "fail to open" << endl;
        return 1;
    }
    /*char p[100];
    in>>p;
    cout<<p;
    in>>p;
    cout<<p;
    in>>p;
    cout<<p;*/
    char c;
    while(in){        //in指针指到最后一个字符后、文件范围外，仍为true
        c=in.get();  //in指针指向get后面字符的位置，再get，in指针才为false
        if(in) cout<<c;  //因此需要再进行一次if的判定
    }
    in.close();

    system("pause");
    return 0;
}