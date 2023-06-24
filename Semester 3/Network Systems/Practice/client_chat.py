import os
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 5555))
s.send("Hello".encode())
if os.fork() == 0:
    while 1:
        print(s.recv(100))
    exit(0)
while 1:
    s.send(raw_input())
s.close()
