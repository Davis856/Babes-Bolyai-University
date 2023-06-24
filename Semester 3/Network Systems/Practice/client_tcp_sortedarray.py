import socket
import struct

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    arr1 = []
    arr2 = []
    len1 = int(input("len1="))
    for i in range(len1):
        x = int(input())
        arr1.append(x)
    len2 = int(input("len2="))
    for i in range(len2):
        x = int(input())
        arr2.append(x)

    res1 = s.send(struct.pack('!I', len1))
    for i in range(len1):
        s.send(struct.pack('!I', arr1[i]))

    res2 = s.send(struct.pack('!I', len2))
    for i in range(len2):
        s.send(struct.pack('!I', arr2[i]))

    rarr = []
    result = s.recv(4)
    result = struct.unpack('!I', result)
    for i in range(result[0]):
        x = s.recv(4)
        x = struct.unpack('!I', x)
        rarr.append(x)

    print("merged= ")
    for i in range(result[0]):
        print(rarr[i][0])

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
