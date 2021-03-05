#include <iostream>

#include <mmsystem.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
using namespace std;
class person {
  private:
    int age;
    char name[10];
    char sex;

  public:
    person() {
        strcpy(name, "xxx");
        age = 0;
        sex = ' ';
    }
    /*person(char *p) : age(0), sex('m') { strcpy(name, p); }
    person(person &p) {
        strcpy(name, p.name);
        age = p.age;
        sex = p.sex;
    }
    person(char *name, int age, char sex) {
        strcpy(this->name, name);
        this->age = age;
        this->sex = sex;
    }*/
    void Register(char *name, int age, char sex);
    void showme();
    virtual void printdata() = 0;
    ~person() { cout << "xiaohu\n"; };
};
void person::Register(char *name, int age, char sex) {
    strcpy(this->name, name);
    this->age = age;
    this->sex = sex;
}
void person::showme() {
    cout << this->name << '\t' << this->age << '\t' << this->sex << '\t';
}
class singer : public person {
    float salary;

  public:
    singer();
    singer(char *name, int age, char sex, float salary);
    void chagngedata(char *name, int age, char sex, float salary);
    void palymusic(char *ps);
    virtual void printdata() {
        person::showme();
        cout << salary << endl;
    }
    ~singer() { cout << "xiaochu" << endl; }
};
singer::singer() : person() { salary = 0.0; }
singer::singer(char *name, int age, char sex, float salary) {
    person::Register(name, age, sex);
    this->salary = salary;
}
void singer::chagngedata(char *name, int age, char sex, float salary) {
    person::Register(name, age, sex);
    this->salary = salary;
}
void singer::palymusic(char *ps) {
    char str[100] = "play ";
    strcat(str, ps);
    cout << str;
    mciSendString(TEXT(str), NULL, 0, NULL);
    char a;
    cin >> a;
}

int main() {
    person *p1;
    singer s("zhangsan", 14, 'm', 2.5);
    p1 = &s;     //只要有函数的重载，就可以进行赋值
    p1->printdata();

    system("pause");
    return 0;
}