from __future__ import annotations

from typing import Optional, overload

from .Node import LinkedNode as LN, T


class LinkedStack:
    def __init__(self) -> None:
        self._head: Optional[LN] = None
        self._size: int = 0

    @property
    def head(self) -> Optional[LN]:
        return self._head

    @property
    def size(self) -> int:
        return self._size

    def empty(self) -> bool:
        return (self.size == 0)

    def push(self, data: T) -> None:
        new_node: LN = LN(data=data)
        if self.empty():
            self._head = new_node
        else:
            new_node.next = self.head
            self._head = new_node

        self._size += 1
        return None

    def pop(self) -> Optional[T]:
        if self.empty():
            return None

        removed: LN = self._head
        self._head = self.head.next
        self._size -= 1
        return removed.data

    def clear(self) -> None:
        pass


class LinkedList(LinkedStack):
    def __init__(self):
        super().__init__()

    def push_front(self, data: T) -> None:
        super().push(data=data)
        return None

    def push_back(self, data: T) -> None:
        return self.insert(data=data, index=self.size)

    def push(self, data: T) -> None:
        return self.push_back(data=data)

    @overload
    def insert(self, data: T, index: int) -> None:
        if (index == 0):
            self.push_front(data=data)
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
        pass

    def at(self, index: int) -> Optional[T]:
        pass

    def pop(self, index: int) -> Optional[T]:
        pass

    def pop_back(self) -> Optional[T]:
        pass

    def pop_front(self) -> Optional[T]:
        pass

    def remove(self, data: T) -> None:
        pass

    def contains(self, data: T) -> bool:
        return (self.find(data=data) is not None)

    def find(self, data: T) -> Optional[int]:
        actual_node: LN = self._head
        for i in range(self.size):
            if (actual_node.data == data):
                return i

            actual_node = actual_node.next

        return None

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
        pass

    @overload
    def append(self, node: LN) -> None:
        pass

    @overload
    def append(self, linked_list: LinkedList) -> None:
        pass

    def append(self, data: T | LN | LinkedList) -> None:
        pass

    def halve(self):
        pass

    def slice(self, start: int, stop: int, step: int = 1) -> None:
        pass

    def _before_index(self, index: int) -> LN:
        it: LN = self.head
        if (index > self.size):
            index = self.size

        for _ in range(index - 1):
            it = it.next
        return it

    def _last_node(self) -> LN:
        return self._before_index(index=self.size)
