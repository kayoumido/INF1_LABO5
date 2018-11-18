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

const int CALENDAR_WIDTH = 21;
const int NUMBER_DAYS_IN_WEEK = 7;
const int SEPARATOR_SIZE = 2;
const char DISPLAY_FILL = '.';

void displayCalendar();
string getDayName(int day);

int main() {
  displayCalendar();

  return 0;
}

void displayCalendar() {
  string year = "2016";
  string name = "Mars";
  int nbDays = 31;
  int mondayPosition = 1;
  int firstDayOfMonth = 3;

  cout << setfill(DISPLAY_FILL);
  cout << setw(CALENDAR_WIDTH / 2 - (int)year.length() / 2) << DISPLAY_FILL;
  cout << setw((int)year.length()) << year;
  cout << setw(CALENDAR_WIDTH - (CALENDAR_WIDTH / 2 - (int)year.length() / 2) - (int)year.length()) << DISPLAY_FILL << endl;

  cout << setw(CALENDAR_WIDTH) << DISPLAY_FILL << endl;

  cout << setw(CALENDAR_WIDTH / 2 - (int)name.length() / 2) << DISPLAY_FILL;
  cout << setw((int)name.length()) <<  name;
  cout << setw(CALENDAR_WIDTH - (CALENDAR_WIDTH / 2 - (int)name.length() / 2) - (int)name.length()) << DISPLAY_FILL << endl;

  int firstWeekDay = NUMBER_DAYS_IN_WEEK - (mondayPosition - 1);
  int i = firstWeekDay;
  do {
    if (i == NUMBER_DAYS_IN_WEEK) i = 0;

    cout << setw(3) << getDayName(i);
    i++;

    if (i > 6 and firstWeekDay != NUMBER_DAYS_IN_WEEK) i = 0;

  } while(i != firstWeekDay);
  cout << endl;
  
  for (int j = 1; j <= nbDays; ++j) {
    int dayPosition = j % NUMBER_DAYS_IN_WEEK;

    cout << DISPLAY_FILL;
    cout << setw(SEPARATOR_SIZE) << j;

    // If we are at the end if the week, pass to the next line
    if (dayPosition == 0) cout << endl;

    // If it's the last day of the month, fill the end of the line with DISPLAY_FILL
    if (j == nbDays and j % NUMBER_DAYS_IN_WEEK != 0)
      cout << setw(CALENDAR_WIDTH - (dayPosition * SEPARATOR_SIZE + dayPosition)) << DISPLAY_FILL;
  }
}

string getDayName(int day) {
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

