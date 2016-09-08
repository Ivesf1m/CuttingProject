#include "startscreen.hpp"
#include <iostream>

#define START_PAGE 0
#define OPTIONS_PAGE 1

StartScreen::StartScreen(QWidget * parent) 
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(START_PAGE);

	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(toOptionsPage()));
	connect(ui.backToStartFrameButton, SIGNAL(clicked()), this,
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
	ui.stackedWidget->setCurrentIndex(0);
}
