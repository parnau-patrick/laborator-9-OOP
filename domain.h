#pragma once
#include <string>
#include<iostream>
using std::string;

class Film
{
private:
    string titlu;
    string gen;
    int anAparitie;
    string actorPrincipal;

public:
    // Constructor
    Film(string titlu, string gen, int anAparitie, string actorPrincipal)
        : titlu(titlu), gen(gen), anAparitie(anAparitie), actorPrincipal(actorPrincipal) {}

    // Destructor
    ~Film() = default;

    // Copie constructor
    Film(const Film& ot): titlu(ot.titlu), gen(ot.gen), anAparitie(ot.anAparitie), actorPrincipal(ot.actorPrincipal) 
    {
        //std::cout << "hei!\n";
    }

    // Copy assignment operator
    Film& operator=(const Film& ot) 
    {
        if (this != &ot) 
        {
            titlu = ot.get_titlu();
            gen = ot.get_gen();
            anAparitie = ot.get_anAparitie();
            actorPrincipal = ot.get_actorPrincipal();
        }
        return *this;
    }

    // Move constructor
    Film(Film&&) noexcept = default;

    // Move assignment operator
    Film& operator=(Film&&) noexcept = default;

    // Getters
    const string& get_titlu() const noexcept;
    const string& get_gen() const noexcept;
    int get_anAparitie() const noexcept;
    const string& get_actorPrincipal() const noexcept;

    // Setters
    void setTitlu(string newTitlu);
    void setGen(string newGen);
    void setAnAparitie(int newAnAparitie) noexcept;
    void setActorPrincipal(string newActorPrincipal); 
    
};


class DTOFilm
{
private:
    string type;  // genul filmului
    int count;  // numarul de filme

public:

    //Constructor
    DTOFilm(string type1, int count1) : type{ type1 }, count{ count1 } {}

    DTOFilm(string type1) : type{ type1 }, count { 0 } {}

    DTOFilm() : type{ "" }, count{ 0 } {}

    //Functie pentru returnarea tipului
    string getType() const
    {
        return type;
    }

    //Functie pentru returnarea numarului
    int getCount() const noexcept
    {
        return count;
    }

};