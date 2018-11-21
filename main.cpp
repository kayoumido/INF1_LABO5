/* ---------------------------
 Laboratoire : 5 - Calendrier
 Fichier : main.cpp
 Auteur(s) : Kayoumi Doran, Bonzon Ludovic et Geleta Fekadu
 Date : 14.11.2018
 But : Afficher dans la console le calendrier d'une année donnée par l'utilisateur (1600-3000)
	   et permettant de pouvoir choisir la position du lundi dans l'ordre des 7 jours de la semaine (1-7)

 Remarque(s) :
 Compilateur : g++ 6.3.0
 --------------------------- */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

const unsigned NUMBER_DAYS_IN_WEEK = 7;
const char DISPLAY_FILL = ' ';
enum Months { JANUARY, FEBRURARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
enum Days { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

/**
 * @brief Display the calendar for a given year
 *
 * @param month	unsigned Month number [0-11]
 * @param firstDayOfMonth unsigned First day of a given month
 * @param mondayPosition unsigned Position of the Monday in the header [1-7]
 * @param year unsigned Year to display [1600-3000]
 * @param WIDTH	unsigned Calendar display width
 * @param COL_WIDTH	unsigned Calendar columns width
 *
 * @return unsigned Position of the next 1st of the month
 */
unsigned displayCalendar(
	unsigned month,
	unsigned firstDayOfMonth,
	unsigned mondayPosition,
	unsigned year,
	const int& WIDTH,
	const int& COL_WIDTH);

/**
 * @brief Determines if a given year is a leap year or a common year
 *
 * If the year is divisible by 4 and not divisible by 100 or
 * if the year is divisible by 400, then it's a leap year
 * (all divisions are integer divisions)
 * All the other cases, it's a common year
 *
 * @param year unsigned The year which will be checked
 * @return bool Is or isn't a leap year
 */
bool isLeapYear(unsigned year);

/**
 * @brief Determines the day of the week of the 1st of January of any given year
 * Source of the calculation (Method 2):
 * https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
 *
 * @param year unsigned The year of which the 1st January day will be determined
 * @return unsigned Day of the week matching the criteria (e.g. 1 = Lundi, 2 = Mardi, ..., 7 = Dimanche [1-7])
 */
unsigned dayOf1stJan(unsigned year);

/**
 * @brief Get the initial of a day based on its number
 *  e.g. 2 (Mardi) --> M
 *
 * @param day int The day number [0-6]
 * @return string Initial of the day (L,M,M,J,V,S,D)
 */
string getDayInitial(unsigned day);

/**
 * @brief Get the name of a month based on its number
 *  e.g 7 --> Aout
 *
 * @param month int Month number [0-11]
 * @return string Month name
 */
string getMonthName(unsigned month);

/**
 * @brief Obtains the number of days in any given month
 *
 * There's a odd/even link between the months and their number of days,
 * but months such as February have either 28 or 29 days,
 * and July and August always have 31 days which creates a shift for the second part of the year

 * @param year unsigned Year used to determine if it's a leap year or not
 * @param month unsigned Current month given to calculate the number of days [0-11]
 * @return unsigned Number of days in a specific month of a specific year
 */
unsigned getMonthLength(unsigned year, unsigned month);

/**
  * @brief Ask and validates user data
  *
  * @param question string Question to ask the user
  * @param errorMessage string Error message to display if the user enters non valid value
  * @param MIN_VALUE unsigned Minimum value for the expected value
  * @param MAX_VALUE unsigned Maximum value for the expected value
  * @return unsigned Validated user input
  */
unsigned checkUserInput(const string& question, const string& errorMessage, unsigned MIN_VALUE, unsigned MAX_VALUE);

/**
 * @brief Displays an empty line
 *
 * @return void
 */
void displayEmptyLine(unsigned colWidth);

/**
 * @brief Displays a centered text
 *
 * @param text string The string to display centered
 * @param colWidth unsigned Width of the column
 * @return void
 */
void displayCenteredText(const string& text, unsigned colWidth);

/**
 * @brief Cleans the cin stream after use
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
	const unsigned COL_WIDTH = 3;
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

	cout << endl;
	displayCenteredText(to_string(year), CALENDAR_WIDTH);

	// Display the entire calendar based on the user input
	unsigned firstDayOfMonth = dayOf1stJan(year);
	for (unsigned month = 0; month < 12; ++month) {
		displayEmptyLine(CALENDAR_WIDTH);
		firstDayOfMonth = displayCalendar(month, firstDayOfMonth, mondayPosition, year, CALENDAR_WIDTH, COL_WIDTH);
	}

	return 0;
}

unsigned displayCalendar(unsigned month,
	unsigned firstDayOfMonth,
	unsigned mondayPosition,
	unsigned year,
	const int& WIDTH,
	const int& COL_WIDTH) {

	unsigned nbDays = getMonthLength(year, month);

	displayCenteredText(getMonthName(month), WIDTH);

	unsigned firstDayOfWeek = NUMBER_DAYS_IN_WEEK - (mondayPosition - 1);
	unsigned i = firstDayOfWeek;
	// Displays the intial letter of the weekday
	do {
		if (i == NUMBER_DAYS_IN_WEEK or (i > 6 and firstDayOfWeek != NUMBER_DAYS_IN_WEEK)) i = 0;

		cout << setw(COL_WIDTH) << getDayInitial(i);
		i++;
	} while (i != firstDayOfWeek);
	cout << endl;

	unsigned firstDayMondayPositionDiff = (firstDayOfMonth - 1) + (mondayPosition - 1);
	unsigned firstDayMonthPosition = firstDayMondayPositionDiff > NUMBER_DAYS_IN_WEEK - 1 ?
		firstDayMondayPositionDiff - NUMBER_DAYS_IN_WEEK
		: firstDayMondayPositionDiff;

	for (size_t p = 0; p < firstDayMonthPosition; ++p) {
		cout << setw(COL_WIDTH) << DISPLAY_FILL;
	}

	unsigned dayMonthPosition = firstDayMonthPosition;
	for (unsigned date = 1; date <= nbDays; ++date) {
		// If we are at the end of the week, pass to the next line, i.e. the next week.
		if (dayMonthPosition == NUMBER_DAYS_IN_WEEK) {
			cout << endl;
			dayMonthPosition = 0;
		}

		cout << setw(COL_WIDTH) << date;

		// If it's the last day of the month and it's not a Sunday, fill the end of the line with DISPLAY_FILL
		if (date == nbDays and dayMonthPosition != NUMBER_DAYS_IN_WEEK - 1) {
			cout << setw(WIDTH - ((int)dayMonthPosition * COL_WIDTH) - COL_WIDTH) << DISPLAY_FILL;
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
	return ((year % 4 == 0) && year % 100 != 0) || year % 400 == 0;
}

unsigned dayOf1stJan(unsigned year) {
	unsigned day = 1;
	unsigned month = 1;

	unsigned c = (14 - month) / 12;	// c == 1 for January and February, 0 for all the other months
	unsigned a = year - c;
	unsigned m = month + 12 * c - 2;

	unsigned january1st = (day + a + a / 4 - a / 100 + a / 400 + (31 * m) / 12) % 7;
	return january1st == 0 ? NUMBER_DAYS_IN_WEEK : january1st;
}

unsigned checkUserInput(const string& question,
	const string& errorMessage,
	const unsigned MIN_VALUE,
	const unsigned MAX_VALUE) {
	bool inputError;
	string rawInput;
	unsigned value = 0;

	do {
		inputError = false;
		rawInput = "";

		cout << question;
		cin >> rawInput;

		// Checks that the length of the input isn't longer than what we want
		if (rawInput.length() != (unsigned)(log10(MIN_VALUE) + 1)) {
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
	switch (month) {
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