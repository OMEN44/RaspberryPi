#include <iostream>

using namespace std;

void addToInt(int &x) {
    x += 5;
}

int main()
{
    //create a variable
    int var = 7;
    cout << "Value of var: " << var << endl; //prints Value of var: 7

    //create a pointer to the variable
    int* ptr = &var;
    cout << "Value of ptr that points to &var: " << ptr << endl; //prints Value of ptr: 0x7ffeeb0b4a3c

    //dereference the pointer
    cout << "Value of *ptr: " << *ptr << endl; //prints Value of *ptr: 7

    //change the value of the variable through the pointer
    cout << "Setting *ptr to 8" << endl; //prints Setting *ptr to 8
    *ptr = 8;
    cout << "Value of var: " << var << endl; //prints Value of var: 8

    //create a reference to the variable
    cout << "Creating a reference to var named 'ref'" << endl; //prints Creating a reference to var
    int& ref = var;
    cout << "Value of ref: " << ref << endl; //prints Value of ref: 8

    //change the value of the variable through the reference
    cout << "Setting ref to 9" << endl; //prints Setting ref to 9
    ref = 9;
    cout << "Value of var: " << var << endl; //prints Value of var: 9


    //With functions
    int x = 0;
    int& rx = x;
    cout << "Value of x: " << x << endl; //prints Value of x: 0
    cout << "Value of rx: " << rx << endl; //prints Value of rx: 0

    cout << "Adding 5 to rx" << endl; //prints Adding 5 to x
    addToInt(rx);

    cout << "Value of x: " << x << endl; //prints Value of x: 5
    cout << "Value of rx: " << rx << endl; //prints Value of rx: 5


    return 0;
}