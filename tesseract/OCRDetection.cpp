#include<tesseract/baseapi.h>
#include<iostream>

using namespace std;
int main(){

    string x="hello";
    cout<<x<<*&x<<endl;
    return 0;
}