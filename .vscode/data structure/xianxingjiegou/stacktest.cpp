#include<iostream>
#include "stack1.h"
#include<string.h>
#include<cstdlib>
using namespace std;
int main(){
    liststack<int> p;
    cout<<"shurushumu"<<endl;
    int n;
    cin>>n;
    cout<<"shuru"<<endl;
    int m;
    while(n){
        cin>>m;
        p.Push(m);
        n--;
    }
    cout<<p;
    int k;
    p.Pop(k);
    cout<<k;
    return 0;
}