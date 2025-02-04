
#define _USE_MATH_DEFINES
#include <windows.h>
#include <iostream>
#include <cstring>
#include <iostream>
#include <string>
#include <iomanip>
#include <memoryapi.h>
#include <errhandlingapi.h>
#include <cmath>


const std::string key = std::to_string(M_PI + M_PI * (20.0 / 7.0));

constexpr int CONST_FUNC_SIZE = 171;

const unsigned char functionBytes_cipher[] = "\x64\x7A\xA7\xD4\x79\xB4\xD9\x07\x7A\xB8\x7F\x3E\x79\x89\x41\x54\x45\x06\x04\x41\x5D\x57\x79\x8D\x4D\x5C\x55\x5E\x5D\x48\x43\x49\x7F\xBC\x72\xE2\x79\xBB\x7B\xE9\xF7\x72\xD5\x37\x7A\xF6\x77\xD6\x31\x31\x37\x35\x7F\xF5\x74\xCA\x2E\x31\x31\x37\xDE\x32\x7A\xB2\x77\xD6\x30\x79\xBC\x60\x27\x7A\xBA\x77\xD6\x79\x30\xE7\x3A\x81\x32\xB5\xF2\x5B\xD8\x79\xB4\x48\xCF\x22\x45\x35\x96\x30\x31\x37\x35\xDC\x70\x79\xF5\x6B\xC1\x31\x37\x35\x37\xD9\x1D\x7A\xA5\x64\x21\x7F\xBE\x72\xC2\x79\x33\xFE\x3E\x87\x27\x7D\xBA\x7F\xE1\x7A\xA5\x74\xC1\x7F\x34\xFF\x3D\x87\x32\x16\xF3\x45\x30\x8D\x36\x32\x31\x32\xC5\x20\x79\xB4\x70\xC7\x33\x79\xB1\x53\xC1\x3E\x41\xF8\x8F\x32\x31\x32\x2E\x79\xB2\xF3\x05\x6A\xF1";


void xor_array(const unsigned char* input, const char* key, size_t length, unsigned char* output) {
	for (size_t i = 0; i < length; ++i) {
		output[i] = input[i] ^ key[i % strlen((const char*)key)];
	}
}

// Function to print a single argument
template<typename T>
void printArgument(T&& arg) {
	std::cout << "Value: " << std::forward<T>(arg) << ", Type: " << typeid(arg).name() << "\n";
}

// Variadic template function to print all forwarded arguments
template<typename... Args>
void printAllArguments(Args&&... args) {
	(printArgument(std::forward<Args>(args)), ...);
}

template<typename... Args>
int execute_function_bytes(const unsigned char* bytes, Args&&... args) {
	// Allocate executable memory
	LPVOID executableMemory = VirtualAlloc(
		NULL,
		CONST_FUNC_SIZE,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);

	if (executableMemory == NULL) {
		std::cerr << "Memory allocation failed: " << GetLastError() << std::endl;
		return 1;
	}

	// Print all arguments before executing the function
	//std::cout << "Arguments:\n";
	//printAllArguments(std::forward<Args>(args)...);
	//std::cout << std::endl;

	// Copy function bytes to executable memory
	memcpy(executableMemory, bytes, CONST_FUNC_SIZE);

	// Cast executable memory to function pointer
	auto func_ptr = reinterpret_cast<int(*)(Args...)>(executableMemory);

	// Execute function
	int result = func_ptr(std::forward<Args&&>(args)...);

	//std::cout << "Dynamically executed function returned: " << result << std::endl;

	// Free allocated memory
	VirtualFree(executableMemory, 0, MEM_RELEASE);

	return result;
}

int main() {
	std::cout << "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n";
	std::cout << "\xd7~~~~~~~~~~~~~< Crackme by Matija Bensa >~~~~~~~~~~~~~~\xd7\n";
	std::cout << "\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n";
	std::cout << "                         Mission                        \n";
	std::cout << "  Get the correct password.\n";
	std::cout << "  This time function that checks password is crypted,\n";
	std::cout << "  so you will have to find out how to decrypt it first.\n";
	std::cout << "  To get the function you will have to get the key to\n";
	std::cout << "  unlock it. The key is not hardcoded.\n";
	std::cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n";
	std::cout << "\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\n";
	std::cout << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n";
	std::cout << std::endl;


	// un-xor functionBytes
	unsigned char out2[CONST_FUNC_SIZE];
	xor_array(functionBytes_cipher, key.c_str(), CONST_FUNC_SIZE, out2);

	while (true) {
		std::cout << "Enter password:\n";
		std::string password;
		std::getline(std::cin, password);

		// () run opcode
		auto res = execute_function_bytes(out2, password.c_str());
		if (res == 0) {
			std::cout << "==========\nCORRECT !\n==========\n";
			break;
		}
		std::cout << "wrong password\n";
	}

	std::cout << "Press key to exit\n";
	std::cin.get();
	return 0;
}


