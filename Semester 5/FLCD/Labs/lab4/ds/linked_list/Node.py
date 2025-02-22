class Node:
    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next

    def __str__(self) -> str:
        return f"Node(value = {self.value})"

    def __repr__(self) -> str:
        return str(self)
