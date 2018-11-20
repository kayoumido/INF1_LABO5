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

const unsigned CALENDAR_WIDTH = 21;
const unsigned NUMBER_DAYS_IN_WEEK = 7;
const unsigned SEPARATOR_SIZE = 3;
const char DISPLAY_FILL = '.';

/**
 * Display the calendar for a given month
 *
 * @return void
 */
int displayCalendar(int month, int firstDayOfMonth, int mondayPosition);

/**
 * Determines if a given year is a leap year
 *
 * @param year unsigned the year which will be checked
 * @return unsigned number of days in the given year (365 or 366)
 */
unsigned isLeapYear(unsigned year);

/**
 * Determines the day of the week of the 1st of January of any given year
 * Source of the calculation (Method 2): 
 * https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
 *
 * @param year unsigned the year of which the 1st January day will be determined
 * @return unsigned day of the week matching the criteria (e.g. 0 = Dimanche, 1 = Lundi, 2 = Mardi, etc... [0-6])
 */
unsigned dayOf1stJan(unsigned year);

/**
 * Get the initial of a day based on it's number
 *  e.g. 2 (Mardi) --> M
 *
 * @param day int the day number (0-6)
 * @return string day
 */
string getDayInitial(int day);

/**
 * Get the name of a month based on it's number
 *  e.g 8 --> Aout
 *
 * @param month int Month number
 * @return string month name
 */
string getMonthName(int month);

/**
  * Ask and validates user data
  *
  * @param question string question to ask the user
  * @param errorMessage string error message to display if the user enters non valid value
  * @param MIN_VALUE int min value for the expected value
  * @param MAX_VALUE int max value for the expected value
  * @return int value Validated user input
  */
int checkUserInput(string question, string errorMessage, const int MIN_VALUE, const int MAX_VALUE);

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
void displayCenteredText(string text, unsigned colWidth);

/**
 *
 * @param ss
 * @return void
 */
void cleanStream();

int main() {
	const int MIN_YEAR = 1600;
	const int MAX_YEAR = 3000;
	const int MIN_DAY = 1;
	const int MAX_DAY = 7;
	const string YEAR_QUESTION = "Quelle annee voulez-vous afficher? (1600-3000) ";
	const string DAY_QUESTION = "Quel jour de la semaine est le lundi? (1-7) ";
	const string ERROR_MSG = "Entree non valide";

	int year = 0;
	int mondayPosition = 0;

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
  displayCenteredText(yearStr, CALENDAR_WIDTH);

	// Display the entire calendar based on the user input
	int firstDayOfMonth = dayOf1stJan(year);
	for (int i = 0; i < 12; ++i)
    firstDayOfMonth = displayCalendar(i, firstDayOfMonth, mondayPosition);

	// For Visual Studio : pause the console 
	//system("Pause");

	return 0;
}

int displayCalendar(int month, int firstDayOfMonth, int mondayPosition) {
	string name = getMonthName(month);
	int nbDays = 31;

	displayEmptyLine(CALENDAR_WIDTH);
	displayCenteredText(name, CALENDAR_WIDTH);

	int firstDayOfWeek = NUMBER_DAYS_IN_WEEK - (mondayPosition - 1);
	int i = firstDayOfWeek;
	do {
		if (i == NUMBER_DAYS_IN_WEEK or (i > 6 and firstDayOfWeek != NUMBER_DAYS_IN_WEEK)) i = 0;

		cout << setw(SEPARATOR_SIZE) << getDayInitial(i);
		i++;
	} while (i != firstDayOfWeek);
	cout << endl;

	int firstDayMondayPositionDiff = (firstDayOfMonth - 1) + (mondayPosition - 1);
	int firstDayMonthPosition = firstDayMondayPositionDiff > NUMBER_DAYS_IN_WEEK - 1 ?
		firstDayMondayPositionDiff - NUMBER_DAYS_IN_WEEK
		: firstDayMondayPositionDiff;

	for (int p = 0; p < firstDayMonthPosition; ++p) {
		cout << setw(SEPARATOR_SIZE) << DISPLAY_FILL;
	}

	int dayMonthPosition = firstDayMonthPosition;
	for (int date = 1; date <= nbDays; ++date) {
		// If we are at the end of the week, pass to the next line, i.e. the next week.
		if (dayMonthPosition == NUMBER_DAYS_IN_WEEK) {
			cout << endl;
			dayMonthPosition = 0;
		}

		cout << setw(SEPARATOR_SIZE) << date;

		// If it's the last day of the month and it's not a Sunday, fill the end of the line with DISPLAY_FILL
		if (date == nbDays and dayMonthPosition != NUMBER_DAYS_IN_WEEK - 1) {
			cout << setw(CALENDAR_WIDTH - (dayMonthPosition * SEPARATOR_SIZE) - SEPARATOR_SIZE) << DISPLAY_FILL;
		}

		++dayMonthPosition;
	}
	cout << endl;

	return ++dayMonthPosition - (mondayPosition - 1);
}

string getDayInitial(int day) {
	switch (day) {
    case 0: return "L";
    case 1:
    case 2: return "M";
    case 3: return "J";
    case 4: return "V";
    case 5: return "S";
    case 6: return "D";
	}
}

string getMonthName(int month) {
	switch (month) {
    case 0: return "Janvier";
    case 1: return "Fevrier";
    case 2: return "Mars";
    case 3: return "Avril";
    case 4: return "Mai";
    case 5: return "Juin";
    case 6: return "Juillet";
    case 7: return "Aout";
    case 8: return "Septembre";
    case 9: return "Octobre";
    case 10: return "Novembre";
    case 11: return "Decembre";
	}
}

void displayCenteredText(const string text, const unsigned colWidth) {
	cout << setw(colWidth / 2 - (int)text.length() / 2) << DISPLAY_FILL;
	cout << setw((int)text.length()) << text;
	cout << setw(colWidth - (colWidth / 2 - (int)text.length() / 2) - (int)text.length()) << DISPLAY_FILL << endl;
}

void displayEmptyLine(const unsigned colWidth) {
  displayCenteredText("", colWidth);
}

unsigned isLeapYear(unsigned year) {
	const unsigned LEAP_YEAR_DAYS = 366;
	const unsigned NORMAL_YEAR_DAYS = 365;

	// is a leap year (366 days)
	if (((year % 4 == 0) && (year % 100) != 0) || year % 400 == 0)
		return LEAP_YEAR_DAYS;
	else // is a normal year (365 days)
		return NORMAL_YEAR_DAYS;
}

unsigned dayOf1stJan(unsigned year) {
	unsigned day = 1;
	unsigned month = 1;

	int c = (14 - month) / 12;
	int a = year - c;
	int m = month + 12 * c - 2;

	int january1st = (day + a + a / 4 - a / 100 + a / 400 + (31 * m) / 12) % 7;
	return january1st == 0 ? NUMBER_DAYS_IN_WEEK : january1st;
}

int checkUserInput(string question, string errorMessage, const int MIN_VALUE, const int MAX_VALUE) {
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
