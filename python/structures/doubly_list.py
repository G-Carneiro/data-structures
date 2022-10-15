from .Node import DoublyLinkedNode as DLN, T

from .linked_list import LinkedList


class DoublyLinkedList(LinkedList):
    def __init__(self):
        super().__init__()

    def insert(self, data: T, index: int) -> None:
        pass

    def pop(self, index: int) -> T:
        # FIXME:
        head: DLN = self.head
        previous: DLN = self._before_index(index=index)
        self._head = self[index]
        data: T = super().pop_front()
        self._head.previous = previous
        previous.next = self.head
        self._head = head
        return data

    def pop_front(self) -> T:
        data: T = super().pop_front()
        self._head.previous = None
        return data
