#include "ChatWindow.h"
#include "ChatSession.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    ChatSession currentSession;

    ChatWindow user1{ currentSession, "John" };
    ChatWindow user2{ currentSession, "Marry" };
    ChatWindow user3{ currentSession, "Alex" };

    currentSession.registerObserver(&user1);
    currentSession.registerObserver(&user2);
    currentSession.registerObserver(&user3);

    user1.show();
    user2.show();
    user3.show();

    return a.exec();
}
