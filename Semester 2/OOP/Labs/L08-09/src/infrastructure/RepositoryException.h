#ifndef __REPOSITORY_EXCEPTION_H__
#define __REPOSITORY_EXCEPTION_H__

#include <stdexcept>
#include <string>

using std::string;

class RepositoryException : public std::exception
{
private:
	string message;

public:
	RepositoryException(const string message);

	const char* what() const override;
};

#endif