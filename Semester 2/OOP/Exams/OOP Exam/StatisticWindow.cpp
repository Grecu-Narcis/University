#include "StatisticWindow.h"

#include <QPainter>

StatisticWindow::StatisticWindow(Service& service, QWidget *parent)
	: QWidget(parent), service{ service }
{
	ui.setupUi(this);
}

StatisticWindow::~StatisticWindow()
{}

void StatisticWindow::paintEvent(QPaintEvent * event)
{
	drawStatistic();
}

void StatisticWindow::update()
{
	repaint();
}

void StatisticWindow::drawStatistic()
{
	QPainter painter{ this };

	unordered_map<string, int> statistic;

	for (auto patient : service.getAllPatients())
		statistic[patient.getSpecialisation()]++;

	for (auto patient : service.getAllPatients())
		if (patient.getDiagnosis() == "undiagnosed")
			statistic["undiagnosed"]++;

	int x = 0;
	int y = 0;

	for (auto specialisation : statistic)
	{
		painter.drawRect(x, y, 100, specialisation.second * 100);
		painter.drawText(x, y, 100, 100, Qt::AlignCenter, QString::fromStdString(specialisation.first));
		x += 100;
	}
}
