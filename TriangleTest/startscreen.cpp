#include "startscreen.hpp"
#include <iostream>

#define START_PAGE 0
#define OPTIONS_PAGE 1
#define INSTRUCTIONS_PAGE 2
#define CREDITS_PAGE 3

StartScreen::StartScreen(QWidget * parent) 
	: QWidget(parent)
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
}

StartScreen::~StartScreen() {
	
}

void StartScreen::toOptionsPage()
{
	ui.stackedWidget->setCurrentIndex(OPTIONS_PAGE);
}

void StartScreen::toStartPage()
{
	ui.stackedWidget->setCurrentIndex(START_PAGE);
}

void StartScreen::toCreditsPage()
{
	ui.stackedWidget->setCurrentIndex(CREDITS_PAGE);
}

void StartScreen::toInstructionsPage()
{
	ui.stackedWidget->setCurrentIndex(INSTRUCTIONS_PAGE);
}
