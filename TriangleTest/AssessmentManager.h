#pragma once

#include "Chart.h"

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
	const string& getAntissepticChoiceAssessment();
	void setAntissepticChoiceAssessment(const string& assessment);

	const Chart* getChart();
	void setChart(const Chart* chart);

	const string& getChosenAntisseptic();
	void setChosenAntisseptic(const string& antisseptic);

	const string& getChosenScalpel();
	void setChosenScalpel(const string& scalpel);

	const string& getScalpelChoiceAssessment();
	void setScalpelChoiceAssessment(const string& assessment);

	const string& getTreatmentAssessment();
	void setTreatmentAssessment(const string& treatmentAssessment);

	TreatmentType getTreatmentType();
	void setTreatmentType(TreatmentType type);	

	//Main assessment function
	void assess();

private:
	const Chart* chart;
	TreatmentType treatmentType;
	string treatmentAssessment;
	string chosenScalpel;
	string scalpelChoiceAssessment;
	string chosenAntisseptic;
	string antissepticChoiceAssessment;

	//Helper functions
	void assessAntissepticChoice();
	void assessScalpelChoice();
	void assessTreatmentType();
};

