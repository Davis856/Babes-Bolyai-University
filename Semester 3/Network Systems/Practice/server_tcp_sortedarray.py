import socket
import struct


def merge(arr, l, m, r):
    n1 = m - l + 1
    n2 = r - m

    # create temp arrays
    L = [0] * (n1)
    R = [0] * (n2)

    # Copy data to temp arrays L[] and R[]
    for i in range(0, n1):
        L[i] = arr[l + i]

    for j in range(0, n2):
        R[j] = arr[m + 1 + j]

    # Merge the temp arrays back into arr[l..r]
    i = 0  # Initial index of first subarray
    j = 0  # Initial index of second subarray
    k = l  # Initial index of merged subarray

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    # Copy the remaining elements of L[], if there
    # are any
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    # Copy the remaining elements of R[], if there
    # are any
    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1


# l is for left index and r is right index of the
# sub-array of arr to be sorted


def mergeSort(arr, l, r):
    if l < r:
        # Same as (l+r)//2, but avoids overflow for
        # large l and h
        m = l + (r - l) // 2

        # Sort first and second halves
        mergeSort(arr, l, m)
        mergeSort(arr, m + 1, r)
        merge(arr, l, m, r)

try:
    rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rs.bind(('0.0.0.0', 1234))
    rs.listen(5)
    cs, addr = rs.accept()
    print(f"Hello, {addr[0]}.")

    arr1 = []
    len1 = cs.recv(4)
    len1 = struct.unpack("!I", len1)
    for i in range(len1[0]):
        x = cs.recv(4)
        x = struct.unpack("!I", x)
        arr1.append(x[0])

    arr2 = []
    len2 = cs.recv(4)
    len2 = struct.unpack("!I", len2)
    for i in range(len2[0]):
        x = cs.recv(4)
        x = struct.unpack("!I", x)
        arr2.append(x[0])

    arr3 = arr1 + arr2
    len3 = len(arr3)

    mergeSort(arr3, 0, len3-1)

    cs.send(struct.pack("!I", len3))
    for i in range(len3):
        cs.send(struct.pack("!I", arr3[i]))


except socket.error as msg:
    print(msg.strerror)
    exit(-1)