#pragma once
#include <QtWidgets\qwidget.h>
#include "ui_startscreen.h"
#include "AssessmentManager.h"

class StartScreen : public QWidget {
	Q_OBJECT

public:
	StartScreen(QWidget * parent = Q_NULLPTR);
	~StartScreen();

public slots:
	void otherIncisionAssessment();
	void noSurgeryAssessment();
	void scalpelChoiceAssessment();
	void toChartPage();
	void toCreditsPage();
	void toInstructionsPage();
	void toOptionsPage();
	void toReportPage();
	void toScalpelPage();
	void toStartPage();
	void toStartPageFromReport();
	void toTreatmentDecisionPage();

private:
	Ui::startScreen ui;
	Chart* chart;
	AssessmentManager* manager;

};
