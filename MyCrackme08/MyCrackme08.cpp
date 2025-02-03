
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <cstdio>
#include <windows.h>
#include <fileapi.h>
#include <corecrt.h>
#include <winreg.h>
#include <sstream>
#include <iosfwd>
#include "MyCrackme08.h"
#include <cstring>
#include <iomanip>
#include <ios>


void RC4Init(std::vector<size_t>& S, const std::string& key, size_t key_size) {
	S.resize(key_size);
	for (size_t i = 0; i < key_size; i++) {
		S[i] = i;
	}

	size_t j = 0;
	for (size_t i = 0; i < key_size; i++) {
		j = (j + S[i] + key[i % key.size()]) % key_size;
		std::swap(S[i], S[j]);
	}
}

void RC4(const std::string& data_buffer, const std::string& key, const size_t key_size, std::string& output_data_buffer) {
	std::vector<size_t> S;
	RC4Init(S, key, key_size);

	output_data_buffer = data_buffer;
	size_t i = 0, j = 0;
	for (size_t n = 0; n < data_buffer.size(); n++) {
		i = (i + 1) % key_size;
		j = (j + S[i]) % key_size;
		std::swap(S[i], S[j]);
		size_t k = S[(S[i] + S[j]) % key_size];
		output_data_buffer[n] ^= k;
	}
}

void read_dword_from_registry(HKEY accessMask, const TCHAR* szSubKey, const TCHAR* szValueName, DWORD& output) {
	HKEY hKey;
	LONG lResult = RegOpenKeyEx(accessMask, szSubKey, 0, KEY_READ, &hKey);

	if (lResult == ERROR_SUCCESS) {
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof(output);

		lResult = RegQueryValueEx(hKey, szValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(&output), &dwSize);

		if (lResult == ERROR_SUCCESS) {
			//std::cout << "Read DWORD value from registry: " << output << std::endl;
		}
		else {
			std::cerr << "Error reading DWORD value from registry: " << lResult << std::endl;
		}

		RegCloseKey(hKey);
	}
	else {
		std::cerr << "Error opening registry key: " << lResult << std::endl;
	}
}

void read_string_from_registry(HKEY accessMask, const TCHAR* szSubKey, const TCHAR* szValueName, std::string& output) {
	HKEY hKey;
	LONG lResult = RegOpenKeyEx(accessMask, szSubKey, 0, KEY_READ, &hKey);

	if (lResult == ERROR_SUCCESS) {
		DWORD dwType = REG_SZ;
		DWORD dwSize = 0;

		lResult = RegQueryValueEx(hKey, szValueName, NULL, &dwType, NULL, &dwSize);

		if (lResult == ERROR_SUCCESS) {
			std::vector<BYTE> buffer(dwSize);

			lResult = RegQueryValueEx(hKey, szValueName, NULL, &dwType, buffer.data(), &dwSize);

			if (lResult == ERROR_SUCCESS) {
				std::wstring wstr(reinterpret_cast<WCHAR*>(buffer.data()));
				output = std::string(wstr.begin(), wstr.end());
				//std::wcout << L"Read string value from registry: " << wstr << std::endl;
			}
			else {
				std::cerr << "Error reading string value from registry: " << lResult << std::endl;
			}
		}
		else {
			std::cerr << "Error querying value size: " << lResult << std::endl;
		}

		RegCloseKey(hKey);
	}
	else {
		std::cerr << "Error opening registry key: " << lResult << std::endl;
	}
}

void convert_time_to_date_time(time_t time_value) {
	struct tm time_info;

	// Convert time_t to struct tm using localtime_s
	localtime_s(&time_info, &time_value);

	// Print the formatted date and time
	printf("%04d-%02d-%02d %02d:%02d:%02d\n", time_info.tm_year + 1900, time_info.tm_mon + 1, time_info.tm_mday,
		time_info.tm_hour, time_info.tm_min, time_info.tm_sec);
}

