#pragma once
#include <QtWidgets\qwidget.h>
#include "ui_startscreen.h"

class StartScreen : public QWidget {
	Q_OBJECT

public:
	StartScreen(QWidget * parent = Q_NULLPTR);
	~StartScreen();

public slots:
	void toStartPage();
	void toOptionsPage();

private:
	Ui::startScreen ui;
};
