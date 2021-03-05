#include <iostream>
#include <string.h>
#include "list1.h"
using namespace std;
#define Maxsize 100
int main() {
    List<int> LA;
    LA.input();
    int k;
    cin>>k;
    LA.Insert(4,k);
    LA.output();
    system("pause");
    return 0;
}