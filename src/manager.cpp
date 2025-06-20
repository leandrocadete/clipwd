#include "manager.h"
Manager::Manager(string fname) {
    this->fileName = fname;
    maxRows = 200;
    createFile();
}
Manager::Manager(string fname, size_t size) {
    this->fileName = fname;
    maxRows = size;
    createEmptyFile(fname);
}

Manager::Manager(string fname, size_t size, bool newFile) {
    this->fileName = fname;
    maxRows = size;
    if (newFile)
        createEmptyFile(fname);
}

Manager::~Manager() {    
}

int Manager::getMaxRows() {
    return maxRows;
}

bool Manager::writePwd(Pwd pwd, string key){
    FILE *file = fopen(fileName.c_str(), "r+");
    Encrypt encrypt;
    encrypt.setKey(key.c_str());
    int length;
    char * cpwd = encrypt.encrypt(pwd.pwd, &length);
    pwd.size_pwd = length;
    strcpy(pwd.pwd, cpwd);
    if(file == nullptr) {
        cerr << "Error to read file " << endl;
        return false;
    }
    fseek(file, sizeof (Pwd) * pwd.id, SEEK_SET);
    fwrite(&pwd, sizeof (Pwd), 1, file);
    fclose(file);
    return true;
}
void Manager::readPwdOne(int id, string key){
    FILE *file = fopen(fileName.c_str(), "r");
    Encrypt encrypt;
    encrypt.setKey(key.c_str());
    if(file == nullptr) {
        cerr << "Error to read file" << endl;
        return;
    }
    fseek(file, sizeof(Pwd) * id, SEEK_SET);
    Pwd *pwd = new Pwd();
    fread(pwd, sizeof(Pwd), 1, file);

    cout << "------------------READ ONE---------------------------" << endl;
    cout << "ID: " << pwd->id << endl;
    cout << "Description: " << pwd->description << endl;
    cout << "pwd: " << pwd->pwd << endl;
    cout << "pwd decryped:" << encrypt.decrypt(pwd->pwd, pwd->size_pwd) << endl;
    cout << "-----------------------------------------------------" << endl;
    fclose(file);
}
bool Manager::createFile(int c){
    Pwd *pwd;
    FILE *file = fopen(fileName.c_str(), "rb");
    if (file != nullptr) {
        for (int i = 0; i < maxRows; i++) {
            pwd = new Pwd();
            fread(pwd, sizeof(Pwd), 1, file);
            vec.push_back(*pwd);
        }

        if (c > 0) {
            cout << "List: " << vec.size() << endl;
            for (const auto& x : vec) {
                cout << "id: " << x.id;
                cout << " description:" << x.description << endl;
                cout << " encrypted pwd:" << x.pwd << endl;
            }
            cout << "End list" << endl;
        }
    } else if (file == nullptr) {
        file = fopen(fileName.c_str(), "wb");
        if(file != nullptr) {
            pwd = new Pwd();
            for (int i = 0; i < maxRows; i++) {
                pwd->id = i;
                strcpy(pwd->description, ""); // empty
                fwrite(pwd, sizeof (Pwd), 1, file);
            }
            delete pwd;
        } else {
            cerr << "Error to create file" << endl;
            return false;
        }
    }
    fclose(file);
    return true;
}
bool Manager::createEmptyFile(string fname) {
    cout << "createEmptyFile: " << fname << endl;
    FILE * file = fopen(fname.c_str(), "wb");
    if(file != nullptr) {
        Pwd *pwd = new Pwd();
        for (int i = 0; i < maxRows; i++) {
            pwd->id = i;
            strcpy(pwd->description, "");
            fwrite(pwd, sizeof (Pwd), 1, file);
        }
        delete pwd;
        fclose(file);
    } else {
        cerr << "Error to create file" << endl;
        return false;
    }
    return true;
}
string** Manager::list(string key) {
    cout << "Will read the list" << endl;

    string **strs = new string*[maxRows]; // [100][4]
    for(int i = 0; i < maxRows; i++) {
        strs[i] = new string[4];
    }
    //cout << "after **strs allocation" << endl;
    FILE *file = fopen(fileName.c_str(), "r");
    Encrypt encrypt;
    //cout << "After Encrypt ctor - " << key << endl;
    encrypt.setKey(key.c_str());
    //cout << "setKey " << key << endl;
    if(file == nullptr) {
        cerr << "Error to read file" << endl;
        return NULL;
    }

    char *buffer = new char[4];
    //cout << "After buffer allocation" << endl;
    for (int i = 0; i< maxRows; i++) {
        Pwd *pwd = new Pwd();
        fread(pwd, sizeof(Pwd), 1, file);
        //if(strcmp(pwd->description, "empty")) continue;
        //cout << "------------------READ ONE---------------------------" << endl;
        //cout << "ID: " << pwd->id << endl;
        sprintf(buffer, "%d", pwd->id);
        strs[i][0] = string(buffer);

        //cout << "Description: " << pwd->description << endl;
        strs[i][1] = pwd->description;
        //cout << "pwd: " << pwd->pwd << endl;
        strs[i][2] = pwd->pwd;
        //cout << "pwd decryped:" << encrypt.decrypt(pwd->pwd, pwd->size_pwd) << endl;
        strs[i][3] = encrypt.decrypt(pwd->pwd, pwd->size_pwd);
        //cout << "-----------------------------------------------------" << endl;
    }
    fclose(file);
    return strs;
}
