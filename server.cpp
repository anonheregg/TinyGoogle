import socket
import struct

def receive_image(save_path, server_ip, server_port):
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        
        server_socket.bind((server_ip, server_port))

        
        server_socket.listen(1)
        print("Server is listening on {}:{}".format(server_ip, server_port))

        
        client_socket, client_address = server_socket.accept()
        print("Connected to client:", client_address)

        
        size_data = client_socket.recv(4)
        image_size = struct.unpack("!I", size_data)[0]

        
        image_data = b""
        remaining_bytes = image_size
        while remaining_bytes > 0:
            chunk = client_socket.recv(min(4096, remaining_bytes))
            if not chunk:
                break
            image_data += chunk
            remaining_bytes -= len(chunk)
        if(image_data[1]!=108):
            with open(save_path,"wb") as file:
                file.write(image_data)
        else:
            with open(save_path[:-4]+"txt","wb") as file:
                file.write(image_data)
        print("Image received and saved successfully")
    except Exception as e:
        print("Error:", e)
    finally:
        
        server_socket.close()
        print("Server socket closed")
i=1
while(0<1):
    save_path = f"received/received_image{i}.jpeg"
    #server_ip = "192.168.92.246" 
    server_ip="127.0.0.1" 
    server_port = 5500 


    receive_image(save_path, server_ip, server_port)
    i+=1
