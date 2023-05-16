#include <iostream>

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>

template<typename T>
class Noeud{
    public:
        T donnee;
        Noeud<T> *suivant;
};

template<typename T>
class Liste{
    public:
        Liste();
        ~Liste();
        bool est_vide();
        void ajoute(T valeur);
        void affiche();
        T& operator[] (size_t n);
        long int cherche(T valeur);
        void stocke(size_t n, T valeur);
        void pousse_file(T valeur);
        T retire_file();
        void pousse_pile(T valeur);
        T retire_pile();

    private:
        Noeud<T> *premier;
        Noeud<T> *dernier;
};

template<typename T>
class DynaTableau{
    public:
        DynaTableau();
        DynaTableau(size_t capacite);
        ~DynaTableau();
        bool est_vide();
        void ajoute(T valeur);
        void affiche();
        void afficheMem(); //permet de débugger la mémoire
        T& operator[] (size_t n);
        long int cherche(T valeur);
        void stocke(size_t n, T valeur);
        void pousse_file(T valeur);
        T retire_file();
        void pousse_pile(T valeur);
        T retire_pile();

    private:
        T *donnees;
        size_t tete;
        size_t taille;
        size_t capacite;
};

template<typename T>
Liste<T>::Liste() : premier(nullptr), dernier(nullptr){};

template<typename T>
Liste<T>::~Liste() {
    Noeud<T> *ptr = this->premier;

    while (ptr != nullptr) {
        Noeud<T> *del = ptr;
        ptr = ptr->suivant;
        delete del;
    }
}

template<typename T>
bool Liste<T>::est_vide() {
    return this->dernier == nullptr;
}

template<typename T>
void Liste<T>::ajoute(T valeur) {
    if (this->est_vide()) {
        this->premier = new Noeud<T>{valeur, nullptr};
        this->dernier = this->premier;
    } else {
        this->dernier->suivant = new Noeud<T>{valeur, nullptr};
        this->dernier = this->dernier->suivant;
    }
}

template<typename T>
void Liste<T>::affiche() {
    std::cout << '{';

    Noeud<T> *noeud = this->premier;
    while (noeud != nullptr) {
        std::cout << noeud->donnee << ", ";
        noeud = noeud->suivant;
    }

    std::cout << "}\n";
}

template<typename T>
T& Liste<T>::operator[](size_t n) {
    Noeud<T>* noeud = this->premier;
    size_t index = 0;

    if (noeud == nullptr) {
        std::cout << "Index out of bound, the length is "
            << index
            << " but the index is "
            << n
            << "!\n";
    }

    while (index<n) {
        if (noeud == nullptr) {
            std::cout << "Index out of bound, the length is "
                << index
                << " but the index is "
                << n
                << "!\n";
        }
        index++;
        noeud = noeud->suivant;
    }

    return noeud->donnee;
}

template<typename T>
long int Liste<T>::cherche(T valeur) {
    Noeud<T>* noeud = this->premier;
    long int index = 0;

    if (noeud == nullptr) {
        return -1;
    }

    while (noeud->donnee != valeur) {
        if (noeud == nullptr) {
            return -1;
        }
        index++;
        noeud = noeud->suivant;
    }

    return index;
}

template<typename T>
void Liste<T>::stocke(size_t n, T valeur) {
    if (this->premier == nullptr) {
        this->premier = new Noeud<T>{valeur, nullptr};
        this->dernier = this->premier;
        return;
    }

    if (n == 0) {
        this->premier = new Noeud<T>{valeur, this->premier};
    }

    Noeud<T>* noeud = this->premier;
    size_t index = 1;


    while (index<n && noeud->suivant != nullptr) {
        index++;
        noeud = noeud->suivant;
    }

    noeud->suivant = new Noeud<T>{valeur, noeud->suivant};

    if (noeud->suivant->suivant == nullptr) {
        this->dernier = noeud->suivant;
    }
}

template<typename T>
void Liste<T>::pousse_file(T valeur) {
    if (this->dernier == nullptr) {
        this->dernier = new Noeud<T>{valeur, nullptr};
        this->premier = this->dernier;
    } else {
        this->dernier->suivant = new Noeud<T>{valeur, nullptr};
        this->dernier = this->dernier->suivant;
    }
}

template<typename T>
T Liste<T>::retire_file() {
    if (this->premier == nullptr) {
        std::cout << "Aucun élément à retirer.\n";
        exit(1);
    }

    Noeud<T> res = *this->premier;

    delete this->premier;
    this->premier = res.suivant;

    if (this->premier == nullptr) {
        this->dernier = nullptr;
    }

    return res.donnee;
}

