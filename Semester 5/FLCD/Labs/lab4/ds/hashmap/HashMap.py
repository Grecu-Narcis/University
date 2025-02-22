from ds.linked_list.LinkedList import LinkedList


class HashMap:
    def __init__(self, size=1009):
        self.__buckets = [LinkedList() for _ in range(size)]
        self.__size = size

    def add(self, item) -> tuple:
        bucket_index = self.__hash_string(item)
        item_position = self.find(item)

        if item_position is not None:
            return item_position

        list_index = self.__buckets[bucket_index].add(item)

        return bucket_index, list_index

    def find(self, item):
        bucket_index = self.__hash_string(item)
        found_position = self.__buckets[bucket_index].find(item)

        if found_position >= 0:
            return bucket_index, found_position

        return None

    def get(self, bucket_position, list_position):
        if bucket_position >= self.__size:
            return None

        return self.__buckets[bucket_position][list_position]

    def __hash_string(self, string_to_hash: str):
        result = sum(map(ord, string_to_hash))

        return result % self.__size

    def __str__(self):
        result = f"HashMap(size={self.__size}, buckets=\n"
        for index, bucket in enumerate(self.__buckets):
            if bucket.is_empty():
                continue

            result += f"Bucket: {index} -> {str(bucket)}\n"

        result += ")"

        return result
