#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


class Kaartspel {

private:

    bool *kaarten;
    size_t n;

public:
    Kaartspel(char *bestand_naam) {

        ifstream bestand(bestand_naam);

        n = 0;
        bestand >> n;

        size_t bytes = sizeof(bool) * 4 * n;

        kaarten = (bool*)malloc(bytes);
        memset(kaarten, false, bytes);

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

    void print_kaarten() {

        for(int i = 0; i < 4; i++) {

            for(int j = 0; j < n; j++) {

                if(kaarten[i * n + j]) cout << '1';
                else cout << '0';
            }

            cout << endl;
        }

    }

    ~Kaartspel() {

        free(kaarten);
    }

};

int main(int argc, char** argv) {

    if(argc < 2) {
        cout << "Geef aub een invoerbestand mee" << endl;
    }
    else {
        char *bestand_naam = argv[1];

        Kaartspel spel(bestand_naam);
        spel.print_kaarten();
    }

    return 0;
}
