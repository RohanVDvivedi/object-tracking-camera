#include <iostream>
#include <windows.h>
#include <SerialClass.h>

Serial s("COM6");
using namespace std;

/*
    for accessing the pressed state of keys
    include windows.h
    and pressed state of <key> == true,,, if (GetAsyncKeyState(VK_<key>)!=0)
*/


int main()
{
    while(1)
    {
        if(GetAsyncKeyState(VK_LEFT)!=0)
        {
            s.write_uint_serial(120);
            cout<<"left"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==125)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);
        }
        if(GetAsyncKeyState(VK_RIGHT)!=0)
        {
            s.write_uint_serial(130);
            cout<<"right"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==135)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);
        }
        if(GetAsyncKeyState(VK_UP)!=0)
        {
            s.write_uint_serial(140);
            cout<<"up"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==145)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);
        }
        if(GetAsyncKeyState(VK_DOWN)!=0)
        {
            s.write_uint_serial(150);
            cout<<"down"<<endl;
            Sleep(5);
            if(s.read_uint_serial()==155)
            {
                cout<<"DONE"<<endl;
            }
            Sleep(2);
        }
        Sleep(2);
    }
    return 0;
}
