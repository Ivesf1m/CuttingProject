#pragma once

#include "Chart.h"
#include <glm.hpp>

using glm::vec3;

enum TreatmentType {
	SUBMENTAL_INCISION,
	DIFFERENT_INCISION,
	NO_SURGERY,
	INVALID_TREATMENT_TYPE
};

class AssessmentManager
{
public:
	AssessmentManager();
	~AssessmentManager();

	//Getters and setters
	float getAcceptableRadius();
	void setAcceptableRadius(float acceptableRadius);
	
	const string& getAntissepticChoiceAssessment();
	void setAntissepticChoiceAssessment(const string& assessment);

	const Chart* getChart();
	void setChart(const Chart* chart);

	const string& getChosenAntisseptic();
	void setChosenAntisseptic(const string& antisseptic);

	const string& getChosenScalpel();
	void setChosenScalpel(const string& scalpel);

	const string& getEndPointAssessment();
	void setEndPointAssessment(const string& assessment);

	const vec3& getIdealEndPoint();
	void setIdealEndPoint(const vec3& endPoint);

	const vec3& getIdealStartPoint();
	void setIdealStartPoint(const vec3& startPoint);

	float getOptimalRadius();
	void setOptimalRadius(float optimalRadius);

	const string& getScalpelChoiceAssessment();
	void setScalpelChoiceAssessment(const string& assessment);

	const string& getStartPointAssessment();
	void setStartPointAssessment(const string& assessment);

	const string& getTreatmentAssessment();
	void setTreatmentAssessment(const string& treatmentAssessment);

	TreatmentType getTreatmentType();
	void setTreatmentType(TreatmentType type);	

	//Main assessment function
	void assess();

private:
	//Pre-surgical traits.
	const Chart* chart;
	TreatmentType treatmentType;
	string treatmentAssessment;
	string chosenScalpel;
	string scalpelChoiceAssessment;
	string chosenAntisseptic;
	string antissepticChoiceAssessment;
	string startPointAssessment;
	string endPointAssessment;

	//Surgical traits
	vec3 idealStartPoint;
	vec3 idealEndPoint;
	float optimalRadius;
	float acceptableRadius;

	//Helper functions
	void assessAntissepticChoice();
	void assessEndPoint(const vec3& endPoint);
	void assessScalpelChoice();
	void assessStartPoint(const vec3& startPoint);
	void assessTreatmentType();
};

