#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class MyCrackme05_1 {
public:
	void run() {
		std::cout << "========================================================\n";
		std::cout << " ~~~~~~~~~~~~~< Crackme by Matija Bensa >~~~~~~~~~~~~~ =\n";
		std::cout << "=                        Mission                       =\n";
		std::cout << "= Write a keygen algorithm that gets                   =\n";
		std::cout << "= you correct password for any input username.         =\n";
		std::cout << "========================================================\n";
		while (true) {
			std::cout << "Enter Username:\n";
			std::string input_username;
			std::getline(std::cin, input_username);
			if (input_username.size() < 5) {
				std::cout << "Username length is too short.\n";
				break;
			}
			std::cout << "Enter Password:\n";
			std::string input_password;
			std::getline(std::cin, input_password);
			std::string key = "_$\"7\\'";
			std::string result_xor = {};
			xor_strings(result_xor, input_username, key);
			std::string result_xor_hex;
			text_to_hex(result_xor_hex, result_xor);
			//std::cout << "XOR result: " << result_xor_hex << std::endl;
			int retFlag;
			check_password(result_xor_hex, input_password, retFlag);
			if (retFlag == 0) break;
		}
	}
private:
	static void text_to_hex(std::string& output, const std::string& input) {
		std::stringstream ss;
		for (auto& c : input) {
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
		}
		output = ss.str();
	}
	static void xor_strings(std::string& output, const std::string& input, const std::string& key) {
		for (size_t i = 0; i < input.length(); ++i) {
			output += input[i] ^ key[i % key.length()];
		}
	}
	static void check_password(std::string& result_xor_hex, std::string& input_password, int& retFlag) {
		retFlag = 1;
		if (result_xor_hex == input_password) {
			std::cout << "~~~~~~~~~~~~~\nPassword Correct!\n~~~~~~~~~~~~~\n";
			retFlag = 0;
			return;
		}
		else {
			std::cout << "Wrong Password!\n";
		}
	}
};
int main() {
	MyCrackme05_1 myCrackme;
	myCrackme.run();
	std::cout << "Press key to exit\n";
	std::cin.get();
	return 1;
}