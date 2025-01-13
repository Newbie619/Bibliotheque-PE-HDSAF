

#pragma once
#define BIBB_H

#define MAX_LIVRES 100

typedef struct {
    int id;
    char titre[100];
    char auteur[100];
    char description[200];
    char utilisateur[50];
    float prix;
    char categorie[50];
    int disponibilite; // 1 pour disponible, 0 pour non disponible
} Livre;

// Function prototypes
void ajouterLivre(Livre livre);
void afficherLivres();
void rechercherLivre(char *titreRecherche);
void modifierLivre(int idModif);
void supprimerLivre(int idSupp);
void trierParTitre();
void trierParCategorie();
void chargerLivres();  // To load the books from the file







