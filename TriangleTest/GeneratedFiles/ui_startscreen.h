/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startScreen
{
public:
    QStackedWidget *stackedWidget;
    QWidget *startPage;
    QFrame *startFrame;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *instructionsButton;
    QPushButton *creditsButton;
    QPushButton *exitButton;
    QWidget *optionsPage;
    QFrame *optionsFrame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *completeProcedureButton;
    QPushButton *cutOnlyButton;
    QPushButton *backToStartFrameButton;
    QWidget *instructionsPage;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *instructionsBackButton;
    QWidget *creditsPage;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *creditsBackButton;

    void setupUi(QWidget *startScreen)
    {
        if (startScreen->objectName().isEmpty())
            startScreen->setObjectName(QStringLiteral("startScreen"));
        startScreen->resize(600, 600);
        stackedWidget = new QStackedWidget(startScreen);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 601, 601));
        startPage = new QWidget();
        startPage->setObjectName(QStringLiteral("startPage"));
        startFrame = new QFrame(startPage);
        startFrame->setObjectName(QStringLiteral("startFrame"));
        startFrame->setGeometry(QRect(180, 130, 271, 411));
        verticalLayout = new QVBoxLayout(startFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        startButton = new QPushButton(startFrame);
        startButton->setObjectName(QStringLiteral("startButton"));

        verticalLayout->addWidget(startButton);

        instructionsButton = new QPushButton(startFrame);
        instructionsButton->setObjectName(QStringLiteral("instructionsButton"));

        verticalLayout->addWidget(instructionsButton);

        creditsButton = new QPushButton(startFrame);
        creditsButton->setObjectName(QStringLiteral("creditsButton"));

        verticalLayout->addWidget(creditsButton);

        exitButton = new QPushButton(startFrame);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        verticalLayout->addWidget(exitButton);

        stackedWidget->addWidget(startPage);
        optionsPage = new QWidget();
        optionsPage->setObjectName(QStringLiteral("optionsPage"));
        optionsFrame = new QFrame(optionsPage);
        optionsFrame->setObjectName(QStringLiteral("optionsFrame"));
        optionsFrame->setEnabled(true);
        optionsFrame->setGeometry(QRect(170, 140, 271, 411));
        optionsFrame->setFrameShape(QFrame::StyledPanel);
        optionsFrame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(optionsFrame);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 271, 411));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        completeProcedureButton = new QPushButton(verticalLayoutWidget);
        completeProcedureButton->setObjectName(QStringLiteral("completeProcedureButton"));

        verticalLayout_2->addWidget(completeProcedureButton);

        cutOnlyButton = new QPushButton(verticalLayoutWidget);
        cutOnlyButton->setObjectName(QStringLiteral("cutOnlyButton"));

        verticalLayout_2->addWidget(cutOnlyButton);

        backToStartFrameButton = new QPushButton(verticalLayoutWidget);
        backToStartFrameButton->setObjectName(QStringLiteral("backToStartFrameButton"));

        verticalLayout_2->addWidget(backToStartFrameButton);

        stackedWidget->addWidget(optionsPage);
        instructionsPage = new QWidget();
        instructionsPage->setObjectName(QStringLiteral("instructionsPage"));
        verticalLayoutWidget_2 = new QWidget(instructionsPage);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(430, 510, 160, 80));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        instructionsBackButton = new QPushButton(verticalLayoutWidget_2);
        instructionsBackButton->setObjectName(QStringLiteral("instructionsBackButton"));

        verticalLayout_3->addWidget(instructionsBackButton);

        stackedWidget->addWidget(instructionsPage);
        creditsPage = new QWidget();
        creditsPage->setObjectName(QStringLiteral("creditsPage"));
        verticalLayoutWidget_3 = new QWidget(creditsPage);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(430, 510, 160, 80));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        creditsBackButton = new QPushButton(verticalLayoutWidget_3);
        creditsBackButton->setObjectName(QStringLiteral("creditsBackButton"));

        verticalLayout_4->addWidget(creditsBackButton);

        stackedWidget->addWidget(creditsPage);

        retranslateUi(startScreen);
        QObject::connect(exitButton, SIGNAL(clicked()), startScreen, SLOT(close()));

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(startScreen);
    } // setupUi

    void retranslateUi(QWidget *startScreen)
    {
        startScreen->setWindowTitle(QApplication::translate("startScreen", "StartScreen", 0));
        startButton->setText(QApplication::translate("startScreen", "Iniciar", 0));
        instructionsButton->setText(QApplication::translate("startScreen", "Instru\303\247\303\265es", 0));
        creditsButton->setText(QApplication::translate("startScreen", "Cr\303\251ditos", 0));
        exitButton->setText(QApplication::translate("startScreen", "Sair", 0));
        completeProcedureButton->setText(QApplication::translate("startScreen", "Procedimento completo", 0));
        cutOnlyButton->setText(QApplication::translate("startScreen", "Apenas corte", 0));
        backToStartFrameButton->setText(QApplication::translate("startScreen", "Voltar", 0));
        instructionsBackButton->setText(QApplication::translate("startScreen", "Voltar", 0));
        creditsBackButton->setText(QApplication::translate("startScreen", "Voltar", 0));
    } // retranslateUi

};

namespace Ui {
    class startScreen: public Ui_startScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
