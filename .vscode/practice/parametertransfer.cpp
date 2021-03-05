#include <iostream>
using namespace std;
void swap(int *x,int *y){
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void swap1(int &x,int &y){
    int temp;
    temp=x;
    x=y;
    y=temp;
}
int main(){
    cout<<"输入两个数"<<endl;
    int a,b;
    cin>>a>>b;
    //swap(&a,&b);
    swap1(a,b);
    cout<<a<<' '<<b;
    system("pause");
    return 0;
}