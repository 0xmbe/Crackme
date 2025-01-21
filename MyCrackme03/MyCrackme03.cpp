#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

bool check_username_and_password(char* username, char* password) {
	if (strcmp(username, "Matija") != 0) {
		return false;
	}
	if (strcmp(password, "Pass3") != 0) {
		return false;
	}
	return true;
}
void test2() {
	std::string str1;
	auto aa = str1.c_str();
	//memset()
}
void test1() {
	int counter1 = 0;
	int counter2 = 0;
	char input_name[12] = "Some input";
	char s_Matija;
	//char s_Matija = new char[6];
	strcpy(&s_Matija, "Matija");
	do {
		counter1 = counter2 + 1;
		auto aaa = (&s_Matija)[counter2];
		if (input_name[counter2] != (&s_Matija)[counter2])
			//goto LAB_14000116d;
			int wrongPass;
		counter2 = counter1;
	} while (counter1 != 7);

LAB_14000116d:
	int aa = 0;
}

int main()
{
	//test1();
	std::cout << "Hello WorldC++!\n";
	std::cout << "Enter username:" << std::endl;
	char username[50];
	std::cin.get(username, 50);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard newline
	//std::getline(std::cin, username);
	std::cout << "Enter password:" << std::endl;
	char password[50];
	std::cin.get(password, 50);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard newline
	if (check_username_and_password(username, password)) {
		std::cout << "Username: " << username << " and password: " << password << " are correct!" << std::endl;
	}
	else {
		std::cout << "Wrong password!" << std::endl;
	}
	getchar();
	return 0;
}
