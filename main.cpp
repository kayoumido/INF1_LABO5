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
#include <iomanip>

using namespace std;

const unsigned CALENDAR_WIDTH = 21;
const unsigned NUMBER_DAYS_IN_WEEK = 7;
const unsigned SEPARATOR_SIZE = 2;
const char DISPLAY_FILL = '.';

/**
 * Display the calendar for a given month
 *
 * @return void
 */
void displayCalendar(int month, int firstDayOfMonth, int mondayPosition);

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
  * @param max int max value for the expected value
  * @param min int min value for the expected value
  * @return int Validated user input
  */
int getUserInput(string question, string errorMessage, int max, int min);

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

int main() {
  cout << setfill(DISPLAY_FILL);
  // displayCalendar();
  displayCalendar(1, 2, 1);
  return 0;
}

void displayCalendar(int month, int firstDayOfMonth, int mondayPosition) {
  string year = "2016";
  string name = getMonthName(month);
  int nbDays = 31;

  displayCenteredText(year, CALENDAR_WIDTH);
  displayEmptyLine(CALENDAR_WIDTH);
  displayCenteredText(name, CALENDAR_WIDTH);

  int firstDayOfWeek = NUMBER_DAYS_IN_WEEK - (mondayPosition - 1);
  int i = firstDayOfWeek;
  do {
    if (i == NUMBER_DAYS_IN_WEEK) i = 0;

    cout << setw(3) << getDayInitial(i);
    i++;

    if (i > 6 and firstDayOfWeek != NUMBER_DAYS_IN_WEEK) i = 0;

  } while(i != firstDayOfWeek);
  cout << endl;

  
  int firstDayMondayPositionDiff = (firstDayOfMonth - 1) + (mondayPosition - 1);
  int firstDayMonthPosition = firstDayMondayPositionDiff > NUMBER_DAYS_IN_WEEK - 1 ?
          firstDayMondayPositionDiff - NUMBER_DAYS_IN_WEEK
          : firstDayMondayPositionDiff;

  for (int p = 0; p < firstDayMonthPosition; ++p) {
    cout << setw(3) << DISPLAY_FILL;
  }

  int dayMonthPosition = firstDayMonthPosition;
  for (int date = 1; date <= nbDays; ++date) {
    // If we are at the end of the week, pass to the next line, i.e. the next week.
    if (dayMonthPosition == NUMBER_DAYS_IN_WEEK) {
      cout << endl;
      dayMonthPosition = 0;
    }

    cout << DISPLAY_FILL;
    cout << setw(SEPARATOR_SIZE) << date;

    // If it's the last day of the month and it's not a Sunday, fill the end of the line with DISPLAY_FILL
    if (date == nbDays and dayMonthPosition != NUMBER_DAYS_IN_WEEK - 1) {
      cout << setw(CALENDAR_WIDTH - (dayMonthPosition * SEPARATOR_SIZE + dayMonthPosition + 3 )) << DISPLAY_FILL;
    }

    ++dayMonthPosition;
  }
}

string getDayInitial(int day) {
  switch (day) {
    case 0:
      return "L";
    case 1:
    case 2:
      return "M";
    case 3:
      return "J";
    case 4:
      return "V";
    case 5:
      return "S";
    case 6:
      return "D";
  }
}

string getMonthName(int month) {
  switch (month) {
    case 0:
      return "Janvier";
    case 1:
      return "Fevrier";
    case 2:
      return "Mars";
    case 3:
      return "Avril";
    case 4:
      return "Mai";
    case 5:
      return "Juin";
    case 6:
      return "Juillet";
    case 7:
      return "Aout";
    case 8:
      return "Septembre";
    case 9:
      return "Octobre";
    case 10:
      return "Novembre";
    case 11:
      return "Decembre";
  }
}

void displayCenteredText(const string text, const unsigned colWidth) {
  cout << setw(colWidth / 2 - (int)text.length() / 2) << DISPLAY_FILL;
  cout << setw((int)text.length()) << text;
  cout << setw(colWidth - (colWidth / 2 - (int)text.length() / 2) - (int)text.length()) << DISPLAY_FILL << endl;
}

void displayEmptyLine(const unsigned colWidth) {
  cout << setw(colWidth) << DISPLAY_FILL << endl;
}

