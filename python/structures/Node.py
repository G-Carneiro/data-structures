from __future__ import annotations

from typing import Optional

T = int


class Node:
    def __init__(self, data: T) -> None:
        self._data: T = data

    @property
    def data(self) -> T:
        return self._data


class LinkedNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._next: Optional[LinkedNode] = None

    @property
    def next(self) -> Optional[LinkedNode]:
        return self._next

    @next.setter
    def next(self, node: LinkedNode = None):
        self._next = node


class DoublyLinkedNode(Node):
    def __init__(self, data: T) -> None:
        super().__init__(data)
        self._next: Optional[DoublyLinkedNode] = None
        self._previous: Optional[DoublyLinkedNode] = None

    @property
    def next(self) -> Optional[DoublyLinkedNode]:
        return self._next

    @next.setter
    def next(self, node: DoublyLinkedNode = None):
        self._next = node

    @property
    def previous(self) -> Optional[DoublyLinkedNode]:
        return self._previous

    @previous.setter
    def previous(self, node: DoublyLinkedNode = None):
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
