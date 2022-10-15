from __future__ import annotations

from .Node import LinkedNode as LN, T
from .linked_list import LinkedList


class CircularList(LinkedList):
    def __init__(self):
        super().__init__()

    def push_front(self, data: T) -> None:
        super().push_front(data=data)
        self[-1].next = self.head
        return None

    def push_back(self, data: T) -> None:
        super().push_back(data=data)
        self[-1].next = self.head
        return None

    def insert(self, data: T, index: int | LN) -> None:
        pass

    def pop(self, index: int) -> T:
        head: LN = self.head
        self._head = self[index]
        data: T = self.pop_front()
        self._head = head
        return data

    def pop_front(self) -> T:
        data: T = super().pop_front()
        self[-1].next = self.head
        return data

    def append(self, linked_list: CircularList) -> None:
        # TODO: test this exhaustively
        super().append(linked_list=linked_list)
        linked_list[-1].next = self.head
        return None
