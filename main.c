#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
/*** declaration de la structure etudiant ***/
struct etudiant
{
    char nom[22];
    char prenom[34];
    int key;
};typedef struct etudiant ETUD;
/***declaration de l'arbre binaire de recherche "Arbre". o๙ SAG=="Suite de l'Arbre เ Gauche"***/
typedef struct Arbre
{
	ETUD d;
	struct Arbre * SAG;
	struct Arbre * SAD;
} Arbre;
  /*** fonction permettant d'afficher les etudiants(situ้s dans le noeuds) dans l'ordre croissant en utilisant la "key" de l'etudiant comme crit่re de tri**/
liste_decroissante(Arbre * Racine)
{
	if (Racine!=NULL)
	{   /*** affichage de la branche gauche, car elle est la plus petite selon la "key" des etudiants***/
		liste_decroissante(Racine->SAG);
		/*** affichage de la racine***/
		printf("\t\t\t%s %s %d \n",Racine->d.nom,Racine->d.prenom,Racine->d.key);
		/***affichage de la branche droite***/
		liste_decroissante(Racine->SAD);
	}
}
/*** fonction qui permet de creer un noeud, c'est เ dire inserer un nouveau etudiant "f" dans l'arbre "racine"***/
Arbre * insertion_noeud(Arbre * Racine,ETUD f)
{
	if (Racine!=NULL)
	{
		if (Racine->d.key>f.key)// si la key du nouveau element est inferieure เ la key de l'etudiant เ ajouter
		{
			Racine->SAG=insertion_noeud(Racine->SAG,f);//insertion gauche
		}
		else  // si non
		{
			Racine->SAD=insertion_noeud(Racine->SAD,f);//insertion  droite
		}
	}
	else
	{
		Racine=(Arbre *)malloc(sizeof(Arbre));
		Racine->d=f;
		Racine->SAD=NULL;
		Racine->SAG=NULL;
	}
return Racine;
}

affichageDeArbre(Arbre * Racine)
{   system("color 4E"); /*** permet de changer la couleur de la console et la couleur des ecritures***/
	if (Racine!=NULL)
	{
		printf("\t\t%s %s %10d \n",Racine->d.nom,Racine->d.prenom,Racine->d.key);

		if (Racine->SAD!=NULL || Racine->SAG!=NULL)
		{
			affichageDeArbre(Racine->SAG);
			affichageDeArbre(Racine->SAD);
		}
	}
}

