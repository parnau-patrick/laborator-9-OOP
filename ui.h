#pragma once
#include"service.h"

class UI
{
	FilmService& serv;
public:
	UI(FilmService& serv) noexcept :serv{ serv }
	{

	}
	 
	void startUI();
};

void exportHTML(const string& fisier, const vector<Film>& filme);

void afiseazaCos(const FilmService& serv);

void afisare(const Film& f);

/*
Coordonare aplicatie

	pre: true
	post: coordoneaza aplicatia
*/
//void run();