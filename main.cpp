#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "menu.cpp"
using namespace std;

int main()
{
    ReadFile();
    CreateAndLoad();
    int s = 1;
    char bus[20];
    while (1)
    {
        Menu();
        cin >> s;
        if (s == 0)
            break;
        switch (s)
        {
        case 1:
            system("clear");
            Function1();
            break;
        case 2:
            system("clear");
            Function2();
            break;
        case 3:
            system("clear");
            Function3();
            break;
        case 4:
            system("clear");
            WriteMenu();
            CreateAndLoad();
            break;
        default:
            cout << "Option does not exist" << endl;
        }
        system("read -n 1 -s -p 'Press any key to continue...'");
        system("clear");
    }
    cout << "Exit successful!" << endl;
    return 0;
}
