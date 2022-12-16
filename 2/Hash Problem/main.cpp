#include <iostream>
#include <fstream>
#include "Server.h"

using namespace std;

int main()
{
    Server s("credentials.txt");
    //s.insert_secret_notes("a", "a", "a");
    s.show_secret_notes("b","a");
    //s.print();
    //s.delete_secret_notes("a","a");
    return 0;
}