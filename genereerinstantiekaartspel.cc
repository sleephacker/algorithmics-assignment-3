// Hulpprogramma bij programmeeropdracht 3 van Algoritmiek, voorjaar 2018.
// Genereert random instantie voor Kaartspel, bij een door
// de gebruiker opgegeven waarde n. De gebruiker geeft ook op wat de kans
// moet zijn dat een kaart aanwezig is of niet.
//
// De random instantie bestaat uit vier bitstrings ter lengte n,
// die aangeven of een kaart wel (bit = 1) of niet (bit = 0) aanwezig is.
//
//   Rudy van Vliet, 4 mei 2018.

#include <cstdlib>
#include <iostream>

using namespace std;

//****************************************************************************

int main() {
	int n,
		kans,
		kleur, i,
		r;

	cout << "Geef n: ";
	cin >> n;
	cout << "Geef een geheel getal tussen (en inclusief) 0 en 100,\n";
	cout << "  de kans (als percentage) voor een willekeurige kaart\n";
	cout << "  om aanwezig te zijn: ";
	cin >> kans;

	cout << endl;
	cout << n << endl;

	srand((unsigned)time(0));
	for(kleur = 1; kleur <= 4; kleur++) {
		for(i = 1; i <= n; i++) {
			r = ((rand()) % 100) + 1;  // een random geheel getal tussen
									// (en inclusief) 1 en 100
			if(r <= kans)
				cout << '1';
			else
				cout << '0';
		}
		cout << endl;
	}

	return 0;

}
