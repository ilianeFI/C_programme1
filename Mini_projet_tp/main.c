#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

typedef struct date{

    char jour[3];
    char mois[3];
    char anne[5];
}date;

typedef struct produit{

    char  nom_produit[50];
    char  reference [100];
    float Montant;
    date  date_achat;
}produit;

typedef struct liste{

    produit cellule;
    struct liste* link;
}liste;

// fonction qui initialise une liste vide et la retourne :

liste* cree_liste_produit(){

    liste* head=NULL;
    return head;
}

//fonction qui verifie si la liste est vide ou non :

int est_vide(liste *head){

    if(head->link==NULL){
        return 1;

    }
    else{
        return 0;
    }
}

//fonction qui va retourner un produit cree en lui affectant ses donnees :

liste *cree_produit() {
    liste *new = (liste *)malloc(sizeof(liste));
    
    // Nom du produit
    printf("Entrer le nom du produit  : ");
    fflush(stdin);  // Vide le tampon d'entrée
    fgets(new->cellule.nom_produit, sizeof(new->cellule.nom_produit), stdin);
    new->cellule.nom_produit[strcspn(new->cellule.nom_produit, "\n")] = '\0';

    // Référence du produit
    printf("Entrer la reference du produit  : ");
    fflush(stdin);
    fgets(new->cellule.reference, sizeof(new->cellule.reference), stdin);
    new->cellule.reference[strcspn(new->cellule.reference, "\n")] = '\0';

    // Montant du produit
    printf("Entrer le montant du produit : ");
    scanf("%f", &new->cellule.Montant);
    getchar();  // Consomme le '\n' restant après scanf

    // Date d'achat
    printf("Entrer la date dachat du produit :\n");

    // Jour
    printf("Entrer le jour  : ");
    fflush(stdin);
    fgets(new->cellule.date_achat.jour, sizeof(new->cellule.date_achat.jour), stdin);
    new->cellule.date_achat.jour[strcspn(new->cellule.date_achat.jour, "\n")] = '\0';

    // Mois
    printf("Entrer le mois : ");
    fflush(stdin);
    fgets(new->cellule.date_achat.mois, sizeof(new->cellule.date_achat.mois), stdin);
    new->cellule.date_achat.mois[strcspn(new->cellule.date_achat.mois, "\n")] = '\0';

    // Année
    printf("Entrer l'annee  : ");
    fflush(stdin);
    fgets(new->cellule.date_achat.anne, sizeof(new->cellule.date_achat.anne), stdin);
    new->cellule.date_achat.anne[strcspn(new->cellule.date_achat.anne, "\n")] = '\0';

    new->link = NULL;

    return new;
}



//fonction qui affiche l'etat du produit passe en parametres

void afficher_produit(liste* produit){
    printf("-------------------------------------------\n");
    printf("nom du produit : %s",produit->cellule.nom_produit);
    printf("\nReference :%s",produit->cellule.reference);
    printf("\nMontant :%.2f dh",produit->cellule.Montant);
    printf("\nDate dachat :%s/%s/%s",produit->cellule.date_achat.jour,produit->cellule.date_achat.mois,produit->cellule.date_achat.anne);
    
    printf("\n-------------------------------------------\n");
}

//fonction qui ajoute un produit au debut de la liste

liste* ajouter_produit_debut(liste* head){
    liste* new=cree_produit();
    new->link=head;
    head=new;
    return head;
}

//fonction qui ajoute un produit a la fin de la liste

