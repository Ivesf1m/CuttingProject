#include "startscreen.hpp"
#include <iostream>

#define START_PAGE 0
#define OPTIONS_PAGE 1
#define INSTRUCTIONS_PAGE 2
#define CREDITS_PAGE 3
#define CHART_PAGE 4
#define TREATMENT_DECISION_PAGE 5
#define REPORT_PAGE 6

StartScreen::StartScreen(QWidget * parent) 
	: QWidget(parent), chart(NULL), manager(NULL)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(START_PAGE);

	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(toOptionsPage()));
	connect(ui.backToStartFrameButton, SIGNAL(clicked()), this,
		SLOT(toStartPage()));
	connect(ui.instructionsBackButton, SIGNAL(clicked()), this,
		SLOT(toStartPage()));
	connect(ui.instructionsButton, SIGNAL(clicked()), this,
		SLOT(toInstructionsPage()));
	connect(ui.creditsButton, SIGNAL(clicked()), this, SLOT(toCreditsPage()));
	connect(ui.creditsBackButton, SIGNAL(clicked()), this,
		SLOT(toStartPage()));
	connect(ui.completeProcedureButton, SIGNAL(clicked()), this, 
		SLOT(toChartPage()));
	connect(ui.chartPageBackButton, SIGNAL(clicked()), this,
		SLOT(toOptionsPage()));
	connect(ui.backToChartButton, SIGNAL(clicked()), this, 
		SLOT(toChartPage()));
	connect(ui.chartPageForwardButton, SIGNAL(clicked()), this,
		SLOT(toTreatmentDecisionPage()));
	connect(ui.noSurgeryButton, SIGNAL(clicked()), this,
		SLOT(toReportPage()));
	connect(ui.noSurgeryButton, SIGNAL(clicked()), this,
		SLOT(noSurgeryAssessment()));
	connect(ui.reportPageStartButton, SIGNAL(clicked()), this,
		SLOT(toStartPageFromReport()));
}

StartScreen::~StartScreen() {
	delete chart;
	delete manager;
}

void StartScreen::noSurgeryAssessment()
{
	if (manager) {
		delete manager;
		manager = NULL;
	}

	manager = new AssessmentManager();
	manager->setChart(chart);
	manager->setTreatmentType(TreatmentType::NO_SURGERY);
	manager->assess();

	ui.treatmentChoiceBox->setText(QString::fromStdString(
		manager->getTreatmentAssessment()));
}

void StartScreen::toChartPage()
{
	ui.stackedWidget->setCurrentIndex(CHART_PAGE);
	if (!chart) {
		chart = new Chart(PATIENT_READY);
		ui.patientNameBox->setText(QString::fromStdString(chart->getPatientName()));
		ui.dateBox->setText(QString::fromStdString(chart->getDate()));
		ui.clinicBox->setText(QString::fromStdString(chart->getClinic()));
		ui.chartNumberBox->setText(QString::fromStdString(chart->getChartNumber()));

	}
}

void StartScreen::toCreditsPage()
{
	ui.stackedWidget->setCurrentIndex(CREDITS_PAGE);
}

void StartScreen::toInstructionsPage()
{
	ui.stackedWidget->setCurrentIndex(INSTRUCTIONS_PAGE);
}

void StartScreen::toOptionsPage()
{
	ui.stackedWidget->setCurrentIndex(OPTIONS_PAGE);
}

void StartScreen::toReportPage()
{
	ui.stackedWidget->setCurrentIndex(REPORT_PAGE);
}

void StartScreen::toStartPage()
{
	ui.stackedWidget->setCurrentIndex(START_PAGE);
}

void StartScreen::toStartPageFromReport()
{
	ui.stackedWidget->setCurrentIndex(START_PAGE);
	delete chart;
	delete manager;
}

void StartScreen::toTreatmentDecisionPage()
{
	ui.stackedWidget->setCurrentIndex(TREATMENT_DECISION_PAGE);
}
