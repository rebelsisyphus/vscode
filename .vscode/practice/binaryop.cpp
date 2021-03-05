#include <fstream>
#include <iostream>
#include<iomanip>
#include <string.h>
using namespace std;
class student {
  private:
    char name[10];
    char Class[10];
    char sex;
    int age;

  public:
    student() {}
    student(char *n, char *c, char s, int a) {
        strcpy(name, n);
        strcpy(Class, c);
        sex = s;
        age = a;
    }
    void showme() {
        /*cout.width(6);
        cout.fill(' ');
        cout.setf(ios::left);
        cout << name << '\t' << Class << '\t' << sex << '\t' << age << endl;*/
        cout<<setw(10)<<setfill(' ')<<setiosflags(ios::left)<<name;
        cout<<setw(10)<<setfill(' ')<<setiosflags(ios::left)<<Class;
        cout<<setw(10)<<setfill(' ')<<setiosflags(ios::left)<<sex;
        cout<<setw(10)<<setfill(' ')<<setiosflags(ios::left)<<age<<endl;
    }
    ~student() {}
};

int main() {
    student stu[3] = {student("zhangsan", "chem", 'm', 18),
                      student("lisi", "cs", 'm', 19),
                      student("xiaohong", "phy", 'f', 18)};
    ofstream out("C:\\Users\\sisyphus\\Desktop\\eg\\xinxi.txt", ios::binary);
    if (!out) {
        cout << "fail to open\n";
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        out.write((char *)&stu[i], sizeof(stu[i]));
    }
    out.close();
    ifstream read1("C:\\Users\\sisyphus\\Desktop\\eg\\xinxi.txt", ios::binary);
    if (!read1) {
        cout << "fail to open\n";
        return 1;
    }
    student stu2;
    read1.seekg(0,ios::end);     //指针指向文件末尾
    int len=read1.tellg();
    int i;
    i=read1.tellg()/sizeof(stu2);
        cout<<i<<endl;
    for(int k=len/sizeof(stu2)-1;k>=0;k--){  //k=2,1,0
        read1.seekg(k*sizeof(stu2));          //seekg（int a）指针从开始处向后移动a  
        read1.read((char*)&stu2,sizeof(stu2));   //读取
        stu2.showme(); 
                  //因为使用for循环不需要再进行检验
    }
    /*while (read1) {
        read1.read((char *)&stu2, sizeof(stu2));
        if (read1)
            stu2.showme();
    }*/
    read1.close();
    system("pause");
    return 0;
}