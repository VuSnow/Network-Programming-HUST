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

    // consider the first character of the hazchem code
    switch (hazchem[0])
    {
    case 1:
        material = "jets";
        break;
    case 2:
        material = "fog";
        break;
    case 3:
        material = "foam";
        break;
    case 4:
        material = "Dry agent";
        break;
    default:
        cout << "Invalid material. Try again" << endl;
        break;
    }

}