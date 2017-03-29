#include <fstream>
#include "utils.cpp"

using namespace std;

#ifndef STRUCT_CPP
#define STRUCT_CPP 

//Contains definitions for custom structures 'Date', 'Time' and 'Flight'.

//Definition for 'Date' structure containing int month, day and year.
struct Date {
public:
	int month;
	int day;
	int year;
	
	//Takes string 'mm/dd/yyyy' as argument and generates date.
	static Date parse(string input) {
		Date date;
		vector<string> buff = split(input, '/');
		if (buff.size() != 3) return date;
		date.month = atoi(buff[0].data());
		date.day = atoi(buff[1].data());
		date.year = atoi(buff[2].data());

		return date;
	};

	Date() {
	month = 0;
	day = 0;
	year = 0;
	}

	//Does exactly the same thing as Date::parse, but doesn't check if input has valid format.
	Date(string input) {
		vector<string> buff = split(input, '/');
		month = atoi(buff[0].data());
		day = atoi(buff[1].data());
		year = atoi(buff[2].data());
	}

	Date& operator=(const Date &date) {
		month = date.month;
		day = date.day;
		year = date.year;

		return *this;
	}
};

inline bool operator<(const Date &left, const Date &right) {
	return ((left.year < right.year) ||
		   ((left.year == right.year) && (left.month < right.month)) ||
		   ((left.year == right.year) && (left.month == right.month) && (left.day < right.day)));
}

inline bool operator>(const Date &left, const Date &right) {
	return (right < left);
}

inline bool operator<=(const Date &left, const Date &right) {
	return (!(left > right));
}

inline bool operator>=(const Date &left, const Date &right) {
	return (!(left < right));
}

inline bool operator==(const Date &left, const Date &right) {
	return (left.month == right.month) && (left.day == right.day) && (left.year == right.year);
}

inline bool operator!=(const Date &left, const Date &right) {
	return !(left==right);
}

ostream& operator<<(ostream &os,const Date &date) {

	if (date.month < 10) os << '0' << date.month;
	else os << date.month;

	os << '/';

	if (date.day < 10) os << '0' << date.day;
	else os << date.day;

	os << '/' << date.year;

	return os;
}

//Takes Date from istream and returns it if it is valid. Otherwise sets failbit for istream.
istream& operator>>(istream &is, Date &date) {
	string input;
	is >> input;
	is.ignore();
	Date temp;

	if ((input.length() >= 5) &&
	    (input.length() <= 10) &&
	   ((input[1] == '/') || (input[2] == '/')) &&
	   ((input[3] == '/') || (input[5] == '/'))) {

		temp = Date::parse(input);
		if (((date.month == 2) && (date.day > 29)) || (date.month > 12) || (date.day > 31))
		   is.setstate(std::ios::failbit);

		else date = temp;
	}
	else is.setstate(std::ios::failbit);

	return is;
}

//Definition for 'Time' structure containing int hour and minute.
struct Time {
public:
	unsigned int hour;
	unsigned int minute;

	//Takes string 'hh:mm' as argument and generates Time.
	static Time parse(string input) {
		Time time;
		vector<string> buff = split(input, ':');
		if (buff.size() != 2) return time;
		time.hour = atoi(buff[0].data());
		time.minute = atoi(buff[1].data());

		return time;
	};

	Time() {
		hour = 25;
		minute = 0;
	}

	//Does exactly the same thing as Time::parse, but doesn't check if input has valid format.
	Time(string input) {
		vector<string> buff = split(input, ':');
		hour = atoi(buff[0].data());
		minute = atoi(buff[1].data());
	}

	Time& operator=(const Time &time) {
		hour = time.hour;
		minute = time.minute;

		return *this;
	}
};

ostream& operator<<(ostream &os,const Time &time) {

	if (time.hour < 10) os << '0' << time.hour;
	else os << time.hour;

	os << ':';

	if (time.minute < 10) os << '0' << time.minute;
	else os << time.minute;

	return os;
}

//Takes Time from istream and returns it if it is valid. Otherwise sets failbit for istream.
istream& operator>>(istream &is, Time &time) {
	string input;
	is >> input;
	is.ignore();
	Time temp;
	if ((input.length() >= 3) && (input.length() <= 5) &&
	   ((input.find(':') == 1) || (input.find(':') == 2))) {

		temp = Time::parse(input);

		if ((temp.hour < 24) && (temp.minute < 60)) time = temp;
		else is.setstate(std::ios::failbit);
	}

	else is.setstate(std::ios::failbit);

	return is;
}

//Defines structure 'Flight'.
struct Flight {
public:
	string destination;
	Date date;
	string day;
	string id;
	Time flight_time;
	Time arrival_time;
	vector <string> passengers;

	static Flight parse(string input) {
		Flight flight;

		vector<string> buff = split(input,'|');

		flight.destination = buff[0];
		flight.date = Date::parse(buff[1]);
		flight.day = buff[2];
		flight.id = buff[3];
		flight.flight_time = Time::parse(buff[4]);
		flight.arrival_time = Time::parse(buff[5]);

		for (int i = 6; i != buff.size(); ++i) flight.passengers.push_back(buff[i]);

		return flight;
	}
};

ostream& operator<<(ostream &os,const Flight &flight) {
	char tab = '\t';

	os << flight.destination << tab << flight.date << tab << flight.day << tab << flight.id << tab << flight.flight_time << tab << flight.arrival_time << endl;

	for (int i = 0; i != flight.passengers.size(); ++i) 
			os << tab << flight.passengers[i] << endl;
	
	os << endl;
	return os;
}

#endif