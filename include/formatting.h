#ifndef FORMATTING_H
#define FORMATTING_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void clearScreen();
void fillLines(int width, char character);
void headerCentre(int width, string x);
void headerBorder(int width, string alignment, string x);
void pressAnyKeyToContinue();
void printParagraphBordered(int width, string alignment, const string &paragraph);
void printTableMain(int width, string n, string title, string username);
string inputParagraph(string msg);
#endif // FORMATTING_H
