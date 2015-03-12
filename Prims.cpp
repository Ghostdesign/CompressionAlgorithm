//
//  main.cpp
//  devoir4Info3012
//
//  Created by Yann Ouedraogo on 2015-03-05.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  A00167123 eyo3005@umoncton.ca

#include <iostream>
#include <fstream>      //librairie pour la lecture du fichier
#include <list>        //librairie pour la liste d'adjacence
#include <vector>     //librairie pour utiliser tableau dynamique
#include <sstream>   //librairie pour la lecture des ligne
using namespace std;

//definir un nouveau type pour saugevarger un sommet et son cout
typedef struct adjNoeud
{
    int sommet;
    int poids;
    adjNoeud(int V, int poid)//fonction qui assigne le sommet et le poid
    {
        sommet = V;
        poids = poid;
    }
    int getV()//fonction qui retourne le sommet
    {
        return sommet;
    }
    int cout()//fonction qui retourne le cout
    {
        return poids;
    }
}adjNoeud;
//Class graph avec les declations de prototype de fonction
class graph
{public:
    int V;
    graph(int V);       //Constructeur
    list<adjNoeud> *adj;    // declation d'une liste de pointeur de type adjNoeud pour la liste d'adjacence
    void sup_bracket(string &);//fonction pour supprimer les parenthese quand on lira le fichier d'entree
    void etudefile();//fonction qui lit le fichier
    int minimundist(int[],bool[]);//fonction qui retourne l'index du sommet qui a l'arc avec le cout le moins eleve
    void prims();//fonction pour determiner l'arbre minimum de recouvrement
    void afficher(int[]);//affiche l'arbre
};

graph::graph(int V)// constructeur
{
    this->V=V;   // initialisation du sommet
    adj=new list<adjNoeud>[V];//intialisation de la liste d'adjacence
}
//fonction pour supprimer les parenthese dans le input.txt
void graph::sup_bracket(string &ligne)
{
    for (int i=0; i<ligne.length(); i++)
    {
        if (ligne[i]==')'||ligne[i]=='(')// Chaque ligne est examiner charactere par charactere a la recherche de paranthese si on en rencontre
        {
            ligne[i]=' ';//echanger le caractere par un espace
        }
    }
}

int graph::minimundist(int distance[],bool vu[])
{
    int min = 10000;//cest la limite que arc peut avoir comme cout
    int somMini=0;//pour recuperer l'indice qui correspond au sommet qui a l'arc avec le plus faible cout
    
    for (int i = 0; i < V; i++)
    {
        if (vu[i] == false && distance[i] <= min)//sil n'a pas ete visite epuis sa distance inferieur a la limite qu'on accorde au cout des arc
        {
            min = distance[i];
            somMini = i;
        }
    }
    return somMini;//indice de celui qui le plus faible cout
}

void graph::etudefile()
{
    string ligne;
    string nomFichier="input.txt";// nom du fichier a lire
    ifstream readfile(nomFichier,ios::in);//ouverture du fichier
    if (readfile.is_open())
    {
        while (!readfile.eof())// tant qu'on est pas arriver a la fin du fichier
        {
            int source;
            int dest;
            int poid;
            getline(readfile,ligne);// on recupere la ligne avec le getline
            sup_bracket(ligne);// on met des espace a la place des parenthese
            stringstream ss;
            ss<<ligne;//variable de type string stream vu quil n'y a que des chiffres et espace on reconvertit la string avec le traitement de la ligne et surtout pour faire une boucle jusqua la fin de la ligne
            ss>>source;
            while (!ss.eof())
            {
                ss>>dest>>poid;
                adjNoeud node(dest,poid);//ajouter les informations sur le fils du sommet
                adj[source].push_back(node);//ajout de la source dans la liste adjacente
            }
        }
        readfile.close();
    }
    else
        cerr<<"le Fichier n'a pas pu s'ouvrir..."<<endl;//gestion d'erreur au cas ou le fichier n'Est pas lu
}

void graph::afficher(int parent[])
{
    cout<<"L'arbre de recouvrement"<<endl;
    for(int i=1;i<V;i++)
    {
        cout<<parent[i]<<"----"<<i<<"\n";//on affiche les valeur de 1 au dernier sommet toute en affichant ses parents
    }
}

void graph::prims()
{
    int parent[V]; //On stocke les sommet qui constitue l'Arbre minimal de recouvrement
    int distance[V]; //distance nous aide a choisir ce qui ont le cout le plus minimum
    bool vu[V]; // pour observer si un sommet n'est pas encore inclue dans l'arbre de recouvrement minimum
    
    for (int i = 0; i < V; i++)
    {
        distance[i] = 10000;//initialisation des distance
        vu[i] = false;//ansi que leur presence dans l'arbre
    }
    parent[0] = -1;//initialisation de la racince de l'Arbre
    distance[0] = 0;//mise a jour de sa distance
    for(int j=0;j<V;j++)
    {
        int mindist=minimundist(distance,vu);//qui nous retourne l'indice du sommet qui a un faible cout
        vu[mindist]=true;// le marqué
        list<adjNoeud>::iterator i;
        for(i=adj[mindist].begin();i!=adj[mindist].end();i++)
        {
            if(vu[i->getV()]==false && i->cout() < distance[i->getV()])//comparer le cout a tous les autre dans la liste d'ajacence
            {
                //mettre a jour le cout
                parent[i->getV()]=mindist;
                distance[i->getV()]=i->cout();
            }
        }
    }
    afficher(parent);
}

int main()
{
    graph G(8); //8 correspond au nombre de sommet || a modifier au cas ou on change de graphe
    G.etudefile();
    G.prims();
    return 0;
}