#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

/*
//    string response = "";
    Roboteq device;
    int status = device.Connect("/dev/ttyACM0");

    if(status != RQ_SUCCESS)
    {
        cout<<"Error connecting to device: "<<status<<"."<<endl;
        return 1;
    }

    cout<<"- SetConfig(_DINA, 1, 1)...";
    if((status = device.SetConfig(_DINA, 1, 1)) != RQ_SUCCESS)
        cout<<"failed --> "<<status<<endl;
    else
        cout<<"succeeded."<<endl;

    //Wait 10 ms before sending another command to device
    sleepms(10);

    int result;
    cout<<"- GetConfig(_DINA, 1)...";
    if((status = device.GetConfig(_DINA, 1, result)) != RQ_SUCCESS)
        cout<<"failed --> "<<status<<endl;
    else
        cout<<"returned --> "<<result<<endl;

    //Wait 10 ms before sending another command to device
    sleepms(10);

    cout<<"- GetValue(_ANAIN, 1)...";
    if((status = device.GetValue(_ANAIN, 1, result)) != RQ_SUCCESS)
        cout<<"failed --> "<<status<<endl;
    else
        cout<<"returned --> "<<result<<endl;

    //Wait 10 ms before sending another command to device
    sleepms(10);

    cout<<"- SetCommand(_GO, 2, 150)...";
    if((status = device.SetCommand(_GO, 2, 150)) != RQ_SUCCESS)
        cout<<"failed --> "<<status<<endl;
    else
        cout<<"succeeded."<<endl;

    device.Disconnect();
*/
    return a.exec();
}
