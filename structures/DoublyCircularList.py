from typing import List, Optional

from generic_type import T
from Node import DoublyLinkedListNode as Node


class DoublyCircularList:
    def __init__(self, start_list: Optional[List[T]] = None) -> None:
        self._head: Optional[Node] = None
        self._size: int = 0
        if start_list:
            self._insert_values(values=start_list)

    def head(self) -> Optional[Node]:
        return self._head

    def size(self) -> int:
        return self._size

    def empty(self) -> bool:
        return (self._size == 0)

    def push_back(self, data: T) -> None:
        if self.empty():
            self._head = Node(data)
        elif (self._size == 1):
            new_node: Node = Node(data)
            new_node.set_previous(self._head)
            new_node.set_next(self._head)
            self._head.set_previous(new_node)
            self._head.set_next(new_node)
        else:
            new_node: Node = Node(data)
            tail: Node = self._head.previous()
            new_node.set_previous(tail)
            new_node.set_next(self._head)
            tail.set_next(new_node)
            self._head.set_previous(new_node)

        self._size += 1

        return None

    def push_front(self, data: T) -> None:
        if self.empty():
            self._head = Node(data)
            self._size += 1
        else:
            self.push_back(data)
            self._head = self._head.previous()

        return None

    def insert(self, data: T, index: Optional[int] = None) -> None:
        if ((index is None) or (index > self._size)):
            index = self._size

        if (index == self._size):
            self.push_back(data=data)
        elif (index == 0):
            self.push_front(data=data)
        else:
            actual_node: Node = self._head
            new_node = Node(data)

            for _ in range(index):
                actual_node = actual_node.next()

            previous_node: Node = actual_node.previous()
            new_node.set_previous(previous_node)
            new_node.set_next(actual_node)
            previous_node.set_next(new_node)
            actual_node.set_previous(new_node)

            self._size += 1

        return None

    def _insert_values(self, values: List[T]) -> None:
        for value in values:
            self.push_back(value)

        return None
