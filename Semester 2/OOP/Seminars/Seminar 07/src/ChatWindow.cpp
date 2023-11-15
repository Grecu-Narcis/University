#include "ChatWindow.h"

#include <QListWidgetItem>

ChatWindow::ChatWindow(ChatSession& session, string user, QWidget *parent)
	: currentSession{ session }, userName{ user },  QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QString::fromStdString(this->userName));

	connect(ui.sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
}

ChatWindow::~ChatWindow()
{}

void ChatWindow::update()
{
	ui.chatList->clear();

	QFont textFont;

	textFont.setPixelSize(20);

	for (const auto& message : currentSession.getMessages())
	{
		string messageText;

		if (message.first == this->userName)
		{
			messageText = message.second;

			QListWidgetItem* currentMessage = new QListWidgetItem{ QString::fromStdString(messageText) };
			currentMessage->setTextAlignment(Qt::AlignRight);
			currentMessage->setFont(textFont);

			ui.chatList->addItem(currentMessage);
		}

		else
		{
			messageText = "[ " + message.first + " ]: " + message.second;
			QListWidgetItem* currentMessage = new QListWidgetItem{ QString::fromStdString(messageText) };
			currentMessage->setTextAlignment(Qt::AlignLeft);

			ui.chatList->addItem(currentMessage);
			currentMessage->setFont(textFont);
		}
	}
}

void ChatWindow::sendMessage()
{
	string messageText = ui.messageInput->text().toStdString();
	ui.messageInput->clear();

	currentSession.addMessage(userName, messageText);
}
