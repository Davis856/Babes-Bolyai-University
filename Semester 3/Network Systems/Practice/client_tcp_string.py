import socket
import struct

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    text = input("string=")
    res = s.send(text.encode())

    c = s.recv(2)

    c = struct.unpack('!H', c)
    print('spaces=' + c[0].__format__('d'))

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
