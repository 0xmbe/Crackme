#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <string>
#pragma comment(lib, "ws2_32.lib")	
#include <iomanip>
#include <sstream>


void xor_and_hex_string(std::string& output, const std::string& input, const std::string& key) {
	std::stringstream ss;
	for (size_t i = 0; i < input.length(); ++i) {
		char xored_char = input[i] ^ key[i % key.length()];
		ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(xored_char));
	}
	output = ss.str();
}
void unxor_and_dehex_string(std::string& output, const std::string& input, const std::string& key) {
	std::stringstream ss;	// 1. hex to text, 2. xor
	for (size_t i = 0; i < input.size(); ++++i) {
		std::string hex_pair = input.substr(i, 2);
		std::stringstream ss(hex_pair);	//auto dec_value = std::stoi(hex_pair, nullptr, 16);	// alternative
		int dec_value;
		ss >> std::hex >> dec_value;
		output += dec_value ^ key[i / 2 % key.length()];
	}
}

int try_activate_license(char* received_license_key, const char* sent_license_key) {
	std::string input = received_license_key;
	std::string key = "^&(/*+_0";
	std::string output = {};
	//xor_and_hex_string(output, input, key);
	unxor_and_dehex_string(output, input, key);
	if (strcmp(sent_license_key, output.c_str()) == 0) {
		std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\nPassword Correct!\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
		return 0;
	}
	else {
		std::cout << "Wrong Password!\n";
		return 1;
	}
}
int send_data_to_server(SOCKET ConnectSocket, const char* sendbuf, char* recvbuf) {
	std::cout << "Sending to server: \"" << sendbuf << "\"" << std::endl;
	if (send(ConnectSocket, sendbuf, strlen(sendbuf), 0) == SOCKET_ERROR) {
		std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	//char recvbuf[256];
	int bytesReceived = recv(ConnectSocket, recvbuf, 256, 0);
	if (bytesReceived > 0) {
		recvbuf[bytesReceived] = '\0';
		//std::cout << "Received from server: \"" << recvbuf << "\"" << std::endl;
		std::cout << "Received response from server: \"" << recvbuf << "\"" << std::endl;
		return try_activate_license(recvbuf, sendbuf);
	}
	else {
		std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
		return 1;
	}
}

int main() {
	std::cout << "========================================================\n";
	std::cout << "~~~~~~~~~~~~~~< Crackme by Matija Bensa >~~~~~~~~~~~~~~~\n";
	std::cout << "========================================================\n";
	std::cout << "                         Mission                        \n";
	std::cout << "  Write a server that replicates original server and   \n";
	std::cout << "  sends a response that triggers the correct key in \n";
	std::cout << "  local client application. Essentially make a fake \n";
	std::cout << "  server. \n";
	std::cout << "  This time the license key is encrypted. \n";
	std::cout << "========================================================\n";
	std::cout << std::endl;
	std::cout << "Starting client for sending data through TCP to server" << std::endl;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed." << std::endl;
		std::cout << "Press key to exit\n";
		std::cin.get();
		return 1;
	}
	std::cout << "WSADATA: " << wsaData.szDescription << " " << wsaData.szSystemStatus << std::endl;

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	const char* server_name = "127.0.0.1"; //"localhost";
	const char* server_port = "27015";

	struct addrinfo* result = NULL;
	if (getaddrinfo(server_name, server_port, &hints, &result) != 0) {
		std::cerr << "getaddrinfo failed." << std::endl;
		WSACleanup();
		std::cout << "Press key to exit\n";
		std::cin.get();
		return 1;
	}
	std::cout << "Destination IP: " << server_name << ", PORT: " << server_port << ", " << result->ai_addr << std::endl;

	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		std::cout << "Press key to exit\n";
		std::cin.get();
		return 1;
	}

	if (connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
		std::cerr << "connect failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		std::cout << "Press key to exit\n";
		std::cin.get();
		return 1;
	}

	freeaddrinfo(result);

	while (true) {
		std::cout << "Enter license key for server:\n";
		std::string license_key;
		std::getline(std::cin, license_key);
		// Send data to the server
		const char* sendbuf = license_key.c_str();

		char recvbuf[256] = {};
		int result = send_data_to_server(ConnectSocket, sendbuf, recvbuf);
		//std::cout <<":: " << recvbuf;
		if (result == 0)
			break;
	}

	// close
	closesocket(ConnectSocket);
	WSACleanup();
	std::cout << "Press key to exit\n";
	std::cin.get();
	return 0;
}