
#include <iostream>
#include <string>
#include <bitset>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

std::string text_to_binary(const std::string& text) {
	std::string binary_string = {};
	for (char c : text) {
		binary_string += std::bitset<8>(c).to_string();
	}
	binary_string += '\0';
	return binary_string;
}
std::string binary_to_text(const std::string& binary) {
	std::string text = {};
	for (int i = 0; i < binary.size(); i += 8) {
		std::string byteString = binary.substr(i, 8);
		char bs_char = (char)std::bitset<8>(byteString).to_ulong();

		//auto bs = byteString.;
		text += bs_char;
	}
	text += '\0';
	return text;
}
char* reverse(char* str) {
	//char* original = str;
	size_t strLength = strlen(str);
	//char lastChar = str[strLength];
	char* newStr = new char[strLength];
	//size_t newStrLength1 = strlen(newStr);
	int r = 0;
	for (int i = strLength - 1; i >= 0; i--) {
		newStr[r] = str[i];
		r++;
	}
	newStr[r] = '\0';
	size_t newStrLength = strlen(newStr);
	return newStr;										// DELETE AFTER USE ! -> delete[] newStr;
}
std::string replace_characters(std::string* input, char from, char to) {
	std::string newString;
	while (input->back() == ' ') {			// REMOVE TRAILING SPACES
		input->pop_back();
	}
	for (char ch : *input) {				// REPLACE SPACE WITH 20%
		if (ch == from) {
			newString += to;		//"20%"
		}
		else {
			newString += ch;
		}
	}
	return newString;
}

std::string compress(char* input) {
	std::string compressed;
	for (long long i = 0; input[i] != '\0';) {
		char currentChar = input[i];
		int sameChars = 1;
		while (input[++i] == currentChar) {
			sameChars++;
		}
		compressed += currentChar;
		compressed += std::to_string(sameChars);
		compressed += " ";
	}
	compressed += '\0';
	return compressed;
}

std::string decompress(const char* input) {
	std::string decompressed;
	std::istringstream iss(input);
	std::string token;
	while (std::getline(iss, token, ' ')) {
		if (!token.empty()) {
			char character = token[0];
			int repetitions = std::stoi(token.substr(1));
			decompressed.append(repetitions, character);
		}
	}
	return decompressed;
}
std::string CRYPT(std::string originalText) {
	std::string text_20p = replace_characters(&originalText, ' ', '%');							// REPLACE SPACE WITH %
	std::string text_20p_bin = text_to_binary(text_20p);										// TEXT TO BINARY
	char* text_20p_bin_chr = &text_20p_bin[0];													// REVERSE
	char* text_20p_bin_chr_rev = reverse(text_20p_bin_chr);
	std::string text_20p_bin_chr_rev_comp = compress(text_20p_bin_chr_rev);						// COMPRESS
	return text_20p_bin_chr_rev_comp;
}
std::string DECRYPT(std::string cryptedText) {
	char* cryptedText_char = &cryptedText[0];
	std::string cryptedText_decomp = decompress(cryptedText_char);									// DE-COMPRESS
	char* cryptedText_decomp_char = &cryptedText_decomp[0];											// REVERSE
	char* cryptedText_decomp_char_rev = reverse(cryptedText_decomp_char);
	std::string cryptedText_decomp_char_rev_totext = binary_to_text(cryptedText_decomp_char_rev);	// BINARY TO TEXT
	std::string cryptedText_decomp_char_rev_totext_no20p =											// REPLACE % WITH SPACE
		replace_characters(&cryptedText_decomp_char_rev_totext, '%', ' ');
	return cryptedText_decomp_char_rev_totext_no20p;
}
std::vector<std::string> read_file(std::string filename) {
	std::ifstream file(filename);
	std::string line;
	std::vector<std::string> lines;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
	}
	else {
		std::cout << "No license file found.\n";
	}
	return lines;
}
bool check_password(std::string text1, std::string text2) {
	if (text1.size() < 1)
		return false;
	if (text2.size() < 1)
		return false;
	const char* t1 = text1.c_str();
	const char* t2 = text2.c_str();
	if (strcmp(t1, t2) == 0) {
		return true;
	}
	//if (text1.compare(text2) == 0) {
	//	return true;
	//}
	return false;
}
int main()
{
	std::cout << "================================================\nMission:\nWrite a keygen algorithm that gets you correct password for any input username.\n================================================\n";
	std::cout << "Enter Username:\n";
	std::string input_username;
	std::getline(std::cin, input_username);
	//std::cout << "Enter Password:\n";
	//std::string input_password;
	//std::getline(std::cin, input_password);
	//std::string originalText = "Matija";
	auto start = std::chrono::high_resolution_clock::now();
	// CRYPT:
	std::string cryptedText = CRYPT(input_username);
	//std::cout << cryptedText << std::endl;
	std::vector<std::string> lines = read_file("../MyCrackme04_key.txt");
	if (lines.empty())
		return 0;
	bool result = check_password(lines[1], cryptedText);
	if (result) {
		std::cout << "Password is correct!\n";
	}
	else {
		std::cout << "Wrong password!\n";
	}
	// DE-CRYPT:
	/*std::string deCryptedText = DECRYPT(cryptedText);
	std::cout << deCryptedText << std::endl;*/
	auto end = std::chrono::high_resolution_clock::now();
	auto delta = end - start;
	std::chrono::duration< double > deltaTime = end - start;
	auto milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(deltaTime);
	long long ms = milliseconds.count();
	getchar();
}
