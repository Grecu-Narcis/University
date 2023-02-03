class ValidatorException(Exception):
    def __init__(self, message_list):
        self._message_list = message_list

    def get_message(self):
        return self._message_list

    def __str__(self):
        result = ""
        print(self._message_list)
        for message in self.get_message():
            result += message
            result += "\n"

        return result
