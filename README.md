# algorithmics-assignment-3

## algoritme

### max_score: O(n^2)
```C#
int max_score(int j)
{
	if(mogelijke_sets.contains(j))
		return waarde_van_set(j) + (j == 0 ? 0 : max_score(j - 1));
	
	int max = Integer.MIN_VALUE;
	foreach(int i in mogelijke_sets)
		if(i < j)
		{
			int score = max_score(i) + rij_score(i + 1, j);
			if(score > max)
				max = score;
		}
	return max;
}
```
Dit lijkt op O(n!), maar dat is het niet als je begint bij `max_score(0)` en een lookup table bijhoudt voor iedere volgende `max_score(j)`. `max_score(j)` roept nooit `max_score(i)` aan met `i >= j`. In dat geval kan iedere `max_score()` binnen de functie als O(1) beschouwd worden, en komt de functie kwa complexiteit ongeveer neer op:
```C#
int max_score(int j)
{
	int[] tussentijds_resultaat = new int[j + 1];
	for(int i = 0; i <= j; i++)
	{
		foreach(int k in mogelijke_sets) // deze loop komt overeen met de loop in de bovenstaande functie
			if(k < i)
				// doe iets O(1)
		tussentijds_resultaat[i] = ...; // dit komt overeen met de laatste return in de bovenstaande functie
	}
	return tussentijds_resultaat[j];
}
```

### rij_score: O(1)
```C#
int rij_score(int i, int j) => lookup[i, j];
```

### init_lookup: O(n^2)
```C#
int[,] lookup = new int[N, N];

void init_lookup()
{
	// initialiseer variabelen
	for(int i = 0; i < N; i++)
		for(int j = i; j < N; j++)
			for(int figuur = 0; figuur < 4; figuur++)
			{
				// bereken rij_score(i, j) op basis van variabelen en kaarten[figuur, j]
				// werk variabelen bij op basis van kaarten[figuur, j]
				// lookup[i, j] = de_juiste_waarde
			}
}
```

### De reden voor een lookup table
Zonder een lookup table zou `rij_score()` O(n) en `max_score()` O(n^3) worden, aangezien er dan O(n^2) keer een functie van O(n) wordt aangeroepen.
