//
//  cleaning.cpp
//  cleaning
//
//  Created by okawa on 2018/02/06.
//  Copyright (c) 2017 okawa-h. All rights reserved.
//

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

bool isDirectory(const char* filepath) {
    
    struct stat st;
    stat(filepath,&st);
    return st.st_mode & S_IFDIR;
    
}

std::string getCurrentDirectory() {

	char dir[255];
	getcwd(dir,255);
	return dir;

}

std::vector<std::string> readFiles(std::string dir) {
    
    std::vector<std::string> files;
    DIR *dp = opendir(dir.c_str());
    dirent* entry;
    
    if (dp != NULL) {
        
        do {
            entry = readdir(dp);
            if (entry != NULL) {
                
                char* filename = entry->d_name;
                if (!strcmp(filename, ".") || !strcmp(filename, "..")) continue;
                
                const std::string filepath = dir + "/" + std::string(filename);
                
                if (isDirectory(filepath.c_str())) {
                    
                    struct stat st;
                    stat(filepath.c_str(),&st);
                    printf("%s\n",filepath.c_str() );
                    printf("最終修正時刻 : %s",ctime(&st.st_mtime));
                    printf("最終状態変更時刻 : %s",ctime(&st.st_ctime));

                    readFiles(filepath);
                    
                } else {
                    
                    if (!strcmp(filename, ".DS_Store")) {
                        files.push_back(filepath);
                    }
                    
                }
                
            }
        } while (entry != NULL);
        
    }
    
    closedir(dp);
    return files;
    
}

void deleteFiles(std::vector<std::string> files) {
    
    for (int i = 0; i != files.size(); ++i) {
        std::string file = files[i];
        remove(file.c_str());
        printf("%s\n",file.c_str());
    }
    printf("\n👆 kill 👆\n");
    
}

void showFiles(std::vector<std::string> files) {
    
    printf("\n");
    for (int i = 0; i != files.size(); ++i) {
        std::string file = files[i];
        printf("%s\n",file.c_str());

    }
    
}

void prompt(std::vector<std::string> files) {
    
    std::string action;
    std::cout << "\n😎 Can i delete 💩 files? [y/n]\n";
    std::cin >> action;
    if (action == "y") {
        std::cout << "\n🏃 delete 💩 files\n\n";
        deleteFiles(files);
    } else if (action == "n"){
        std::cout << "\n👋\n";
    } else {
        prompt(files);
    }
    
}

void run(std::string dir) {
    
    if (!isDirectory(dir.c_str())) {
        printf("\n😂 No directory 😂\n");
        exit(1);
    }
    
    std::vector<std::string> files = readFiles(dir);
    if (0 < files.size()) {
        showFiles(files);
        prompt(files);
    } else {
        printf("\n🎉 clean 🎉\n");
    }

}

int main(int argc, char* argv[]) {

	int result;
	while ((result = getopt(argc,argv,"ce:")) != -1) {
		switch(result){

			case 'c':

				run(getCurrentDirectory());
				exit(1);
				break;

			case 'e':
				fprintf(stdout,"%c %s\n",result,optarg);
				break;

			//need value
			case ':':
				break;

			case '?':
				fprintf(stdout,"unknown\n");
				break;
			default:
				std::cout << "Enter path" << std::endl;
				break;
		}
	}

    std::string dir;
    std::cout << "Enter 🔍 path" << std::endl;
    std::cin >> dir;
    run(dir);
    
    return 0;
    
}