EnregArbreDansFichier(Arbre * Racine,char * NomFic)
{
	//int nb;
	FILE * fic;
	fic=fopen(NomFic,"a+");
	if (Racine!=NULL)
	{
		/*nb=Racine->d.key;
		fwrite(&nb,sizeof(int),1,fic);*/
		fprintf(fic,"%s %s %10d\n",Racine->d.nom,Racine->d.prenom,Racine->d.key);
		fclose(fic);
		if (Racine->SAD!=NULL || Racine->SAG!=NULL)
		{
			EnregArbreDansFichier(Racine->SAG,NomFic);
			EnregArbreDansFichier(Racine->SAD,NomFic);
		}
	}
}
/********** insertion d'un noeud(arbre)**********/
Arbre * insertion_d_un_noeud(Arbre * Racine,char * NomFic)
{
    ETUD m;
	FILE * fic;
	fic=fopen(NomFic,"r+");
	//fscanf(fic,"%s %s %10d",Racine->d.nom,Racine->d.prenom,&Racine->d.key);
	//fread(&m,sizeof(int),1,fic);
	while (!feof(fic))
	{
	    fscanf(fic,"%s %s %10d",m.nom,m.prenom,&m.key);
		Racine = insertion_noeud(Racine,m);

		//fread(&m,sizeof(int),1,fic);

	}
	fclose(fic);
	return Racine;
}
///
/*Arbre * insertion_d_un_noeud(Arbre * racine, char * nomFic)
{

}*/
/*** affichage dans l'ordre croissante( avec la key comme crit่re de tri) ***/
liste_croissante(Arbre * Racine)
{   //PERMET DE MODIFIER LA COULEUR DE L'INTERFACE ET DES ECRITURES

	if (Racine!=NULL)
	{
		liste_croissante(Racine->SAD);
		printf("\t\t\t%s %s %d \n",Racine->d.nom,Racine->d.prenom,Racine->d.key);
		liste_croissante(Racine->SAG);
	}
}
/********** addition des cl้s de tous les noeuds de l'arbre**********/
int addition_keys(Arbre * Racine)
{
	int total=0;
	if (Racine!=NULL)
	{
		total=addition_keys(Racine->SAG);
		total+=Racine->d.key;
		total+=addition_keys(Racine->SAD);
	}
	return total;
}
/******************** fonction permettant de compter le nombre de noeuds se trouvant dans l'arbre********************/
int noeudsTotaux(Arbre * Racine)
{   system("color 2");
	int total=0;
	if (Racine!=NULL)
	{
		total=noeudsTotaux(Racine->SAG);
		total++;
		total+=noeudsTotaux(Racine->SAD);
	}
	return total;
}
/******************** fonction permettant la recherche d'un noeud grace เ sa cl้********************/
Arbre * Recherche_d_un_noeud(Arbre * Racine,  int valeur)
{
	if (Racine!=NULL)
	{
		if (Racine->d.key>valeur)
		{
			Racine=Recherche_d_un_noeud(Racine->SAG,valeur);
		}
		else
		{
			if (Racine->d.key<valeur)
			{
				Racine=Recherche_d_un_noeud(Racine->SAD,valeur);
			}
		}
		return Racine;
	}
}
/******************** fonction suppression***********************/
Arbre * supprimer_un_noeud(Arbre * Racine, int valeur)
{
	Arbre * noeud_a_supprimer;
	if (Racine->d.key==valeur) // on a trouv้ l'้l้ment เ supprimer
	{
		noeud_a_supprimer=Racine;
		if (noeud_a_supprimer->SAG==NULL) //si ya pa de SAG, on retourne SAD
			return noeud_a_supprimer->SAD;
		else
		{
			Racine=noeud_a_supprimer->SAG; //sinon on recherche dans SAG l'endroit pour ins้rer le SAD
				while (Racine->SAD!=NULL)
				{
					Racine=Racine->SAD;
				}
				Racine->SAD=noeud_a_supprimer->SAD;
			return noeud_a_supprimer->SAG;
		}
		free(noeud_a_supprimer);
	}
	else
	{
		if (Racine->d.key>valeur)
		{
			Racine->SAG=supprimer_un_noeud(Racine->SAG,valeur);
		}
		else
		{
			Racine->SAD=supprimer_un_noeud(Racine->SAD,valeur);
		}
	}
	return Racine;
}
/********************* fonction d'affichage du menu ********************/
int menu()
{
	int Choix;
	do
	{
		system("cls"); //efface l'้cran
		printf("             ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n");
		printf("             บ                                                      บ\n");
		printf("             บ                    menu Principal                    บ\n");
		printf("             บ                                                      บ\n");
		printf("             ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n");
		printf("\n                 1- Ajouter un noeud");
		printf("\n                 2- Afficher l'arbre");
		printf("\n                 3- Afficher l'arbre dans l'ordre croissant");
		printf("\n                 4- Afficher l'arbre dans l'ordre decroissant");
		printf("\n                 5- addition_keys des noeuds");
		printf("\n                 6- Nombre de noeuds");
		printf("\n                 7- Rechercher un noeud");
		printf("\n                 8- Enlever un noeud");
		printf("\n                 9- Enregister l'arbre dans un fichier");
		printf("\n                10- Charger l'arbre \205 partir d'un fichier");
		printf("\n                11- Quitter\n");
		printf("\n\n\n\n\n\n\nChoix :");
		scanf("%d",&Choix);
	} while (Choix <1 || Choix >11);
	system("cls");
	return Choix;
}
/******************** la fonction main********************/
main()
{     system("color 2F");

    int valeur;
    ETUD k[20];
	int Choix;
	char * NomFic="Fic.txt";
	Arbre * Racine;
	Arbre * RepRecherche;
	Racine=NULL;
	Choix = menu();
	int n;
	while (Choix!=11)
	{
		if (Racine==NULL && Choix>1 && Choix <10)
		{
			printf("Vous devez d'abord saisir un arbre");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
			getch();
		}
		else
		{
			switch (Choix)
			{
				case 1 :   system("color F0");

				    printf("entrez le nombre d'etudiants que vous voulez enregistrer");
                        scanf("%d",&n);
				    for(int i=0;i<n;i++)
				   {


				    printf("Saisir le nom de l'etudiant \n ");
							scanf("%s",k[i].nom);
							printf("saisir le prenom de l'etudiant:\n");
							scanf("%s",k[i].prenom);
							printf("entrez le numero identifiant l'etudiant (0 pour finir la saisie) :\n");
							scanf("%d",&k[i].key);



								Racine=insertion_noeud(Racine,k[i]);

                        printf("\n\n\n\t\t encore un etudiant\n\n");
				   }
							getch();
							break;
				case 2 :    printf("les etudiants dans l'arbre sont:\n\n\n");
				    affichageDeArbre(Racine);
							printf("\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 3 :	system("color 9A");
				    printf("les etudiants dans l'arbre dans l'ordre decroissant sont:\n\n\n");
                    liste_decroissante(Racine);
							printf("\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 4 :	system("color 5A");
				    printf("les etudiants dans l'arbre dans l'ordre croissant sont:\n\n\n");
				    liste_croissante(Racine);

							printf("\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 5 :	system("color FC");
                            liste_decroissante(Racine);
							printf("\nTotal : %d",addition_keys(Racine));
							printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 6 :	 system("color 4D");
				    liste_decroissante(Racine);
							printf("\nTotal : %d",noeudsTotaux(Racine));
							printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 7 :	system("color 4A");
                            printf("Saisir la valeur \205 rechercher : ");
							scanf("%d", &valeur);
							RepRecherche=Recherche_d_un_noeud(Racine,valeur);
							if (RepRecherche->d.key==valeur)
							{
                            printf("%s %s %d \n",Racine->d.nom,Racine->d.prenom,Racine->d.key);							}
							else
							{
								printf("Impossible de trouver la valeur recherch\202e");
							}
							printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 8 :	system("color 2F");
                            printf("Saisir la valeur du noeud \205 supprimer : \n");
							scanf("%d",&valeur);
							Racine=supprimer_un_noeud(Racine,valeur);
							printf("\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 9 :	system("color 2F");
                            system("del Fic.txt");
							system("cls");
							EnregArbreDansFichier(Racine,NomFic);
							printf("Arbre enregistr\202\n");
							printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
				case 10 :	Racine=insertion_d_un_noeud(Racine,NomFic);
							printf("Arbre charg\202\n");
							printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
							getch();
							break;
			}
		}
		Choix=menu();
	}
}


