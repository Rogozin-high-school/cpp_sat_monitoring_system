/*

    protocol as follows: 

    first byte
    {
    integer - 1

    float - 2

    string - 3
    }
    the id of the parameter is 4 bytes long

    the length of the message shall be 3 bytes

    in addition a full message shall look like this : <x(type)><xxxx(id)><xxxx(length)><msg(0-999 bytes)>
*/


#pragma once
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>

#define BUFFER_SIZE 1024 
#define _INTEGER 1
#define _FLOAT 2
#define _STRING 3

using std::string;

class DataHub
{
public:
    DataHub(string ip, int port);
    ~DataHub();
    void SendData(int var_id, string data);
    void SendData(int var_id, int data);
    void SendData(int var_id, float data);
    void* RecvData();
    static void int_to_bytes(int num, char* buffer);
    static int bytes_to_int(char* buffer);
private:
    string _ip;
    int _port,
        sock_id;
    struct sockaddr_in serverAddr;
    static string GetString(int num, int refactor);
};

