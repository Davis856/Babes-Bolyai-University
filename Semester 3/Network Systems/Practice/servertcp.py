import socket
import struct

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")
    a = cs.recv(2)
    a = struct.unpack('!H', a)
    b = cs.recv(2)
    b = struct.unpack('!H', b)
    suma = a[0]+b[0]
    res = cs.send(struct.pack('!H', suma))

except socket.error as msg:
    print(msg.strerror)
    exit(-1)
