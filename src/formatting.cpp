#include "../include/formatting.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

void clearScreen() {
    system(CLEAR_SCREEN);
}

void fillLines(int width, char character){
    cout << " " << setw(width) << setfill(character) << "" << endl;
    cout << setfill(' ');
}

void headerCentre(int width, string x){
    int leftPadding = (width - x.length()) / 2;
    int rightPadding = width - x.length() - leftPadding;

    cout << setw(leftPadding) << setfill(' ') << "" << x;
    cout << setw(rightPadding) << setfill(' ') << "" << endl;
}

void headerBorder(int width, string alignment, string text){
    int horizontalPadding = 0;

   if (alignment == "left") {
        horizontalPadding = 1;
    } else if (alignment == "right") {
        horizontalPadding = width - text.length() - 1;
    } else if (alignment == "center") {
        horizontalPadding = (width - text.length()) / 2;
    }

    cout << '|' << setw(horizontalPadding) << setfill(' ') << "";
    cout << text;
    cout << setw(width - horizontalPadding - text.length()) << setfill(' ') << "" << '|' << endl;
}

void pressAnyKeyToContinue(){
    cout << endl << " Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void printParagraphBordered(int width, string alignment, const string &paragraph) {
    istringstream iss(paragraph);
    string line, substring;

    while (getline(iss, line)) {
        const size_t maxWidth = width - 2;
        for (size_t pos = 0; pos < line.length(); pos += maxWidth) {
            if (pos + maxWidth < line.length()){
                substring = line.substr(pos, maxWidth-1);
                substring = substring + "-";
            } else {
                substring = line.substr(pos, maxWidth);
            }
            headerBorder(width, alignment, substring);
        }
    }
}

void printTableMain(int width, string n, string title, string username){

    int totalWidth = width - 2;

    int leftPadding = (totalWidth - title.length() - username.length() - 4) / 2;
    int rightPadding = totalWidth - title.length() - username.length() - 4 - leftPadding;

    cout << "| " << setw(3) << n << " ";
    cout << setw(leftPadding) << setfill(' ') << "" << title;
    cout << setw(rightPadding) << setfill(' ') << "" << username << " |" << endl;
}

string inputParagraph(string msg){
    string x;
    cout << msg;
    getline(cin, x);
    return x;
}
