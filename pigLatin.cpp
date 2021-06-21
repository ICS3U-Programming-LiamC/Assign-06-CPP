// Copyright (c) 2021 Liam Csiffary All rights reserved.
//
// Created by: Liam Csiffary
// Date: May June 16, 2021
// code converts all text to pig latin

#include <iostream>
#include <list>
#include <algorithm>
#include "YVowels.h"

// did this to avoid annoying error
using namespace N;
using std::string;
using std::list;
using std::cout;
using std::cin;
using std::endl;
const char WHITESPACE[11] = " \n\r\t\f\v";


void welcome() {
    cout << "Welcome! This code converts text from english to pig latin!\n";
}


// REMOVES ALL WHITE SPACE BEFORE AND AFTER STRING

// removes space before string
std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
// removes space after string
std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
// calls the two functions above using the string as an argument
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}



list<string> userInput;
bool capitalizerTest = false;
bool capitalizer = false;

// this function handles the punctuation per word
string Punctuator(string word, char puncter) {
    // remove any punctuation that was detected in the word
    word.erase(remove(word.begin(), word.end(), puncter), word.end());
    // now add it back to the end
    // the reason I have to do this is because earlier when I rearanged the
    // word it also moved the punctuation that was attacched to it to be
    // in the middle of the word somewhere. This moves it back to the end
    word = word + puncter;

    // if the last word had a capital then capitalize this one
    if (capitalizer == true) {
        word[0] = ::toupper(word[0]);
        capitalizer = false;
    }
    // this is here so that I can delay the capitilization by a word
    // if a word ends in a period then capitalizer is set to true
    // but since the capitalizer check has already passed it wont affect
    // the current word but it will affect the next one
    if (capitalizerTest == true) {
        capitalizer = true;
        capitalizerTest = false;
    }
    return word;
}

// found this code on
// https://java2blog.com/split-string-space-cpp/
// it splits the string into diferent parts so that I can add them to the list
// if I dont do this than the list interprets the users input
// as one long things and saves it all to one index
void splitString(string str, string delimiter = " ") {
    int start = 0;
    int end = str.find(delimiter);
    // the condition here isnt really necessary as its a text and
    // -1 should come up
    while (end != -1) {
        userInput.push_back(str.substr(start, end - start));
        // cout << str.substr(start, end - start) << endl;
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    userInput.push_back(str.substr(start, end - start));
    // cout << str.substr(start, end - start);
}

// this part does all the moving of the letters
string Swapper(string word, string y) {
    string letter;
    letter = word[0];
    string saved;
    while (true) {
        // as long as the first letter is not a vowel move the
        // start of the word to the back of it
        if (letter == "a" || letter == "e" || letter == "i" ||
        letter == "o" || letter == "u" || letter == y) {
            break;
        } else {
            word = word.substr(1, word.length() - 1) + word.front();
            letter = word[0];
        }
    }
    // return the word
    return word;
}

// this adds the suffixes the capitals as well as calls most of
// the other functions
string latinConverter() {
    string yVow;
    string swapped;
    string letter;
    string suffix;
    string final;
    for (string each : userInput) {
        yVow = "a";
        string temp = each;
        temp.erase(remove(temp.begin(), temp.end(), '.'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), ';'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), '!'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), '?'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), ':'), temp.end());
        for (string oddWord : yVowelWords) {
            if (oddWord == temp) {
                yVow = "y";
            }
        }

        swapped = each;
        letter = swapped[0];
        // if word already starts with a vowel add way to the end
        if (letter == "a" || letter == "e" || letter == "i"
        || letter == "o" || letter == "u" || letter == yVow) {
            suffix = "way";
        } else {
            // otherwise call the function and add ay to the end
            swapped = Swapper(swapped, yVow);
            suffix = "ay";
        }
        // adds the suffix
        swapped = swapped + suffix;
        // defines the variable
        char punctuation;

        // couldnt use switch case as they dont work for chars
        // correction it can use chars just not strings
        // but I already made this code and wont bother
        // changing it
        // basically if theres punctuation in the word
        // it will set the puncter to it so that
        // it can be added on later in the code
        if (swapped.find(".") != string::npos) {
            punctuation = '.';
            capitalizerTest = true;
        } else if (swapped.find(",") != string::npos) {
            punctuation = ',';
        } else if (swapped.find("!") != string::npos) {
            punctuation = '!';
            capitalizerTest = true;
        } else if (swapped.find("?") != string::npos) {
            punctuation = '?';
            capitalizerTest = true;
        } else if (swapped.find(";") != string::npos) {
            punctuation = ';';
        } else {
            punctuation = 0;
        }
        // call this function which handles the rest of the punctuation work
        swapped = Punctuator(swapped, punctuation);

        // cout << swapped << "\n";
        final = final + swapped + " ";
    }
    // makes the first letter capitalized
    final[0] = ::toupper(final[0]);
    return final;
}

int main() {
    welcome();
    string sentence;
    string final;
    cout << "What would you like to convert to pig latin: ";
    getline(cin, sentence);

    sentence = trim(sentence);

    // https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/
    for_each(sentence.begin(), sentence.end(), [](char & c) {
        c = ::tolower(c);
    });

    // removes all spaces before and after the string!
    splitString(sentence);

    final = latinConverter();
    cout << final;
}
