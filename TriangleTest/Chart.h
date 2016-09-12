#pragma once

#include <string>

using std::string;

//This enum will indicate the possible types of charts that can be created.
//PATIENT_READY is a chart for patients that are ready for surgery.
//PATIENT_NOT_READY is a chart for patients not ready for surgery because
// of exposed or non-scarred injuries.
//SCARRING_PROBLEM is a chart for a patient with a scarring issue of some
// nature that makes the submental incision inappropriate.
enum ChartType{
	PATIENT_READY,
	PATIENT_NOT_READY,
	SCARRING_PROBLEM
};

class Chart
{
public:
	Chart(ChartType type = PATIENT_READY);
	~Chart();

	//Getters and setter
	ChartType getChartType() const;
	void setChartType(ChartType type);

	const string& getPatientName();
	void setPatientName(const string& name);

	const string& getChartNumber();
	void setChartNumber(const string& chartNumber);

	const string& getDate();
	void setDate(const string& date);

	const string& getClinic();
	void setClinic(const string& clinic);

	const string& getPatientHistory();
	void setPatientHistory(const string& patientHistory);

private:
	//Function hat generater chart number, date and patientHistory.
	void setup();

	ChartType type;
	string patientName;
	string chartNumber;
	string date;
	string clinic;
	string patientHistory;
};

