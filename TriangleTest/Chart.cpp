#include "Chart.h"
#include <chrono>
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

const wstring& Chart::getPatientHistory()
{
	return patientHistory;
}

void Chart::setPatientHistory(const wstring& patientHistory)
{
	this->patientHistory = patientHistory;
}

void Chart::setup()
{
	//Chart number
	std::default_random_engine engine;
	auto rseed = std::chrono::high_resolution_clock::now().
		time_since_epoch().count();
	engine.seed(static_cast<unsigned int>(rseed));
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

	//Patient history
	if (type == ChartType::PATIENT_READY) {
		patientHistory = wstring(L"O paciente sofreu um acidente de moto, ") +
			wstring(L"que resultou em lacerações faciais e fratura na região ") +
			wstring(L"da sínfise mandibular. Os ferimentos superficiais foram ") +
			wstring(L"tratados na chegada do paciente e se encontram todos em ") +
			wstring(L"bom estado. O paciente não apresenta histórico de ") + 
			wstring(L"doenças cardíacas, diabetes ou outras doenças que ") +
			wstring(L"requerem atenção especial.");
	}
	else if (type == ChartType::PATIENT_NOT_READY) {
		patientHistory = wstring(L"O paciente sofreu um acidente de moto, que") +
			wstring(L" resultou em graves lacerações faciais e fratura na ") + 
			wstring(L"região da sínfise mandibular. Foi realizada limpeza e ") + 
			wstring(L"foi feito curativo nas feridas na face, mas elas ainda ") +
			wstring(L"se encontram expostas e com risco considerável de ") + 
			wstring(L"infecção. O paciente não apresenta histórico de doenças ") +
			wstring(L"cardíacas, diabetes ou outras doenças que requerem ") +
			wstring(L"atenção especial.");
	}
	else if (type == ChartType::SCARRING_PROBLEM) {
		patientHistory = wstring(L"O paciente sofreu um acidente de moto, ") +
			wstring(L"que resultou em lacerações faciais e fratura na região ") +
			wstring(L"da sínfise mandibular. Os ferimentos superficiais foram ") +
			wstring(L"tratados na chegada do paciente e se encontram todos em ") +
			wstring(L"bom estado. O paciente é diabético e está com sua taxa ") +
			wstring(L"de glicemia alterada.");
	}
}
