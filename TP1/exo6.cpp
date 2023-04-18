#include <iostream>

#include <cstddef>
#include <cstdlib>
#include <new>

template<typename T>
struct Noeud{
    T donnee;
    Noeud<T> *suivant;
};

template<typename T>
class Liste{
    public:
        Liste();
        bool est_vide();
        void ajoute(T valeur);
        void affiche();
        T& operator[] (size_t n);
        size_t cherche(T valeur);
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
        T& operator[] (size_t n);
        long int cherche(T valeur);
        void stocke(size_t n, T valeur);
        void pousse_file(T valeur);
        T retire_file();
        void pousse_pile(T valeur);
        T retire_pile();

    private:
        T *donnees;
        size_t tete
        size_t taille;
        size_t capacite;
};

template<typename T>
Liste<T>::Liste() : premier(nullptr), dernier(nullptr){};

template<typename T>
bool Liste<T>::est_vide() {
    return this->dernier == nullptr;
}

template<typename T>
void Liste<T>::ajoute(T valeur) {
    if (this->est_vide()) {
        this->premier = new Noeud{T, nullptr};
        this->dernier = this->premier;
    } else {
        this->dernier->suivant = new Noeud{T, nullptr};
        this->dernier = this->dernier->suivant;
    }
}

template<typename T>
void Liste<T>::affiche() {
    std::cout << '{';

    Noeud<T> *noeud = this->premier;
    while (noeud != nullptr) {
        std::cout << noeud << ", ";
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

    while (index<n) {
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
    Noeud<T>* noeud = this->premier;
    size_t index = 0;

    if (noeud == nullptr) {
        this->premier = new Noeud<T>{valeur, nullptr};
        this->dernier = this->premier;
        return;
    }

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
    this->dernier = new Noeud<T>{valeur, this->dernier->suivant};
}

template<typename T>
T Liste<T>::retire_file() {
    T res = *this->premier;

    delete this->premier;
    this->premier = res->suivant;

    if (this->premier == nullptr) {
        this->dernier = nullptr;
    }

    return res;
}

template<typename T>
void Liste<T>::pousse_pile(T valeur) {
    this->premier = new Noeud{Noeud<T>{valeur, this->premier->suivant};

    if (this->dernier == nullptr) {
        this->dernier = this->premier;
    }
}

template<typename T>
T Liste<T>::retire_file() {
    T res = *this->premier;

    delete this->premier;
    this->premier = res->suivant;

    if (this->premier == nullptr) {
        this->dernier = nullptr;
    }

    return res;
}

template<typename T>
DynaTableau::DynaTableau() :
    tete(0),
    taille(0),
    capacite(7)
{
    this->donnees = static_cast<T*>(malloc(sizeof(T)*this->capacite));
}

template<typename T>
DynaTableau::DynaTableau(capacite) :
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
        this->donnes = static_cast<T*>(realloc(this->donnees, sizeof(T)*this->capacite;
        memmove(
            this->donnees + this->tete + this->taille + 1,
            this->donnees + this->tete,
            (this->taille - this->tete) * sizeof(T));
        this->tete += this->taille+1;
    }

    this->donnes[(this->tete+this->taille)%this->capacite] = valeur;
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
T& DynaTableau<T>::operator[](size_t n) {
    if(this->m_length <= index) {
        cout << "Index out of bound : the length is "
            << this->taille
            << " but the index is "
            << index << '\n';
        exit(1);
    }

    return this->donnes[(this->tete+n)%this->capacite];
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
        this->donnes = static_cast<T*>(realloc(this->donnees, sizeof(T)*this->capacite;
        memmove(
            this->donnees + this->tete + this->taille,
            this->donnees + this->tete,
            (this->taille - this->tete) * sizeof(T));
        this->tete += this->taille+1;
    }

    size_t index = (n + this->taille) % this->capacite;

    if (n < this->tete) {
        //TODO
    } else {
        
    }

    this->donnees[index] = valeur;
}
/*
class DynaTableau{
    public:
        void stocke(size_t n, T valeur);
        void pousse_file(T valeur);
        T retire_file();
        void pousse_pile(T valeur);
        T retire_pile();

    private:
        T *donnees;
        size_t tete
        size_t queue
        size_t taille;
        size_t capacite;
};
*/

int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste\n";
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau\n";
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste\n";
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau\n";
    }

    std::cout << "Elements initiaux:\n";
    affiche(&liste);
    affiche(&tableau);
    std::cout << '\n';

    std::cout << "5e valeur de la liste " << liste[4] << '\n';
    std::cout << "5e valeur du tableau " << tableau[4] << '\n';

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << '\n';
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << '\n';

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:\n";
    affiche(&liste);
    affiche(&tableau);
    std::cout << '\n';

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << '\n';
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là...\n";
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << '\n';
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là...\n";
    }

    return 0;
}
