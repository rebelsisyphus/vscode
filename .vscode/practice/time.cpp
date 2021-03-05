#include<iostream>
#include<time.h>
int main()
{
    time_t t;
    time(&t);
    printf("Today's date and time: %s", ctime(&t));
    system("pause");
    return 0;
}