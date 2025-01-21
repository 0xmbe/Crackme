#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <WinSock2.h>
#include <iomanip>
#include <sstream>
#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib

#define DEFAULT_PORT "27015" 



std::string check_valid_password(char* receivedPassword) {
	std::string response = {};
	if (strcmp(receivedPassword, "asf)Eeg9eg9G/E)jve9") == 0) {
		return response = "3F554E066F4E38093B411168056E765A284311";
	}
	else {
		return response = "0";
	}
}
void server_listening_for_receive_data_thread(SOCKET ClientSocket) {
	char recvbuf[256];
	int received_buffer_size;

	// Receive data from the client
	do {
		received_buffer_size = recv(ClientSocket, recvbuf, 256, 0);
		if (received_buffer_size > 0) {
			recvbuf[received_buffer_size] = '\0';
			std::cout << "Received from client: \"" << recvbuf << "\"" << std::endl;

			// Send data back to the client (optional)
			std::cout << "Responding back ..." << std::endl;
			std::string response = {};
			response += "Message received: ";
			response += "\"";
			response += recvbuf;
			response += "\"";
			response += " Response: ";


			// check password
			std::string password_response = check_valid_password(recvbuf);
			std::cout << password_response << std::endl;

			received_buffer_size = send(ClientSocket, password_response.c_str(), password_response.length(), 0);
			if (received_buffer_size == SOCKET_ERROR) {
				std::cerr << "send failed: " << WSAGetLastError() << std::endl;
			}
		}
		// ... (rest of the server code) ...
		std::this_thread::sleep_for(std::chrono::milliseconds(500));        // delay server listening
	} while (true);

	// Close the client socket
	closesocket(ClientSocket);
}

int main() {
	std::cout << "Starting server for receiving data through TCP to server" << std::endl;
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed." << std::endl;
		return 1;
	}
	std::cout << "WSADATA: " << wsaData.szDescription << " " << wsaData.szSystemStatus << std::endl;

	// Create a socket
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		std::cerr << "socket() failed." << std::endl;
		WSACleanup();
		return 1;
	}

	// Bind the socket to an address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Allow connections from any address
	serverAddress.sin_port = htons(atoi(DEFAULT_PORT));

	if (bind(ListenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "bind() failed." << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Start listening for connections
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "listen() failed." << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	std::cout << "Server started and listening on port " << DEFAULT_PORT << std::endl;

	std::cout << "Waiting for password ..." << std::endl;
	while (true) {
		// Accept a connection
		SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			std::cerr << "accept() failed." << std::endl;
			continue;
		}

		// Create a new thread to handle the client
		std::thread serverListeningThread(server_listening_for_receive_data_thread, ClientSocket);
		serverListeningThread.detach();
	}

	// Close the listening socket
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}