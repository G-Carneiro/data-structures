from __future__ import annotations
from typing import Optional

from generic_type import T


class Node:
    def __init__(self, data: T) -> None:
        self._data: T = data
        self._next: Optional[Node] = None
        self._previous: Optional[Node] = None

    def data(self) -> T:
        return self._data

    def next(self) -> Optional[Node]:
        return self._next

    def previous(self) -> Optional[Node]:
        return self._previous

    def set_previous(self, node: Node) -> None:
        self._previous = node
        return None

    def set_next(self, node: Node) -> None:
        self._next = node
        return None


