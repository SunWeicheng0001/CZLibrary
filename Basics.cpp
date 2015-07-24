#include "Basics.h"
namespace cz{
	/************************************************************************
	NonCopyable
	************************************************************************/
	NonCopyable::NonCopyable(){}
	NonCopyable::NonCopyable(const NonCopyable&){}
	NonCopyable& NonCopyable::operator=(const NonCopyable&){ return *this; }

	/************************************************************************
	Error
	************************************************************************/
	Error::Error(std::string _description){description = _description;}
	std::string Error::Description()const{return description;}

	/************************************************************************
	Object
	************************************************************************/
	Object::~Object(){}

	/************************************************************************
	DateTime
	************************************************************************/
	DateTime SystemTimeToDateTime(const SYSTEMTIME& systemTime){
		DateTime dateTime;
		dateTime.year = systemTime.wYear;
		dateTime.month = systemTime.wMonth;
		dateTime.dayOfweek = systemTime.wDayOfWeek;
		dateTime.day = systemTime.wDay;
		dateTime.hour = systemTime.wHour;
		dateTime.minute = systemTime.wMinute;
		dateTime.second = systemTime.wSecond;
		dateTime.milliseconds = systemTime.wMilliseconds;

		FILETIME fileTime;
		SystemTimeToFileTime(&systemTime, &fileTime);
		ULARGE_INTEGER largeInteger;
		largeInteger.HighPart = fileTime.dwHighDateTime;
		largeInteger.LowPart = fileTime.dwLowDateTime;
		dateTime.filetime = largeInteger.QuadPart;
		dateTime.totalMilliseconds = dateTime.filetime / 10000;

		return dateTime;
	}

	SYSTEMTIME DateTimeToSystemTime(const DateTime& dateTime){
		ULARGE_INTEGER largeInteger;
		largeInteger.QuadPart = dateTime.filetime;
		FILETIME fileTime;
		fileTime.dwHighDateTime = largeInteger.HighPart;
		fileTime.dwLowDateTime = largeInteger.LowPart;

		SYSTEMTIME systemTime;
		FileTimeToSystemTime(&fileTime, &systemTime);
		return systemTime;
	}

	DateTime DateTime::LocalTime()
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		return SystemTimeToDateTime(systemTime);
	}

	DateTime DateTime::UtcTime()
	{
		SYSTEMTIME utcTime;
		GetSystemTime(&utcTime);
		return SystemTimeToDateTime(utcTime);
	}

	DateTime DateTime::ToLocalTime()
	{
		SYSTEMTIME utcTime = DateTimeToSystemTime(*this);
		SYSTEMTIME localTime;
		SystemTimeToTzSpecificLocalTime(NULL, &utcTime, &localTime);
		return SystemTimeToDateTime(localTime);
	}

	DateTime DateTime::ToUtcTime()
	{
		SYSTEMTIME localTime = DateTimeToSystemTime(*this);
		SYSTEMTIME utcTime;
		TzSpecificLocalTimeToSystemTime(NULL, &localTime, &utcTime);
		return SystemTimeToDateTime(utcTime);
	}

	/***********************************************************************
	Interface
	***********************************************************************/

	Interface::~Interface(){}
}