import socket
from time import sleep
import struct
import random

IP = '127.0.0.1'
PORT = 1234
ADDR = (IP, PORT)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(ADDR)

repeated = random.randint(0, 100)
print(repeated)

s.send(struct.pack('!I', repeated))

counter = 0

histo = dict()

while True:
    while counter <= repeated:
        s.send(struct.pack('!I', random.randint(0, 1000)))
        # time.sleep(1)
        counter += 1

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