void perform_bitshifting_left(std::string& str, int shift) {
	for (char& c : str) {
		c = c << shift;
	}
}
void perform_bitshifting_right(std::string& str, int shift) {
	for (char& c : str) {
		c = c >> shift;
	}
}

void text_to_hex(std::string& output, const std::string& input) {
	std::stringstream ss;
	for (auto& c : input) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
	}
	output = ss.str();
}

void generate_unique_key(std::string& output) {

	// Get disk SN
	DWORD disc_volume_seria_dw;
	GetVolumeInformationA(NULL, NULL, 0, &disc_volume_seria_dw, NULL, NULL, NULL, 0);
	std::string disc_volume_serial = std::to_string(disc_volume_seria_dw);
	//std::cout << "Disc Serial Number: " << disc_volume_serial << std::endl;

	// Get OS install date
	DWORD InstallDate = {};
	read_dword_from_registry(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), TEXT("InstallDate"), InstallDate);
	//std::cout << "InstallDate: " << InstallDate << std::endl;
	//convert_time_to_date_time(InstallDate);

	//Get OS Product name
	std::string ProductName;
	read_string_from_registry(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), TEXT("ProductName"), ProductName);
	//std::cout << "ProductName: " << ProductName << std::endl;

	// Get OS Win version
	std::string WinREVersion;
	read_string_from_registry(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), TEXT("WinREVersion"), WinREVersion);
	//std::cout << "WinREVersion: " << WinREVersion << std::endl;

	// Combine all unique IDs
	std::stringstream combined;
	combined << disc_volume_serial << InstallDate << ProductName << WinREVersion;
	std::string combined_string = combined.str();
	combined_string.reserve();

	// Do some bitshifting
	perform_bitshifting_left(combined_string, 2);
	//std::cout << combined_string << std::endl;

	// Convert to hex
	text_to_hex(output, combined_string);
}

int main() {
	std::cout << "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n";
	std::cout << "\xd7~~~~~~~~~~~~~< Crackme by Matija Bensa >~~~~~~~~~~~~~~\xd7\n";
	std::cout << "\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n";
	std::cout << "                         Mission                        \n";
	std::cout << "  Get a unique system key.\n";
	std::cout << "  Key is not hardcoded, it is uniqly generated\n";
	std::cout << "  based on your system. Find out how.\n";
	std::cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n";
	std::cout << "\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\n";
	std::cout << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n";
	std::cout << std::endl;

	while (true) {

		std::cout << "Enter unique computer password\n";
		std::string user_input_password;
		std::getline(std::cin, user_input_password);

		// Generate unique key
		std::string unique_key = {};
		generate_unique_key(unique_key);
		//std::cout << "unique_key:\n" << unique_key << std::endl;

		// Encrypt unique key with unique key (self key) RC4
		std::string unique_key_cipher;
		RC4(unique_key, unique_key, 256, unique_key_cipher);
		//std::cout << "unique_key_cipher:\n";
		//for (unsigned char c : unique_key_cipher) {
		//	printf("%02x", c);
		//}
		//std::cout << std::endl;

		// Encrypt user password with RC4
		std::string user_input_password_cipher;
		RC4(user_input_password, unique_key, 256, user_input_password_cipher);
		//std::cout << "user_password_cipher:\n";
		//for (unsigned char c : user_input_password_cipher) {
		//	printf("%02x", c);
		//}
		//std::cout << std::endl;

		//// Decryption
		//std::string decrypted;
		//RC4(unique_key, unique_key, 256, decrypted);
		//std::cout << "Decrypted:\n" << decrypted << std::endl;

		// Check if user password cipher and unique key cipher match
		if (memcmp(unique_key_cipher.c_str(), user_input_password_cipher.c_str(), unique_key_cipher.size()) == 0) {
			std::cout << "\nCORRECT PASSWORD!\n\n";
			break;
		}
		else {
			std::cout << "Wrong password!\n";
		}
	}

	std::cout << "Press key to exit\n";
	std::cin.get();
	return 0;
}