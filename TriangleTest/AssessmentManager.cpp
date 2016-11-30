#include "AssessmentManager.h"
#include <cmath>

#define PI 3.14159265

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

void AssessmentManager::addAntissepticChoice(const string& choice)
{
	correctAntissepticChoices.push_back(choice);
}

const vector<string>& AssessmentManager::getCorrectAntissepticChoices()
{
	return correctAntissepticChoices;
}

void AssessmentManager::setCorrectAntissepticChoices(const vector<string>& choices)
{
	this->correctAntissepticChoices = choices;
}

void AssessmentManager::addScalpelChoice(const string& choice)
{
	correctScalpelChoices.push_back(choice);
}

const vector<string>& AssessmentManager::getCorrectScalpelChoices()
{
	return correctScalpelChoices;
}

void AssessmentManager::setCorrectScalpelChoices(const vector<string>& choices)
{
	this->correctScalpelChoices = choices;
}

const string& AssessmentManager::getDepthAssessment()
{
	return depthAssessment;
}

void AssessmentManager::setDepthAssessment(const string& assessment)
{
	this->depthAssessment = assessment;
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

float AssessmentManager::getMaximumAcceptedDepth()
{
	return maximumAcceptedDepth;
}

void AssessmentManager::setMaximumAcceptedDepth(float maximumDepth)
{
	this->maximumAcceptedDepth = fabs(maximumDepth);
}

long AssessmentManager::getMaximumElapsedTime()
{
	return maximumElapsedTime;
}

void AssessmentManager::setMaximumElapsedTime(long maximumTime)
{
	this->maximumElapsedTime = maximumTime;
}

long AssessmentManager::getMinimumElapsedTime()
{
	return minimumElapsedTime;
}

void AssessmentManager::setMinimumElapsedTime(long minimumTime)
{
	this->minimumElapsedTime = minimumTime;
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

const string& AssessmentManager::getTimeAssessment()
{
	return timeAssessment;
}

void AssessmentManager::setTimeAssessment(const string& assessment)
{
	this->timeAssessment = assessment;
}

const string& AssessmentManager::getTrajectoryAssessment()
{
	return trajectoryAssessment;
}

void AssessmentManager::setStringAssessment(const string& assessment)
{
	this->trajectoryAssessment = assessment;
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
	for (auto antisseptic : correctAntissepticChoices) {
		if (chosenAntisseptic.compare(antisseptic) == 0) {
			antissepticChoiceAssessment = "Antissepctico escolhido corretamente.";
			return;
		}
	}
	antissepticChoiceAssessment = "Antissepctico escolhido incorretamente.";		
}

void AssessmentManager::assessDepth(vector<float> depths)
{
	bool badDepth = false;
	for (float d : depths) {
		if (d > maximumAcceptedDepth)
			badDepth = true;
	}

	if (badDepth)
		depthAssessment = "O corte excedeu a profundidade máxima adequada.";
	else
		depthAssessment = "O corte foi feito com profundidade adequada.";
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
	for (auto scalpel : correctScalpelChoices) {
		if (chosenAntisseptic.compare(scalpel) == 0) {
			scalpelChoiceAssessment = "Bisturi escolhido corretamente.";
			return;
		}
	}
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

void AssessmentManager::assessTime(long elapsedTime)
{
	if (elapsedTime < minimumElapsedTime)
		timeAssessment = "O corte foi realizado muito rapidamente.";
	else if (elapsedTime > maximumElapsedTime)
		timeAssessment = "O corte foi realizado muito lentamente.";
	else
		timeAssessment = "O corte foi realizado em tempo adequado.";
}

void AssessmentManager::asssesTrajectory(CollisionPath& path)
{
	vector<vec3>& points = path.getCollisionPoints();
	bool goodDirection = true;
	if (points.size() > 2) {
		vec3 firstVector = glm::normalize(points[1] - points[0]);
		for (unsigned int i = 1; i < points.size() - 1; ++i) {
			vec3 secondVector = glm::normalize(points[i + 1] - points[i]);
			float cosine = glm::dot(firstVector, secondVector);
			if (cosine < std::cos(PI / 6.0f))
				goodDirection = false;
		}
	}

	if (goodDirection) {
		trajectoryAssessment = string("O corte foi realizado sem desvios ") +
			string("significativos em sua trajetoria.");
	}
	else {
		trajectoryAssessment = string("Houve desvio(s) significativos ") +
			string("na trajetória do corte.");
	}

	//A PARTE DA SVM ENTRA AQUI.
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