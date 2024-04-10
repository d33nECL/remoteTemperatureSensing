import socket
import threading
import os
from datetime import datetime

# Function to handle connections from each Arduino
def handle_client(client_socket, addr, log_file_path):
    print('Connection from', addr)

    # Receive data
    data = client_socket.recv(1024).decode()
    print('Received data:', data)

    # Extract probe name and temperature from data
    probe_name, temp_data = data.split(',')

    # Get current timestamp
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    # Write data to the log file
    with open(log_file_path, 'a') as log_file:
        log_file.write(f'{timestamp},{probe_name},{temp_data}\n')

    # Close the connection
    client_socket.close()

# Create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Define the IP address and port to listen on
host = '10.0.1.166'
port = 80

# Bind the socket to the address and port
s.bind((host, port))

# Listen for incoming connections
s.listen(5)

# Define the path to the log file
log_file_path = 'Z:\\Sensornet\\Logs\\remoteTempLog.asc'

while True:
    # Accept connection
    client_socket, addr = s.accept()

    # Start a new thread to handle the connection
    client_thread = threading.Thread(target=handle_client, args=(client_socket, addr, log_file_path))
    client_thread.start()
