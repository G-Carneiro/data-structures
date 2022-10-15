from __future__ import annotations

from copy import copy
from typing import overload

from .Node import LinkedNode as LN, T
from .linked_base import LinkedBase


class LinkedList(LinkedBase):
    def __init__(self):
        super().__init__()

    def push_front(self, data: T) -> None:
        super()._push_front(data=data)
        return None

    def push_back(self, data: T) -> None:
        return self.insert(data=data, index=self.size)

    def push(self, data: T) -> None:
        return self.push_back(data=data)

    @overload
    def insert(self, data: T, index: int) -> None:
        if (index == 0):
            self._push_front(data=data)
        else:
            previous: LN = self._before_index(index=index)
            self.insert(data=data, previous=previous)
        return None

    @overload
    def insert(self, data: T, previous: LN) -> None:
        new_node: LN = LN(data=data)
        next_ = previous.next
        new_node.next = next_
        previous.next = new_node
        self._size += 1

        return None

    def insert(self, data: T, index: int | LN) -> None:
        ...

    def insert_sorted(self, data: T) -> None:
        previous: LN = self.head
        key = self.size
        for key, node in enumerate(self):
            if (node.data > data):
                break
            previous = node

        if (key == 0):
            self.push_front(data=data)
        else:
            self.insert(data=data, previous=previous)
        return None

    def at(self, index: int) -> T:
        return self[index].data

    def pop(self, index: int) -> T:
        # TODO: use super() or create new based method?
        previous: LN = self._before_index(index=index)
        head: LN = self.head
        removed: LN = previous.next
        self._head = removed
        super()._pop_front()
        previous.next = self.head
        self._head = head
        return removed.data

    def pop_back(self) -> T:
        return self.pop(index=self.size - 1)

    def pop_front(self) -> T:
        return super()._pop_front()

    def remove(self, data: T) -> None:
        self.pop(index=self.find(data=data))
        return None

    def contains(self, data: T) -> bool:
        try:
            self.find(data=data)
        except ValueError:
            return False

        return True

    def find(self, data: T) -> int:
        for i, node in enumerate(self):
            if (node.data == data):
                return i

        raise ValueError

    def invert(self) -> None:
        if (self.size < 2):
            return None
        for i in range(self.size):
            self.insert(data=self.pop_back(), index=i)

        return None

    def clone(self) -> LinkedList:
        pass

    @overload
    def append(self, data: T) -> None:
        self.push_back(data=data)
        return None

    @overload
    def append(self, linked_list: LinkedList) -> None:
        self[-1].next = linked_list.head
        self._size += linked_list.size
        return None

    def append(self, data: T | LN | LinkedList) -> None:
        pass

    def halve(self):
        pass

    def slice(self, start: int, stop: int, step: int = 1) -> None:
        pass

    def _before_index(self, index: int) -> LN:
        return self[index - 1]

    def __add__(self, other: T | LN | LinkedList) -> None:
        self.append(data=other)
        return None

    def __getitem__(self, key: int) -> LN:
        self._check_empty()
        if (key < 0):
            key = key % self.size
        elif (key >= self.size):
            raise IndexError

        item: LN = self.head
        for _ in range(key):
            item = item.next

        return item

    def __reversed__(self) -> LinkedList:
        new: LinkedList = copy(self)
        new.invert()
        return new
