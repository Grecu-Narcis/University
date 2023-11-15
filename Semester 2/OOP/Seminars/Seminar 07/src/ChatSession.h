#pragma once

#include "Subject.h"

#include <vector>
#include <string>

using std::pair;
using std::string;

class ChatSession : public Subject
{
private:
	std::vector<pair<string, string>> messages;

public:
	void addMessage(string user, string message);
	std::vector<pair<string, string>> getMessages();
};

