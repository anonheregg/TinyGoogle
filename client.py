import socket
import struct

def send_image(image_path, server_ip, server_port):
    # Create a TCP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        client_socket.connect((server_ip, server_port))
        print("Connected to the server")

        # Read the image file as binary data
        with open(image_path, "rb") as file:
            image_data = file.read()

        # Send the size of the image
        size_data = struct.pack("!I", len(image_data))
        client_socket.sendall(size_data)

        # Send the image data to the server
        client_socket.sendall(image_data)
        print("Image sent successfully")
    except Exception as e:
        print("Error:", e)
    finally:
        # Close the socket connection
        client_socket.close()
        print("Connection closed")

# Specify the image file path, server IP, and server port
image_path = "path_to_image.jpg"
server_ip = "127.0.0.1"  # Replace with the server IP address
server_port = 5000  # Replace with the server port

# Call the send_image function
send_image(image_path, server_ip, server_port)
