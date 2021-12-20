from __future__ import annotations
from typing import Optional

from generic_type import T


class Node:
    def __init__(self, data: T) -> None:
        self._data: T = data

    def data(self) -> T:
        return self._data


class LinkedListNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._next: Optional[LinkedListNode] = None

    def next(self) -> Optional[LinkedListNode]:
        return self._next

    def set_next(self, node: LinkedListNode) -> None:
        self._next = node
        return None


class DoublyLinkedListNode(LinkedListNode):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._previous: Optional[DoublyLinkedListNode] = None

    def previous(self) -> Optional[DoublyLinkedListNode]:
        return self._previous

    def set_previous(self, node: DoublyLinkedListNode) -> None:
        self._previous = node
        return None


class BinaryTreeNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._left: Optional[BinaryTreeNode] = None
        self._right: Optional[BinaryTreeNode] = None

    def left(self) -> Optional[BinaryTreeNode]:
        return self._left

    def set_left(self, node: BinaryTreeNode) -> None:
        self._left = node
        return None

    def right(self) -> Optional[BinaryTreeNode]:
        return self._right

    def set_right(self, node: BinaryTreeNode) -> None:
        self._right = node
        return None
