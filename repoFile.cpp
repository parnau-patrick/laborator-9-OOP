#include"repoFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
Incarc filmele din fisier in lista de filme

	pre: true
	post: incarca filmele din fisier in lista de filme

*/
void RepoFile::loadFile()
{
	ifstream fin(fisier); // deschid fisierul pentru a citi filmele
	string line;

	while (getline(fin, line)) // cat timp mai exista filme in fisier
	{

		istringstream iss(line); 
		string token;

		string titlu, gen, actorPrincipal;
		int anAparitie=0;

		int i = 0;

		while (getline(iss, token, ';')) // obtin datele filmului din fisier
		{
			if (i == 0) // titlul filmului
			{
				titlu = token;
			}

			if (i == 1) // genul filmului
			{
				gen = token;
			}

			if (i == 2) // anul de aparitie al filmului
			{
				anAparitie = std::stoi(token); // transform string-ul in int
			}

			if (i == 3) // actorul principal din film
			{
				actorPrincipal = token;
			}

			i++; // incrementez i
		}

		const Film f{ titlu, gen, anAparitie, actorPrincipal }; // creez un film cu datele obtinute din fisier

		store(f);  // salvez filmul citit din fisier in lista de filme
	}

	fin.close();
}

//Scriu filmele din lista de filme in fisier
void RepoFile::writeFile()
{
	ofstream fout(fisier); // deschid fisierul pentru a scrie filmele

	const vector<Film> filme2 = getAll(); // obtin toate filmele din repo

	for (const auto& f : filme2) // scriu toate filmele din repo in fisier
	{
		fout << f.get_titlu() << ";" << f.get_gen() << ";" << f.get_anAparitie() << ";" << f.get_actorPrincipal() << '\n';
	}

	fout.close();
}

//Golesc fisierul
void RepoFile::emptyFile()
{

	ofstream fout(fisier); // deschid fisierul pentru a scrie filmele

	fout << "";

	fout.close();
}