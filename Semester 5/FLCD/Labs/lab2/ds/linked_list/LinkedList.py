from typing import Optional

from ds.linked_list.Node import Node


class LinkedList:
    def __init__(self):
        self.__head: Optional[Node] = None
        self.__tail: Optional[Node] = None
        self.__size = 0

    def get_head(self):
        return self.__head

    def add(self, element) -> int:
        node = Node(element)
        self.__size += 1

        if self.__head is None:
            self.__head = self.__tail = node
            return self.__size - 1

        self.__tail.next = node
        self.__tail = node

        return self.__size - 1

    def find(self, item):
        current_node = self.__head
        index = 0

        while current_node is not None:
            if item == current_node.value:
                return index

            index += 1
            current_node = current_node.next

        return -1

    def is_empty(self):
        return self.__size == 0

    def __getitem__(self, index):
        if index >= self.__size:
            return None

        current_node = self.__head

        while index > 0:
            current_node = current_node.next
            index -= 1

        return current_node.value

    def __str__(self) -> str:
        nodes_as_strings = []

        current: Node = self.__head

        while current is not None:
            nodes_as_strings.append(str(current))
            current = current.next

        return f"LinkedList(size = {self.__size}, {', '.join(nodes_as_strings)})"

    def __repr__(self) -> str:
        return str(self)
