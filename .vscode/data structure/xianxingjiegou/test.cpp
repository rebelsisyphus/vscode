#include<iostream>
#include "quene.h"
using namespace std;
int main(){
    listquene<int> q;
    int m;
    cout<<"shuru"<<endl;
    cin>>m;
    int n;
    for(int k=0;k<m;k++){
        cin>>n;
        q.enquene(n);
    }
    int k;
    q.dequene(k);
    cout<<k<<endl;
    cout<<q;
    return 0;
}