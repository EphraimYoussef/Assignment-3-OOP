// File name: A3_SheetPb4_20221023.cpp
// Purpose:  Template – Set
// Author(s): افرايم يوسف خميس دميان
// ID(s): 20221023
// Section: S24
// Date: 9/12/2023

#include <bits/stdc++.h>

using namespace std;

template < class T >
class Set {
private:
    vector <T> vec;
public:
    void push (T n){
        if ( count(vec.begin(), vec.end(),n) == 0 ){
            vec.push_back(n);
            sort(vec.begin(), vec.end());
        }
    }

    void remove (T n){
        if ( count(vec.begin(), vec.end(),n) != 0 ){
            vec.erase(find(vec.begin(), vec.end(),n));
        }
    }

    unsigned int size () {
        return vec.size();
    }

    bool isMember (T n) {
        if ( count(vec.begin(), vec.end(),n) == 0 ) {
            return false;
        }
        else {
            return true;
        }
    }

    T* copy() {
        T *arr = new T [vec.size()];
        for (int i = 0 ; i < vec.size() ; ++i) {
            arr[i] = vec[i];
        }
        return arr;
    }
};

int main() {
    Set <int> setInt;
    Set <string> setString;

    setInt.push(2);
    setInt.push(-5);
    setInt.push(23);
    setInt.push(0);
    setInt.push(23); //repeated

    setString.push("red");
    setString.push("blue");
    setString.push("green");
    setString.push("orange");
    setString.push("blue"); //repeated

    cout << "setInt size = " << setInt.size() << endl;
    cout << "setString size = " << setString.size() << endl;

    cout << "\nsetInt elements : \n";
    int *arrInt = setInt.copy();
    for (int i = 0 ; i < setInt.size() ; ++i) {
        cout << arrInt[i] << "  ";
    }

    cout << "\n\nsetString elements : \n";
    string *arrString = setString.copy();
    for (int i = 0 ; i < setString.size() ; ++i) {
        cout << arrString[i] << "  ";
    }

    cout << "\n\nsetInt elements after remove ( -5 ) : \n";
    setInt.remove(-5);
    int *arrInt2 = setInt.copy();
    for (int i = 0 ; i < setInt.size() ; ++i) {
        cout << arrInt2[i] << "  ";
    }

    cout << "\n\nsetString elements after remove ( orange ) : \n";
    setString.remove("orange");
    string *arrString2 = setString.copy();
    for (int i = 0 ; i < setString.size() ; ++i) {
        cout << arrString2[i] << "  ";
    }

    cout << "\n\n(23) is a member of setInt ? " << ( setInt.isMember(23) ? "yes\n" : "no\n" );
    cout << "(yellow) is a member of setString ? " << ( setString.isMember("yellow") ? "yes\n" : "no\n" );

    delete[] arrInt;
    delete[] arrInt2;
    delete[] arrString;
    delete[] arrString2;

    return 0;
}
