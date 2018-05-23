#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


class Kaartspel {

private:

    bool *kaarten;
    size_t n;

    int *rijscore_arr;
    int *maxscore;

    // Index in rijscore
    // i >= 0, j >= 0
    int rijscore_index(int i, int j) {
        return rijscore_arr[i * n + j];
    }

    // Index in kaarten
    // i >= 0, j >= 0
    int kaarten_index(int i, int j) {
        return kaarten[i * n + j];
    }
public:
    Kaartspel(char *bestand_naam) {

        ifstream bestand(bestand_naam);

        n = 0;
        bestand >> n;

        size_t bytes = sizeof(bool) * 4 * n;

        kaarten = (bool*)malloc(bytes);
        memset(kaarten, false, bytes);

        bytes = sizeof(int) * n * n;
        rijscore_arr = (int*)malloc(bytes);
        memset(rijscore_arr, -1, bytes);

        bytes = sizeof(int) * n;
        maxscore = (int*)malloc(bytes);
        memset(maxscore, -1, bytes);


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

    // Anders dan in opdracht:
    // i >= 0, j >= 0
    // Handiger met indexen
    int rijscore(int i, int j) {
     
        int huidig = rijscore_index(i, j);
        if(huidig != -1) return huidig;
          
        if(i == j || i == j - 1) return (rijscore_arr[i * n + j] = 0);

        // Bekijk of er voorgaande kaarten zijn
        // waarmee we een rij kunnen vormen
        // die eindigt op j.
        
        int score = 0;

        for(int k = 0; k < 4; k++) { // Loop rijen

            int l;
            
            // Loop kolommen
            for(l = j; l >= 0; l--) if(!kaarten_index(k, l) || j - l == 4) break;

            // l 'wijst' nu net voor de start
            // van een mogelijke rij.
            // Waarde is één hoger dan index

            if(j - l == 3) score += (j + 1) + j + j - 1;

            // Voorliggende rij wordt al meegenomen door rijscore(i, j - 1)
            if(j - l == 4) score += j + 1; 
        }

        return rijscore(i, j - 1) + score;
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
        free(rijscore_arr);
        free(maxscore);
    }

};

int main(int argc, char** argv) {

    if(argc < 2) {
        cout << "Geef aub een invoerbestand mee" << endl;
    }
    else {
        char *bestand_naam = argv[1];

        Kaartspel spel(bestand_naam);
        cout << spel.rijscore(0, 9) << endl;
    }

    return 0;
}
