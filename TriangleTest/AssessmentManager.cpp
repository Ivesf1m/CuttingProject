#include "AssessmentManager.h"



AssessmentManager::AssessmentManager()
	: chart(NULL)
{
}


AssessmentManager::~AssessmentManager()
{
}

float AssessmentManager::getAcceptableRadius()
{
	return acceptableRadius;
}

void AssessmentManager::setAcceptableRadius(float acceptableRadius)
{
	this->acceptableRadius = acceptableRadius;
}

const string& AssessmentManager::getAntissepticChoiceAssessment()
{
	return antissepticChoiceAssessment;
}

void AssessmentManager::setAntissepticChoiceAssessment(const string& assessment)
{
	this->antissepticChoiceAssessment = assessment;
}

const Chart* AssessmentManager::getChart()
{
	return chart;
}

void AssessmentManager::setChart(const Chart* chart)
{
	this->chart = chart;
}

const string& AssessmentManager::getChosenAntisseptic()
{
	return chosenAntisseptic;
}

void AssessmentManager::setChosenAntisseptic(const string& antisseptic)
{
	this->chosenAntisseptic = antisseptic;
}

const string& AssessmentManager::getChosenScalpel()
{
	return chosenScalpel;
}

void AssessmentManager::setChosenScalpel(const string& scalpel)
{
	this->chosenScalpel = scalpel;
}

const string& AssessmentManager::getEndPointAssessment()
{
	return endPointAssessment;
}

void AssessmentManager::setEndPointAssessment(const string& assessment)
{
	this->endPointAssessment = assessment;
}

const vec3& AssessmentManager::getIdealEndPoint()
{
	return idealEndPoint;
}

void AssessmentManager::setIdealEndPoint(const vec3& endPoint)
{
	this->idealEndPoint = endPoint;
}

const vec3& AssessmentManager::getIdealStartPoint()
{
	return idealStartPoint;
}

void AssessmentManager::setIdealStartPoint(const vec3& startPoint)
{
	this->idealStartPoint = startPoint;
}

float AssessmentManager::getOptimalRadius()
{
	return optimalRadius;
}

void AssessmentManager::setOptimalRadius(float optimalRadius)
{
	this->optimalRadius = optimalRadius;
}

const string& AssessmentManager::getScalpelChoiceAssessment()
{
	return scalpelChoiceAssessment;
}

void AssessmentManager::setScalpelChoiceAssessment(const string& assessment)
{
	this->scalpelChoiceAssessment = assessment;
}

const string& AssessmentManager::getStartPointAssessment()
{
	return startPointAssessment;
}

void AssessmentManager::setStartPointAssessment(const string& assessment)
{
	this->startPointAssessment = assessment;
}

const string& AssessmentManager::getTreatmentAssessment()
{
	return treatmentAssessment;
}

void AssessmentManager::setTreatmentAssessment(const string& treatmentAssessment)
{
	this->treatmentAssessment = treatmentAssessment;
}

TreatmentType AssessmentManager::getTreatmentType()
{
	return treatmentType;
}

void AssessmentManager::setTreatmentType(TreatmentType type)
{
	this->treatmentType = type;
}

void AssessmentManager::assess()
{
	assessTreatmentType();
}

void AssessmentManager::assessAntissepticChoice()
{
	if (chosenAntisseptic.compare("pvpi") == 0 ||
		chosenAntisseptic.compare("clorexidina") == 0)
		antissepticChoiceAssessment = "Antissepctico escolhido corretamente.";
	else
		antissepticChoiceAssessment = "Antissepctico escolhido incorretamente.";
}

void AssessmentManager::assessEndPoint(const vec3& endPoint)
{
	float distance = glm::distance(idealEndPoint, endPoint);
	if (distance <= optimalRadius)
		endPointAssessment = "O corte terminou em local correto.";
	else if (distance > optimalRadius && distance <= acceptableRadius)
		endPointAssessment = "O corte terminou em local aceitavel.";
	else
		endPointAssessment = "O corte terminou em local incorreto.";
}

void AssessmentManager::assessScalpelChoice()
{
	if (chosenScalpel.compare("15") == 0 ||
		chosenScalpel.compare("15c") == 0)
		scalpelChoiceAssessment = "Bisturi escolhido corretamente.";
	else
		scalpelChoiceAssessment = "Bisturi escolhido incorretamente.";
}

void AssessmentManager::assessStartPoint(const vec3& startPoint)
{
	float distance = glm::distance(idealStartPoint, startPoint);
	if (distance <= optimalRadius)
		startPointAssessment = "O corte foi iniciado em local correto.";
	else if (distance > optimalRadius && distance <= acceptableRadius)
		startPointAssessment = "O corte foi iniciado em local aceitavel.";
	else
		startPointAssessment = "O corte foi iniciado em local incorreto.";
}

void AssessmentManager::assessTreatmentType()
{
	if (!chart)
		return;

	if (treatmentType == SUBMENTAL_INCISION &&
		chart->getChartType() == ChartType::PATIENT_READY) 
		treatmentAssessment = "Tratamento correto.";
	else if (treatmentType == DIFFERENT_INCISION &&
		chart->getChartType() == ChartType::SCARRING_PROBLEM)
		treatmentAssessment = "Tratamento correto.";
	else if(treatmentType == NO_SURGERY &&
		chart->getChartType() == ChartType::PATIENT_NOT_READY)
		treatmentAssessment = "Tratamento correto.";
	else
		treatmentAssessment = "Tratamento incorreto.";
}