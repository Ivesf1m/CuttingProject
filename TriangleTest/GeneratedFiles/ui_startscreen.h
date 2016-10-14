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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
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
    QWidget *chartPage;
    QLabel *patientNameLabel;
    QLabel *chartNumberLabel;
    QLabel *clinicLabel;
    QLabel *dateLabel;
    QLabel *doctorLabel;
    QLabel *patientHistoryLabel;
    QTextBrowser *patientNameBox;
    QTextBrowser *chartNumberBox;
    QTextBrowser *dateBox;
    QTextBrowser *clinicBox;
    QTextBrowser *doctorBox;
    QTextBrowser *patientHistoryBox;
    QPushButton *chartPageForwardButton;
    QPushButton *chartPageBackButton;
    QWidget *treatmentDecisionPage;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *submentalIncisionButton;
    QPushButton *noSurgeryButton;
    QTextBrowser *textBrowser;
    QPushButton *backToChartButton;
    QWidget *reportPage;
    QTextBrowser *textBrowser_2;
    QLabel *treatmentChoiceLabel;
    QTextBrowser *treatmentChoiceBox;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_6;
    QPushButton *reportPageStartButton;
    QPushButton *reportPageExitButton;
    QWidget *scalpelPage;
    QTextBrowser *textBrowser_3;
    QFrame *scalpelFrame;
    QLabel *scalpelLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *scalpel10;
    QRadioButton *scalpel11;
    QRadioButton *scalpel12;
    QRadioButton *scalpel12d;
    QRadioButton *scalpel15;
    QRadioButton *scalpel15c;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *scalpelBackButton;
    QPushButton *scalpelForwardButton;
    QWidget *antissepticPage;
    QTextBrowser *textBrowser_4;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QFrame *alcohol96Frame;
    QLabel *alcohol96Label;
    QFrame *pvpiFrame;
    QLabel *pvpiLabel;
    QFrame *clorhexidineFrame;
    QLabel *clorhexidineLabel;
    QFrame *alcohol70Frame;
    QLabel *alcohol70Label;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *alcohol96Button;
    QRadioButton *pvpiButton;
    QRadioButton *clorhexidineButton;
    QRadioButton *alcohol70Button;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *antissepticsBackButton;
    QPushButton *antissepticsForwardButton;

    void setupUi(QWidget *startScreen)
    {
        if (startScreen->objectName().isEmpty())
            startScreen->setObjectName(QStringLiteral("startScreen"));
        startScreen->resize(600, 599);
        stackedWidget = new QStackedWidget(startScreen);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 700, 902));
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
        chartPage = new QWidget();
        chartPage->setObjectName(QStringLiteral("chartPage"));
        patientNameLabel = new QLabel(chartPage);
        patientNameLabel->setObjectName(QStringLiteral("patientNameLabel"));
        patientNameLabel->setGeometry(QRect(10, 20, 101, 16));
        chartNumberLabel = new QLabel(chartPage);
        chartNumberLabel->setObjectName(QStringLiteral("chartNumberLabel"));
        chartNumberLabel->setGeometry(QRect(10, 60, 121, 16));
        clinicLabel = new QLabel(chartPage);
        clinicLabel->setObjectName(QStringLiteral("clinicLabel"));
        clinicLabel->setGeometry(QRect(10, 100, 101, 16));
        dateLabel = new QLabel(chartPage);
        dateLabel->setObjectName(QStringLiteral("dateLabel"));
        dateLabel->setGeometry(QRect(320, 60, 47, 13));
        doctorLabel = new QLabel(chartPage);
        doctorLabel->setObjectName(QStringLiteral("doctorLabel"));
        doctorLabel->setGeometry(QRect(320, 100, 47, 13));
        patientHistoryLabel = new QLabel(chartPage);
        patientHistoryLabel->setObjectName(QStringLiteral("patientHistoryLabel"));
        patientHistoryLabel->setGeometry(QRect(10, 140, 121, 16));
        patientNameBox = new QTextBrowser(chartPage);
        patientNameBox->setObjectName(QStringLiteral("patientNameBox"));
        patientNameBox->setGeometry(QRect(110, 10, 451, 31));
        chartNumberBox = new QTextBrowser(chartPage);
        chartNumberBox->setObjectName(QStringLiteral("chartNumberBox"));
        chartNumberBox->setGeometry(QRect(130, 50, 171, 31));
        dateBox = new QTextBrowser(chartPage);
        dateBox->setObjectName(QStringLiteral("dateBox"));
        dateBox->setGeometry(QRect(360, 50, 211, 31));
        clinicBox = new QTextBrowser(chartPage);
        clinicBox->setObjectName(QStringLiteral("clinicBox"));
        clinicBox->setGeometry(QRect(50, 90, 251, 31));
        doctorBox = new QTextBrowser(chartPage);
        doctorBox->setObjectName(QStringLiteral("doctorBox"));
        doctorBox->setGeometry(QRect(370, 90, 201, 31));
        patientHistoryBox = new QTextBrowser(chartPage);
        patientHistoryBox->setObjectName(QStringLiteral("patientHistoryBox"));
        patientHistoryBox->setGeometry(QRect(10, 160, 571, 321));
        chartPageForwardButton = new QPushButton(chartPage);
        chartPageForwardButton->setObjectName(QStringLiteral("chartPageForwardButton"));
        chartPageForwardButton->setGeometry(QRect(480, 540, 75, 23));
        chartPageBackButton = new QPushButton(chartPage);
        chartPageBackButton->setObjectName(QStringLiteral("chartPageBackButton"));
        chartPageBackButton->setGeometry(QRect(40, 540, 75, 23));
        stackedWidget->addWidget(chartPage);
        treatmentDecisionPage = new QWidget();
        treatmentDecisionPage->setObjectName(QStringLiteral("treatmentDecisionPage"));
        verticalLayoutWidget_4 = new QWidget(treatmentDecisionPage);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(140, 120, 319, 441));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        submentalIncisionButton = new QPushButton(verticalLayoutWidget_4);
        submentalIncisionButton->setObjectName(QStringLiteral("submentalIncisionButton"));

        verticalLayout_5->addWidget(submentalIncisionButton);

        noSurgeryButton = new QPushButton(verticalLayoutWidget_4);
        noSurgeryButton->setObjectName(QStringLiteral("noSurgeryButton"));

        verticalLayout_5->addWidget(noSurgeryButton);

        textBrowser = new QTextBrowser(treatmentDecisionPage);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(30, 30, 531, 61));
        backToChartButton = new QPushButton(treatmentDecisionPage);
        backToChartButton->setObjectName(QStringLiteral("backToChartButton"));
        backToChartButton->setGeometry(QRect(500, 522, 75, 61));
        stackedWidget->addWidget(treatmentDecisionPage);
        reportPage = new QWidget();
        reportPage->setObjectName(QStringLiteral("reportPage"));
        textBrowser_2 = new QTextBrowser(reportPage);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(10, 10, 581, 41));
        treatmentChoiceLabel = new QLabel(reportPage);
        treatmentChoiceLabel->setObjectName(QStringLiteral("treatmentChoiceLabel"));
        treatmentChoiceLabel->setGeometry(QRect(10, 70, 141, 21));
        QFont font;
        font.setPointSize(10);
        treatmentChoiceLabel->setFont(font);
        treatmentChoiceBox = new QTextBrowser(reportPage);
        treatmentChoiceBox->setObjectName(QStringLiteral("treatmentChoiceBox"));
        treatmentChoiceBox->setGeometry(QRect(150, 70, 251, 31));
        verticalLayoutWidget_5 = new QWidget(reportPage);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(429, 499, 171, 101));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        reportPageStartButton = new QPushButton(verticalLayoutWidget_5);
        reportPageStartButton->setObjectName(QStringLiteral("reportPageStartButton"));

        verticalLayout_6->addWidget(reportPageStartButton);

        reportPageExitButton = new QPushButton(verticalLayoutWidget_5);
        reportPageExitButton->setObjectName(QStringLiteral("reportPageExitButton"));

        verticalLayout_6->addWidget(reportPageExitButton);

        stackedWidget->addWidget(reportPage);
        scalpelPage = new QWidget();
        scalpelPage->setObjectName(QStringLiteral("scalpelPage"));
        textBrowser_3 = new QTextBrowser(scalpelPage);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(10, 10, 581, 41));
        scalpelFrame = new QFrame(scalpelPage);
        scalpelFrame->setObjectName(QStringLiteral("scalpelFrame"));
        scalpelFrame->setGeometry(QRect(10, 70, 571, 421));
        scalpelFrame->setFrameShape(QFrame::StyledPanel);
        scalpelFrame->setFrameShadow(QFrame::Raised);
        scalpelLabel = new QLabel(scalpelFrame);
        scalpelLabel->setObjectName(QStringLiteral("scalpelLabel"));
        scalpelLabel->setGeometry(QRect(6, 2, 561, 421));
        horizontalLayoutWidget = new QWidget(scalpelPage);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 500, 581, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        scalpel10 = new QRadioButton(horizontalLayoutWidget);
        scalpel10->setObjectName(QStringLiteral("scalpel10"));

        horizontalLayout->addWidget(scalpel10);

        scalpel11 = new QRadioButton(horizontalLayoutWidget);
        scalpel11->setObjectName(QStringLiteral("scalpel11"));

        horizontalLayout->addWidget(scalpel11);

        scalpel12 = new QRadioButton(horizontalLayoutWidget);
        scalpel12->setObjectName(QStringLiteral("scalpel12"));

        horizontalLayout->addWidget(scalpel12);

        scalpel12d = new QRadioButton(horizontalLayoutWidget);
        scalpel12d->setObjectName(QStringLiteral("scalpel12d"));

        horizontalLayout->addWidget(scalpel12d);

        scalpel15 = new QRadioButton(horizontalLayoutWidget);
        scalpel15->setObjectName(QStringLiteral("scalpel15"));

        horizontalLayout->addWidget(scalpel15);

        scalpel15c = new QRadioButton(horizontalLayoutWidget);
        scalpel15c->setObjectName(QStringLiteral("scalpel15c"));

        horizontalLayout->addWidget(scalpel15c);

        horizontalLayoutWidget_2 = new QWidget(scalpelPage);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 550, 581, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        scalpelBackButton = new QPushButton(horizontalLayoutWidget_2);
        scalpelBackButton->setObjectName(QStringLiteral("scalpelBackButton"));

        horizontalLayout_2->addWidget(scalpelBackButton);

        scalpelForwardButton = new QPushButton(horizontalLayoutWidget_2);
        scalpelForwardButton->setObjectName(QStringLiteral("scalpelForwardButton"));

        horizontalLayout_2->addWidget(scalpelForwardButton);

        stackedWidget->addWidget(scalpelPage);
        antissepticPage = new QWidget();
        antissepticPage->setObjectName(QStringLiteral("antissepticPage"));
        textBrowser_4 = new QTextBrowser(antissepticPage);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(10, 10, 581, 41));
        horizontalLayoutWidget_3 = new QWidget(antissepticPage);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 60, 581, 421));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        alcohol96Frame = new QFrame(horizontalLayoutWidget_3);
        alcohol96Frame->setObjectName(QStringLiteral("alcohol96Frame"));
        alcohol96Frame->setFrameShape(QFrame::StyledPanel);
        alcohol96Frame->setFrameShadow(QFrame::Raised);
        alcohol96Label = new QLabel(alcohol96Frame);
        alcohol96Label->setObjectName(QStringLiteral("alcohol96Label"));
        alcohol96Label->setGeometry(QRect(6, 2, 131, 411));

        horizontalLayout_3->addWidget(alcohol96Frame);

        pvpiFrame = new QFrame(horizontalLayoutWidget_3);
        pvpiFrame->setObjectName(QStringLiteral("pvpiFrame"));
        pvpiFrame->setFrameShape(QFrame::StyledPanel);
        pvpiFrame->setFrameShadow(QFrame::Raised);
        pvpiLabel = new QLabel(pvpiFrame);
        pvpiLabel->setObjectName(QStringLiteral("pvpiLabel"));
        pvpiLabel->setGeometry(QRect(6, 2, 131, 411));

        horizontalLayout_3->addWidget(pvpiFrame);

        clorhexidineFrame = new QFrame(horizontalLayoutWidget_3);
        clorhexidineFrame->setObjectName(QStringLiteral("clorhexidineFrame"));
        clorhexidineFrame->setFrameShape(QFrame::StyledPanel);
        clorhexidineFrame->setFrameShadow(QFrame::Raised);
        clorhexidineLabel = new QLabel(clorhexidineFrame);
        clorhexidineLabel->setObjectName(QStringLiteral("clorhexidineLabel"));
        clorhexidineLabel->setGeometry(QRect(6, 2, 131, 411));

        horizontalLayout_3->addWidget(clorhexidineFrame);

        alcohol70Frame = new QFrame(horizontalLayoutWidget_3);
        alcohol70Frame->setObjectName(QStringLiteral("alcohol70Frame"));
        alcohol70Frame->setFrameShape(QFrame::StyledPanel);
        alcohol70Frame->setFrameShadow(QFrame::Raised);
        alcohol70Label = new QLabel(alcohol70Frame);
        alcohol70Label->setObjectName(QStringLiteral("alcohol70Label"));
        alcohol70Label->setGeometry(QRect(6, 2, 131, 411));

        horizontalLayout_3->addWidget(alcohol70Frame);

        horizontalLayoutWidget_4 = new QWidget(antissepticPage);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 490, 581, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        alcohol96Button = new QRadioButton(horizontalLayoutWidget_4);
        alcohol96Button->setObjectName(QStringLiteral("alcohol96Button"));

        horizontalLayout_4->addWidget(alcohol96Button);

        pvpiButton = new QRadioButton(horizontalLayoutWidget_4);
        pvpiButton->setObjectName(QStringLiteral("pvpiButton"));

        horizontalLayout_4->addWidget(pvpiButton);

        clorhexidineButton = new QRadioButton(horizontalLayoutWidget_4);
        clorhexidineButton->setObjectName(QStringLiteral("clorhexidineButton"));

        horizontalLayout_4->addWidget(clorhexidineButton);

        alcohol70Button = new QRadioButton(horizontalLayoutWidget_4);
        alcohol70Button->setObjectName(QStringLiteral("alcohol70Button"));

        horizontalLayout_4->addWidget(alcohol70Button);

        horizontalLayoutWidget_5 = new QWidget(antissepticPage);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 540, 581, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        antissepticsBackButton = new QPushButton(horizontalLayoutWidget_5);
        antissepticsBackButton->setObjectName(QStringLiteral("antissepticsBackButton"));

        horizontalLayout_5->addWidget(antissepticsBackButton);

        antissepticsForwardButton = new QPushButton(horizontalLayoutWidget_5);
        antissepticsForwardButton->setObjectName(QStringLiteral("antissepticsForwardButton"));

        horizontalLayout_5->addWidget(antissepticsForwardButton);

        stackedWidget->addWidget(antissepticPage);

        retranslateUi(startScreen);
        QObject::connect(exitButton, SIGNAL(clicked()), startScreen, SLOT(close()));
        QObject::connect(reportPageExitButton, SIGNAL(clicked()), startScreen, SLOT(close()));

        stackedWidget->setCurrentIndex(5);


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
        patientNameLabel->setText(QApplication::translate("startScreen", "Nome do paciente:", 0));
        chartNumberLabel->setText(QApplication::translate("startScreen", "N\303\272mero do prontu\303\241rio: ", 0));
        clinicLabel->setText(QApplication::translate("startScreen", "Cl\303\255nica: ", 0));
        dateLabel->setText(QApplication::translate("startScreen", "Data:", 0));
        doctorLabel->setText(QApplication::translate("startScreen", "M\303\251dico: ", 0));
        patientHistoryLabel->setText(QApplication::translate("startScreen", "Hist\303\263rico do paciente: ", 0));
        chartPageForwardButton->setText(QApplication::translate("startScreen", "Avan\303\247ar", 0));
        chartPageBackButton->setText(QApplication::translate("startScreen", "Voltar", 0));
        submentalIncisionButton->setText(QApplication::translate("startScreen", "Seguir para a cirurgia, utilizando incis\303\243o submentoniana", 0));
        noSurgeryButton->setText(QApplication::translate("startScreen", "Outro plano de tratamento deve ser utilizado", 0));
        textBrowser->setHtml(QApplication::translate("startScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Dada a condi\303\247\303\243o atual do paciente, qual o melhor curso de tratamento?</span></p></body></html>", 0));
        backToChartButton->setText(QApplication::translate("startScreen", "Voltar para\n"
" o prontu\303\241rio", 0));
        textBrowser_2->setHtml(QApplication::translate("startScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Relat\303\263rio de desempenho</span></p></body></html>", 0));
        treatmentChoiceLabel->setText(QApplication::translate("startScreen", "Escolha do tratamento:", 0));
        reportPageStartButton->setText(QApplication::translate("startScreen", "In\303\255cio", 0));
        reportPageExitButton->setText(QApplication::translate("startScreen", "Sair", 0));
        textBrowser_3->setHtml(QApplication::translate("startScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Selecione a l\303\242mina apropriada para a cirurgia</span></p></body></html>", 0));
        scalpelLabel->setText(QString());
        scalpel10->setText(QApplication::translate("startScreen", "10", 0));
        scalpel11->setText(QApplication::translate("startScreen", "11", 0));
        scalpel12->setText(QApplication::translate("startScreen", "12", 0));
        scalpel12d->setText(QApplication::translate("startScreen", "12D", 0));
        scalpel15->setText(QApplication::translate("startScreen", "15", 0));
        scalpel15c->setText(QApplication::translate("startScreen", "15C", 0));
        scalpelBackButton->setText(QApplication::translate("startScreen", "Voltar", 0));
        scalpelForwardButton->setText(QApplication::translate("startScreen", "Avan\303\247ar", 0));
        textBrowser_4->setHtml(QApplication::translate("startScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Selecione o antiss\303\251ptico a ser utilizado na cirurgia</span></p></body></html>", 0));
        alcohol96Label->setText(QString());
        pvpiLabel->setText(QString());
        clorhexidineLabel->setText(QString());
        alcohol70Label->setText(QString());
        alcohol96Button->setText(QApplication::translate("startScreen", "\303\201lcool 96", 0));
        pvpiButton->setText(QApplication::translate("startScreen", "PVPI", 0));
        clorhexidineButton->setText(QApplication::translate("startScreen", "Clorexidina", 0));
        alcohol70Button->setText(QApplication::translate("startScreen", "\303\201lcool 70", 0));
        antissepticsBackButton->setText(QApplication::translate("startScreen", "Voltar", 0));
        antissepticsForwardButton->setText(QApplication::translate("startScreen", "Avan\303\247ar", 0));
    } // retranslateUi

};

namespace Ui {
    class startScreen: public Ui_startScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
