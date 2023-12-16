// File name:A3_SheetPb3_20221098
// Purpose: STL – Map
// Author(s): Abdelrahman Kadry Mohamed
// ID(s): 20221098
// Section:S24
// Date: 10/12/2023
#include <bits/stdc++.h>
using namespace std ;
#define el '\n'
#define sp ' '
#define END return 0 ;

//see where the word will end
bool isValid (char c ){
    if (c == '.' ||c == ' ' ||c == '.' ||c == ',' ||c == '_'||c == char(13)){
        return true;
    }
    else return false;
}

//checking if the word is valid
bool isValidString (const string& string1 ){
    for (int i = 0; i < string1.size(); ++i) {
        if (string1[i] == '-') continue;
        if (string1[i] < 'A' || string1[i] >'z' || (string1[i] >'Z' &&  string1[i] <'a') )
            return false ;
    }
    return true ;
}

// reading the input file and extracting a table with the words and how many times they appear
map <string , int > frequencyTable ( string& fillName ) {

    map<string, int> wordsFrequency;
    ifstream document(fillName);

    if (!document.is_open()) {
        cout << "Can not open the fill " << el;
        exit(1);
    }

    string wordsLine;
    while (getline(document, wordsLine)) {
        int count = 0 ;

        for (int i = 0; i < wordsLine.size(); ++i) {
            if  (isValid(wordsLine[i])){
                string keyword = wordsLine.substr((i ) - count , count);
                for (int j = 0; j < keyword.size(); ++j) {
                    keyword[j] = (char)tolower(keyword[j]) ;
                }
                count = -1 ;
                if (!keyword.empty() && isValidString(keyword) )
                    wordsFrequency[keyword]++ ;
            }
            count++ ;
        }
    }
        document.close();
        return wordsFrequency;
}

int main(){

    cout << "Enter the file name: \n" ;
    string targetFile ;
    cin >> targetFile;


    map<string, int> wordsCounter = frequencyTable(targetFile);
    vector<pair <int, string>> wordsCounter2 ;

    for (const auto& item : wordsCounter ){
        wordsCounter2.emplace_back(item.second , item.first);
    }

    std::sort(wordsCounter2.begin(), wordsCounter2.end());

    cout << "   Word                       Appearance \n" << "-------------------------------------------" << el;
    string space = "               |                " ;
    int sizes = space.size() ;

    for (const auto& item : wordsCounter2 ){
        cout << "- " << item.second ;

        for (int i = 0; i < sizes - item.second.size(); ++i) {
            cout << sp ;
        }

        cout << item.first <<  el;
    }
    END
}
