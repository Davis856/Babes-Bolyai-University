import socket
import threading
import os
import time
import struct

mylock = threading.Lock()
e = threading.Event()
e.clear()
threads = []
client_count = 0


def worker(cs):
    global mylock, client_guessed, cmd, winner_thread, client_count, e

    my_idcount = client_count
    print('client #', client_count, 'from: ', cs.getpeername(), cs)
    message = 'Hello client #' + str(client_count)
    cs.sendall(bytes(message, 'ascii'))

    cmd = cs.recv(1024).decode()

    exit_code = os.system(cmd)
    cs.sendall(struct.pack('!I', exit_code))

    time.sleep(1)
    cs.close()
    print("Worker Thread ", my_idcount, " end")


def resetSrv():
    global mylock, client_guessed, winner_thread, threads, e, client_count
    while True:
        e.wait()
        for t in threads:
            t.join()
        print("all threads are finished now")
        e.clear()
        mylock.acquire()
        threads = []
        mylock.release()


if __name__ == '__main__':
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind(('0.0.0.0', 1234))
        rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)
    t = threading.Thread(target=resetSrv, daemon=True)
    t.start()
    while True:
        client_socket, addrc = rs.accept()
        t = threading.Thread(target=worker, args=(client_socket,))
        threads.append(t)
        client_count += 1
        t.start()
