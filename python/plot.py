# Schrijf altijd commentaarregels wanneer je code schrijft ander is het voor mij een puzzel wat
# de functie is van een regel code.
import csv
import matplotlib.pyplot as plt
import matplotlib.cm as cm


def plotfile(filename, title):
    Tmin = 30
    Tmax = 110

    # Parse het .csv-bestand en gebruik de comma als delimiter.
    xarray = []
    yarray = []
    tarray = []

    with open(filename + '.csv') as csvfile:
        readCSV = csv.reader(csvfile, delimiter=',')
        for row in readCSV:
            xarray.append(float(row[0]))
            yarray.append(float(row[1]))
            tarray.append(float(row[3]))
 

    cm = plt.cm.get_cmap('jet')
    sc = plt.scatter(xarray, yarray, marker='o', c = tarray, s=10, cmap=cm, edgecolors='', vmin = Tmin, vmax = Tmax)

    # De labels zijn in LaTeX gedrukt
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')
    plt.title(title)


    cb = plt.colorbar(sc)


    # Bewaar het bestand als .png
    plt.savefig(filename +'.svg', format='svg', dpi=1) # dpi = 1200 voor hogere resolutie.

    plt.show()

