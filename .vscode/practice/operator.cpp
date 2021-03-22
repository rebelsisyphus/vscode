#include<iostream>
#include<cmath>
using namespace std;
class complex{
    private:
    int real,imag;
    public:
    complex(int r=0,int i=0):real(r),imag(i){}
    int realshow(){return real;}
    int imagshow(){return imag;}
    void printc(){
      cout<<real<<'+'<<imag<<'i'<<endl;  
    }
    complex operator+(complex &);
    complex operator+(int);
    friend complex operator+(int x,complex &c);
    friend ostream & operator<<(ostream &os,const complex &c);
    bool operator==(complex);
    complex operator++();
    complex operator++(int);
    complex Sum(complex &);
    ~complex(){};
};
 complex complex::operator+(complex &c){
    complex temp; 
    temp.real=this->real+c.real;
    temp.imag=this->imag+c.imag;
    return temp;
 }
 complex complex::operator+(int c){
    complex temp; 
    temp.real+=c;
    temp.imag+=this->imag;
    return temp;
 }
complex complex::operator++(){
    this->real+=1;
    return *this;
  }
complex complex::operator++(int){
    this->real+=1;
    return *this;
  }
bool complex::operator==(complex c){
    if(this->real==c.real && this->imag==c.imag) return true;
    else return false;
}
complex operator+(int x,complex &c){
    complex temp; 
    temp.real=c.real+x;
    temp.imag=c.imag;
    return temp;
}
ostream &operator<<(ostream &os,const complex &c){
    os<<c.real<<'+'<<c.imag<<'i'<<endl;  
    return os;
}
int main(){
    complex c1(1,2),c2(5,3);
    complex c3;
    c3=c2+2;
    cout<<c3<<c2<<endl;
    return 0;
    
}