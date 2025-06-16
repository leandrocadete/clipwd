#include <iostream>
#include <cstdlib>
#include "manager.h"
#include "Encrypt.h"
#include "pwd.h"
#include "helper.hh"
#include <fstream>

using namespace std;

const char* createOrReadKey(int* size) {
    fstream file("key.db", std::fstream::in);
    if (file.is_open()) {
        file.seekg(0, std::ios::beg);
        string str;
        file >> str;
        *size = str.size();
        return str.c_str();
    } else {
        file = fstream("key.db", std::fstream::out);
        cout << "Enter a default key (between 8 - 20 characteres) to encrypt the password - Example 98@@454" << endl;
        string strKey;
        cin >> strKey;
        file << strKey << endl;
        *size = strKey.size();
        return strKey.c_str();
    }
}


int main(int argc, char** argv) {
    int keySize = 0;
    const char* default_key = createOrReadKey(&keySize);
    char* str_default_key = new char[100];
    strcpy(str_default_key, default_key);
    if (keySize) {
        cout << "KEY:" << default_key << endl;
    }

    int test = 1;
    if (test) {
        Helper *help = new Helper();
        if (argc < 2) {
            printf("** Error: Missing arguments **\n");
            help->showHelp();
            return -1;
        }
        int decision = help->encryptOrDecrypt(argv);
        Pwd *pwd = new Pwd();
        Manager* manager = new Manager("my000db.db");
        if (decision == 0) {
            FILE * fileVersion = fopen("version.db", "r");
            char *version = new char[10];
            fread(version, 10, 1, fileVersion);
            printf("Version: %s", version);
            fclose(fileVersion);
            free(version);
        } else if (decision == 1) {
            printf("Decript\n");
        } else if (decision == 2) { // -c
            printf("Encrypt\n");            
            // -c 10 "description" "pwd_key"            
            pwd->id = atoi(argv[2]);            
            strcpy(pwd->description, argv[3]);
            strcpy(pwd->pwd, argv[4]);
            pwd->size_pwd = strlen(pwd->pwd);
            manager->writePwd(*pwd, str_default_key);
        } else if (decision == 3) {
            printf("List all pwd\n");        
            cout << "-----------" << endl;
            int limit = 0, start = 0;
            std::string** list = manager->list(str_default_key);
            if (argc == 2) {
                limit = manager->getMaxRows() - 1;
            } else if (argc == 3) {
                if (strcmp(argv[2], "all") == 0) {
                    limit = manager->getMaxRows() - 1;
                } else {
                    limit = atoi(argv[2]);
                }                
            } else if (argc == 4) {
                start = atoi(argv[2]);
                limit = atoi(argv[3]) + 1;
            }

            for(int i = start; i < limit; i++) {                
                cout << list[i][0] 
                << " " 
                << list[i][1].c_str()
                << "\t\t" 
                << list[i][2] 
                << "\t\t"
                << list[i][3] << endl;
            }
            cout << "-----------" << endl;
        } else {
            printf("** Error: Wrong argument **\n");
            help->showHelp();
            return -2;
        }        
        return 0;
        
    }
    return 0;
}

