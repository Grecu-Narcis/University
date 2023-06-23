#include "RepositoryException.h"


RepositoryException::RepositoryException(const string message) : message(message)
{
}

const char* RepositoryException::what() const
{
    return message.c_str();
}
