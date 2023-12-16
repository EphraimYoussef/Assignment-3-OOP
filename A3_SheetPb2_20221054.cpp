// File name: A3_SheetPb05_YourID.cpp
// Purpose: check document similarity and other operations.
//retrieval and search engines.
// Author: Ramez Ragaay Makram Zaki
// ID: 20221054
// Section: S24
// Date: 9-12-2023 (saturday)

#include <bits/stdc++.h>
using namespace std;

class StringSet {
private:
    vector <string> set1;
    void LoadFromFile(const string &fileName);
    void LoadFromString(const string &s);
    string to_lower_punc_remove(const string &word);

public:
    StringSet(const string &s);
    StringSet();
//    ~StringSet();
    void RemoveDuplicates();
    float is_similar_to(StringSet const &other);
    StringSet operator + (StringSet& other);
    StringSet operator * (StringSet& other);
    void addStr(const string &word);
    void removeStr(const string &word);
    void clearSet();
    void print();
    int numOfStrings();
};
StringSet::StringSet(){};
StringSet::StringSet(const string &s) {
    if(s.find(".txt") != string::npos){
        LoadFromFile(s);
        RemoveDuplicates();
    }
    else{
        LoadFromString(s);
        RemoveDuplicates();
    }
}
string StringSet::to_lower_punc_remove(const string &word){
    string tmp = "";
    for (auto c : word){
        if(c <= 90 && c >= 65) {
            c += 32;
            tmp += c;
        }
        else if(c <= 122 && c >= 97)
            tmp += c;
    }
    return tmp;
}
void StringSet::LoadFromString(const string &s){
    string word;
    for(int i = 0 ; i < s.size(); i++){
        if(s[i] != ' '){
            word += s[i];
        }
        else{
            if(!word.empty()){
                set1.push_back(to_lower_punc_remove(word));
            }
            word.clear();
        }
    }
    set1.push_back(to_lower_punc_remove(word));

}
void StringSet::LoadFromFile(const string &fileName){
    ifstream file(fileName);
    if(!file.is_open()){
        cout << "Wrong file name." << endl;
    }
    else{
        string word;
        while(file >> word){
            set1.push_back(to_lower_punc_remove(word));
        }
        file.close();
    }
}
void StringSet::RemoveDuplicates() {
    set < string > tmp;
    for(auto it : set1){
        tmp.insert(it);
    }
    set1.clear();
    for(auto it : tmp){
        set1.push_back(it);
    }
}
float StringSet ::is_similar_to(const StringSet &other) {
    if(this->set1.empty() ||other.set1.empty())
        return 0;
    set <string> sm;
    for(auto it : this->set1){
        if(std::find(other.set1.begin(), other.set1.end(),it) != other.set1.end())
            sm.insert(it);
    }
    float intersect_words = sm.size();
    float sim = intersect_words / ((sqrt(this->set1.size()))*(sqrt(other.set1.size())));
    cout  << "common: " << intersect_words;
    return sim;
}
StringSet StringSet::operator+(StringSet& other){
    StringSet S3("");
    set <string> sm;
    for(auto it : this->set1){
        sm.insert(it);
    }
    for(auto it : other.set1){
        sm.insert(it);
    }
//    the set removes the dupllicates.
    for(auto it : sm){
        S3.set1.push_back(it);
    }
    return S3;
}
StringSet StringSet::operator*(StringSet& other){
    StringSet S3("");
    set <string> sm;
    vector <string> allS;
    for(auto it : this->set1){
        sm.insert(it);
        allS.push_back(it);
    }
    for(auto it : other.set1){
        sm.insert(it);
        allS.push_back(it);
    }
//    if there is a word that found twice this means that it was in the two documents (intersection).
    for(auto it : sm){
        if(count(allS.begin(), allS.end(), it) > 1)
            S3.set1.push_back(it);
    }
    return S3;
}
void StringSet::addStr(const string &word){
    string w = word;
    to_lower_punc_remove(w);
    set1.push_back(w);
}
void StringSet::removeStr(const string &word){
    string w = word;
    to_lower_punc_remove(w);
    if(std::find(set1.begin(), set1.end(),w) != set1.end()){
        set1.erase(find(set1.begin(), set1.end(),w));
    }
    else{
        cout << "This word is not found." << endl;
    }

}
void StringSet::clearSet(){
    set1.clear();
}
int StringSet::numOfStrings() {
    return set1.size();
}
void StringSet::print(){
    if (this->set1.empty())
        cout << "this set is empty" << endl;
    else {
        cout << "--------------------" << endl;
        for (auto it: set1) {
            if (it.size() % 2 != 0)
                cout << "|" << string((ceil(20.0 - it.size()) / 2.0) - 1, ' ') << it
                     << string((ceil(20.0 - it.size()) / 2.0), ' ') << "|";
            else
                cout << "|" << string((ceil(20.0 - it.size()) / 2.0) - 1, ' ') << it
                     << string((ceil(20.0 - it.size()) / 2.0) - 1, ' ') << "|";
            cout << endl;
        }
        cout << "--------------------" << endl;
    }
}
int main() {
    string s1, s2;
    cout << "enter a name for the to documents (if it is a text write [.txt] as extention.)" << endl;
    cin >> s1 >> s2;
    StringSet doc1(s1), doc2(s2);
    cout << doc1.is_similar_to(doc2) << endl;
    doc1.print();
    string w = "Hello!";
    doc1.addStr(w);
    doc2.clearSet();
    doc1.removeStr(w);
    doc1.print();
    cout <<doc2.is_similar_to(doc1) << endl;
    doc2.print();
    return 0;
}
