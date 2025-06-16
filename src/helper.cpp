#ifndef HELPER_CPP
#define HELPER_CPP

#include "helper.hh"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

void Helper::showHelp() {
   printf("Software to store encrypted passwords\n"); 
   printf("Usage: \n");
   printf("qPasswordManager [options]\n");
   printf("Options:\n");
   printf("   -l, --list Show all passwords\n");
   printf("   -h, --help\n");
   printf("   -c, --create\n");
   printf("   -v, --version\n");
}

int Helper::encryptOrDecrypt(char *argv[]) {    
    if (strcmp(argv[1], "-d") == 0) {
        printf("001 - Arg value: %s\n", argv[1]);
        return 1;
    } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--create") == 0) {
        printf("002 - Arg value: %s\n", argv[1]);
        return 2;
    } else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
        printf("002 - Arg value: %s\n", argv[1]);
        return 3;
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        return -1;
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        return 0;
    }
    return -3;
}

#endif
