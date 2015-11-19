//
//  main.cpp
//  Devoir6INFO2012
//
//  Created by Yann Ouedraogo on 2014-11-08.
//  Copyright (c) 2014 Yann Ghislain Ouedraogo. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <time.h>
using namespace std;
// on definit un nouveau type capable de pointer a 2 endroit et de de sauvegarder un entier
typedef struct binNoeud
{
    int data;
    binNoeud* left;
    binNoeud* right;
}binNoeud;
// class binary search tree avec les prototypes des fonction necessaire
class BST
{
private:
    binNoeud* racine;
    void inserthelp(int data,binNoeud* pointeur);
public:
    BST();
    void insert(int data);
    void printhelp(binNoeud* racine,int niveau);
    void print(int data);
    binNoeud* supp(binNoeud*& racine);
    void supphelper(binNoeud*&,int data);
    void remove(int& data)
    {
        supphelper(racine,data);
    };
};
BST::BST()//constructeur
{
    racine=NULL;
}
void BST::insert(int data)
{
    binNoeud* n= new binNoeud;//creation d
    binNoeud* parent=NULL;
    n->data=data;//ajout de la valeur en parametre
    n->left=NULL;
    n->right=NULL;
    if (racine==NULL)// si la racine est vide
    {
        racine=n;// faire pointer la racine vers ce que n pointe et il se trouve que n->data contient la valeur ajouter
    }
    else// sinon
    {
        binNoeud*curr=NULL;//le pointeur curr est senser nous aider a faire la comparaison entre la valeur sur la racine et la valeur quon sapprete a ajoute pour savoir quel direction prendre avec le pointeur
        curr=racine;
        while (curr)
        {
            parent=curr;//parent sert a faire l'ajout au bon endroit
            if (n->data>curr->data)//compraison si la valeur est plus grande dirigé a droite
            {
                curr=curr->right;
            }
            else // sinon alle dirigé à gauche
            {
                curr=curr->left;
            }
        }//ajout a gauche si la valeur est inférieur
        if (n->data<parent->data)
        {
            parent->left=n;
        }
        else//sinon ajouter a droite
        {
            parent->right=n;
        }
    }
}
/*la fonction printhelp fonctionne un peu comme une boucle for on fait deux appel recurssif de maniere a ce que tous l'arbre soit afficher car la "condition d'arret" sera si la racine est null ces a dire quand on rencontre une feuille Bien sur on peut rencontrer une feuille au niveau 2
 d'un arbre de 3 niveau par exemple mais la fonction affiche tous les neud par niveau ainsi il peut se rendre juqu'a la derniere feuille de l'arbre
 */
void BST::printhelp(binNoeud *racine, int niveau)
{
    if (racine==NULL)// si il n'ya aucun element dans l'arbre on sort de la fonction
        return;
    printhelp(racine->right, niveau+1);//on fait un appel recurssif pour aller a droite
    for (int i=0; i<niveau; i++)
    {
        cout<<"  ";
    }
    cout<<racine->data<<"\n";// on affiche la valeur d'ou est ce que on est que ce soit a gauche ou a droite
    printhelp(racine->left, niveau+1);// appel recursif pour aller a gauche
}
void BST::print(int data)//la fonction print appel print help
{
    printhelp(racine, data);
}
// dans la fonction supphelp on fait la recherche du noeud a supprimer et ensuite on le supprime
void BST::supphelper(binNoeud*& racine, int data)
{
    if (racine==NULL)
    {
        cout<<"Aucun element dans l'arbre"<<endl;
    }
    else if (data<racine->data)//on verifie si la valeur est a gauche
    {
        supphelper(racine->left, data);
    }
    else if(data>racine->data)// on verifie si la valeur est a droite
    {
        supphelper(racine->right, data);
    }
    else// rendu ici ces qu'on trouver le neud a supprimer
    {
        binNoeud*temp=racine;
        if (racine->left==NULL)// si le noeud a supprimer n'a pas fils a gauche
        {
            racine=racine->right;//donc on pointe a droite
        }
        else if(racine->right==NULL)// si le noeud a supprimer n2'a pas fils a droite
        {
            racine=racine->left;//donc on pointe a gauche
        }
        else// si a un fils a gauche et a droite
        {
            temp=supp(racine->right);// on remplace le noeud
        }
    }
}
binNoeud* BST::supp(binNoeud*& racine)
{
    assert(racine!=NULL);
    if (racine->left==NULL)
    {
        return supp(racine->left);
    }
    else
    {
        binNoeud* temp=racine;
        racine=racine->right;
        return temp;
    }
}
int main()
{
    BST test;
    int numberchoice;
    bool doitagain=true;
    do{
        cout<<"==================================================================="<<endl;
        cout<<"1. Entrez 15 nombres aleatoirement dans l'arbre"<<endl;
        cout<<"2. Afficher l'arbre"<<endl;
        cout<<"3. Supprimer les 3 derniers noeud de l'arbre"<<endl;
        cout<<"4. Arret du programme"<<endl;
        cout<<"===================================================================="<<endl;
        do
        {
            cout<<"Entrez votre choix s'il vous plait:";
            cin>>numberchoice;
        }
        while (numberchoice<1 || numberchoice>4);
        switch(numberchoice)
        {
            case 1:
                srand(time(NULL));
                int T[20];
                for (int i = 0; i < 15; i++)
                {
                    T[i]=rand()%100;//genere des valeur entre 0 et 19
                    test.insert(T[i]);
                }
                cout<<"les nombres aleatoires entrées sont:"<<endl;
                for (int i = 0; i < 15; i++)
                {
                    cout<<T[i]<<",";
                }
                cout<<endl;
                break;
            case 2:
                test.print(0);
                break;
            case 3:
                for (int i=12; i<15; i++)
                {
                    cout<<T[i]<<" ";
                    test.remove(T[i]);
                }
                cout<<endl;
                break;
            case 4:
                cout<<"Arret du programe.."<<endl;
                doitagain=false;
                break;
        }
    }
    while(doitagain);

    return 0;
}
