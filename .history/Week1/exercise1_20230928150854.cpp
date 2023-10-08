#include<iostream>
using namespace std;

int main(){
    string hazchem;
    bool reverseColor = false;
    string material, reactivity, protection, containment, evacuation;

    cout << "Enter HAZCHEM code";
    cin >> hazchem;


    // consider the second character of the hazchem code
    if(hazchem[1] == 'S' || hazchem[1] == 'T' || hazchem[1] == 'Y' || hazchem[1] == 'Z'){
        string answer;
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

    // consider the second character of the hazchem code
    

}