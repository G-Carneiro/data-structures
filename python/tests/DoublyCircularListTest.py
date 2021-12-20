import unittest

from ..structures.DoublyCircularList import DoublyCircularList
from ..structures.Node import DoublyLinkedListNode as Node


class DoublyCircularListTest(unittest.TestCase):
    def setUp(self) -> None:
        self._doubly: DoublyCircularList = DoublyCircularList()

    def test_empty(self) -> None:
        self.assertTrue(self._doubly.empty())
        self._doubly.push_back(0)
        self.assertFalse(self._doubly.empty())

        return None

    def test_push_back(self) -> None:
        self._doubly.push_back(0)
        self.assertEqual(1, self._doubly.size())
        self._doubly.push_back(1)
        self.assertEqual(2, self._doubly.size())

        head: Node = self._doubly.head()
        tail: Node = head.previous()

        self.assertEqual(0, head.data())
        self.assertEqual(1, tail.data())
        self.assertEqual(head, tail.next())
        self.assertEqual(head, tail.previous())
        self.assertEqual(tail, head.next())
        self.assertEqual(tail, head.previous())

        self._doubly.push_back(2)
        self.assertEqual(3, self._doubly.size())

        tail = head.previous()
        second: Node = head.next()

        self.assertEqual(0, head.data())
        self.assertEqual(2, tail.data())
        self.assertEqual(head, tail.next())
        self.assertEqual(second, tail.previous())
        self.assertEqual(second, head.next())
        self.assertEqual(tail, head.previous())
        self.assertEqual(head, second.previous())
        self.assertEqual(tail, second.next())

        for i in range(3, 10):
            self._doubly.push_back(i)
            tail = head.previous()
            self.assertEqual(i, tail.data())

            self.assertEqual(head, tail.next())
            self.assertEqual(second, head.next())
            self.assertEqual(tail, head.previous())
            self.assertEqual(head, second.previous())
            self.assertEqual(i - 1, tail.previous().data())

        self.assertEqual(10, self._doubly.size())

        return None

    def test_find(self) -> None:
        for i in range(10):
            self.assertIsNone(self._doubly.find(i))
            self._doubly.push_back(i)
            self.assertEqual(i, self._doubly.find(i))

        for i in range(10):
            self.assertEqual(i, self._doubly.find(i))

        self.assertIsNone(self._doubly.find(-1))
        self.assertIsNone(self._doubly.find(10))

        return None

    def test_contains(self) -> None:
        for i in range(10):
            self.assertFalse(self._doubly.contains(i))
            self._doubly.push_back(i)
            self.assertTrue(self._doubly.contains(i))

        for i in range(10):
            self.assertTrue(self._doubly.contains(i))

        self.assertFalse(self._doubly.contains(-1))
        self.assertFalse(self._doubly.contains(10))

        return None

    def test_clear(self) -> None:
        for i in range(1000):
            self._doubly.push_back(i)

        self._doubly.clear()

        self.assertIsNone(self._doubly.head())
        self.assertEqual(0, self._doubly.size())

        return None

    def test_shuffle(self) -> None:
        for i in range(1000):
            self._doubly.push_back(i)

        self._doubly.shuffle()

        self.assertEqual(1000, self._doubly.size())

        for i in range(1000):
            self.assertTrue(self._doubly.contains(i))

        return None

    def test_insert(self) -> None:
        for i in range(5):
            self._doubly.push_back(i)

        for i in range(6, 10):
            self._doubly.push_back(i)

        self._doubly.insert(5, 5)

        for i in range(10):
            self.assertEqual(i, self._doubly.find(i))

        return None

    def test_push_front(self) -> None:
        self._doubly.push_front(0)
        self.assertEqual(1, self._doubly.size())
        self._doubly.push_front(1)
        self.assertEqual(2, self._doubly.size())

        head: Node = self._doubly.head()
        tail: Node = head.previous()

        self.assertEqual(1, head.data())
        self.assertEqual(0, tail.data())
        self.assertEqual(head, tail.next())
        self.assertEqual(head, tail.previous())
        self.assertEqual(tail, head.next())
        self.assertEqual(tail, head.previous())

        self._doubly.push_front(2)
        self.assertEqual(3, self._doubly.size())

        head = self._doubly.head()
        second: Node = self._doubly.head().next()

        self.assertEqual(2, head.data())
        self.assertEqual(0, tail.data())
        self.assertEqual(head, tail.next())
        self.assertEqual(second, tail.previous())
        self.assertEqual(second, head.next())
        self.assertEqual(tail, head.previous())
        self.assertEqual(head, second.previous())
        self.assertEqual(tail, second.next())

        for i in range(3, 10):
            self._doubly.push_front(i)
            head = self._doubly.head()
            second = head.next()
            self.assertEqual(i, head.data())

            self.assertEqual(head, tail.next())
            self.assertEqual(second, head.next())
            self.assertEqual(tail, head.previous())
            self.assertEqual(head, second.previous())
            self.assertEqual(i - 1, head.next().data())

        self.assertEqual(10, self._doubly.size())

        return None

    def test_pop_back(self) -> None:
        for i in range(10):
            self._doubly.push_back(i)

        for i in reversed(range(10)):
            self.assertTrue(self._doubly.contains(i))
            self.assertEqual(i, self._doubly.pop_back())
            self.assertFalse(self._doubly.contains(i))

        self.assertTrue(self._doubly.empty())

        return None

    def test_pop_front(self) -> None:
        for i in range(10):
            self._doubly.push_back(i)

        for i in range(10):
            self.assertTrue(self._doubly.contains(i))
            self.assertEqual(i, self._doubly.pop_front())
            self.assertFalse(self._doubly.contains(i))

        self.assertTrue(self._doubly.empty())

        return None

    def test_pop(self) -> None:
        for i in range(10):
            self._doubly.push_back(i)

        self.assertEqual(5, self._doubly.pop(5))
        self.assertEqual(6, self._doubly.pop(5))
        self.assertEqual(8, self._doubly.size())

        return None

    def test_remove(self) -> None:
        for i in range(10):
            self._doubly.push_back(i)

        self._doubly.remove(4)
        self.assertEqual(9, self._doubly.size())
        self.assertFalse(self._doubly.contains(4))

        return None
