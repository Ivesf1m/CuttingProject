#pragma once

#include "Chart.h"
#include "CollisionPath.h"
#include <glm.hpp>
#include <vector>

using glm::vec3;
using std::vector;

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

	void addAntissepticChoice(const string& choice);
	const vector<string>& getCorrectAntissepticChoices();
	void setCorrectAntissepticChoices(const vector<string>& choices);

	void addScalpelChoice(const string& choice);
	const vector<string>& getCorrectScalpelChoices();
	void setCorrectScalpelChoices(const vector<string>& choices);

	const string& getDepthAssessment();
	void setDepthAssessment(const string& assessment);

	const string& getEndPointAssessment();
	void setEndPointAssessment(const string& assessment);

	const vec3& getIdealEndPoint();
	void setIdealEndPoint(const vec3& endPoint);

	const vec3& getIdealStartPoint();
	void setIdealStartPoint(const vec3& startPoint);

	float getMaximumAcceptedDepth();
	void setMaximumAcceptedDepth(float maximumDepth);

	long getMaximumElapsedTime();
	void setMaximumElapsedTime(long maximumTime);

	long getMinimumElapsedTime();
	void setMinimumElapsedTime(long minimumTime);

	float getOptimalRadius();
	void setOptimalRadius(float optimalRadius);

	const string& getScalpelChoiceAssessment();
	void setScalpelChoiceAssessment(const string& assessment);

	const string& getStartPointAssessment();
	void setStartPointAssessment(const string& assessment);

	const string& getTimeAssessment();
	void setTimeAssessment(const string& assessment);

	const string& getTrajectoryAssessment();
	void setStringAssessment(const string& assessment);

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
	vector<string> correctScalpelChoices;
	string chosenAntisseptic;
	string antissepticChoiceAssessment;
	vector<string> correctAntissepticChoices;
	string startPointAssessment;
	string endPointAssessment;
	string depthAssessment;
	string trajectoryAssessment;
	string timeAssessment;

	//Surgical traits
	vec3 idealStartPoint;
	vec3 idealEndPoint;
	float optimalRadius;
	float acceptableRadius;
	float maximumAcceptedDepth;
	long minimumElapsedTime;
	long maximumElapsedTime;

	//Helper functions
	void assessAntissepticChoice();
	void assessDepth(vector<float> depths);
	void assessEndPoint(const vec3& endPoint);
	void assessScalpelChoice();
	void assessStartPoint(const vec3& startPoint);
	void assessTime(long elapsedTime);
	void asssesTrajectory(CollisionPath& path);
	void assessTreatmentType();
};

