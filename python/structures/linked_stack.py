from .linked_base import LinkedBase
from .Node import T


class LinkedStack(LinkedBase[T]):
    def __init__(self):
        super().__init__()

    def push(self, data: T) -> None:
        super()._push_front(data=data)
        return None

    def pop(self) -> T:
        return super()._pop_front()
