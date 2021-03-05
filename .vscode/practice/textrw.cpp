#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ifstream fin("C:\\Users\\sisyphus\\Desktop\\eg\\ccc.txt");
    ofstream fout("C:\\Users\\sisyphus\\Desktop\\eg\\ddd.txt");
    if (!fout || !fin) {
        cout << "fail to open" << endl;
        return 1;
    }
    char ch[10];
    int math, english, chinese;
    while (fin) {
        fin >> ch >> math >> english >> chinese;
        if (fin) {
            float avg = (math + english + chinese) / 3;
            fout << ch << '\t' << math << '\t' << english << '\t' << chinese<<'\t'<<avg
                 << endl;
        }
    }
    fin.close();
    fout.close();
    system("pause");
    return 0;
}