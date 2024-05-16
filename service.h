#pragma once
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include <memory>
#include<sstream>
#include<functional>
#include"domain.h"
#include"repo.h"
#include"repoFile.h"
#include"undo.h"
using std::string;
using std::map;
using std::vector; 
using std::function;  
using std::stringstream; 
using namespace std;

//Service pentru Film
class FilmService
{
private:
	//FilmRepo& rep; - repo pentru filme (fara fisiere)
    RepoAbstract& rep;
    CosRepo& repoC;

	//pentru UNDO
    vector<unique_ptr<ActiuneUndo>> undoAction;  

public:
	
    // FilmService(FilmRepo& rep, CosRepo& repoC) noexcept : rep{ rep }, repoC{ repoC } {} - repo pentru filme (fara fisiere)
    FilmService(RepoAbstract& rep, CosRepo& repoC) noexcept : rep{ rep }, repoC{ repoC } {}

    FilmService(const FilmService& ot) = delete;
    FilmService() = default;

    //Adauga film
    void add(string titlu, string gen, int anAparitie, string actorPrincipal); 

    //Sterge film
    void sterge(string titlu, string gen); 

    //Modifica film
    void modifica(string titlu, string gen, const Film& film);

    //Returneaza toate filmele
    const vector<Film>& getAll() noexcept;

    //Cauta film dupa titlu
    vector<Film> cauta(string titlu); 

    //Filtreaza filme
    vector<Film> filtrare(int filtru, string tip);

    //Sorteaza filme
    vector<Film> sortare(int tip); 

    //Sterge toate filmele din cos
    void delCos();

    //Adauga film in cos
    void addCos(string titlu, string gen);

    //Returneaza toate filmele din cos
    const vector<Film>& getAllCos() const noexcept;

    //Genereaza un cos care contine aleatoriu un numar de filme dat din lista
    vector<Film> genereazaCos(int numar);

    //Realizare Undo
    void Undo();

    map<string, DTOFilm> raport();
};