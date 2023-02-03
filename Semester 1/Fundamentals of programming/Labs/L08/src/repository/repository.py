from src.repository.repository_exception import RepositoryException


class Repository:
    def __init__(self):
        self._objects = []

    def store(self, object):
        if self.find(object.id) is not None:
            raise RepositoryException("Element having id = " + str(object.id) + " already stored!")

        self._objects.append(object)

    def find(self, object_id):
        for object in self._objects:
            if object.id == object_id:
                return object

        return None

    def delete_by_id(self, object_id):
        object = self.find(object_id)

        if object is None:
            raise RepositoryException("Element having id = " + str(object_id) + " not in repository!")

        self._objects.remove(object)

        return object

    def update(self, new_object):
        object = self.find(new_object.id)

        if object is None:
            raise RepositoryException('Element having id = ' + str(new_object.id) + ' not in repository!')

        self.delete_by_id(object.id)
        self.store(new_object)

    def get_all(self):
        return self._objects

    def __len__(self):
        return len(self._objects)
