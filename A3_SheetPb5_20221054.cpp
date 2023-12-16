// File name: A3_SheetPb05_YourID.cpp
// Purpose: task manager to see running processes on operating system
// Author: Ramez Ragaay Makram Zaki
// ID: 20221054
// Section: S24
// Date: 9-12-2023 (saturday)

#include <bits/stdc++.h>
using namespace std;

class Process{
private:
    int PID;
    long long mem;
    string name;
public:
    Process(int pid, int m, string n);
    int getPID();
    long long getMem();
    string getName();
};

Process::Process(int pid, int m, string n){PID = pid, mem = m, name = n;};

int Process::getPID(){
    return PID;
}
long long Process::getMem(){
    return mem;
}
string Process::getName(){
    return name;
}

class TaskManger{
    vector <Process> vp;
public:
    void fill();
    void display();
};

void TaskManger::fill(){
    system("tasklist > task_list.txt");
    ifstream file("task_list.txt");
    if(file.is_open()){
        string word;
//        this for loop to skip the first 3 lines
        for(int i = 0; i < 3; i++){
            getline(file,word);
        }
//        this while loop for collecting the name, process ID and memory usage and store them in the vector vp
        while (getline(file, word)){
            istringstream istrStream(word);
            int pID;
            int memory;
            string nm;
            istrStream >> nm >> pID >> memory;
            Process p1(pID, memory, nm);
            vp.push_back(p1);
        }
        file.close();
    }
}

void TaskManger::display(){
    cout << "Sort by: " << endl << "(1)sorted by name" << endl
     << "(2) sorted by PID" << endl<< "(3)sorted by memory use" << endl;
    int sort_type;
    cin >> sort_type;
    bool valid = true;

    if(sort_type == 1){
        sort(vp.begin(), vp.end(),
             [](Process A, Process B)->bool {return A.getName() < B.getName();});
    }
    else if(sort_type == 2){
        sort(vp.begin(), vp.end(),
             [](Process A, Process B)->bool {return A.getPID() < B.getPID();});
    }
    else if(sort_type == 3){
        sort(vp.begin(), vp.end(),
             [](Process A, Process B)->bool {return A.getMem() < B.getMem();});
    }
    else{
        valid = false;
        cout << "error, run again" << endl;
    }
    if(valid) {
        cout << "Name" << string(25,' ') <<
        "PID" << string(10,' ') << "Memory usage" << endl;
        cout << string(60, '-') << endl;
        for (auto i: vp) {
            string p = to_string(i.getPID());

            cout << i.getName() << string(29 - i.getName().size(),' ')
            << i.getPID() << string(13-p.size(),' ') <<
            i.getMem() << " KB" << endl;
        }
    }
}

int main() {
    TaskManger t;
    t.fill();
    t.display();
    return 0;
}
