#include "ValidatorException.h"


ValidatorException::ValidatorException(string message) : message(message)
{
}

const char* ValidatorException::what() const
{
    return message.c_str();
}
