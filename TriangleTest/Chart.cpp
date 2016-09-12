#include "Chart.h"
#include <ctime>
#include <random>
#include <sstream>

using std::stringstream;

Chart::Chart(ChartType type)
	: type(type), clinic("Cirurgia Bucomaxilar"),
	  patientName("John Doe")
{
	setup();
}


Chart::~Chart()
{
}

ChartType Chart::getChartType() const
{
	return type;
}

void Chart::setChartType(ChartType type)
{
	this->type = type;
}

const string& Chart::getPatientName()
{
	return patientName;
}

void Chart::setPatientName(const string& name)
{
	this->patientName = name;
}

const string& Chart::getChartNumber()
{
	return chartNumber;
}

void Chart::setChartNumber(const string& chartNumber)
{
	this->chartNumber = chartNumber;
}

const string& Chart::getDate()
{
	return date;
}

void Chart::setDate(const string& date)
{
	this->date = date;
}

const string& Chart::getClinic()
{
	return clinic;
}

void Chart::setClinic(const string& clinic)
{
	this->clinic = clinic;
}

const string& Chart::getPatientHistory()
{
	return patientHistory;
}

void Chart::setPatientHistory(const string& patientHistory)
{
	this->patientHistory = patientHistory;
}

void Chart::setup()
{
	//Chart number
	std::default_random_engine engine;
	std::uniform_int_distribution<int> dist(10000, 99999);
	stringstream ss;
	ss << dist(engine);
	chartNumber = ss.str();

	//Date
	time_t now = time(0);
	tm* timeStruct = gmtime(&now);
	int year = 1900 + timeStruct->tm_year;
	int month = timeStruct->tm_mon + 1;
	int day = timeStruct->tm_mday;
	stringstream dateStream;
	dateStream << day << "/" << month << "/" << year;
	date = dateStream.str();
}
