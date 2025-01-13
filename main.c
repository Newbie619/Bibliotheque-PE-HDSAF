

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bibb.h"

int main() {
    Livre livreModifie;
    int choix;
    char Nom[50]; // fonction pour saisir le nom de l'utilisateur

    // Saisie du nom de l'utilisateur
    do {
        printf("Saisir votre nom pour commencer utiliser l'application \n");
        scanf("%[^\n]s", Nom);
        if (strlen(Nom) == 0) {
            printf("Erreur de saisie\n");
        }
    } while (strlen(Nom) == 0);

    do {
        printf("***********Menu de Gestion de Bibliothèque************\n\n");
        printf("1 - Ajouter un livre\n");
        printf("2 - Afficher tous les livres\n");
        printf("3 - Rechercher un livre\n");
        printf("4 - Modifier un livre\n");
        printf("5 - Supprimer un livre\n");
        printf("6 - Trier les livres par titre\n");
        printf("7 - Trier les livres par catégorie\n");
        printf("8 - Fin de traitement\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                // Ajouter un livre
                printf("Entrez l'ID du livre : ");
                scanf("%d", &livreModifie.id);
                printf("Entrez le titre : ");
                scanf(" %[^\n]", livreModifie.titre);
                printf("Entrez l'auteur : ");
                scanf(" %[^\n]", livreModifie.auteur);
                printf("Entrez une description : ");
                scanf(" %[^\n]", livreModifie.description);
                printf("Entrez le nom de l'utilisateur : ");
                scanf(" %[^\n]", livreModifie.utilisateur);
                printf("Entrez le prix : ");
                scanf("%f", &livreModifie.prix);
                printf("Entrez la catégorie : ");
                scanf(" %[^\n]", livreModifie.categorie);
                printf("Disponible (1: Oui, 0: Non) : ");
                scanf("%d", &livreModifie.disponibilite);

                ajouterLivre(livreModifie);
                break;
            }
            case 2: {
                // Afficher tous les livres
                afficherLivres();
                break;
            }
            case 3: {
                // Rechercher un livre
                char titrerecherche[100];
                printf("Entrez le titre du livre à rechercher : ");
                scanf(" %[^\n]", titrerecherche);
                rechercherLivre(titrerecherche);
                break;
            }
            case 4: {
                // Modifier un livre
                int idModif;
                printf("Entrez l'ID du livre à modifier : ");
                scanf("%d", &idModif);
                modifierLivre(idModif);
                break;
            }
            case 5: {
                // Supprimer un livre
                int idSupp;
                printf("Entrez l'ID du livre à supprimer : ");
                scanf("%d", &idSupp);
                supprimerLivre(idSupp);
                break;
            }
            case 6: {
                // Trier les livres par titre
                trierParTitre();
                afficherLivres();
                break;
            }
            case 7: {
                // Trier les livres par catégorie
                trierParCategorie();
                afficherLivres();
                break;
            }
            case 8: {
                printf("Fin de traitement\n");
                break;
            }
            default:
                printf("Choix erroné ! Veuillez entrer un choix entre [1-8]\n\n");
        }
    } while (choix != 8);

    return 0;
}




