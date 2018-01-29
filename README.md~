# FEM-opdracht-jaar3

Dit is de GitHub voor ons project. Wanneer je begint altijd het commando uitvoeren:

git pull

Wanneer je klaar bent of je wijziging wilt toevoegen gebruik commando:

git add hier-het-naam-van-het-bestand

Dan een commentaarregel geven:

git commit -m "een-regel-tekst-tussen-de-aanhalingstekens"

En dan het commando:

git push

Voer je gebruikernaam in en wachtwoord. Succes!

***********************- 23 jan 2017 -***********************
Code gecontroleerd op berekenen van oppervlakte van elementen.
Geen fouten gevonden.

Nieuwe map "examples" gemaakt waar code komt waarbij we op een simpel object de FEM testen. 

Nieuwe klasse gemaakt "FEMmetal" waarbij we de tijdsafhankelijke FEM testen op een vierkant stuk metaal.

FEMmetal: berekenen van de C-matrix is geïmplementeerd.
FEMmetal: berekenen van de Kd-matrix is geïmplementeerd.
FEMmetal: invoeren van waarden op randen is geïmplementeerd.
FEMmetal: Assembly van C, Kd is geïmplementeerd. Verder werken aan Ti en Ti+1.

Typefout in solvingHeatEq2DFEM.pdf gecorrigeerd.

***********************- 24 jan 2017 -***********************
FEMmetal: fouten opgelost. 
FEMmetal: PROBLEEM!: ASSEMBLY WERKT NIET CORRECT!
FEMmetal: Assembly subroutine moet herschreven worden want werkt niet voor 2D.
FEMmetal: Assembly subroutine herschreven. Geen foutmeldingen. Onduidelijk is of dit correct is.
FEMmetal: Complete vergelijking in code geschreven. Onduidelijk is of het correct is.
Interpolator: Begin schrijven aan de interpolator. 
Interpolator: Klaar schrijven van klasse Interpolator. Klasse vormt basis voor overerving.
TriangleInterpolation: Begin schrijven van de klasse. 
TriangleInterpolation: Klasse is klaar. 
Modelering van hitte vergelijking in metaal is klaar. De oplossing is NIET CORRECT! Morgen debuggen!!!

***********************- 25 jan 2017 -***********************
Start debugging. Is mijn uitwerking correct? Onzekerheid over de boundary matrix die ik heb gelijkgesteld aan 0. Voor de rest geen fouten kunnen opsporen. Start controleren FEMmetal class. Geen fouten kunnen vinden in FEMmetal class. Start van controle van convergentie van test.obj wanneer t naar oneindig gaat. test.obj convergeert naar de juiste waarde rond 50 000 seconden. Het lijkt te werken voor test.obj. Voor mesh.obj gaat het fout.
Start controleren Interpolator class en TriangleInterpolator class. Interpolator lijkt geen fouten te hebben. FOUT GEVONDEN!!! Na een hele dag te hebben verneukt aan het vinden van een fout in mijn code komt het er op neer dat de interpolatiefunctie N3 in het boek een typefout heeft. Deze komt voort uit het boek van stinkhoer Quek. Fout is aangepast in solvingHeatEq2DFEM.pdf en in de code en werkt nu correct. Code getest vlakken met hoger aantal aan elementen. Dit is gelukt. Echter is de tijd die ervoor nodig is voor fatsoanlijke convergentie behoorlijk hoog. Constanten niet juist??? Morgen: garbage collecting (RAM gehuigen raakt overbodig vol) en code efficienter maken. Nieuwe map "plots" gemaakt.

***********************- 26 jan 2017 -***********************
Garbage collecting gedaan voor een klein deel. Code iets wat efficienter gemaakt. Status in procenten toegevoegd.

***********************- 27 jan 2017 -***********************
Simulatie van andere vormen. Garbage collecting ongedaan gemaakt vanwege errors.

***********************- 28 jan 2017 -***********************
Samenvoegen van Pythoncode met C++. Pythoncode aangepast. Plotjes gemaakt van verschillende vormen.
ReadFromOBJ aangepast om backslash te negeren in .obj bestanden. Process van plotten geautomatiseerd. 


