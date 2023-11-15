#include "T03.h"
#include <QtWidgets/QApplication>

#include "Repository.h"
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository itemsRepository{ "items.txt" };
    Service itemsService{ itemsRepository };

    T03 w{ itemsService };
    w.show();
    return a.exec();
}