template<typename T>
void Liste<T>::pousse_pile(T valeur) {
    this->premier = new Noeud<T>{valeur, this->premier};

    if (this->dernier == nullptr) {
        this->dernier = this->premier;
    }
}

template<typename T>
T Liste<T>::retire_pile() {
    if (this->premier == nullptr) {
        std::cout << "Aucun élément à dépiler.\n";
        exit(1);
    }

    Noeud<T> res = *this->premier;

    delete this->premier;
    this->premier = res.suivant;

    if (this->premier == nullptr) {
        this->dernier = nullptr;
    }

    return res.donnee;
}

template<typename T>
DynaTableau<T>::DynaTableau() :
    tete(0),
    taille(0),
    capacite(7)
{
    this->donnees = static_cast<T*>(malloc(sizeof(T)*this->capacite));
}

template<typename T>
DynaTableau<T>::DynaTableau(size_t capacite) :
    tete(0),
    taille(0),
    capacite(capacite)
{
    this->donnees = static_cast<T*>(malloc(sizeof(T)*this->capacite));
}

template<typename T>
bool DynaTableau<T>::est_vide() {
    return this->taille == 0;
}

template<typename T>
DynaTableau<T>::~DynaTableau() {
    free(this->donnees);
}

template<typename T>
void DynaTableau<T>::ajoute(T valeur) {
    if (this->taille >= this->capacite) {
        this->capacite = 1 + 2*this->capacite;
        this->donnees = static_cast<T*>(realloc(this->donnees, sizeof(T)*this->capacite));

        //On vérifie si la mémoire est croisée
        if (this->tete != 0) {
            memcpy(
                this->donnees + this->capacite - this->taille + this->tete,
                this->donnees + this->tete,
                (this->taille - this->tete) * sizeof(T));
            this->tete += this->taille+1;
        }
    }

    this->donnees[(this->tete+this->taille)%this->capacite] = valeur;
    this->taille++;
}

template<typename T>
void DynaTableau<T>::affiche() {
    std::cout << '{';

    for (size_t i = 0; i < this->taille; i++) {
        std::cout << this->donnees[(this->tete+i)%this->capacite] << ", ";
    }

    std::cout << "}\n";
}

template<typename T>
void DynaTableau<T>::afficheMem() {
    std::cout << this->tete << ":" << this->taille << " [";
    for (size_t i = 0; i < this->capacite; ++i) {
        if (i == (this->tete+this->taille)%this->capacite && this->taille != 0) {
            std::cout << '>';
        }
        if (i == this->tete) {
            std::cout << '<';
        }
        if (i == (this->tete+this->taille)%this->capacite && this->taille == 0) {
            std::cout << '>';
        }
        std::cout << this->donnees[i] << ", ";
    }
    std::cout << "]\n";
}

template<typename T>
T& DynaTableau<T>::operator[](size_t n) {
    if(this->taille <= n) {
        std::cout << "Index out of bound : the length is "
            << this->taille
            << " but the index is "
            << n << ".\n";
        exit(1);
    }

    return this->donnees[(this->tete+n)%this->capacite];
}

template<typename T>
long int DynaTableau<T>::cherche(T valeur) {
    for (long int i = 0; i < this->taille; i++) {
        if (this->donnees[(this->tete+i)%this->capacite] == valeur) {
            return i;
        }
    }

    return -1;
}

