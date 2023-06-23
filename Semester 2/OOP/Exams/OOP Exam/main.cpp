#include "Window.h"
#include <QtWidgets/QApplication>

#include "PatientsRepository.h"
#include "DoctorsRepository.h"
#include "Service.h"

#include "StatisticWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DoctorsRepository doctors{ "doctors.txt" };
    PatientsRepository patients{ "patients.txt" };

    Service service{ doctors, patients };

    vector<Window*> doctorsWindows;

    for (auto doctor : doctors.getAll())
    {
        Window* currentDoctor = new Window{ service, doctor.getName() };        
        service.addObserver(currentDoctor);

        currentDoctor->show();
    }

    StatisticWindow w{ service };
    service.addObserver(&w);
    w.show();

    return a.exec();
}
