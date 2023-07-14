
#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSUS 10
#define MAX_RESSOURCES 10

int Disponible[MAX_RESSOURCES];
int Max[MAX_PROCESSUS][MAX_RESSOURCES];
int Alloue[MAX_PROCESSUS][MAX_RESSOURCES];
int Besoin[MAX_PROCESSUS][MAX_RESSOURCES];
bool Termine[MAX_PROCESSUS];
bool estAllocationSecurisee(int processus) {
    int travail[MAX_RESSOURCES];
    bool fini[MAX_PROCESSUS];
    int sequence[MAX_PROCESSUS];
    int indice = 0;
    // Copie des valeurs disponibles
    for (int i = 0; i < MAX_RESSOURCES; i++) {
        travail[i] = Disponible[i];
    }
    
    // Initialisation des processus non termines
    for (int i = 0; i < MAX_PROCESSUS; i++) {
        fini[i] = Termine[i];
    }
    
    int compteur = 0;
    while (compteur < MAX_PROCESSUS) {
        bool alloue = false;
        for (int p = 0; p < MAX_PROCESSUS; p++) {
            if (!fini[p]) {
                bool suffisant = true;
                for (int r = 0; r < MAX_RESSOURCES; r++) {
                    if (Besoin[p][r] > travail[r]) {
                        suffisant = false;
                        break;
                    }
                }
                if (suffisant) {
                    for (int r = 0; r < MAX_RESSOURCES; r++) {
                        travail[r] += Alloue[p][r];
                    }
                    fini[p] = true;
                    sequence[indice++] = p;
                    alloue = true;
                    compteur++;
                }
            }
        }
        if (!alloue) {
            break;
        }
    }
    // Vérification si tous les processus sont termines
    for (int i = 0; i < MAX_PROCESSUS; i++) {
        if (!fini[i]) {
            return false;
        }
    }
    // Affichage de la sequence sure
    printf("Sequence sure : ");
    for (int i = 0; i < MAX_PROCESSUS; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
    
    return true;
}
bool estDemandeValide(int processus) {
    for (int i = 0; i < MAX_RESSOURCES; i++) {
        if (Besoin[processus][i] > Max[processus][i]) {
            return false;
        }
    }
    return true;
}
void libererRessources(int processus) {
    for (int i = 0; i < MAX_RESSOURCES; i++) {
        Disponible[i] += Alloue[processus][i];
        Alloue[processus][i] = 0;
        Besoin[processus][i] = 0;
    }
    Termine[processus] = true;
}
void algorithmeBanquier() {
    while (true) {
        bool termine = true;
        for (int p = 0; p < MAX_PROCESSUS; p++) {
            if (!Termine[p]) {
                bool demandeValide = estDemandeValide(p);
                if (demandeValide) {
                                       bool allocationSecurisee = estAllocationSecurisee(p);
                    if (allocationSecurisee) {
                        // Allouer les ressources au processus
                        for (int r = 0; r < MAX_RESSOURCES; r++) {
                            Disponible[r] -= Besoin[p][r];
                            Alloue[p][r] += Besoin[p][r];
                            Besoin[p][r] = 0;
                        }
                        libererRessources(p);
                        printf("Processus %d : Alloue les ressources\n", p);
                    }else {
                        termine = false;
                    }
                } else {
                    printf("Processus %d : Demande invalide\n", p);
                    termine = false;
                }
            }
        }
        
        if (termine) {
            break;
        }
    } 
    
    // Vérification si tous les processus ont termine
    bool tousTermines = true;
    for (int p = 0; p < MAX_PROCESSUS; p++) {
        if (!Termine[p]) {
            tousTermines = false;
            break;
        }
    }
    
    if (tousTermines) {
        printf("Aucun interblocage detecte.\n");
    } else {
        printf("Interblocage detecte.\n");
    }
}

int main() {
    // Initialisation des tableaux et des ressources disponibles
    
    // Exécution de l'algorithme du banquier
    algorithmeBanquier();
    
    return 0;
}
