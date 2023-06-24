import socket
import struct

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")
    a = cs.recv(4)
    a = struct.unpack('!I', a)
    length = a[0]
    arr = []
    for i in range(1, length):
        if a[0] % i == 0:
            arr.append(i)

    rlength = len(arr)
    cs.send(struct.pack("!I", rlength))
    for i in range(rlength):
        cs.send(struct.pack("!I", arr[i]))

except socket.error as msg:
    print(msg.strerror)
    exit(-1)
