#include <iostream>
#include <string.h>
#include "list1.h"
using namespace std;
template <class T> class SeqList : public LinearList<T> { //
  protected:
    T *data;
    int maxsize; //表容量
    int last;    //表元素数
    void reSize(int newsize);

  public:
    SeqList(int m = Maxsize); //构造函数规定表容量，默认值为Maxsize
    SeqList(SeqList<T> &L);   //复制构造函数
    ~SeqList() { delete[] data; } //析构函数
    int Size() const {            //最大元素数
        return maxsize;
    }
    int Lenth() const { //表长
        return last + 1;
    }
    int Search(T &x) const;  //在表中搜索x;
    int Locate(int i) const; //定位i;
    T getdata(int i) const { //获得第i个值
        if (i > 0 && i <= last + 1)
            return data[i - 1];
        else {
            cout << "不在范围内" << endl;
            return 0;
        }
    }
    void setdata(int i, T &x) { //修改第i个位置值为x
        if (i > 0 && i <= last + 1)
            data[i - 1] = x;
    }
    bool Insert(int i, T &x); //在第i个元素之后的位置插入x
    bool Remove(int i, T &x); //删除i的值，通过x返回
    bool Isempty() {
        if (last == -1)
            return true;
        else
            return false;
    } // list是否为空
    bool Isfull() { return (last + 1 == maxsize) ? true : false; } //表满
    void input();                                                  //表输入
    void output();                                                 //表输出
    // SeqList<T> operator=(SeqList<T> &L) ; //表复制 感觉没必要
};
template <class T> void SeqList<T>::reSize(int newsize) { //重新规定数组大小
    if (newsize <= 0) {
        cerr << "无效的大小" << endl;
        exit(1);
    }
    if (newsize != maxsize) {
        T *newdata = new T[newsize];
        if (newdata == NULL) {
            cerr << "存储信息分配错误" << endl;
            exit(1); //退出整个进程
        }
        int n = last + 1;
        T *temp1 = data;
        T *temp2 = newdata;
        while (n--)
            *temp2++ = *temp1++; //复制数值到新建数组中
        delete[] data;           //删除旧值
        data = newdata;
        maxsize = newsize;
    }
}
template <class T> SeqList<T>::SeqList(int m) {
    if (m > 0) {
        maxsize = m;
        last = -1;
        data = new T[maxsize];
        if (data == NULL) {
            cerr << "存储信息分配错误" << endl;
            exit(1); //退出整个进程
        }
    }
}
template <class T> SeqList<T>::SeqList(SeqList<T> &L) {
    maxsize = L.Size();
    last = L.Lenth() - 1;
    data = new T[maxsize];
    if (data == NULL) {
        cerr << "存储信息分配错误" << endl;
        exit(1); //退出整个进程
    }
    for (int i = 0; i <= last; i++)
        data[i] = L.getdata(i + 1); // getdata获得的是第i个数即data[i-1]
}
template <class T> int SeqList<T>::Search(T &x) const {
    int i;
    for (i = 0; i <= last; i++) {
        if (data[i] == x)
            return i + 1;
    }
    return 0;
}
template <class T> int SeqList<T>::Locate(int i) const { //检验i位置合理性
    if (i >= 1 && i <= last + 1)
        return i;
    else
        return 0;
}
template <class T>
bool SeqList<T>::Insert(
    int i,
    T &x) { // i∈[0,last+1],0即在第一个元素位置插入，last+1在最后一个元素后插入,即data[i]这个位置
    if (i < 0 || i > last + 1)
        return false; //数不正确
    if (last + 1 >= maxsize)
        return false; //超界
    for (int k = last; k >= i; k--) {
        data[k + 1] = data[k];
    }
    data[i] = x;
    last++;
    return true;
}
template <class T> bool SeqList<T>::Remove(int i, T &x) {
    if (last == -1)
        return false;
    if (i < 1 && i > last + 1)
        return false;
    x = data[i - 1];
    for (int k = i - 1; k < last; k++)
        data[k] = data[k + 1];
    last--;
    return true;
}
template <class T> void SeqList<T>::input() {
    cout << "please enter the number of data:" << endl;
    while (1) {
        cin >> last;
        if (last + 1 <= maxsize)
            break;
        cout << "the number is too big,please enter a right number of data:"
             << endl;
    }
    cout << "please enter " << last + 1 << " data" << endl;
    for (int k = 0; k <= last; k++)
        cin >> data[k];
}
template <class T> void SeqList<T>::output() {
    cout << "output all number:" << endl;
    for (int k = 0; k <= last; k++)
        cout << k << ":" << data[k] << endl;
}