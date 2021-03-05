#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include <tchar.h>
//#pragma comment(lib,"winmm.lib")
using namespace std;
class tong{
	private:
	char type[20];
	char color[20];
	float price;
	int carry_weight;
	int carry_customer;
	public:
	void set_data(char *t,char *c,float pri,int cw,int cc);
	void movecar(int l,int k);
	void horming(int num);
	void downcar(int l);
	void play_mp3(char *ps);
	char *show_type(){ return type;};
};
void tong::set_data(char *t,char *c,float pri,int cw,int cc){
	strcpy(type,t);
	strcpy(color,c);
	price=pri;
	carry_weight=cw;
	carry_customer=cc;
}
void tong::movecar(int l,int k){
	cout<<"\n"<<type<<"水平："<<endl;
	for(int i=0;i<l;i++){
		cout<<' '<<"o-o";
		Sleep(1000/k);
		cout<<"\b\b\b";
	}
}
void tong::downcar(int l){
	cout<<"\n"<<type<<"垂直："<<endl;
	for(int i=0;i<l;i++){
		cout<<"o-o";
		Sleep(500);
		cout<<"\b\b\b"<<" ";
		cout<<endl;
	}
}
void tong::horming(int num){
	for(int i=0;i<num;i++){
		cout<<type;
		cout<<"\007"<<"dididi"<<endl;
		Sleep(1000);
	}
}
void tong::play_mp3(char *ps){
	char str[100]="play ";
	//char p[]="D:\\music\\unravel.mp3";
	strcat(str,ps);
	cout<<str;
    mciSendString(TEXT(str),NULL,0,NULL);
	char a;
	cin>>a;
}
int main()
{
	tong g;
	char tp[]="jinmu";
	char ys[]="white";
	//g.set_data(tp,ys,200000,5,3);
	//g.horming(5);
	//g.movecar(10,3);
	//g.downcar(8);
	char mp[]="D:\\music\\unravel.mp3";
	g.play_mp3(mp);
	system("pause");
	return 0;
}