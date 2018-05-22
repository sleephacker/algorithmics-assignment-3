#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    if(argc < 2) {
        cout << "Geef aub een hulpbestand mee" << endl;
    }
    else {
        cout << "Inlezen: " << argv[1] << endl;
    }

    return 0;
}