liste* ajouter_produit_fin(liste* head){
    liste* new=cree_produit();
    liste* ptr=head;
    while(ptr->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=new;
    return head;
}

//fonction qui va afficher tous les produits de la liste

void afficher_produits(liste *head){
    liste *ptr;
    float s=0;
    ptr=head;
    while(ptr !=NULL){
        afficher_produit(ptr);
        s+=ptr->cellule.Montant;
        ptr=ptr->link;
    }
    printf("le montant total a payer est :%.2f DH",s);
}

//fonction qui renvoi le nombre du poduits de la liste

int longueur(liste *head){
    liste *ptr;
    int i=0;
    ptr=head;
    while(ptr->link!=NULL){
        i++;
        ptr=ptr->link;
    }
    return i;
}

// une fonction qui affiche seulement les produiut achetee pour la date passe en parametre

void afficher_produit_date(liste *head,date date){
    liste *ptr;
    int found;
    float s=0;
    ptr=head;
    while(ptr!=NULL){
        if(strcmp(ptr->cellule.date_achat.jour,date.jour)==0 && strcmp(ptr->cellule.date_achat.mois,date.mois)==0 && strcmp(ptr->cellule.date_achat.anne,date.anne)==0){
             afficher_produit(ptr);
            found=1;
        }
        s+=ptr->cellule.Montant;
        ptr=ptr->link;
    }
    printf("le montant total a payer est :%.2f DH",s);
    if(found!=1){
        printf("Aucun produit trouve");
    }
}

// une fonction permetant de suprimer le premier produit de la liste

liste *supp_debut(liste* head){
    liste *temp=head;
    head=head->link;
    free(temp);
    return head;

}

// une fonction permetant de suprimer le dernier produit de la liste:

void supp_dernier(liste *head){
    liste *ptr=head;
    liste *temp;
    while(ptr->link->link !=NULL){
        ptr=ptr->link;
    }
    temp=ptr->link;
    ptr->link=NULL;
    free(temp);
}

// fonction qui permet de supprimer le produit ayant la refernce passe en parametre :

liste *renbourser(liste *head,char *refer){
    
    liste *ptr=head;
    //?cas 1: si le produit a supprimer est le premier
    if(strcmp(ptr->cellule.reference,refer)==0){
        head=supp_debut(head);
        return head;
    }
    //?cas 2:si le produit a supprimer est le dernier 
    while(ptr->link !=NULL){
        ptr=ptr->link;  
    }
    if(strcmp(ptr->cellule.reference,refer)==0){
        supp_dernier(head);
        return head;
    }
}

// Fonction pour trier la liste selon le montant (tri par sélection)


void trie_liste(liste *head) {
    if (head == NULL) return; // Si la liste est vide, rien à trier

    liste *ptr, *ptr2, *min;
    produit temp;

    for (ptr = head; ptr != NULL; ptr = ptr->link) {
        min = ptr; // On suppose que le minimum est le nœud actuel
        for (ptr2 = ptr->link; ptr2 != NULL; ptr2 = ptr2->link) {
            if (ptr2->cellule.Montant < min->cellule.Montant) {
                min = ptr2; // On met à jour le minimum
            }
        }

        // Si un plus petit élément est trouvé, on échange les valeurs
        if (min != ptr) {
            temp = ptr->cellule;
            ptr->cellule = min->cellule;
            min->cellule = temp;
        }
    }

    afficher_produits(head); // Affiche la liste triée
}

//fonction qui fusion deux listes chainées a une seule

liste *fusioner(liste* head1,liste* head2){
    liste *ptr=head1;
    while(ptr->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=head2;
    return head1;
}

//fonction qui cree une liste copie profonde de la liste chainée :

liste *cloner_liste(liste* head){
    
    liste *head2=NULL; // new head
    liste *ptr=head;
    liste *new,*ptr2;

    while(ptr->link!=NULL){
        new=(liste *)malloc(sizeof(liste));
        new->cellule=ptr->cellule;
        
        if(head2==NULL){ //si la liste est vide
            head2=new;
            new->link=NULL;
        }

        else{

            ptr2=head2;

           while(ptr2->link !=NULL){
                ptr2=ptr2->link;
           }
           ptr2->link=new;
           ptr2=new;
           ptr2->link=NULL;

        }

        ptr=ptr->link;
    }
    return head2;
}

// fonction pour insérer un produit a une position sépcifique :

liste* inserer_produit(liste* head,liste *produit,int position){
    liste *ptr=head;
    int taill_liste,i;

    taill_liste=longueur(head);
    
    if(position==1){
       produit=ajouter_produit_debut(head);
    }
    if(position==taill_liste){
        produit=ajouter_produit_fin(head);
    }
    else{

        for(i=0;i<position;i++){
            ptr=ptr->link;
        }
        produit->link=ptr->link;
        ptr->link=produit;
    }

    return head;

}

// main fonction : 

int main (){
    liste *head;
    liste *head2;
    liste *produit;
    date date;
    int choix;
    int position;
    char refer[100];
    head=cree_liste_produit();
    head2=cree_liste_produit();
    do{
        printf("1:ajouter un produit au debut de la liste\n");
        printf("2:ajouter un produit a la fin de la liste\n");
        printf("3:afficher les produits de la liste\n");
        printf("4:afficher les produits achetee a une date specifique\n");
        printf("5:supprimer le premier produit de la liste\n");
        printf("6:supprimer le dernier produit de la liste\n");
        printf("7:supprimer un produit ayant une reference specifique\n");
        printf("8:trier la liste selon le montant\n");
        printf("9:fusionner deux listes\n");
        printf("10:cloner une liste\n");
        printf("11:inserer un produit a une position specifique\n");
        printf("12:quitter\n");
        printf("entrer votre choix :");
        scanf("%d",&choix);
        system("cls");
        switch(choix){
            case 1:
                head=ajouter_produit_debut(head);
                 printf("\nproduit ajouter ");
                getche();
                system("cls");
                break;
            case 2:
                head=ajouter_produit_fin(head);
                system("cls");
                break;
            case 3:
                afficher_produits(head);
                printf("\nAppuyez sur Entrer pour continuer...");
                getche();
                system("cls");
                break;
            case 4:
                printf("entrer la date :\n");
                printf("\nentrer le jour:");
                scanf("%s",date.jour);
                getchar();
                printf("\nentrer le mois:");
                scanf("%s",date.mois);
                getchar();
                printf("\nentrer l'annee:");
                scanf("%s",date.anne);
                getchar();
                afficher_produit_date(head,date);
                printf("Appuyez sur Entrer pour continuer...");
                getche(); 
                system("cls");
                break;
            case 5:
                head=supp_debut(head);
                printf("\n\nProduit supprime !!");
                getche();
                system("cls");
                break;
            case 6:
                supp_dernier(head);
                printf("\n\nProduit supprime !!");
                getche();
                system("cls");
                break;
            case 7:
                printf("entrer la reference du produit a supprimer\n");
                scanf("%s",refer);
                head=renbourser(head,refer);
                getchar();
                system("cls");
                break;
            case 8:
                trie_liste(head);
                getche();
                system("cls");
                break;
            case 9:
                head=fusioner(head,head2);
                break;
            case 10:
                head2=cloner_liste(head);
                break;
            case 11:
                printf("\nentrer la position:");
                scanf("%d",&position);
                head=inserer_produit(head,produit,position);
                break;
        }

    }while(choix!=12);
    return 0;
}
