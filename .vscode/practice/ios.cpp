#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    /*char c[100];
    cout.setf(ios::right);
    cout<<"shuru:"<<endl;
    
    cin.getline(c,80,']');
    cout<<c;
    cin.getline(c,70);
    cout<<c;
    cout.width(10);
    cout.fill('0');
    cout.setf(ios::left|ios::showpoint|ios::scientific);
    cout.setf(ios::fixed);  //
    cout.precision(5);     //固定的除小数点的位数，用fixed后变成小数点后的位数
    cout<<12.35645645<<endl;*/
    double a=1.0868457;
    cout<<"hex:"<<setw(10)<<setfill('*')<<setiosflags(ios::left)<<setprecision(12)<<a<<endl;
    system("pause");
    return 0;
}