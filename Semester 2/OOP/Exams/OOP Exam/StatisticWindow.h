#pragma once

#include <QWidget>
#include <unordered_map>

#include "ui_StatisticWindow.h"

#include "Service.h"

#include "Observer.h"

using std::unordered_map;

class StatisticWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	StatisticWindow(Service& service, QWidget *parent = nullptr);
	~StatisticWindow();

	void paintEvent(QPaintEvent* event);

	void update();

	void drawStatistic();

private:
	Ui::StatisticWindowClass ui;

	Service& service;
};
