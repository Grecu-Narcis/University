#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QCheckBox>

#include "../business/AdministratorService.h"
#include "../business/UserService.h"


class AppGUI : public QMainWindow
{
	Q_OBJECT

private:
	QWidget* adminWindow, *userWindow, *requirePresenterWindow;
	QLabel* mainMenuLabel, * adminMenuLabel, * userMenuLabel, * currentTutorial;
	QPushButton* adminModeButton, * userModeButton, *displayChartButton, *submitPesenterButton;
	
	QLineEdit* tutorialTitleInput, * tutorialPresenterInput, * tutorialLinkInput,
		* tutorialNumberOfLikesInput, * tutorialDurationMinutesInput, * tutorialDurationSecondsInput,
		* requiredPresenterInput;

	QListWidget* tutorialsList;
	QCheckBox* likeCheckBox, * watchListType;

	vector<Tutorial> allTutorialsWithGivenPresenter;

	int indexOfCurrentTutorial;

	UserService& userService;
	AdministratorService& adminService;

	void loadDataToList(QListWidget* listToLoad, vector<Tutorial> dataToLoad);
	

private slots:
	void setMainMenuLayout();
	void setAdminLayout();
	void setUserLayout();
	void setRequirePresenterLayout();
	void validateRequiredPresenter();

	void addTutorialToDatabase();
	void updateTutorialFromDatabase();
	void removeTutorialFromDatabase();

	void addTutorialToWatchList();
	void getNextTutorialFromDatabase();
	void deleteTutorialFromWatchList();
	void openWatchList();

	void displayChartOfTutorials();

public:
	AppGUI(AdministratorService& adminService, UserService& userService, QWidget* parentWidget = nullptr);
};

