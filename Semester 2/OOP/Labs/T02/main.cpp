#include "Controller.h"
#include "HospitalDepartment.h"
#include "NeonatalUnit.h"
#include "Surgery.h"
#include "UI.h"

int main()
{
	Controller departmentsController;
	departmentsController.addDepartment(new NeonatalUnit{ "Cluj Neonatal", 20, 8.7 });
	departmentsController.addDepartment(new Surgery{ "Emergency Bucharest", 15, 7 });
	departmentsController.addDepartment(new NeonatalUnit{ "Botosani Neonatal", 10, 8.2 });
	departmentsController.addDepartment(new Surgery{ "US State Hospital", 60, 250 });

	UI ui{ departmentsController };

	ui.start();

	return 0;
}