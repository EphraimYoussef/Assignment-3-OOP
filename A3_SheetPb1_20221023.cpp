// File name: A3_SheetPb1_20221023.cpp
// Purpose:  Label Generator
// Author(s): افرايم يوسف خميس دميان
// ID(s): 20221023
// Section: S24
// Date: 9/12/2023

#include <bits/stdc++.h>

using namespace std;

class LabelGenerator {
protected:
    int num;
    string str;
public:
    LabelGenerator (string s,int n): str(s),num(n) {}
    virtual string nextLabel (){
        string s = str + to_string(num);
        num++;
        return s;
    }
};

class FileLabelGenerator : public LabelGenerator {
private:
    string fileName;
    vector<string>labels;
    int index;
public:
    FileLabelGenerator (string s,int n,string fileName): LabelGenerator( s,n ) , fileName(fileName) {
        index = 0;
        ifstream input (fileName);
        string line;
        while (getline(input,line)){
            labels.push_back(line);
        }
    }
    string nextLabel() override{
        string s = str + to_string(num) + ' ' + labels[index];
        index++;
        num++;
        return s;
    }
};

int main() {
    LabelGenerator figureNumbers("Figure ", 1);
    LabelGenerator pointNumbers("P", 0);

    cout << "Figure numbers: ";
    for (int i = 0; i < 3; i++) {
        cout << figureNumbers.nextLabel() << ( (i==2)? "." : " , " );
    }

    cout << endl << "Point numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << pointNumbers.nextLabel() << ( (i==4)? "." : " , " );
    }

    cout << endl << "More figures: ";
    for (int i = 0 ; i < 3 ; i++) {
        cout << figureNumbers.nextLabel() << ( (i==2)? "." : " , " );
    }
    cout << endl;

    FileLabelGenerator fileFigureLabels ("Figure ", 1,"labels.txt");
    cout << "Figure labels: \n";
    for (int i = 0 ; i < 6 ; i++) {
        cout << fileFigureLabels.nextLabel() << endl;
    }

    return 0;
}
