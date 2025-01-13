
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bibb.h"

Livre livres[MAX_LIVRES];
int nbLivres = 0;

void chargerLivres() {
    FILE *fichier = fopen("real_books.csv", "r");
    if (!fichier) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    Livre livre;
    nbLivres = 0; // Reset the counter before loading books
    while (fscanf(fichier, "%d,%99[^,],%99[^,],%199[^,],%49[^,],%f,%49[^,],%d\n",
                  &livre.id, livre.titre, livre.auteur, livre.description, livre.utilisateur,
                  &livre.prix, livre.categorie, &livre.disponibilite) == 8) {
        livres[nbLivres++] = livre;
    }

    fclose(fichier);
}

void ajouterLivre(Livre livre) { // fonction pour ajouter un livre
    FILE *fichier = fopen("real_books.csv", "a");
    if (!fichier) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "%d,%s,%s,%s,%s,%.2f,%s,%d\n",
            livre.id,
            livre.titre,
            livre.auteur,
            livre.description,
            livre.utilisateur,
            livre.prix,
            livre.categorie,
            livre.disponibilite);

    fclose(fichier);
    printf("Livre ajouté avec succès.\n");
}

void afficherLivres() { // Fonction pour afficher tous les livres
    chargerLivres(); // Ensure the books are loaded before displaying

    printf("ID,Titre,Auteur,Description,Utilisateur,Prix,Catégorie,Disponibilité\n");
    for (int i = 0; i < nbLivres; i++) {
        printf("%d,%s,%s,%s,%s,%.2f,%s,%d\n",
               livres[i].id,
               livres[i].titre,
               livres[i].auteur,
               livres[i].description,
               livres[i].utilisateur,
               livres[i].prix,
               livres[i].categorie,
               livres[i].disponibilite);
    }
}

void rechercherLivre(char *titreRecherche) { // fonction pour rechercher un livre
    chargerLivres(); // Load the books from the file before searching

    int trouve = 0;
    for (int i = 0; i < nbLivres; i++) {
        if (strstr(livres[i].titre, titreRecherche)) {
            printf("Livre trouvé : %d,%s,%s,%s,%s,%.2f,%s,%d\n",
                   livres[i].id,
                   livres[i].titre,
                   livres[i].auteur,
                   livres[i].description,
                   livres[i].utilisateur,
                   livres[i].prix,
                   livres[i].categorie,
                   livres[i].disponibilite);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun livre trouvé avec le titre \"%s\".\n", titreRecherche);
    }
}

void modifierLivre(int idModif) { // fonction pour modifier un livre
    chargerLivres(); // Load the books before modifying

    FILE *fichier = fopen("real_books.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers.\n");
        return;
    }

    Livre livreModifie;
    char ligne[500];
    int id;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        sscanf(ligne, "%d,", &id);
        if (id == idModif) {
                printf("Entrez les nouvelles informations :\n");
                livreModifie.id = id;  // Preserve the ID
                printf("Titre : ");
                scanf(" %[^\n]", livreModifie.titre);
                printf("Auteur : ");
                scanf(" %[^\n]", livreModifie.auteur);
                printf("Description : ");
                scanf(" %[^\n]", livreModifie.description);
                printf("Utilisateur : ");
                scanf(" %[^\n]", livreModifie.utilisateur);
                printf("Prix : ");
                scanf("%f", &livreModifie.prix);
                printf("Catégorie : ");
                scanf(" %[^\n]", livreModifie.categorie);
                printf("Disponible (1: Oui, 0: Non) : ");
                scanf("%d", &livreModifie.disponibilite);

            fprintf(temp, "%d,%s,%s,%s,%s,%.2f,%s,%d\n",
                    livreModifie.id,
                    livreModifie.titre,
                    livreModifie.auteur,
                    livreModifie.description,
                    livreModifie.utilisateur,
                    livreModifie.prix,
                    livreModifie.categorie,
                    livreModifie.disponibilite);
            trouve = 1;
        } else {
            fputs(ligne, temp);
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("real_books.csv");
    rename("temp.csv", "real_books.csv");

    if (trouve) {
        printf("Livre modifié avec succès.\n");
    } else {
        printf("Livre avec ID %d introuvable.\n", idModif);
    }
}

void supprimerLivre(int idSupp) {    // fonction pour supprimer un livre
    chargerLivres(); // Load the books before deleting

    FILE *fichier = fopen("real_books.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (!fichier || !temp) {
        printf("Erreur d'ouverture des fichiers.\n");
        return;
    }

    char ligne[500];
    int id;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        sscanf(ligne, "%d,", &id);
        if (id != idSupp) {
            fputs(ligne, temp);
        } else {
            trouve = 1;
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("real_books.csv");
    rename("temp.csv", "real_books.csv");

    if (trouve) {
        printf("Livre supprimé avec succès.\n");
    } else {
        printf("Livre avec ID %d introuvable.\n", idSupp);
    }
}

void trierParTitre() {
    chargerLivres();  // Load the books from the file before sorting
    for (int i = 0; i < nbLivres - 1; i++) {
        for (int j = 0; j < nbLivres - i - 1; j++) {
            if (strcmp(livres[j].titre, livres[j + 1].titre) > 0) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }
    printf("Les livres ont été triés par titre.\n");
}

void trierParCategorie() {
    chargerLivres();  // Load the books from the file before sorting
    for (int i = 0; i < nbLivres - 1; i++) {
        for (int j = 0; j < nbLivres - i - 1; j++) {
            if (strcmp(livres[j].categorie, livres[j + 1].categorie) > 0) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }
    printf("Les livres ont été triés par catégorie.\n");
}



