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
			wstring(L"que resultou em lacera��es faciais e fratura na regi�o ") +
			wstring(L"da s�nfise mandibular. Os ferimentos superficiais foram ") +
			wstring(L"tratados na chegada do paciente ao local de atendimento, ") +
			wstring(L"se encontram todos em bom estado e com aspecto dentro do") +
			wstring(L"padr�o esperado para este tipo de les�o. ") +
			wstring(L"O paciente n�o apresenta hist�rico de ") + 
			wstring(L"doen�as card�acas, diabetes ou outros agravos que ") +
			wstring(L"requerem aten��o especial.");
	}
	else if (type == ChartType::PATIENT_NOT_READY) {
		patientHistory = wstring(L"O paciente sofreu um acidente de moto, que") +
			wstring(L" resultou em graves lacera��es faciais e fratura na ") + 
			wstring(L"regi�o da s�nfise mandibular. Foi realizada assepsia no local ") + 
			wstring(L"e, em seguida, feitos curativos nas feridas localizadas ") + 
			wstring(L"na face. No entanto, as feridas ainda ") +
			wstring(L"se encontram expostas e com risco consider�vel de ") + 
			wstring(L"infec��o. O paciente n�o apresenta hist�rico de doen�as ") +
			wstring(L"card�acas, diabetes ou outros agravos que requerem ") +
			wstring(L"aten��o especial.");
	}
	else if (type == ChartType::SCARRING_PROBLEM) {
		patientHistory = wstring(L"O paciente sofreu um acidente de moto, ") +
			wstring(L"que resultou em lacera��es faciais e fratura na regi�o ") +
			wstring(L"da s�nfise mandibular. Os ferimentos superficiais foram ") +
			wstring(L"tratados na chegada do paciente ao local de atendimento ") +
			wstring(L"e se encontram todos em bom estado e com aspecto dentro") +
			wstring(L"do padr�o esperado para este tipo de les�o. ") +
			wstring(L"O paciente � diab�tico e est� com sua taxa ") +
			wstring(L"de glicemia alterada.");
	}
}
