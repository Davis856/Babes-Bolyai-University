import socket
import struct
import random
import time

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    counter = 0
    repeated = random.randint(0, 100)

    s.send(struct.pack('!I', repeated))

    while counter <= repeated:
        s.send(struct.pack('!I', random.randint(0, 1000)))
        # time.sleep(1)
        counter += 1

    histo = dict()

    histo_length = s.recv(4)
    histo_length = struct.unpack("!I", histo_length)
    for i in range(histo_length[0]):
        key = s.recv(4)
        key = struct.unpack('!I', key)
        value = s.recv(4)
        value = struct.unpack('!I', value)
        histo[key[0]] = value[0]

    for key, value in histo.items():
        print(key, value)

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
