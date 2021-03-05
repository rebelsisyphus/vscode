#include <assert.h>
#include <iostream>
#include "list1.h"
using namespace std;
const int stackincrease = 20;
template <class T> class Stack;
template <class T> class SeqStack;
template <class T> class liststack;
template <class T> ostream &operator<<(ostream &os, const SeqStack<T> &s);  //友元函数一定要提前声明
template <class T> ostream &operator<<(ostream &os, const liststack<T> &s);  //友元函数一定要提前声明
template <class T> class Stack {
  public:
    virtual void Push( T &x) = 0;   //压栈
    virtual bool Pop(T &x) = 0;          //出栈 ，栈顶元素用x返回
    virtual bool getTop(T &x) const = 0; //得到栈顶元素，x返回
    virtual bool Isempty() const = 0;    //判空
    virtual bool Isfull() const = 0;     //判满
    virtual int getsize() const = 0;     //栈元素数
};
template <class T> class SeqStack : public Stack<T> {
  private:
    T *data;
    int top; //栈顶指针
    int maxsize;
    void overflowstack(); //溢出处理
  public:
    SeqStack(int sz = 50) : top(-1), maxsize(sz) {
        data = new T[maxsize];
        assert(data != NULL); // assert函数当判断为假的时候输出
    }
    ~SeqStack() { delete[] data; }
    void Push(T &x);   //压栈
    bool Pop(T &x);          //出栈 ，栈顶元素用x返回
    bool getTop(T &x) const; //得到栈顶元素，x返回
    bool Isempty() const { return (top == -1) ? true : false; }         //判空
    bool Isfull() const { return (top + 1 == maxsize) ? true : false; } //判满
    int getsize() const { return top + 1; } //栈元素数
    void makeempty() { top = -1; }          //清空栈
    friend ostream &operator<<<T>(ostream &os, const SeqStack<T> &s); //重载输出  一定要加<T>否则就不是模板函数
};
template <class T> void SeqStack<T>::overflowstack() {
    T *newdata = new T[maxsize + stackincrease];
    assert(newdata != NULL);
    for (int i = 0; i <= top; i++)
        newdata[i] = data[i];
    maxsize = maxsize + stackincrease;
    delete[] data;
    data = newdata;
}
template <class T> void SeqStack<T>::Push(T &x) {
    if (Isfull())
        overflowstack();
    data[++top] = x;
}
template <class T> bool SeqStack<T>::Pop(T &x) {
    if (Isempty())
        return false;
    x = data[top--];
    return true;
}
template <class T> bool SeqStack<T>::getTop(T &x) const {
    if (Isempty())
        return false;
    x = data[top];
    return true;
}
template <class T> ostream &operator<<(ostream &os, const SeqStack<T> &s) {
    for (int i = 0; i <= s.top; i++)
        os << s.data[i] << ' ';
    return os;
}
template <class T> class liststack:public Stack<T>{
    private:
    Linknode<T> *top;
    public:
    liststack(){
        top=new Linknode<T>;
        assert(top != NULL); // assert函数当判断为假的时候停止程序
    }
    ~liststack() { makeempty();  } 
    void makeempty();
    void Push( T &x);   //压栈
    bool Pop(T &x);          //出栈 ，栈顶元素用x返回
    bool getTop(T &x) const; //得到栈顶元素，x返回
    bool Isempty() const { return (top->next==NULL) ? true : false; }         //判空
    bool Isfull() const { return  true; } //判满
    int getsize() const ; //栈元素数
    friend ostream &operator<<<T>(ostream &os, const liststack<T> &s); //重载输出  一定要加<T>否则就不是模板函数
};
template <class T> void liststack<T>::makeempty(){
    Linknode<T> *p;
    while(top->next!=NULL){
        p=top->next;
        top->next=p->next;
        delete p;
    }
    delete top;
}
template <class T> void liststack<T>::Push(T &x){
    Linknode<T> *newdata;
    newdata=new Linknode<T>(x);
    newdata->next=top->next;
    top->next=newdata;
}
template <class T> bool liststack<T>::Pop(T&x){
    if(Isempty()) return false;
    Linknode<T> *p=top->next;
    x=p->data;
    top->next=p->next;
    delete p;
    return true;
}
template <class T> bool liststack<T>::getTop(T&x)const{
    if(Isempty()) return false;
    Linknode<T> *p=top->next;
    x=p->data;
    return true;
}
template <class T> int liststack<T>::getsize()const{
    int count=0; 
    Linknode<T> *p=top->next;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}
template <class T> ostream &operator<<(ostream &os, const liststack<T> &s) {
    Linknode<T> *p=(s.top)->next;
    while(p!=NULL){
       cout<<p->data<<' ';
       p=p->next;
    }
    return os;
}