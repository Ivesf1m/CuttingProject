#include "AssessmentManager.h"



AssessmentManager::AssessmentManager()
	: chart(NULL)
{
}


AssessmentManager::~AssessmentManager()
{
}

const Chart* AssessmentManager::getChart()
{
	return chart;
}

void AssessmentManager::setChart(const Chart* chart)
{
	this->chart = chart;
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