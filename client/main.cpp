#include <iostream>
#include <stdio.h>
#include <dirent.h>

    int main(void) {
        DIR * rep = opendir(".");

        if (rep != NULL) {
            struct dirent * ent;

            while ((ent = readdir(rep)) != NULL) {
                printf("%s\n", ent->d_name);
            }

            closedir(rep);
        }

        return 0;
    }