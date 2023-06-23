#ifndef __VALIDATOR_EXCEPTION_H__
#define __VALIDATOR_EXCEPTION_H__

#include <string>
#include <vector>
#include <stdexcept>


using std::string;

class ValidatorException : public std::exception
{
private:
	string message;

public:
	ValidatorException(string message);
	const char* what() const override;
};

#endif