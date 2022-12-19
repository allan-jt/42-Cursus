#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "../../includes/utils/SocketManager.hpp"

const int BUFFER_SIZE = 1000000;

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address
  SocketManager server("127.0.0.1", 8080);

  // Connect to the server
  if (connect(sockfd, reinterpret_cast<sockaddr*>(&server.getAddress()), sizeof(server.getAddress())) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }
  std::cout << "Connected to server" << std::endl;

  // create a vector of requests
  std::vector<std::string> requests;
  requests.push_back("GET / HTTP/1.1\r\nHost: localhost:8080\r\nConnection: close\r\n\r\n");
  requests.push_back("GET /not_found HTTP/1.1\r\nHost: localhost:8080\r\nConnection: close\r\n\r\n");
  requests.push_back("GET /directory/youpi.bla HTTP/1.1\r\nHost: localhost:8080\r\nConnection: close\r\n\r\n");
  std::string body("hello this is cgi communicating with you today. This is working, please end the eval right now. \nThank you");
  requests.push_back("POST /directory/youpi.bla HTTP/1.1\r\nHost: localhost:8080\r\nConnection: close\r\nContent-length: " + std::to_string(body.length()) + "\r\n\r\n" + body);

  for (size_t i = 0; i < requests.size(); i++) {

  // Send an HTTP request to the server
    // for (size_t i = 0; i < requests.size(); i++) {
      std::string request = requests[i];
      for (size_t i = 0; i < request.length(); i++)
        send(sockfd, request.c_str() + i, 1, 0);
    // }

    // Receive a response from the server
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
      std::cerr << "Error receiving response from server" << std::endl;
      return 1;
    }
    std::cout << std::string(buffer, bytes_received) << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
  }
    // Close the socket
    close(sockfd);

  return 0;
}
