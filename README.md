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


