#include "startscreen.hpp"
#include <chrono>
#include <iostream>
#include <qmessagebox.h>
#include <random>

#define START_PAGE 0
#define OPTIONS_PAGE 1
#define INSTRUCTIONS_PAGE 2
#define CREDITS_PAGE 3
#define CHART_PAGE 4
#define TREATMENT_DECISION_PAGE 5
#define REPORT_PAGE 6
#define SCALPEL_PAGE 7

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
	connect(ui.otherIncisionButton, SIGNAL(clicked()), this,
		SLOT(toReportPage()));
	connect(ui.otherIncisionButton, SIGNAL(clicked()), this,
		SLOT(otherIncisionAssessment()));
	connect(ui.reportPageStartButton, SIGNAL(clicked()), this,
		SLOT(toStartPageFromReport()));
	connect(ui.submentalIncisionButton, SIGNAL(clicked()), this,
		SLOT(toScalpelPage()));
	connect(ui.scalpelBackButton, SIGNAL(clicked()), this,
		SLOT(toTreatmentDecisionPage()));
	connect(ui.scalpelForwardButton, SIGNAL(clicked()), this,
		SLOT(scalpelChoiceAssessment()));
}

StartScreen::~StartScreen() {
	delete chart;
	delete manager;
}

void StartScreen::otherIncisionAssessment()
{
	if (manager) {
		delete manager;
		manager = NULL;
	}

	manager = new AssessmentManager();
	manager->setChart(chart);
	manager->setTreatmentType(TreatmentType::DIFFERENT_INCISION);
	manager->assess();

	ui.treatmentChoiceBox->setText(QString::fromStdString(
		manager->getTreatmentAssessment()));
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

void StartScreen::scalpelChoiceAssessment()
{
	if (!manager)
		return;

	string chosenScalpel;
	if (ui.scalpel10->isChecked())
		chosenScalpel = "10";
	else if (ui.scalpel11->isChecked())
		chosenScalpel = "11";
	else if (ui.scalpel12->isChecked())
		chosenScalpel = "12";
	else if (ui.scalpel12d->isChecked())
		chosenScalpel = "12d";
	else if (ui.scalpel15->isChecked())
		chosenScalpel = "15";
	else if (ui.scalpel15c->isChecked())
		chosenScalpel = "15c";
	else {
		QMessageBox msgBox;
		msgBox.setWindowTitle("Error!");
		msgBox.setText(QString::fromWCharArray(
			L"Uma das opções de bisturis deve ser selecionada!"));
		msgBox.show();
	}
}

void StartScreen::toChartPage()
{
	ui.stackedWidget->setCurrentIndex(CHART_PAGE);
	if (!chart) {
		//Generating a random chart type.
		ChartType ctype;
		std::default_random_engine engine;
		unsigned int rseed = std::chrono::high_resolution_clock::now().
			time_since_epoch().count();
		engine.seed(rseed);
		std::uniform_int_distribution<int> dist(1, 10);
		int number = dist(engine);
		std::cout << number << std::endl;
		if (number <= 5)
			ctype = ChartType::PATIENT_READY;
		else if (number > 5 && number < 7)
			ctype = ChartType::PATIENT_NOT_READY;
		else
			ctype = ChartType::SCARRING_PROBLEM;

		chart = new Chart(ctype);
		ui.patientNameBox->setText(QString::fromStdString(
			chart->getPatientName()));
		ui.dateBox->setText(QString::fromStdString(chart->getDate()));
		ui.clinicBox->setText(QString::fromStdString(chart->getClinic()));
		ui.chartNumberBox->setText(QString::fromStdString(
			chart->getChartNumber()));
		ui.patientHistoryBox->setText(QString::fromStdWString(
			chart->getPatientHistory()));
		//ui.patientHistoryBox->setText(QApplication::translate(
			//"startScreen", chart->getPatientHistory().c_str(), 0));
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

void StartScreen::toScalpelPage()
{
	ui.stackedWidget->setCurrentIndex(SCALPEL_PAGE);
	ui.scalpelLabel->setPixmap(QPixmap("bisturis.jpg")
		.scaledToWidth(ui.scalpelFrame->width()));
}

void StartScreen::toStartPage()
{
	ui.stackedWidget->setCurrentIndex(START_PAGE);
}

void StartScreen::toStartPageFromReport()
{
	ui.stackedWidget->setCurrentIndex(START_PAGE);
	delete chart;
	chart = NULL;
	delete manager;
	manager = NULL;
}

void StartScreen::toTreatmentDecisionPage()
{
	ui.stackedWidget->setCurrentIndex(TREATMENT_DECISION_PAGE);
}
