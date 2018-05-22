#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


void print_kaarten(bool *kaarten, size_t n) {

    for(int i = 0; i < 4; i++) {

        for(int j = 0; j < n; j++) {

            if(kaarten[i * n + j]) cout << '1';
            else cout << '0';
        }

        cout << endl;
    }

}

void lees_bestand_in(bool *kaarten, size_t n, ifstream& bestand) {

    memset(kaarten, false, sizeof(bool) * 4 * n);

    // i = -1, verwijder beginnende \r\n
    for(int i = -1, j = 0; i < 4;) {

        char kar = bestand.get();

        if(kar == '\r') continue;
        if(kar == '\n') {
            i += 1;
            j = 0;
            continue;
        }

        kaarten[i * n + j] = kar == '1';
        j += 1;
    }
}


int main(int argc, char** argv) {

    if(argc < 2) {
        cout << "Geef aub een invoerbestand mee" << endl;
    }
    else {
        char *bestand_naam = argv[1];
        cout << "Inlezen: " << bestand_naam << endl;

        ifstream bestand(bestand_naam);

        int n = 0;
        bestand >> n;
        cout << "Grootte: " << n << endl;

        bool *kaarten = (bool*)malloc(sizeof(bool) * 4 * n);

        lees_bestand_in(kaarten, n, bestand);

        print_kaarten(kaarten, n);

        free(kaarten);
    }

    return 0;
}
