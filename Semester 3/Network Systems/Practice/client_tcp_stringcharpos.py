import socket
import struct

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    string = input("string=")
    char = input("char=")

    s.send(string.encode())
    s.send(char.encode())

    arr = []
    length = s.recv(4)
    length = struct.unpack('!I', length)
    for i in range(length[0]):
        x = s.recv(4)
        x = struct.unpack('!I', x)
        arr.append(x)

    print("result=")
    for i in range(length[0]):
        print(arr[i][0])

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
