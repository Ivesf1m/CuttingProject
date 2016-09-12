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
	const Chart* getChart();
	void setChart(const Chart* chart);

	const string& getTreatmentAssessment();
	void setTreatmentAssessment(const string& treatmentAssessment);

	TreatmentType getTreatmentType();
	void setTreatmentType(TreatmentType type);

	void assess();

private:
	const Chart* chart;
	TreatmentType treatmentType;
	string treatmentAssessment;

	//Helper functions
	void assessTreatmentType();
};

