from __future__ import annotations

from typing import Optional

T = int


class Node:
    def __init__(self, data: T) -> None:
        self._data: T = data

    @property
    def data(self) -> T:
        return self._data


class LinkedListNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._next: Optional[LinkedListNode] = None

    @property
    def next(self) -> Optional[LinkedListNode]:
        return self._next

    @next.setter
    def next(self, node: LinkedListNode = None):
        self._next = node


class DoublyLinkedListNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._next: Optional[DoublyLinkedListNode] = None
        self._previous: Optional[DoublyLinkedListNode] = None

    @property
    def next(self) -> Optional[DoublyLinkedListNode]:
        return self._next

    @next.setter
    def next(self, node: DoublyLinkedListNode = None):
        self._next = node

    @property
    def previous(self) -> Optional[DoublyLinkedListNode]:
        return self._previous

    @previous.setter
    def previous(self, node: DoublyLinkedListNode = None):
        self._previous = node


class BinaryTreeNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._left: Optional[BinaryTreeNode] = None
        self._right: Optional[BinaryTreeNode] = None

    @property
    def left(self) -> Optional[BinaryTreeNode]:
        return self._left

    @left.setter
    def left(self, node: BinaryTreeNode = None):
        self._left = node

    @property
    def right(self) -> Optional[BinaryTreeNode]:
        return self._right

    @right.setter
    def right(self, node: BinaryTreeNode = None) -> None:
        self._right = node
