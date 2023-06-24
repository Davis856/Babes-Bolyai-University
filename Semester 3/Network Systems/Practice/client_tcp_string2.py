import socket

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", 1234))

    print("Connected successfully.")

    text = input("string=")
    res = s.send(text.encode())

    c = s.recv(1024).decode()
    print(f"reversed: {c}")

    s.close()
except socket.error as msg:
    print(msg.strerror)
    exit(-1)
