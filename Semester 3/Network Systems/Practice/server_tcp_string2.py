import socket

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    print("Waiting for connections.")
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")
    text = cs.recv(1024).decode()
    text = text[::-1]
    cs.send(text.encode())
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
