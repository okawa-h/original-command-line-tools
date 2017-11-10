//
//  main.cpp
//  deleteTrash
//
//  Created by okawa on 2017/11/09.
//  Copyright (c) 2017年 okawa-h. All rights reserved.
//

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>

std::vector<std::string> delete_files;

bool isDirectory( const char* filepath ) {
    
    struct stat st;
    stat(filepath,&st);
    if (st.st_mode & S_IFDIR) return true;
    return false;
    
}

void read(std::string dir) {
    
    const char* path = dir.c_str();
    DIR *dp = opendir(path);
    dirent* entry;
    
    if (dp != NULL) {
        
        do {
            entry = readdir(dp);
            if (entry != NULL) {
                
                char* filename = entry->d_name;
                if (!strcmp(filename, ".") || !strcmp(filename, "..")) continue;
                
                const std::string filepath = dir + "/" + std::string(filename);
                
                if (isDirectory(filepath.c_str())) {
                    
                    read(filepath);
                    
                } else {
                    
                    if (!strcmp(filename, ".DS_Store")) {
                        delete_files.push_back(filepath);
                    }
                    
                }
                
            }
        } while (entry != NULL);
        
    }
    
    closedir(dp);
    
}

void deleteFiles() {
    
    for (int i = 0; i != delete_files.size(); ++i) {
        std::string target = delete_files[i];
        remove(target.c_str());
        printf("%s\n",target.c_str());
    }
    printf("\n👆 kill 👆\n");
    
}

void showFiles() {
    
    printf("\n");
    for (int i = 0; i != delete_files.size(); ++i) {
        std::string target = delete_files[i];
        printf("%s\n",target.c_str());
    }
    
}

void prompt() {
    
    std::string choice;
    std::cout << "\n😎 Can i delete 💩 files? [y/n]\n";
    std::cin >> choice;
    if (choice == "y") {
        std::cout << "\n🏃 delete 💩 files\n\n";
        deleteFiles();
    } else if (choice == "n"){
        std::cout << "\n👋\n";
    } else {
        prompt();
    }
    
}

int main() {
    
    std::string dir;
    std::cout << "Enter 🔍 path" << std::endl;
    std::cin >> dir;
    
    if (!isDirectory(dir.c_str())) {
        printf("\n😂 No directory 😂\n");
        exit(1);
    }
    
    read(dir);
    if (0 < delete_files.size()) {
        showFiles();
        prompt();
    } else {
        printf("\n🎉 clean 🎉\n");
    }
    
    return 0;
    
}

