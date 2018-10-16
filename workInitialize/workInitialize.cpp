//
//  main.cpp
//  workInitialize
//
//  Created by okawa on 2017/11/10.
//  Copyright (c) 2017 okawa-h. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

std::string ask(std::string ask) {

	std::string input;
	std::cout << "enter " + ask << std::endl;
	std::cin >> input;
	return input;

}

bool existsDir(const char *dir) {

	struct stat fileStat;
	int ret = stat(dir, &fileStat);
	return (0 == ret);

}

std::string getCurrentDirectory() {

	char dir[255];
	getcwd(dir,255);
	return dir;

}

void createProject(std::string name,const char *dir) {

	if (existsDir(dir)) {

		printf("this project has already been initialized⚠️\n");
		exit(0);

	}

	if (mkdir(dir,0775) == 0) {

		std::string conDir = dir;
		std::string dir00  = conDir + "00_doc";
		std::string dir01  = conDir + "01_material";
		std::string dir02  = conDir + "02_design";
		std::string dir03  = conDir + "03_edit";
		std::string dir04  = conDir + "04_html";

		int counter = 0;
		mkdir(dir00.c_str(),0775);
		mkdir(dir01.c_str(),0775);
		mkdir(dir02.c_str(),0775);
		mkdir(dir03.c_str(),0775);
		mkdir(dir04.c_str(),0775);
		printf("プロジェクト【%s】を作成しました🎉\n",name.c_str());

	} else {

		printf("プロジェクト【%s】の作成に失敗しました\n",name.c_str());

	}

}

int main() {

	std::string name = ask("project name 👷");
	std::string dir  = ask("create directory 📁");
	std::string path = dir + name + "/";

	createProject(name,path.c_str());

	return 0;

}
