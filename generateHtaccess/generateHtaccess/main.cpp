//
//  main.cpp
//  generateHtaccess
//
//  Created by okawa on 2017/11/10.
//  Copyright (c) 2017 okawa-h. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <fstream>

std::string ask(std::string ask) {

	std::string input;
	std::cout << "Enter " + ask << std::endl;
	std::cin >> input;
	return input;

}

std::string getCurrentDirectory() {

	char dir[255];
	getcwd(dir,255);
	return dir;

}

void generateFile(std::string filename, std::string inputdata) {

	std::ofstream file;
	file.open(filename);
	std::cout << "writing " << filename << "..." << std::endl;
	file << inputdata << std::endl;
	file.close();

}

std::string getHtaccessData() {

	return "AuthType Basic\nAuthName \"Input your ID and Password.\"\nAuthUserFile \"htpasswd.\"\nrequire valid-user";

}

void generateHtpasswd(std::string username,std::string password) {

	char buffer[100];
	std::string command = "htpasswd -c -b ./htpasswd.txt " + username + " " + password;
	strcpy(buffer,command.c_str());
	system(buffer);

}

int main() {

	std::string username = ask("username 😎");
	std::string password = ask("password 🔑");

	generateFile("htaccess.txt",getHtaccessData());
	generateHtpasswd(username,password);
	std::cout << "Please edit htaccess.txt. AuthUserFile will be sever path." << std::endl;

	return 0;

}
