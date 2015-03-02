//
//  main.cpp
//  TP2info2014
//
//  Created by Yann Ouedraogo on 2015-02-08.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  eyo3005@umoncton.ca A00167123

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
#include <regex>
using namespace std;
int Nposition=0;//variable pour deplacer de n position
class compress
{
public:
    int cpt;//compteur
    int position;//variable pour recupera la position
    compress();// constructeur
    void coordone();//convertie le premier mot d'une phrase en minuscule
    vector<string> tab;//tab stocke les mot lue dans le fichier d'entre a compresse
    list<string> intermediare;//represente la liste autoorganise pour la compression
    vector<string> final;//recupere la phrase de sortie apres compression
    vector<string> tab2;//tab2 stock les mot lu dans le fichier d'entree a decompresse
    list<string> intermediare2;// liste autoorganise pour la decompression
    vector<string> final2;// recupere la phrase de sortie apres decompression
    bool estUnChiffre(const string &);//fonction pour verifier si la string en lecture est un chiffre
    int estLa(string);// fonction qui donne la position ou se trouve le mot
    bool existe(string);//fonction qui verifi si un mot existe deja dans notre liste auto organise
    void compression(string,string);//fonction pour la compression
    void decompress(string,string);//focntion pour la decompression
    int taille();
};
compress::compress()
{
    
}
int compress:: estLa(string target)//fonction qui prend en parametre le mot a cibler
{
    int counteer=0;int ret=0;//ret pour la position retenue quand le mot match a l'iterateur quand il parcour la liste
    for (list<string>::iterator it = intermediare.begin(); it != intermediare.end(); it++)//boucle pour parcourir la liste
    {
        counteer++;//s'incremete a chaque fois quon avance dans la liste
        if(*it==target)// si l'iterateur qui correspoun au string qui sont dans la liste match au mot qu'on cherche
        {
            ret=counteer;
            position=counteer-1;// recupere la position en prenan la valeur de counteer dans position
        }
    }
    return counteer;//retourne le compteur
}
bool compress::existe(string x)
{
    string i;
    bool exists =any_of(begin(intermediare),end(intermediare), [&](string i)//focntion qui retourne true si l'element quon cherche se trouve dans l'intervalle de la liste auto organiser
    {
        return i == x;
    });
    if (exists==true)
    {
        return true;
    }
    else
        return false;
}
bool compress::estUnChiffre(const string & s)//fonction qui prend en parametre une string passe par reference
{
    return regex_match(s,regex("[0-9]+"));//grace a la librairie regex on peut savoir si ce un chiffre il retourne 0 ou 1
}
void compress:: coordone()// la fonction coordone met juste le premier mot de la phrase en minuscule
{
    string str=tab[0];//on recupere le premier mot stocker dans la case zero de tab
    transform(str.begin(), str.end(), str.begin(),::tolower);//grace a la fonction de la classe Algorithm on converti en minuscule la string
    tab[0]=str;
}
void compress:: compression(string entre,string sortie)
{
    string ligne, mot;
    ifstream readfile(entre,ios::in);//ouverture du fichier
    int i=0;
    if (readfile.is_open())
    {
        while (!readfile.eof())// tant qu'on est pas arriver a la fin du fichier
        {
            getline(readfile,ligne);//on recupere la ligne
            stringstream ss;
            ss<<ligne;//on convertie la ligne en stringstream pour pouvoir la parcourir jusqua la fin et recuperer les mot
            while (!ss.eof())
            {
                ss>>mot;//reconversion en string
                tab.push_back(mot);// on sauvegarde le tous dans un tableau
                cpt++;//un compteur pour nous donne la taille du tableau qui viens de stocker tous les mot
            }
        }
        readfile.close();//fermeture du fichier
        i++;
    }
    else
        cerr<<"le Fichier n'a pas pu s'ouvrir..."<<endl;//gestion d'erreur au cas ou le fichier n'Est pas lu
    coordone();//conversion en minuscul du premier mot
    for (int x=0; x<cpt; x++)//boucle qui parcour le tableau qui contient les mots
    {
        if (existe(tab[x])==0)//si le bool qui verifie si le mot qu'on lit est dans la liste autoOrganise est a 0
        {
            intermediare.push_front(tab[x]);//on l'ajout dans la liste auto organise
            final.push_back(tab[x]);//epuis on l'ajoute aussi dans le tableau final
        }
        else if(existe(tab[x])==1)//si le bool qui verifie si le mot qu'on lit est dans la liste autoOrganise est a 0 est a 1 cest a dire qu'il existe deja dans la liste auto organise
        {
            int progress=0;
            stringstream ss;
            int temp=0;string temp2,temporaire;
            temp=estLa(tab[x]);// on retrouve sa position
            ss<<position;//on fait une conversion de int a string et on ajoute la string obtenu de la position
            temp2=ss.str();//dans la liste final
            list<string>::iterator it=intermediare.begin();//on definit un iterateur qui commence au debut de la liste
            list<string>::iterator prev=it++;
            list<string>::iterator it2=it--;
            //list<string>::iterator it3;
            for (int i=0;i<temp; i++)
            {
                if (progress<position)
                {
                    it++;//avance a en fonction de la position de l'element
                }
                progress++;
            }
            list<string>::iterator it3=it;
            if (Nposition>temp-1)
            {
                cout<<"Le deplacement par defaut est 1"<<endl;
                cout<<"Le deplacement que vous voulez faire est hors du tableau"<<endl;
                return;
            }
            advance(it3,-Nposition);//se rend a la position souhaiter
            swap(*it,*it3);//permute
            final.push_back(temp2);// on ajoute la position dans lexpression final mais le fait de faire la permutation aavant d'Ajouter n'a pas deffet car de toute façon ces la position qu'on met dans la liste final
        }
    }
    ofstream writefile(sortie,ios::out);// ecrire dans le fichier de sortie
    if (writefile)
    {
        for (int i=0; i<final.size(); i++)
        {
            if (i==final.size()-1)// cette condition nous permet de compresser le fichier test d'au moins a 23,68% sachant que
            {
                writefile<<final[i];//chaque espace compte a la fin on en met pas
            }
            else
                writefile<<final[i]<<" ";// on parcour notre tableau final en ecrivant les mot a l'interieur dans le fichier sortie
        }
    }
    writefile.close();//fermeture du fichier
}
int compress::taille()// fonction qui aide a la gestion d'erreur en donnant la taille de la liste auto organise au monent qu'on vas vouloir permuter des mot dans la liste
{
    int lecompteur=0;
    for (list<string>::iterator it = intermediare2.begin(); it != intermediare2.end(); it++)
        lecompteur++;
    return lecompteur;
}
void compress:: decompress(string iinput,string ouutput)
{
    int size=0;
    string ligne, word;
    ifstream readfile2(iinput,ios::in);//ouverture du fichier
    if (readfile2.is_open())
    {
        while (!readfile2.eof())// tant qu'on est pas arriver a la fin du fichier
        {
            getline(readfile2,ligne);//on recupere la ligne
            stringstream ss;
            ss<<ligne;//on convertie la ligne en stringstream pour pouvoir la parcourir jusqua la fin et recuperer les mot
            while (!ss.eof())
            {
                ss>>word;//reconversion en string
                if (word==" ")// si le mot est un espace on l'ajoute pas dans le tableau
                {
                    break;
                }
                else
                {
                    tab2.push_back(word);// on sauvegarde le tous dans un tableau
                    size++;//un compteur pour nous donne la taille du tableau qui viens de stocker tous les mot
                }
            }
        }
        readfile2.close();//fermeture du fichier
    }
    else
        cerr<<"le Fichier n'a pas pu s'ouvrir..."<<endl;//gestion d'erreur au cas ou le fichier n'Est pas lu
   for (int x=0; x<size; x++)
   {
       if (estUnChiffre(tab2[x])==0)//si le booleen qui dit que ces un chiffre est a zero
       {
           intermediare2.push_front(tab2[x]);// on ajoute dans la liste autoorganise
           final2.push_back(tab2[x]);// on ajoute dans le tableau final
       }
       else if(estUnChiffre(tab2[x])==1)// si on rencontre un chiffre
       {
           int condi=taille();
           
           if (Nposition>=condi)
           {
               cout<<"Le deplacement par defaut est 1"<<endl;
               cout<<"Le deplacement que vous voulez faire est hors du tableau"<<endl;
               return;
           }
           string ch=tab2[x];int chaine;
           stringstream s1;
           s1.str(ch);// conversion string a int cest a dire la string de la position en int et aller a cette indice
           s1>>chaine;
           string temporary;
           list<string>::iterator itS=intermediare2.begin();//on definit un iterateur qui commence au debut de la liste
           list<string>::iterator it2S=itS--;
           for (int i=0;i<chaine+1; i++)//on se rend a la position du mot dans la liste auto organise
           {
                   itS++;
           }
           final2.push_back(*itS);//ajouter le mot a la liste final
           list<string>::iterator it3S=itS;//on cree un iterateur a la position de it cest a dire sur le mot
           advance(it3S,-Nposition);//avec advance on on peut deplace avec it3S de la position vers d'autre mot
           swap(*itS,*it3S);//on interchange les mot avec ce que it3S pointe
       }
   }
    ofstream writefile2(ouutput,ios::out);// ecrire dans le fichier de sortie
    if (writefile2)
    {
        for (int i=0; i<final2.size(); i++)
        {
            if (i==final2.size()-1)
            {
                writefile2<<final2[i];//chaque espace compte a la fin on en met pas
            }
            else
                writefile2<<final2[i]<<" ";// on parcour notre tableau final en ecrivant les mot a l'interieur dans le fichier sortie
        }
    }
    writefile2.close();//fermeture du fichier
}
int main(int argc, const char * argv[])
{
    compress man;
    if (argc>4)//si le nombre de parametre est plus grand que ceux autorise on le signal
    {
        cout<<"parametre maximum atteint"<<endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < argc; i++)
        cout << "argv[" << i << "] = " << argv[i] << endl;// on affiche les paremetres a l'utilisateur en cas de verification
    if (strncmp(argv[3],"true", 2)==0)// si le troisieme argument est a true on compresse
    {
        cout<<"Entrez le parametre de deplacement"<<endl;
        if(cin>>Nposition)//pour verifier qu'on a bien affairee a un int
        {
            man.compression(argv[1], argv[2]);
        }
        else
        {
             cerr<<"Entrez un entier s'il vous plait"<<endl;
        }
    }
    else if (strncmp(argv[3],"false", 2)==0)// si il est a false on le decompresse
    {
        cout<<"Entrez le parametre de deplacement"<<endl;
        if (cin>>Nposition)
        {
            man.decompress(argv[1], argv[2]);
        }
        else
        {
            cerr<<"Entrez un entier s'il vous plait"<<endl;
        }
    }
    else
    {
        cout<<"le format n'est pas correcte"<<endl;
    }
    return 0;
}