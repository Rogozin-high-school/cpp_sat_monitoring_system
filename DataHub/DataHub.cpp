#include "DataHub.hpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

/*
Hey33 

Good job for working on the DataHub implementation, hope you're doing great.

Just a few things to bear in mind (I haven't dug into the code so these are just general notes)
1. Don't forget to work with git. Even if you don't intend upload it yet to the shared GitLab, it's great to start commiting your change history.
2. Don't forget to document the methods (so the others can use and debug this library more easily)
3. Protocol definition; You may document your protocol (explain the message structure) in a separate word/md file or in the .hpp file comments.

Keep up the hard work,
Yotam :)
*/

DataHub::DataHub(string ip, int port) {
    sock_id = socket(PF_INET, SOCK_STREAM, 0); // create new socket
    if (sock_id == -1) {
        cout << "error opening socket" << endl;
        return;
    }
    
    socklen_t addrSize = sizeof(serverAddr);
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(port);
    serverAddr.sin_addr.s_addr  = inet_addr(ip.c_str());
    connect(sock_id, (struct sockaddr*)&serverAddr, addrSize); // connect the socket to the server
}

DataHub::~DataHub() {
    close(sock_id);
}

void DataHub::SendData(int var_id, string data) {
    string message = _STRING; // x type
    message += GetString(var_id, 3) + // xxxx id
        GetString(data.size(), 3) +  // xxx data length
        data; // 1-999 data
    write(sock_id, message.c_str(), message.length());
}

void DataHub::SendData(int var_id, int data) {
    char buffer[BUFFER_SIZE] = { 0 };    
    buffer[0] = _INT; // x type 
    char idBuffer[4]; // xxxx id
    int_to_bytes(var_id, idBuffer);
    char lengthBuffer[4]; // xxxx data length
    string datas = to_string(data);
    int_to_bytes(datas.length(), lengthBuffer); 
    memcpy(buffer + 1, idBuffer, 4);
    memcpy(buffer + 5, lengthBuffer, 4);
    memcpy(buffer + 9, datas.c_str(), datas.length());
    write(sock_id, buffer, BUFFER_SIZE); 
}

void DataHub::SendData(int var_id, float data) {
    char buffer[BUFFER_SIZE] = { 0 };    
    buffer[0] = _INT; // x type 
    char idBuffer[4]; // xxxx id
    int_to_bytes(var_id, idBuffer);
    char lengthBuffer[4]; // xxxx data length
    string datas = to_string(data);
    int_to_bytes(datas.length(), lengthBuffer); 
    memcpy(buffer + 1, idBuffer, 4);
    memcpy(buffer + 5, lengthBuffer, 4);
    memcpy(buffer + 9, datas.c_str(), datas.length());
    write(sock_id, buffer, BUFFER_SIZE); 
}

string DataHub::GetString(int num, int factor) {
    string str_num = to_string(num),
        str = "";
    for (int i = str_num.length(); i < factor; i++) {
        str += "0";
    }
    return str + str_num;
}

void* DataHub::RecvData() {
    char buffer[BUFFER_SIZE] = { 0 };
    auto get = read(sock_id, buffer, BUFFER_SIZE - 1);
    buffer[get] = 0;
    string message = buffer;
    return message;
}

void DataHub::int_to_bytes(int num, char* buffer) {
    buffer[0] = (num >> 24) & 0xFF;
    buffer[1] = (num >> 16) & 0xFF;
    buffer[2] = (num >> 8) & 0xFF;
    buffer[3] = num & 0xFF;
}

int DataHub::bytes_to_int(char* b) {
    return b[0] << 24 | b[1] << 16 | b[2] << 8 | b[3];
}