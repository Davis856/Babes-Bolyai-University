import socket
import struct

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    a = int(input('a='))
    b = int(input('b='))

    res = s.send(struct.pack('!H', a))
    tes = s.send(struct.pack('!H', b))
    c = s.recv(2)

    c = struct.unpack('!H', c)
    print('a+b=' + c[0].__format__('d'))

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
