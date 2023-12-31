#include<iostream>
using namespace std;

int main(){
    string hazchem;
    bool reverseColor = false;
    bool reactivity = true;
    bool isProtectionFull = false;
    bool evacuation = false;
    bool isDilute = false;
    string material;

    cout << "Enter HAZCHEM code: ";
    cin >> hazchem;


    // consider the second character of the hazchem code
    if(hazchem[1] == 'S' || hazchem[1] == 'T' || hazchem[1] == 'Y' || hazchem[1] == 'Z'){
        string answer;
        cout << "Is the " << hazchem[1] << " reverse colored? ";
        cin >> answer;
        if(tolower(answer[0]) == 'y'){
            reverseColor = true;
        }
    }else{
        isProtectionFull = true;
    }

    if(hazchem[1] == 'R' || hazchem[1] == 'T' || hazchem[1] == 'X'){
        reactivity = false;
    }

    if(hazchem[1] == 'P' || hazchem[1] == 'R' || hazchem[1] == 'S' || hazchem[1] == 'T'){
        isDilute = true;
    }
    // consider the first character of the hazchem code
    switch (hazchem[0])
    {
    case '1':
        material = "jets";
        break;
    case '2':
        material = "fog";
        break;
    case '3':
        material = "foam";
        break;
    case '4':
        material = "Dry agent";
        break;
    default:
        cout << "Invalid material. Try again" << endl;
        break;
    }

    cout << "*** Emergency action device ***" << endl;
    cout << "Material:\t"<< material << endl;
    cout << "Reactivity:\t" << ((reactivity) ? ("can be violently reactive") : ("")) << endl;

    if(isProtectionFull){
        cout << "Protection:\tfull protective clothing must be worn" << endl;
    }else{
        if(reverseColor){
            cout << "Protection:\tbreathing apparatus, protective gloves for fire only" << endl;
        }else{
            cout << "Protection:\tbreathing apparatus" << endl;
        }
    }

    if(isDilute){
        cout << "Containment:\tthe dangerous goods may be washed down to a drain with a large quantity of water" << endl;
    }else{
        cout << "Containment:\ta need to avoid spillages from entering drains or water courses.";
    }

    if(hazchem.length() == 3 && hazchem[2] == 'E'){
        cout << "Evacuation:\tconsider evacuation" << endl;
    }
    cout << "**********************" << endl;
}
