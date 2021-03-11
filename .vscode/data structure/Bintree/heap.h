#ifndef HEAP_H_
#define HEAP_H_
#include<iostream>
#include <assert.h>
using namespace std;
#define MAXDATA 1000000
#define MAXSIZE 10000
template <class T> T Max(T a,T b){
    return (a>b)?a:b;
}
//最大堆：数组表示的完全二叉树
template<class T>
class Maxheap{
    protected:
       T *data;   //最大堆数组
       T Maxdata;  //哨兵
       int Size;   //元素数
       int Capacity;   //容量
       void percdown(int p); //下滤调整函数
    public:
       Maxheap(int C=MAXSIZE,int M=MAXDATA):Maxdata(M),Capacity(C),Size(0){
           data=new T[Capacity];
           assert(data!=NULL);
           data[0]=Maxdata;
       }
       ~Maxheap(){delete[] data;}
       bool Isfull(){return (Size==Capacity)?true:false; }
       bool Isempty(){return (Size==0)?true:false;}
       bool Insertnode(T &x);
       bool Deletenode(T &x);
       void Buildheap();
       void printheap(){
           for(int k=1;k<=Size;k++) cout<<data[k]<<' ';
       }
};

/*插入操作，将插入值放在data[++size]处，由底向上，上滤，树节点往下，直到小于父节点，插在产生的空位处
  完全二叉树的父节点为儿节点的1/2 */
template <class T>
bool Maxheap<T>::Insertnode(T &x){   
    if(Isfull()){
        cout<<"maxheap is full!"<<endl;
        return false;
    }
    int i;
    for(i=++Size;x>data[i/2];i/=2)   //节点往下，插入值向上滤
        data[i]=data[i/2];
    data[i]=x;     //插在空位
    return true;
}

//删除操作，取出最大值，再取p=data[size--]，放在data[1]处，p下滤，将节点往上传递，直到大于儿节点，插在产生的空位上
//儿节点为父节点*2（+1）
template<class T>
bool Maxheap<T>::Deletenode(T &x){
    if(Isempty()){
        cout<<"maxheap is empty!"<<endl;
        return false;
    }
    int Parent, Child;
    x=data[1];
    T temp=data[Size--];   //size已经更新为size-1
    for( Parent=1; Parent*2<=Size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=Size) && (data[Child]<data[Child+1]) )   //保证2i+1存在
            Child++;                     /* Child指向左右子结点的较大者 */
        if( temp >= data[Child] ) break; /* 找到了合适位置 */
        else  /* 下滤temp */
            data[Parent] =data[Child];
    }
    data[Parent]=temp;
    return true;
} 

// 将一个完美二叉树调整成最大堆
template <class T>    //log2N
void Maxheap<T>::percdown(int p )
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    T X;
    X = data[p]; /* 取出根结点存放的值 */
    for( Parent=p; Parent*2<=Size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=Size) && (data[Child]<data[Child+1]) )
            Child++;  /* Child指向左右子结点的较大者 */
        if( X >= data[Child] ) break; /* 找到了合适位置 */
        else  /* 下滤X */
            data[Parent] = data[Child];
    }
    data[Parent] = X;
}


template <class T>
void Maxheap<T>::Buildheap() //NlogN
{ /* 调整H->Data[]中的元素，使满足最大堆的有序性  */
    int num;
    cout<<"enter the num of element:"<<endl;
    cin>>num;
    assert(num<=Capacity);
    Size=num;
    cout<<"enter the numbers:"<<endl;
    for(int i=1;i<=Size;i++){
        cin>>data[i];
    }
    /* 从最后一个结点的父节点开始，到根结点1 */
    for( int j = Size/2; j>0; j-- )
        percdown(j);
}
#endif