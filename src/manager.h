#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "Encrypt.h"
#include <cstdio>
#include <vector>
using namespace std;

#define MAX_ROWS = 200

typedef struct Pwd {
    int id;
    char description[64];
    char pwd[128];
    int size_pwd;
} stPwd;


class Manager {

private:
    vector<Pwd> vec;
    bool createFile(int c = 0);
    bool readAll();
    string fileName;
    int maxRows;
public:
    Manager(string fname);
    Manager(string fname, size_t size);
    Manager(string fname, size_t size, bool newFile);
    ~Manager();
    bool writePwd(Pwd pwd, string key);
    void readPwdOne(int id, string key);
    string** list(string key);
    bool createEmptyFile(string fname);
    int getMaxRows();
};


#endif // MANAGER_H
