from typing import final, Optional

from .Node import LinkedNode as LN, T


class LinkedBase:
    def __init__(self) -> None:
        self._head: Optional[LN] = None
        self._size: int = 0

    @final
    @property
    def head(self) -> Optional[LN]:
        return self._head

    @final
    @property
    def size(self) -> int:
        return self._size

    @final
    def empty(self) -> bool:
        return (self.size == 0)

    @final
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

    @final
    def clear(self) -> None:
        while (not self.empty()):
            self._pop_front()
        return None

    @final
    def __len__(self) -> int:
        return self.size
