//
//  roughScan1.cc
//  
//
//  Created by Victor Duan on 2015-02-14.
//
//

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

string findLargestFont (const string file) {
    ifstream html_file (file);
    string curLine;
    //associated with each other
    string fontClassL = "";
    int largestSize = 0;
    
    int curSize = 0;
    size_t pxIndex;
    
    bool reachedEndofFontSizes = false;
    
    while (getline(html_file, curLine) && !reachedEndofFontSizes) {
        //if the .ft substring exists then there is a font size associated with it
        if (curLine.find(".ft") != -1) {
            //cout << curLine << endl;
            //gotta find the font size, so find instance of px string
            for (int i = 0; i < 2; i++) {
                curSize += (int)((curLine.at(curLine.find("px") - i - 1)) - '0') * (int)pow(10, i);
                //cout <<
                //cout << curSize<<endl;
            }
            //cout << curSize << endl;
        }
        if (curSize > largestSize) {
            largestSize = curSize;
            fontClassL = curLine.substr(1, 3);
        }
        curSize = 0;
    }
    html_file.close();
    return fontClassL;
    
    
}

void blankName(string &name) {
    const string REPLACEMENT = "NAME";
    int numSpaces;
    
    numSpaces = name.length() - REPLACEMENT.length();
    name = "";
    
    //cout << name.length() << endl;
    //cout << numSpaces<< endl;
    
    for (int i = 0; i < numSpaces / 2; i++) {
        name += " ";
    }
    if (numSpaces %2 != 0) {
        name += " ";
    }
    name += REPLACEMENT;
    for (int i = 0; i < numSpaces / 2; i++) {
        name += " ";
    }
    
}

void replaceName(string file, string font_l) {
    ifstream html_file (file);
    ofstream new_html_file ("newResume.htm");
    string curLine;
    string name;
    int numSpaces;
    
    bool reachedName = false;
    bool isSecondTime = false;
    
    //cout << curLine << endl;
    while (getline(html_file, curLine)) {
        //cout << "inside" << endl;
        if (curLine.find(font_l) != -1) {
            if (isSecondTime) {
                reachedName = true;
                name = curLine.substr(curLine.find_first_of(">") + 1);
                name = name.substr(0, name.length() - 5);
                //cout << name << endl;
                blankName(name);
                curLine = curLine.replace(curLine.find_first_of(">") + 1, name.length(), name);
                cout << curLine << endl;
                //cout << name << endl;
            }
            else {
                isSecondTime = true;
            }
        }
        new_html_file << curLine << endl;
    }

    
    html_file.close ();
    new_html_file.close();
}

int main(void) {
    /*
    ifstream html_file ("resume2.htm");
    string curLine;
    int counter = 0;
    while (getline(html_file, curLine)) {
        cout << curLine << endl;
        cout << counter << endl;
        counter++;
    }
     */
    
    string file = "DavidResume2.htm";
    string font =findLargestFont(file);
    //cout << font << endl;
    replaceName(file, font);
    return 0;
}

