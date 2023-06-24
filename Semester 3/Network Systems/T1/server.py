import socket
import struct

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")

    counter = 0
    repeated = cs.recv(4)
    repeated = struct.unpack('!I', repeated)

    histogram = dict()

    while counter <= repeated[0]:
        number = cs.recv(4)
        number = struct.unpack("!I", number)
        counter += 1
        if number[0] in histogram:
            histogram[number[0]] += 1
        else:
            histogram[number[0]] = 1

    histogram_length = len(histogram)

    cs.send(struct.pack('!I', histogram_length))
    for key, value in histogram.items():
        cs.send(struct.pack('!I', key))
        cs.send(struct.pack('!I', value))

except socket.error as msg:
    print(msg.strerror)
    exit(-1)
