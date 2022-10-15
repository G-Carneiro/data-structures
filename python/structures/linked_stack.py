from __future__ import annotations

from .Node import T
from .linked_base import LinkedBase


class LinkedStack(LinkedBase):
    def __init__(self):
        super().__init__()

    def push(self, data: T) -> None:
        super()._push_front(data=data)
        return None

    def pop(self) -> T:
        return super()._pop_front()
