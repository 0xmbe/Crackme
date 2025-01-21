#include <iostream>
#include <string>

bool check_username_and_password(std::string username, std::string password) {
	if (username.compare("Matija") != 0) {
		return false;
	}
	if (password.compare("Pass1") != 0) {
		return false;
	}
	return true;
}
int main()
{
	std::cout << "Hello WorldC++!\n";
	std::cout << "Enter username:" << std::endl;
	std::string username;
	std::getline(std::cin, username);
	//std::cin.get()
	std::cout << "Enter password:" << std::endl;
	std::string password;
	std::getline(std::cin, password);
	if (check_username_and_password(username, password)) {
		std::cout << "Username: " << username << " and password: " << password << " are correct!" << std::endl;
	}
	else {
		std::cout << "Wrong password!" << std::endl;
	}
	getchar();
	return 0;
}
