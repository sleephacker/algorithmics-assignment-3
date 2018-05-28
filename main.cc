#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

template<class T>
T* maak_array(int N, T waarde) {
	T* arr = new T[N];
	for(int i = 0; i < N; i++) arr[i] = waarde;
	return arr;
}

class Kaartspel {

private:

    bool *kaarten;
    int n;

    int *rijscore_arr;
    int *maxscore_arr;
	
	bool *mogelijke_sets;
	bool *gebruikte_sets;

    // Index in rijscore
    // i >= 0, j >= 0
    int rijscore_index(int i, int j) {
        return rijscore_arr[i * n + j];
    }

    // Index in kaarten
    // i >= 0, j >= 0
    bool kaarten_index(int i, int j) {
        return kaarten[i * n + j];
    }

    void vul_mogelijke_sets() {

        int sets = 0;

		for(int i = 0; i < n; i++) {

			if(mogelijke_set(i)) {
				sets++;

				if(sets < 3) mogelijke_sets[i] = true;
				else if(sets == 3) {
				    
				    mogelijke_sets[i - 1] = mogelijke_sets[i - 2] = false;
				}
				// voor sets > 3 hoeft er niks te gebeuren, mogelijke_sets[i] is al false.
			}
			else sets = 0;
        }

    }

	// geeft een array (met lengte j + 1) met de gebruikte sets door max_score(j)
	// werkt alleen nadat max_score(j) is aangeroepen
	bool* beste_sets(int j) {
		return gebruikte_sets + j * n;
	}


public:

    Kaartspel(char *bestand_naam) {

        ifstream bestand(bestand_naam);

        n = 0;
        bestand >> n;

        kaarten = maak_array<bool>(4 * n, false);
		rijscore_arr = maak_array<int>(n * n, -1);
		maxscore_arr = maak_array<int>(n, -1);
		mogelijke_sets = maak_array<bool>(n, false);
		gebruikte_sets = maak_array<bool>(n * n, false);

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

        vul_mogelijke_sets();
    }

	int grootte() {
		return n;
	}

    bool mogelijke_set(int j) {
    
        return kaarten_index(0, j)
            && kaarten_index(1, j)
            && kaarten_index(2, j)
            && kaarten_index(3, j);
    }


    // Anders dan in opdracht:
    // i >= 0, j >= 0
    // Handiger met indexen
    int rijscore(int i, int j) {
     
        if(i > j || i >= n || j >= n) return 0; // Veiligheids check
        
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
            // Waarde is een hoger dan index

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
          
        int max_score = 0, rechter_set = -1, k = 0;

        for(; k <= j; k++) { 

            if(mogelijke_sets[k]) {
                // Max score door deze set toe te voegen.
                // Het geval dat deze set de 'meest rechter set' is.
                int max_met_set = 4 * (k + 1) + maxscore(k - 1) + rijscore(k + 1, j);
				if(max_met_set > max_score) {
					rechter_set = k;
					max_score = max_met_set;
				}
            }
        }

        // Maar wat als er geen 'meest rechter set' is?
        // dan is de maximale score natuurlijk rijscore(0, j)
        int zonder_set = rijscore(0, j);
		if((zonder_set > max_score) || rechter_set == -1) {
			max_score = zonder_set;
			// geen sets gebruikt, laat alles op false staan
		}
		else {
			// zelfde sets gebruikt als bij max_score(rechter_set - 1)
			// kopieer deze sets en voeg de nieuwe set toe
			int van = (rechter_set - 1) * n;
			int naar = j * n;
			int lengte = rechter_set;
            memcpy(gebruikte_sets + naar, gebruikte_sets + van, sizeof(int) * lengte);
			gebruikte_sets[j * n + rechter_set] = true;
		}

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

	void print_gebruikte_sets(int j) {

		bool* gebruikt = beste_sets(j);

		for(int i = 0; i <= j; i++) {

			if(gebruikt[i]) cout << (i + 1) << ", ";
		}

		cout << endl;
	}

    ~Kaartspel() {

	delete[] kaarten;
	delete[] rijscore_arr;
	delete[] maxscore_arr;
    }

};

int main() {

	char in, *bestand = new char[1000];
	while(true) {
		cout << "1. Los een kaartspel op" << endl;
		cout << "2. Stop het programma" << endl;
		cout << "Maak een keuze: ";
		cin >> in;
		switch(in) {
			case '1':
			{
				cout << "Geef een invoerbestand op: ";
				memset(bestand, 0, 1000 * sizeof(char));
				cin >> bestand;

				if(!ifstream(bestand).good()) {
					cout << "Kan het opgegeven bestand niet openen." << endl;
					break;
				}
				
				Kaartspel spel(bestand);
				cout << "Maximale score: " << spel.maxscore(spel.grootte() - 1) << endl;
				cout << "Gebruikte sets: ";
				spel.print_gebruikte_sets(spel.grootte() - 1);
				
				break;
			}
			case '2':
				return 0;
			default:
				break;
		}
		cout << endl;
	}

	return 0;
}
