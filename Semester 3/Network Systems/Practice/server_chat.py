import select
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setblocking(False)
s.bind(('0.0.0.0', 5555))
s.listen(5)

ins = [s]
outs = []
msg = []
while ins:
    r, w, e = select.select(ins, outs, ins)
    for ss in r:
        if ss == s:
            cs, addr = ss.accept()
            print("Client from:", addr)
            ins.append(cs)
        else:
            print("Data from client")
            data = ss.recv(100)
            if data:
                txt = str(ss.getpeername()[0]) + ":" + str(ss.getpeername()[1]) + ":" + data
                print(txt)
                msg.append(txt)
                if ss not in outs:
                    outs.append(ss)
            else:
                print("Null data, client is gone")
                ins.remove(ss)
                if ss in outs:
                    outs.remove(ss)
                ss.close()
    for ss in e:
        print("Error")
        ins.remove(ss)
        if ss in outs:
            outs.remove(ss)
        ss.close()
    for ss in w:
        for i in msg:
            ss.send(i)
    msg = []
