#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

void receive_image(const std::string& save_path, const std::string& server_ip, int server_port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create server socket." << std::endl;
        return;
    }

    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    server_address.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to bind server socket." << std::endl;
        close(server_socket);
        return;
    }

    if (listen(server_socket, 1) < 0) {
        std::cerr << "Failed to listen on server socket." << std::endl;
        close(server_socket);
        return;
    }

    std::cout << "Server is listening on " << server_ip << ":" << server_port << std::endl;

    struct sockaddr_in client_address{};
    socklen_t client_address_len = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
    if (client_socket < 0) {
        std::cerr << "Failed to accept client connection." << std::endl;
        close(server_socket);
        return;
    }

    std::cout << "Connected to client: " << inet_ntoa(client_address.sin_addr) << std::endl;

    uint32_t image_size;
    if (recv(client_socket, &image_size, sizeof(image_size), 0) < 0) {
        std::cerr << "Failed to receive image size." << std::endl;
        close(client_socket);
        close(server_socket);
        return;
    }
    image_size = ntohl(image_size);

    std::cout << "Image size: " << image_size << " bytes" << std::endl;

    std::vector<uint8_t> image_data(image_size);
    uint32_t remaining_bytes = image_size;
    uint32_t offset = 0;
    while (remaining_bytes > 0) {
        uint32_t chunk_size = std::min(4096u, remaining_bytes);
        uint32_t received_bytes = recv(client_socket, &image_data[offset], chunk_size, 0);
        if (received_bytes <= 0) {
            break;
        }
        remaining_bytes -= received_bytes;
        offset += received_bytes;
    }

    std::ofstream output_file(save_path, std::ios::binary);
    if (!output_file) {
        std::cerr << "Failed to open output file: " << save_path << std::endl;
        close(client_socket);
        close(server_socket);
        return;
    }
    output_file.write(reinterpret_cast<const char*>(image_data.data()), image_data.size());
    output_file.close();

    std::cout << "Image received and saved successfully" << std::endl;

    close(client_socket);
    close(server_socket);
}

int main() {
    std::string save_path = "received_image.jpg";
    std::string server_ip = "172.16.5.224";
    int server_port = 5000;

    receive_image(save_path, server_ip, server_port);

    return 0;
}
