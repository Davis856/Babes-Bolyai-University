import unittest
from src.struct import struct


class StructTests(unittest.TestCase):
    def setUp(self):
        self.array = [1, 2, 3, 4, 5]
        self.array2 = []
        self.array3 = [4, 3, 10, 6, 2, 5, 1, 15, -2]
        self.arr = struct(self.array)
        self.arr2 = struct(self.array2)
        self.arr3 = struct(self.array3)

    def test_create(self):
        arr = [1, 2]
        array = struct(arr)
        self.assertEqual(array.list, [1, 2])

    def test_length(self):
        self.arr.length = 5

    def test_length2(self):
        self.assertEqual(self.arr2.length, 0)

    def test_get(self):
        test = self.arr[0]
        self.assertEqual(test, 1)
        with self.assertRaises(IndexError):
            return self.arr[-1]

    def test_append(self):
        self.arr.append(6)
        self.assertEqual(self.arr.length, 6)

    def test_insert(self):
        self.arr.insert(1, 10)
        self.assertEqual(self.arr.length, 6)

    def test_set(self):
        self.arr[2] = 5
        self.assertEqual(self.arr[2], 5)
        with self.assertRaises(IndexError):
            self.arr[-1] = 5

    def test_delete(self):
        del self.arr[1]
        self.assertEqual(self.arr.length, 4)
        with self.assertRaises(IndexError):
            del self.arr[-1]

    def test_next_iter(self):
        i = iter(self.arr)
        self.assertEqual(next(i), 1)
        self.assertEqual(next(i), 2)

    def test_filter(self):
        res = self.arr.copy()
        res.filter(res.even, 2)
        self.assertEqual(res.list, [2, 4])

    def test_filter_odd(self):
        res = self.arr.copy()
        res.filter(res.odd, 2)
        self.assertEqual(res.list, [1, 3])

    def test_filter2(self):
        with self.assertRaises(StopIteration):
            res = self.arr2.copy()
            res.filter(res.even, 2)

    def test_sort(self):
        res = self.arr.copy()
        res.sort(res.value, 0)
        self.assertEqual(res.list, [1, 2, 3, 4, 5])

    def test_sort2(self):
        res = self.arr.copy()
        res.sort(res.value, 1)
        self.assertEqual(res.list, [5, 4, 3, 2, 1])

    def test_sort3(self):
        res = self.arr3.copy()
        res.sort(res.value, 0)
        self.assertEqual(res.list, [-2, 1, 2, 3, 4, 5, 6, 10, 15])

    def test_len(self):
        self.assertEqual(len(self.arr), 5)