template<typename T>
void DynaTableau<T>::stocke(size_t n, T valeur) {
    if (this->taille >= this->capacite) {
        this->capacite = 1 + 2*this->capacite;
        this->donnees = static_cast<T*>(realloc(this->donnees, sizeof(T)*this->capacite));

        //On vérifie si la mémoire est croisée
        if (this->tete != 0) {
            memcpy(
                this->donnees + this->capacite - this->taille + this->tete,
                this->donnees + this->tete,
                (this->taille - this->tete) * sizeof(T));
            this->tete += this->taille+1;
        }
    }

    if (n > this->taille) {
        std::cout << "Error : can't insert at pos "
            << n
            << ", the length is "
            << this->taille
            << ".\n";
        exit(1);
    }

    if (n==0) {
        this->tete = (this->tete + this->capacite - 1) % this->capacite;
        this->donnees[this->tete] = valeur;
        this->taille += 1;
        return;
    }

    if (n==this->taille) {
        this->donnees[(this->tete + this->taille) % this->capacite] = valeur;
        this->taille += 1;
        return;
    }

    //On sait qu'on n'ajoute pas au extrémités, il va donc falloir utiliser memcpy ou memmove
    size_t index = (n + this->tete) % this->capacite;

    //les données sont-elles séparées ?
    if (this->tete+this->taille > this->capacite) {
        //insère-t-on dans les données à gauche ?
        if (index < this->tete) {
            memcpy(
                this->donnees+index+1,
                this->donnees+index,
                (this->taille-n)*sizeof(T));
        } else {
            std::cout << "leftn't\n";
            memmove(this->donnees + this->tete - 1, this->donnees + this->tete, n*sizeof(T));
        }
    } else {
        std::cout << "split\n";
        index -= 1;
        //les données collent-elles le début de la plage mémoire ?
        if (this->tete == 0) {
            std::cout << "begin\n";
            this->afficheMem();
            this->tete = this->capacite-1;
            this->donnees[this->tete] = this->donnees[0];
            memcpy(this->donnees, this->donnees+1, index*sizeof(T));
            this->afficheMem();
        } else {
            std::cout << "begin't\n";
            memcpy(this->donnees + this->tete - 1, this->donnees + this->tete, (n-1)*sizeof(T));
            this->tete -= 1;
        }
    }

    this->donnees[index] = valeur;
    this->taille += 1;
}

template<typename T>
void DynaTableau<T>::pousse_file(T valeur) {
    this->ajoute(valeur);
}

template<typename T>
T DynaTableau<T>::retire_file() {
    if (this->taille <= 0) {
        std::cout << "Aucun élément à retirer.\n";
        exit(1);
    }

    T res = this->donnees[this->tete];
    this->tete = (this->tete + 1) % this->capacite;
    this->taille -= 1;
    return res;
}

template<typename T>
void DynaTableau<T>::pousse_pile(T valeur) {
    this->ajoute(valeur);
}

template<typename T>
T DynaTableau<T>::retire_pile() {
    if (this->taille <= 0) {
        std::cout << "Aucun élément à dépiler.\n";
        exit(1);
    }

    this->taille -= 1;
    return this->donnees[(this->tete+this->taille) % this->capacite];
}

int main()
{
    Liste<int> liste = {};
    DynaTableau<int> tableau = {0};

    if (!liste.est_vide())
    {
        std::cout << "Oups y a une anguille dans ma liste\n";
    }

    if (!tableau.est_vide())
    {
        std::cout << "Oups y a une anguille dans mon tableau\n";
    }

    tableau.afficheMem();
    for (int i=1; i<=7; i++) {
        liste.ajoute(i*7);
        tableau.ajoute(i*5);
        tableau.stocke(0,i*3);
        tableau.afficheMem();
    }

    if (liste.est_vide())
    {
        std::cout << "Oups y a une anguille dans ma liste\n";
    }

    if (tableau.est_vide())
    {
        std::cout << "Oups y a une anguille dans mon tableau\n";
    }

    std::cout << "Elements initiaux:\n";
    liste.affiche();
    tableau.affiche();
    tableau.afficheMem();
    std::cout << '\n';

    std::cout << "5e valeur de la liste " << liste[4] << '\n';
    std::cout << "5e valeur du tableau " << tableau[4] << '\n';

    std::cout << "21 se trouve dans la liste à " << liste.cherche(21) << '\n';
    std::cout << "15 se trouve dans le tableau à " << tableau.cherche(15) << '\n';

    liste.stocke(4, 7);
    tableau.stocke(4, 7);

    std::cout << "Elements après stockage de 7:\n";
    liste.affiche();
    tableau.affiche();
    tableau.afficheMem();
    std::cout << '\n';

    DynaTableau<int> pile{}; // Liste pile;
    DynaTableau<int> file{}; // Liste file;
    std::cout << "Allô ?\n";

    for (int i=1; i<=7; i++) {
        file.pousse_file(i);
        pile.pousse_pile(i);
    }

    int compteur = 10;
    while(!file.est_vide() && compteur > 0)
    {
        std::cout << file.retire_file() << ' ';
        compteur--;
    }
    std::cout << '\n';

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là...\n";
    }
    std::cout << "File au suivant !\n";

    compteur = 10;
    while(!pile.est_vide() && compteur > 0)
    {
        std::cout << pile.retire_pile() << ' ';
        compteur--;
    }
    std::cout << '\n';

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là...\n";
    }
    std::cout << "Pile poil !\n";

    return 0;
}
