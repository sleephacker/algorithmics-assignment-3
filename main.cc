#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


class Kaartspel {

private:

    bool *kaarten;
    size_t n;

    int *rijscore_arr;
    int *maxscore_arr;

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
        maxscore_arr = (int*)malloc(bytes);
        memset(maxscore_arr, -1, bytes);


        // i = -1, verwijder begi&nnende \r\n
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

    int mogelijke_set(int j) {
    
        return kaarten_index(0, j)
            && kaarten_index(1, j)
            && kaarten_index(2, j)
            && kaarten_index(3, j);
    }


    // Anders dan in opdracht:
    // i >= 0, j >= 0
    // Handiger met indexen
    int rijscore(int i, int j) {
     
        int huidig = rijscore_index(i, j);
        if(huidig != -1) return huidig;
          
        if(i >= j || i == j - 1) return (rijscore_arr[i * n + j] = 0);

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

        return (rijscore_arr[i * n + j] = rijscore(i, j - 1) + score);
    }


    // Anders dan in opdracht:
    // j = 0 kan nog steeds punten opleveren.
    // j is namelijk de index in maxscore_arr
    int maxscore(int j) {
    
        int huidig = maxscore_arr[j];
        if(huidig != -1) return huidig;
        
        if(j == 0) return 0;
          
        int max_score = 0, k = 0;

        for(; k <= j; k++) { 

            if(mogelijke_set(k)) {
                // Max score door deze set toe te voegen.
                // Het geval dat deze set de 'meest rechter set' is.
                int set_score = 4 * (k + 1);
                int max_vorige = maxscore(k - 1);
                int rijs = rijscore(k + 1, j);

                int max_met_set = 4 * (k + 1) + maxscore(k - 1) + rijscore(k + 1, j);
                if(max_met_set > max_score) max_score = max_met_set;
            }
        }

        // Maar wat als er geen 'meest rechter set' is?
        // dan is de maximale score natuurlijk rijscore(0, n)
        int zonder_set = rijscore(0, j);
        if(zonder_set > max_score) max_score = zonder_set;

        return (maxscore_arr[j] = max_score);
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
        free(maxscore_arr);
    }

};

int main(int argc, char** argv) {

    if(argc < 2) {
        cout << "Geef aub een invoerbestand mee" << endl;
    }
    else {
        char *bestand_naam = argv[1];

        Kaartspel spel(bestand_naam);
        cout << spel.maxscore(9) << endl;
    }

    return 0;
}
