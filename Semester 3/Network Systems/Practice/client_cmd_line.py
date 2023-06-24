import socket
import struct

if __name__ == '__main__':
    try:
        s = socket.create_connection(('127.0.0.1', 1234))

        cmd = input("cmd= ")
        s.send(cmd.encode())

        exit_code = s.recv(4)
        exit_code = struct.unpack('!I', exit_code)
        print(exit_code[0])

        s.close()

    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)
