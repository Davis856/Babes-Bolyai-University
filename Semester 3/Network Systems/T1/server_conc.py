import socket
from threading import Thread
import time
import struct

IP = '0.0.0.0'
PORT = 1234
ADDR = (IP, PORT)

clients = []


def worker(client):
    clients.append(client)

    counter = 0
    repeated = client.recv(4)
    repeated = struct.unpack('!I', repeated)[0]

    histogram = dict()
    while counter <= repeated:
        number = client.recv(4)
        number = struct.unpack("!I", number)
        counter += 1
        if number[0] in histogram:
            histogram[number[0]] += 1
        else:
            histogram[number[0]] = 1

    histogram_length = len(histogram)

    client.send(struct.pack('!I', histogram_length))
    for key, value in histogram.items():
        client.send(struct.pack('!I', key))
        client.send(struct.pack('!I', value))


cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
cs.bind(ADDR)
cs.listen(5)

while True:
    try:
        client, _ = cs.accept()
        th = Thread(target=worker, args=(client,))
        th.start()

    except socket.error as msg:
        print(msg.strerror)
        exit(-1)
