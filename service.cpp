#include"service.h"
#include<string>
#include"domain.h"
#include"repo.h"
#include"repoFile.h"
#include<regex>
#include<cctype> 
#include<algorithm>
#include<memory>
#pragma warning(push)
#pragma warning(disable: 4244)
using std::string;
using namespace std;

/*
Adauga un film la lista
	
	pre: titlu - string nenul
		 gen - string nenul
		 anAparitie - int > 0
		 actorPrincipal - string nenul

	post: apeleaza functia store() din repo pentru adaugarea filmului in lista

*/
void FilmService::add(string titlu, string gen, int anAparitie, string actorPrincipal)
{
	Film f{ titlu, gen, anAparitie, actorPrincipal };
	//validare

	///undo.push_back(rep.getAll());

	rep.store(f);
	//rep.writeFile();

	undoAction.push_back(std::make_unique<UndoAdauga>(titlu, gen, rep));
}


/*
Sterge un film din lista

	pre: titlu - string nenul
		 gen - string nenul

	post: apeleaza functia sterge() din repo pentru a sterge filmul din lista

*/
void FilmService::sterge(string titlu, string gen)
{
	vector<Film> filme2 = rep.getAll();
	Film film("", "", -1, "");

	for (const auto& f : filme2) // filmul care urmeaza sa fie sters
	{
		if (f.get_titlu() == titlu && f.get_gen() == gen)
		{
			film = f;
		}
	}

	rep.sterge(titlu, gen);
	//rep.writeFile();

	undoAction.push_back(std::make_unique<UndoSterge>(film, rep)); 
}


/*
Modifica un film din lista

	pre: titlu - string nenul
		 gen - string nenul
		 film - Film

	post: apeleaza functia modifica() din repo pentru a modifica filmul din lista

*/
void FilmService::modifica(string titlu, string gen, const Film& film)
{
	vector<Film> filme2 = rep.getAll();
	Film film2("", "", -1, "");

	for (const auto& f : filme2) // filmul care urmeaza sa modificat
	{
		if (f.get_titlu() == titlu && f.get_gen() == gen)
		{
			film2 = f;
		}
	}

	rep.modifica(titlu, gen, film);
	//rep.writeFile();

	undoAction.push_back(std::make_unique<UndoModifica>(film.get_titlu(), film.get_gen(), film2, rep));
}

//Realizare Undo
void FilmService::Undo()
{
	if (undoAction.empty()) 
	{
		throw RepoException("Nu mai exista operatii!");
	}

	undoAction.back()->doUndo(); 

	undoAction.pop_back(); 

	//rep.writeFile(); 
}


/*
Returneaza toate filmele din lista

	pre: true
	post: apeleaza functia getAll() din repo pentru a returna toate filmele din lista

*/
const vector<Film>& FilmService::getAll() noexcept
{
	return rep.getAll();
}


/*
Cauta un film din lista

	pre: titlu - string nenul
	post: returneaza o lista cu toate filmele care corespund cautarii

*/
vector<Film> FilmService::cauta(string titlu)
{
	//Obtin toate filmele din repository
	vector<Film> filme = rep.getAll();

	//Declar un vector nou pentru a retine rezultatul cautarii
	vector<Film> cautare;

	// Convertesc titlul cautat la litere mici pentru a face cautarea nesensibila la majuscule/minuscule
	string titluLower = titlu;
	transform(titluLower.begin(), titluLower.end(), titluLower.begin(), [](unsigned char c) noexcept { return tolower(c); });

	// Utilizez FIND_IF pentru a cauta filmul
	auto it = find_if(filme.begin(), filme.end(), [&](const Film& f)
	{
			//Convertesc titlul fiecarui film in litere mici
			string titluFilmLower = f.get_titlu();
			transform(titluFilmLower.begin(), titluFilmLower.end(), titluFilmLower.begin(), [](unsigned char c) noexcept { return tolower(c); });
			//Verific daca titlul filmului contine titlul cautat
			return titluFilmLower.find(titluLower) != std::string::npos;
	});

	// Daca gasesc filmul, il adaug la vectorul cautare
	while (it != filme.end())
	{
		cautare.push_back(*it);
		it = find_if(++it, filme.end(), [&](const Film& f)
		{
				//Continui sa caut dupa urmatorul film care corespunde cautarii
				string titluFilmLower = f.get_titlu();
				transform(titluFilmLower.begin(), titluFilmLower.end(), titluFilmLower.begin(), [](unsigned char c) noexcept { return tolower(c); });
				return titluFilmLower.find(titluLower) != std::string::npos;
		});
	}

	return cautare;
}


