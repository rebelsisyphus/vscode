#include "list1.h"
#include <assert.h>
#include <cstdlib>
#include <iostream>
using namespace std;
const int MAXSIZE = 50;
template <class T> class quene {
  public:
    virtual bool enquene(T &x) = 0;
    virtual bool dequene(T &x) = 0;
    virtual bool isempty() const = 0;
    virtual bool isfull() const = 0;
    virtual int getsize() = 0;
    virtual bool getfront(T &x) = 0;
};
template <class T> class sequene;
template <class T> ostream &operator<<(ostream &os, const sequene<T> &q);

template <class T> class sequene : public quene<T> {
  private:
    T *data;
    int maxsize;
    int front,
        rear; //规定front指向队列第一个元素前一个位置，rear指向最后一个元素
  public:
    sequene(int sz = MAXSIZE) : maxsize(sz), front(0), rear(0) {
        data = new T[maxsize];
        assert(data != NULL);
    }
    ~sequene() { delete[] data; }
    bool enquene(T &x);
    bool dequene(T &x);
    bool isempty() const { return (front == rear) ? true : false; }
    bool isfull() const {
        return ((rear + 1) % maxsize == front) ? true : false;
    }
    int getsize() { return (rear - front + maxsize) % maxsize; }
    bool getfront(T &x) {
        if (isempty())
            return false;
        x = data[front + 1];
        return true;
    }
    void makeempty() { front = rear = 0; }
    friend ostream &operator<<<T>(ostream &os, const sequene<T> &q);
};
template <class T> bool sequene<T>::enquene(T &x) {
    if (isfull())
        return false;
    rear = (1 + rear) % maxsize; //第一个元素从data[1]开始，front data[0]没数据
    data[rear] = x;              // front这个位置空下来保证不会溢出
    return true;
}
template <class T> bool sequene<T>::dequene(T &x) {
    if (isempty())
        return false;
    front = (front + 1) % maxsize;
    x = data[front];
    return true;
}
template <class T> ostream &operator<<(ostream &os, const sequene<T> &q) {
    for (int i =q.front ; i != q.rear;
         i = (i + 1) % (q.maxsize))
        cout << q.data[i+1] << ' ';
    return os;
}


//链式队列
template <class T> class listquene;
template <class T> ostream &operator<<(ostream &os, const listquene<T> &q);
template <class T> class listquene:public quene<T>{
    private:
    Linknode<T> *front,*rear;
    public:
    listquene(){
        front=new Linknode<T>;
        rear=front;
        assert(front != NULL);
    }
    ~listquene() { makeempty(); }
    void makeempty();
    bool enquene(T &x);
    bool dequene(T &x);
    bool isempty() const { return (front == rear) ? true : false; }
    bool isfull() const {
        return true;
    }
    int getsize();
    bool getfront(T &x) {
        if (isempty())
            return false;
        x = front->next->data;
        return true;
    }
    friend ostream &operator<<<T>(ostream &os, const listquene<T> &q);
};
template <class T> void listquene<T>::makeempty(){
    Linknode<T> *temp;
    while(front->next!=NULL){
        temp=front->next;
        front->next=temp->next;
        delete temp;
    }
    delete front;
}
template <class T> int listquene<T>::getsize(){
    Linknode<T> *temp=front->next;
    int count=0;
    while(temp!=NULL){
        temp=temp->next;
        count++;
    }
    return count;
}
template <class T> bool listquene<T>::enquene(T&x){
    Linknode<T> *temp=new Linknode<T>(x);
    assert(temp!=NULL);
    rear->next=temp;
    rear=temp;
    return true;
}
template<class T>bool listquene<T>::dequene(T &x){
    if(isempty()) return false;
    Linknode<T> *temp=front->next;
    x=temp->data;
    if(temp==rear) rear=front;
    front->next=temp->next;
    delete temp;
    return true;
}
template <class T> ostream &operator<<(ostream &os, const listquene<T> &q){
    Linknode<T> *temp=q.front->next;
    while(temp!=NULL){
        cout<<temp->data<<' ';
        temp=temp->next;
    }
    return os;
}