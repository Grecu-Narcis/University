#include "ChatSession.h"

void ChatSession::addMessage(string user, string message)
{
    pair<string, string> messageToAdd{ user, message };

    this->messages.push_back(messageToAdd);
    this->notify();
}

std::vector<pair<string, string>> ChatSession::getMessages()
{
    return this->messages;
}
