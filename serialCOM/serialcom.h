#include <windows.h>
#ifndef SERIALCOM
#define SERIALCOM

class serialCOM {

public:
    serialCOM(LPCWSTR comPort, int bRate);
    DWORD sendSerial(int value);
    void closeSerial();
private:
    //variable to store handle created when open serial communication port
    HANDLE hSerial;
};

serialCOM::serialCOM(LPCWSTR comPort, int bRate){
    //Create Serial Handle (Open a serial port)
    hSerial = CreateFile(comPort,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         0,
                         0);

    if (hSerial == INVALID_HANDLE_VALUE){
        if(GetLastError()==ERROR_FILE_NOT_FOUND){
            cout<<"Cant find Comm Port";
        }
        cout<<"Tried to find comm port but other issue occured."<<endl;
    }

    //Set serial parameters
    DCB dcbSerialParams = {0};

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout<<"cant get cstate of comm port before setting param"<<endl;
    }

    dcbSerialParams.BaudRate=bRate;
    dcbSerialParams.ByteSize=DATABITS_8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    dcbSerialParams.fDtrControl = 0;
    dcbSerialParams.fRtsControl = 0;

    if(!SetCommState(hSerial, &dcbSerialParams)){
        cout<<"cant get cstate of comm port after setting param"<<endl;
    }

    //Set serial timeouts so program doesnt hang while waiting for data
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier =10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if(!SetCommTimeouts(hSerial, &timeouts)){
        cout<<"error setting timeouts"<<endl;
    }
}

//Sends interger value through the opened serial port, returns number of bytes sent
DWORD serialCOM::sendSerial(int value){
    DWORD dwBytesWritten;

    if(!WriteFile(hSerial, &value, (DWORD) sizeof (value), &dwBytesWritten, NULL)){
        cout<<"error sending data"<<endl;
    }

    return dwBytesWritten;
}

//Closes the serial port connection
void serialCOM::closeSerial(){
    CloseHandle(hSerial);
}


#endif // SERIALCOM

