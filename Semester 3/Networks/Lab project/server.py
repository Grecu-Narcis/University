import socket
import os
import sys
import threading
import struct
from time import sleep

clients = []
threads = []


def close_socket(socket):
    clients.remove(socket)
    socket.close()


def send_message_to_clients(sender_client: socket, message: str) -> None:
    message_length = struct.pack("!H", len(message))

    for client in clients:
        if client == sender_client:
            continue

        client.send(message_length)
        client.send(str.encode(message))


def read_message_from_client(client_socket: socket) -> str:
    buffer = client_socket.recv(2) # length of the message
    message_length = struct.unpack('!H', buffer)[0]
    print('message length is: ', message_length)

    message = client_socket.recv(message_length)
    message = message.decode()

    return message


def handle_client(client_socket):
    client_name = read_message_from_client(client_socket)
    print("Handle client: ", client_name)

    send_message_to_clients(client_socket, client_name + " joined the chat!")

    try:
        while True:
            message = read_message_from_client(client_socket)
            
            if message is None:
                continue

            if len(message) == 0:
                print("Connection closed by", client_name)

                send_message_to_clients(client_socket, client_name + " left the chat!")
                close_socket(client_socket)
                break
            
            message_to_send = client_name + ": " + message 
            print(message_to_send)
            send_message_to_clients(client_socket, message_to_send)

            
    except (socket.error, struct.error):
        print("Connection closed by", client_name)
        send_message_to_clients(client_socket, client_name + " left the chat!")
        close_socket(client_socket)


def create_listen_socket(ip_address, port):
    listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    listen_socket.bind((ip_address, port))
    listen_socket.listen()

    return listen_socket


def listen_for_clients(listen_socket):
    while True:
        client_socket, client_address = listen_socket.accept()
        clients.append(client_socket)

        print("New connection accepted from: ", client_address)

        client_thread = threading.Thread(target=handle_client, args=[client_socket])
        client_thread.start()


def main():
    if len(sys.argv) != 2:
        print("Incorrect usage. Please use as server.py [PORT]")
        exit(1)

    listen_socket = create_listen_socket('0.0.0.0', int(sys.argv[1]))

    print("Server started...")
    print("Waiting for clients...")

    listen_for_clients(listen_socket)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        exit(1)