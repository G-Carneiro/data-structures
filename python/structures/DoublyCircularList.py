from random import shuffle
from typing import List, Optional

from .Node import DoublyLinkedNode as Node, T


class DoublyCircularList:
    def __init__(self, start_list: List[T] = None) -> None:
        self._head: Optional[Node] = None
        self._size: int = 0
        if start_list:
            self._insert_values(values=start_list)

    @property
    def head(self) -> Optional[Node]:
        return self._head

    @property
    def size(self) -> int:
        return self._size

    def empty(self) -> bool:
        return (self._size == 0)

    def push_back(self, data: T) -> None:
        new_node: Node = Node(data)
        if self.empty():
            self._head = new_node
        elif (self._size == 1):
            new_node.previous = self._head
            new_node.next = self._head
            self._head.previous = new_node
            self._head.next = new_node
        else:
            tail: Node = self._head.previous
            new_node.previous = tail
            new_node.next = self._head
            tail.next = new_node
            self._head.previous = new_node

        self._size += 1

        return None

    def push_front(self, data: T) -> None:
        self.push_back(data)
        if (self.size > 1):
            self._head = self._head.previous

        return None

    def insert(self, data: T, index: int = None) -> None:
        if (index is None) or (index >= self.size):
            self.push_back(data=data)
        elif (index <= 0):
            self.push_front(data=data)
        else:
            head: Node = self._head
            actual_node: Node = self._head

            for _ in range(index):
                actual_node = actual_node.next

            self._head = actual_node
            self.push_front(data=data)
            self._head = head

        return None

    def _insert_values(self, values: List[T]) -> None:
        for value in values:
            self.push_back(value)

        return None

    def pop_back(self) -> Optional[T]:
        if (self.empty()):
            return None

        tail: Node = self._head.previous
        if (self._size == 1):
            tail = self._head
            self._head = None
        elif (self._size == 2):
            self._head.previous = None
            self._head.next = None
        else:
            new_tail: Node = tail.previous
            new_tail.next = self._head
            self._head.previous = new_tail

        self._size -= 1

        return (tail.data)

    def pop_front(self) -> Optional[T]:
        if (self.size > 1):
            self._head = self.head.next
        removed: T = self.pop_back()

        return (removed)

    def pop(self, index: int = None) -> Optional[T]:
        if ((index is None) or (index >= self._size - 1)):
            return self.pop_back()
        elif (index <= 0):
            return self.pop_front()
        else:
            head: Node = self.head
            removed_node: Node = self._head
            for _ in range(index):
                removed_node = removed_node.next

            self._head = removed_node
            self.pop_front()
            self._head = head

            return (removed_node.data)

    def remove(self, data: T) -> None:
        index: int = self.find(data)
        if (index is not None):
            self.pop(index)

        return None

    def find(self, data: T) -> Optional[int]:
        actual_node: Node = self._head
        for i in range(self.size):
            if (actual_node.data == data):
                return i

            actual_node = actual_node.next

        return None

    def contains(self, data: T) -> bool:
        index: Optional[int] = self.find(data)
        return (index is not None)

    def clear(self) -> None:
        self._head = None
        self._size = 0
        return None

    def shuffle(self) -> None:
        if (self._size < 3):
            return None

        nodes: List[Node] = [self._head]
        actual_node: Node = self._head
        tail: Node = self._head.previous
        while (actual_node != tail):
            actual_node = actual_node.next
            nodes.append(actual_node)

        shuffle(nodes)
        for i in range(self._size - 1):
            nodes[i].previous = nodes[i - 1]
            nodes[i].next = nodes[i + 1]

        self._head = nodes[0]
        nodes[-1].previous = nodes[-2]
        nodes[-1].next = self._head

        return None
