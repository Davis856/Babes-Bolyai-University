import socket
import struct

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")
    string = cs.recv(1024).decode()
    char = cs.recv(1024).decode()

    arr = []
    for i in range(len(string)):
        if string[i] is char:
            arr.append(i)

    length = len(arr)
    cs.send(struct.pack('!I', length))
    for i in range(length):
        cs.send(struct.pack('!I', arr[i]))

except socket.error as msg:
    print(msg.strerror)
    exit(-1)
