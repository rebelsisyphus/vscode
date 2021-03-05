#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.1415926
class shape{   //抽象类
    public:
    virtual double area()=0; //纯虚函数
    virtual double circu()=0;
    void printa(){cout<<"chou1\n";}
};
class rectangle:public shape{
    private:
    int x,y;
    int width,hight;
    public:
    rectangle(int x,int y,int w,int h){
        this->x=x;
        this->y=y;
        this->width=w;
        this->hight=h;
    }
    double area(){
        return width*hight;
    }
    virtual double circu(){
        return 2.0*(width+hight);
    }
};
class circle:public shape{
    private:
    int x,y;
    int r;
    public:
    circle(int x,int y,int r){
        this->x=x;
        this->y=y;
        this->r=r;
    }
     double area(){
        return PI*r*r;
    }
    double circu(){
        return 2.0*(PI*r);
    }
    void printa(){cout<<"chou\n";}
};
int main(){
    rectangle r1(10,10,10,5);
    circle c1(1,2,1);
    shape *p1=&r1;
    shape *p2=&c1;
    cout<<"rec a:"<<p1->area()<<endl;
    cout<<"rec c:"<<p1->circu()<<endl;
    cout<<"cir a:"<<p2->area()<<endl;
    cout<<"cir c:"<<p2->circu()<<endl;
    p2->printa();
    system("pause");
    return 0;
}