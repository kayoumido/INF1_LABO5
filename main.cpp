/* ---------------------------
 Laboratoire : 5
 Fichier : main.cpp
 Auteur(s) :
 Date : 14.11.2018
 But :

 Remarque(s) :
 Compilateur : g++ 6.3.0
 --------------------------- */

#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

const unsigned NUMBER_DAYS_IN_WEEK = 7;
const unsigned SEPARATOR_SIZE = 3;
const char DISPLAY_FILL = ' ';

enum Months { JANUARY, FEBRURARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
enum Days { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

/**
 * Display the calendar for a given month
 *
 * @return void
 */
unsigned displayCalendar(unsigned month, unsigned firstDayOfMonth, unsigned mondayPosition, unsigned year, unsigned width);

/**
 * Determines if a given year is a leap year
 * If the year is divisible by 4 and not divisible by 100, then it's a leap year
 * If the year is divisible by 400, then it's a leap year
 *	(all divisions are integer divisions)
 *
 * All the other cases, it's a common year
 *
 * @param year unsigned the year which will be checked
 * @return bool is or isn't a leap year
 */
bool isLeapYear(unsigned year);

/**
 * Determines the day of the week of the 1st of January of any given year
 * Source of the calculation (Method 2):
 * https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
 *
 * @param year unsigned the year of which the 1st January day will be determined
 * @return unsigned day of the week matching the criteria (e.g. 1 = Lundi, 2 = Mardi, ..., 7 = Dimanche [1-7])
 */
unsigned dayOf1stJan(unsigned year);

/**
 * Get the initial of a day based on it's number
 *  e.g. 2 (Mardi) --> M
 *
 * @param day int the day number (0-6)
 * @return string day
 */
string getDayInitial(unsigned day);

/**
 * Get the name of a month based on it's number
 *  e.g 8 --> Aout
 *
 * @param month int Month number
 * @return string month name
 */
string getMonthName(unsigned month);

/**
 *
 * @param year
 * @param month
 * @return
 */
unsigned getMonthLength(unsigned year, unsigned month);

/**
  * Ask and validates user data
  *
  * @param question string question to ask the user
  * @param errorMessage string error message to display if the user enters non valid value
  * @param MIN_VALUE int min value for the expected value
  * @param MAX_VALUE int max value for the expected value
  * @return int value Validated user input
  */
unsigned checkUserInput(const string& question, const string& errorMessage, unsigned MIN_VALUE, unsigned MAX_VALUE);

/**
 * Displays an empty line
 *
 * @return void
 */
void displayEmptyLine(unsigned colWidth);

/**
 *
 * @param text string
 */
void displayCenteredText(const string& text, unsigned colWidth);

/**
 *
 * @return void
 */
void cleanStream();

int main() {
	const unsigned MIN_YEAR = 1600;
	const unsigned MAX_YEAR = 3000;
	const unsigned MIN_DAY = 1;
	const unsigned MAX_DAY = 7;
  const unsigned CALENDAR_WIDTH = 21;
	const string YEAR_QUESTION = "Quelle annee voulez-vous afficher? (1600-3000) ";
	const string DAY_QUESTION = "Quel jour de la semaine est le lundi? (1-7) ";
	const string ERROR_MSG = "Entree non valide";

  unsigned year = 0;
  unsigned mondayPosition = 0;

	// set the default fill
	cout << setfill(DISPLAY_FILL);

	// Obtain and check user input values for the year and the position of the Monday
	year = checkUserInput(YEAR_QUESTION, ERROR_MSG, MIN_YEAR, MAX_YEAR);
	mondayPosition = checkUserInput(DAY_QUESTION, ERROR_MSG, MIN_DAY, MAX_DAY);

	// Convert the year from unsigned to string and display it
	stringstream ssIntToString;
	ssIntToString << year;
	string yearStr;
	ssIntToString >> yearStr;

	cout << endl;
	displayCenteredText(yearStr, CALENDAR_WIDTH);

	// Display the entire calendar based on the user input
  unsigned firstDayOfMonth = dayOf1stJan(year);
	for (unsigned i = 0; i < 12; ++i)
		firstDayOfMonth = displayCalendar(i, firstDayOfMonth, mondayPosition, year, CALENDAR_WIDTH);

	// For Visual Studio : pause the console 
	//system("Pause");

	return 0;
}

unsigned displayCalendar(unsigned month, unsigned firstDayOfMonth, unsigned mondayPosition, unsigned year, unsigned width) {
	unsigned nbDays = getMonthLength(year, month);

	displayEmptyLine(width);
	displayCenteredText(getMonthName(month), width);

  unsigned firstDayOfWeek = NUMBER_DAYS_IN_WEEK - (mondayPosition - 1);
  unsigned i = firstDayOfWeek;
	// Displays the intial letter of the weekday
	do {
		if (i == NUMBER_DAYS_IN_WEEK or (i > 6 and firstDayOfWeek != NUMBER_DAYS_IN_WEEK)) i = 0;

		cout << setw(SEPARATOR_SIZE) << getDayInitial(i);
		i++;
	} while (i != firstDayOfWeek);
	cout << endl;

  unsigned firstDayMondayPositionDiff = (firstDayOfMonth - 1) + (mondayPosition - 1);
  unsigned firstDayMonthPosition = firstDayMondayPositionDiff > NUMBER_DAYS_IN_WEEK - 1 ?
		firstDayMondayPositionDiff - NUMBER_DAYS_IN_WEEK
		: firstDayMondayPositionDiff;

	for (size_t p = 0; p < firstDayMonthPosition; ++p) {
		cout << setw(SEPARATOR_SIZE) << DISPLAY_FILL;
	}

  unsigned dayMonthPosition = firstDayMonthPosition;
	for (unsigned date = 1; date <= nbDays; ++date) {
		// If we are at the end of the week, pass to the next line, i.e. the next week.
		if (dayMonthPosition == NUMBER_DAYS_IN_WEEK) {
			cout << endl;
			dayMonthPosition = 0;
		}

		cout << setw(SEPARATOR_SIZE) << date;

		// If it's the last day of the month and it's not a Sunday, fill the end of the line with DISPLAY_FILL
		if (date == nbDays and dayMonthPosition != NUMBER_DAYS_IN_WEEK - 1) {
			cout << setw(width - (dayMonthPosition * SEPARATOR_SIZE) - SEPARATOR_SIZE) << DISPLAY_FILL;
		}

		++dayMonthPosition;
	}

	cout << endl;

	return ++dayMonthPosition - (mondayPosition - 1);
}

string getDayInitial(unsigned day) {
	switch (day) {
    case Days::MONDAY: return "L";
    case Days::TUESDAY: return "M";
    case Days::WEDNESDAY: return "M";
    case Days::THURSDAY: return "J";
    case Days::FRIDAY: return "V";
    case Days::SATURDAY: return "S";
    case Days::SUNDAY: return "D";
    default: return "!";
	}
}

string getMonthName(unsigned month) {
	switch (month) {
    case Months::JANUARY: return "Janvier";
    case Months::FEBRURARY: return "Fevrier";
    case Months::MARCH: return "Mars";
    case Months::APRIL: return "Avril";
    case Months::MAY: return "Mai";
    case Months::JUNE: return "Juin";
    case Months::JULY: return "Juillet";
    case Months::AUGUST: return "Aout";
    case Months::SEPTEMBER: return "Septembre";
    case Months::OCTOBER: return "Octobre";
    case Months::NOVEMBER: return "Novembre";
    case Months::DECEMBER: return "Decembre";
    default: return "ERROR";
	}
}

void displayCenteredText(const string& text, const unsigned colWidth) {
	cout << setw(colWidth / 2 - (int)text.length() / 2) << DISPLAY_FILL;
	cout << setw((int)text.length()) << text;
	cout << setw(colWidth - (colWidth / 2 - (int)text.length() / 2) - (int)text.length()) << DISPLAY_FILL << endl;
}

void displayEmptyLine(const unsigned colWidth) {
  cout << setw(colWidth) << "" << endl;
}

bool isLeapYear(unsigned year) {
	// is a leap year (366 days)
  return ((year % 4 == 0) && (year % 100) != 0) || year % 400 == 0;
}

unsigned dayOf1stJan(unsigned year) {
	unsigned day = 1;
	unsigned month = 1;

	unsigned c = (14 - month) / 12;
	unsigned a = year - c;
  unsigned m = month + 12 * c - 2;

	unsigned january1st = (day + a + a / 4 - a / 100 + a / 400 + (31 * m) / 12) % 7;
	return january1st == 0 ? NUMBER_DAYS_IN_WEEK : january1st;
}

unsigned checkUserInput(const string& question, const string& errorMessage,
        const unsigned MIN_VALUE, const unsigned MAX_VALUE) {
	bool inputError;
	string rawInput;
	unsigned value;

	do {
		inputError = false;
		rawInput = "";

		cout << question;
		cin >> rawInput;

		if (rawInput.length() != (int)(log10(MIN_VALUE) + 1)) {
			inputError = true;
			continue;
		}

		cleanStream();
		stringstream ssInput(rawInput);

		if (ssInput >> value) {
			if (value < MIN_VALUE or value > MAX_VALUE) {
				inputError = true;
				continue;
			}
		}
		else {
			inputError = true;
			continue;
		}

	} while (inputError and cout << errorMessage << endl);

	return value;
}

void cleanStream() {
	cin.clear();
	cin.ignore(numeric_limits<int>::max(), '\n');
}

unsigned getMonthLength(unsigned year, unsigned month) {

  switch(month) {
    case Months::JANUARY:
    case Months::MARCH:
    case Months::MAY:
    case Months::JULY:
    case Months::AUGUST:
    case Months::OCTOBER:
    case Months::DECEMBER: return 31;

    case Months::APRIL:
    case Months::JUNE:
    case Months::SEPTEMBER:
    case Months::NOVEMBER: return 30;

    case Months::FEBRURARY: return isLeapYear(year) ? 29 : 28;
    default: return 0;
  }
}