/*
Filtreaza lista filme dupa titlu sau an

	pre: filtru - are valoarea 1 sau 2
		 tip - string nenul (un titlu sau an)
	post: returneaza lista filtrata de filme

*/
vector<Film> FilmService::filtrare(int filtru, string tip)
{
	//Obtin toate filmele din repository
	vector<Film> filme = rep.getAll();

	//initializez un vector in care sa retin filmele filtrare
	vector<Film> filtrare;

	// Convertim tipul în litere mici pentru a face cautarea nesensibila la majuscule/minuscule
	transform(tip.begin(), tip.end(), tip.begin(), [](unsigned char c) noexcept { return tolower(c); });

	// Utilizez COPY_IF pentru a filtra filmele în functie de criteriu
	if (filtru == 1)
	{
		//Filtrez filmele dupa titlu
		copy_if(filme.begin(), filme.end(), back_inserter(filtrare), [&](const Film& f)
		{
				//Convertesc titlul fiecarui film in litere mici
				string titluFilmLower = f.get_titlu();
				transform(titluFilmLower.begin(), titluFilmLower.end(), titluFilmLower.begin(), [](unsigned char c) noexcept { return tolower(c); });
				//Verific daca titlul filmului contine sirul "tip"
				return titluFilmLower.find(tip) != std::string::npos;
		});
	}
	else if (filtru == 2)
	{
		//Filtrez filmele dupa anul aparitiei
		copy_if(filme.begin(), filme.end(), back_inserter(filtrare), [&](const Film& f)
		{
				//Verific daca anul de aparitie al filmului este egal cu "tip"
				return tip == std::to_string(f.get_anAparitie());
		});
	}

	return filtrare;
}


/*
Functie de comparare a doua titluri de film

	pre: film1 - Film
		 film2 - Film
	post: returneaza true daca titlu film1 este mai mic lexicografic decat titlu film2, altfel returneaza false

*/
bool comparareTitlu(const Film film1, const Film film2) noexcept
{
	return film1.get_titlu() < film2.get_titlu();
}


/*
Functie de comparare a doi actori principali

	pre: film1 - Film
		 film2 - Film
	post: returneaza true daca actorPrincipal film1 este mai mic lexicografic decat actorPrincipal film2, altfel returneaza false

*/
bool comparareActorPrincipal(const Film film1, const Film film2) noexcept
{
	return film1.get_actorPrincipal() < film2.get_actorPrincipal();
}


/*
Functie de comparare dupa gen si an aparitie

	pre: film1 - Film
		 film2 - Film
	post: - returneaza true daca anAparitie film1 este mai mic decat anAparitie film2
		  - returneaza false daca anAparitie film1 este mai mare decat anAparitie film2
		  - daca anAparitie film1 este egal cu anAparitie film2, atunci:
			- returneaza true daca gen film1 este mai mic lexicografic decat gen film2
			- returneaza false in caz contrar
*/
bool comparareFilm(const Film& film1, const Film& film2) noexcept
{
	if (film1.get_anAparitie() != film2.get_anAparitie()) 
	{
		return film1.get_anAparitie() < film2.get_anAparitie();
	}
	return film1.get_gen() < film2.get_gen();
}

/*
Sorteaza lista de filme dupa titlu, actor sau gen + anAparitie

	pre: tip - 1, 2 sau 3
	post: returneaza lista de filme sortata dupa tipul ales

*/
vector<Film> FilmService::sortare(int tip)
{
	vector<Film> filme = rep.getAll();

	vector<Film> sortat;

	//Folosesc functia SORT pentru sortare
	if (tip == 1)
	{
		sort(filme.begin(), filme.end(), comparareTitlu);
	}

	if (tip == 2)
	{
		sort(filme.begin(), filme.end(), comparareActorPrincipal);
	}

	if (tip == 3)
	{
		sort(filme.begin(), filme.end(), comparareFilm);
	}

	return filme;
}


/*
Adauga un film in cos

	pre: titlu - string nenul
		 gen - string nenul
	post: apeleaza functia add() din repo pentru adaugarea filmului in cos

*/
void FilmService::addCos(string titlu, string gen)
{
	repoC.add(titlu, gen);
}


/*
Sterge toate filmele din cos

	pre: true
	post: apeleaza functia del() din repo pentru a sterge toate filmele din cos

*/
void FilmService::delCos()
{
	repoC.del();
}


/*
Returneaza toate filmele din cos

	pre: true
	post: returneaza lista de filme din cos, primita dupa apelarea functiei getAllCos() din repo

*/
const vector<Film>& FilmService::getAllCos() const noexcept
{
	return repoC.getAllCosRepo();
}


/*
Genereaza un cos cu un numar dat de filme alese aleatoriu din lista de filme

	pre: numar - intr > 0
	post: returneaza o lista de filme cu un numar dat de elemente generate aleatoriu, primita dupa apelarea functiei genereaza() din repo

*/
vector<Film> FilmService::genereazaCos(int numar)
{
	return repoC.genereaza(numar);
}


map<string, DTOFilm> FilmService::raport()
{
	map<string, DTOFilm> mp;
	vector<Film> filme = rep.getAll();

	for (const auto& m : filme)
	{
		DTOFilm f(m.get_gen());
		mp[m.get_gen()] = f;
	}

	for (const auto& m : filme)
	{
		const int nr = mp[m.get_gen()].getCount() + 1;
		DTOFilm val(m.get_gen(), nr);
		mp[m.get_gen()] = val;
	}

	return mp;

}
