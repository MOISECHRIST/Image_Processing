#include <stdio.h>
#include <stdlib.h>

// Fonction pour enregistrer l'histogramme dans un fichier PPM
void saveHistogramToPPM(int hist[], int bins) {
    FILE *file = fopen("histogram.pgm", "wb");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    unsigned char *hist_char=(unsigned char *)malloc(bins*50*100*sizeof(unsigned char *));


    fprintf(file, "P5\n%d %d\n255\n", bins * 50, 100);
    for (int i = 1; i <= bins; i++) {
        int count = hist[i];
        
        for (int j = 0; j < count; j++) {
            fprintf(file, "255 0 0 "); // Rouge pour les barres de l'histogramme
        }
    }

    fclose(file);
    printf("L'histogramme a été enregistré dans le fichier 'histogram.ppm'.\n");
}

int main() {
    // ... (votre code pour générer l'histogramme)

    // Exemple de données d'histogramme (à remplacer par vos propres données)
    int hist[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    saveHistogramToPPM(hist, 10);

    return 0;
}
