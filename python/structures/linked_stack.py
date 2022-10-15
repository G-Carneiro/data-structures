from __future__ import annotations

from typing import Optional, overload

from .Node import LinkedNode as LN, T


class LinkedBase:
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

    def _check_empty(self):
        if self.empty():
            raise Exception("Empty!")
        return None

    def _push_front(self, data: T) -> None:
        new_node: LN = LN(data=data)
        new_node.next = self.head
        self._head = new_node

        self._size += 1
        return None

    def _pop_front(self) -> T:
        self._check_empty()
        removed: LN = self._head
        self._head = self.head.next
        self._size -= 1
        return removed.data

    def clear(self) -> None:
        pass

    def __len__(self) -> int:
        return self.size


class LinkedQueue(LinkedBase):
    def __init__(self):
        super().__init__()
        self._last: Optional[LN] = None

    def push(self, data: T) -> None:
        new_node: LN = LN(data=data)
        if self.empty():
            self._head = new_node
        else:
            self._last.next = new_node

        self._last = new_node
        self._size += 1
        return None

    def enqueue(self, data: T) -> None:
        return self.push(data=data)

    def pop(self) -> T:
        data: T = super()._pop_front()
        if self.empty():
            self._last = None
        return data

    def dequeue(self) -> T:
        return self.pop()


class LinkedStack(LinkedBase):
    def __init__(self):
        super().__init__()

    def push(self, data: T) -> None:
        super()._push_front(data=data)
        return None

    def pop(self) -> T:
        return super()._pop_front()


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
        pass

    def at(self, index: int) -> T:
        return self[index].data

    def pop(self, index: int) -> T:
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
        pass

    def contains(self, data: T) -> bool:
        return (self.find(data=data) is not None)

    def find(self, data: T) -> int:
        actual_node: LN = self._head
        for i in range(self.size):
            if (actual_node.data == data):
                return i

            actual_node = actual_node.next

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
