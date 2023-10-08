#include<iostream>
using namespace std;

int main(){
    string hazchem;
    string reverseColor;
    string material, reactivity, protection, containment, evacuation;

    cout << "Enter HAZCHEM code";
    cin >> hazchem;

    // consider the second character of the hazchem code
    if(hazchem[1] == 'S' || hazchem[1] == 'T' || hazchem[1] == 'Y' || hazchem[1] == 'Z'){
        cout << "Is the S reverse colored? ";
        cin >> reverseColor;
    }

    
}