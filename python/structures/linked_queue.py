from typing import Optional

from .Node import LinkedNode as LN, T
from .linked_base import LinkedBase


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
