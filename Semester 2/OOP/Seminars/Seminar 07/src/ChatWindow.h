#pragma once

#include <QWidget>
#include <string>

#include "ui_ChatWindow.h"
#include "ChatSession.h"

using std::string;

class ChatWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ChatWindow(ChatSession& session, string user, QWidget *parent = nullptr);
	~ChatWindow();

	void update();

public slots:
	void sendMessage();

private:
	Ui::ChatWindowClass ui;

	ChatSession& currentSession;
	string userName;
};
