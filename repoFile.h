#pragma once
#include"repo.h"

// Repo pentru fisiere, clasa extinsa a clasei FilmRepo
class RepoFile: public FilmRepo
{
private:
	string fisier;

public:

	//constructor
	RepoFile(const string& file) : FilmRepo(), fisier{ file } 
	{
		loadFile();
	}

	void setPath(const string& file)
	{
		this->fisier = file;
	}

	//Incarc filmele din fisier in lista de filme
	void loadFile();

	//Scriu filmele din lista de filme in fisier
	void writeFile();

	//Golesc fisierul
	void emptyFile();

	~RepoFile() = default; 

	/*
	//Adaug film in repo
	virtual void store(const Film& film);

	//Sterg film din repo
	virtual void sterge(string titlu, string gen);

	//Modific film din repo
	virtual void modifica(string titlu, string gen, const Film& film);
	*/

	void store(const Film& film) override
	{
		FilmRepo::store(film);
		writeFile();
	}

	void sterge(string titlu, string gen) override
	{
		FilmRepo::sterge(titlu, gen); 
		writeFile();  
	}

	void modifica(string titlu, string gen, const Film& film) override
	{
		FilmRepo::modifica(titlu, gen, film);
		writeFile();
	}
};