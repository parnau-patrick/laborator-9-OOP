#include"repo.h"
#include<vector> 
#include"domain.h"
#include<algorithm>
#include<chrono>
#include<random>
#include<vector>
using namespace std;


/*
Functie pentru a obtine mesajul returnat de o exceptie

	pre: true
	post: returneaza mesajul returnat de exceptie
*/
string RepoException::get_message()
{
	return msg;
}

/*
Adauga un film in lista

	pre: film - Film
	post: adauga film in lista
	exception: arunca exceptie daca deja exista un film cu acelasi titlu si gen
*/
void FilmRepo::store(const Film& film)
{
	//utilizez RANGE FOR pentru a parcurge vectorul de filme
	for (const Film& f : filme)
	{
		if (f.get_titlu() == film.get_titlu() && f.get_gen() == film.get_gen())
		{
			throw RepoException("Filmul exista deja!");
		}
	}

	filme.push_back(film);

}

/*
Sterge un film din lista

	pre: titlu - string nenul
		 gen - string nenul
	post: sterge din lista filmul cu acelasi titlu si gen
	exception: arunca exceptie daca filmul de sters nu exista

*/
void FilmRepo::sterge(string titlu, string gen)
{
	auto it =remove_if(filme.begin(), filme.end(), [&](const Film& f) noexcept {  return f.get_titlu() == titlu && f.get_gen() == gen;});

	if (it != filme.end()) {
		filme.erase(it, filme.end());
		return;
	}

	throw RepoException("Filmul nu exista!");
}


/*
Modifica un film din lista

	pre: titlu - string nenul
		 gen - string nenul
		 film - Film
	post: modifica filmul cu acelasi titlu si gen furnizat cu datele din film
	exception: arunca exceptie daca filmul de modificat nu exista

*/
void FilmRepo::modifica(string titlu, string gen, const Film& film)
{

	//utilizez RANGE FOR pentru a parcurge vectorul de filme
	for (auto& it : filme)
	{
		if (it.get_titlu() == titlu && it.get_gen() == gen)
		{
			it.setTitlu(film.get_titlu());
			it.setGen(film.get_gen());
			it.setAnAparitie(film.get_anAparitie());
			it.setActorPrincipal(film.get_actorPrincipal());
			return;
		}
	}

	throw RepoException("Filmul nu exista!");
}


/*
Returneaza lista de filme

	pre: true
	post: returneaza lista de filme
*/
const vector<Film>& FilmRepo::getAll() noexcept
{
	return filme;
}


/*
Adauga un film in cos

	pre: titlu - string nenul
		 gen - string nenul
	post: adauga un film in cos
	exception: arunca exceptie daca filmul de adaugat in cos nu exista

*/
void CosRepo::add(string titlu, string gen)
{
	vector<Film> filme = rep.getAll();

	//utilizez RANGE FOR pentru a parcurge vectorul de filme
	for (const auto& f : filme)
	{
		if (f.get_titlu() == titlu && f.get_gen() == gen)
		{
			this->cos.push_back(f); // Folosim metoda push_back a obiectului filme
			return;
		}
	}

	throw RepoException("Filmul nu exista!");
}

/*
Sterge toate filmele din cos

	pre: true
	post: sterge toate filmele din cos
	exception: arunca exceptie daca cosul este gol

*/
void CosRepo::del()
{
	if (cos.size() == 0)
	{
		throw RepoException("Nu exista filme in cos!");
	}

	cos.clear();
}


/*
Genereaza un cos cu un numar dat de filme random din lista

	pre: numar - int > 0
	post: genereaza un cos cu un numar dat de filme random din lista

*/
vector<Film> CosRepo::genereaza(int numar)
{
	vector<Film> filme = rep.getAll();
	vector<Film> generat;

	//Verific daca lista de filme din repo este goala
	if (filme.size() == 0)
	{
		return generat;
	}

	//Amestec aleatoriu filmele din lista
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cos.begin(), cos.end(), std::default_random_engine(static_cast<unsigned>(seed)));

	//Adaug numarul de filme cerut in lista generat
	int j = 0;
	for (int i = 1; i <= numar; i++)
	{
		if (j == filme.size())
		{
			j = 0;

			//Amestec aleatoriu filmele din lista
			std::shuffle(cos.begin(), cos.end(), std::default_random_engine(static_cast<unsigned>(seed)));
		}

		generat.push_back(filme.at(j));
		j++;
	}

	return generat;
}


/*
Returneaza filmele din cos

	pre: true
	post: returneaza filmele din cos

*/
const vector<Film>& CosRepo::getAllCosRepo() noexcept
{
	return cos;
}






/*
Adauga un film in lista

	pre: film - Film
	post: adauga film in lista
	exception: arunca exceptie daca deja exista un film cu acelasi titlu si gen
*/
void RepoAbstract::store(const Film& film) 
{
	//utilizez RANGE FOR pentru a parcurge vectorul de filme
	for (const Film& f : filme)
	{
		if (f.get_titlu() == film.get_titlu() && f.get_gen() == film.get_gen())
		{
			throw RepoException("Filmul exista deja!");
		}
	}

	filme.push_back(film);

}

/*
Sterge un film din lista

	pre: titlu - string nenul
		 gen - string nenul
	post: sterge din lista filmul cu acelasi titlu si gen
	exception: arunca exceptie daca filmul de sters nu exista

*/ 
void RepoAbstract::sterge(string titlu, string gen)
{
	auto it = remove_if(filme.begin(), filme.end(), [&](const Film& f) noexcept {  return f.get_titlu() == titlu && f.get_gen() == gen; });

	if (it != filme.end()) {
		filme.erase(it, filme.end());
		return;
	}

	throw RepoException("Filmul nu exista!");
}


/*
Modifica un film din lista

	pre: titlu - string nenul
		 gen - string nenul
		 film - Film
	post: modifica filmul cu acelasi titlu si gen furnizat cu datele din film
	exception: arunca exceptie daca filmul de modificat nu exista

*/
void RepoAbstract::modifica(string titlu, string gen, const Film& film) 
{

	//utilizez RANGE FOR pentru a parcurge vectorul de filme
	for (auto& it : filme)
	{
		if (it.get_titlu() == titlu && it.get_gen() == gen)
		{
			it.setTitlu(film.get_titlu());
			it.setGen(film.get_gen());
			it.setAnAparitie(film.get_anAparitie());
			it.setActorPrincipal(film.get_actorPrincipal());
			return;
		}
	}

	throw RepoException("Filmul nu exista!");
}


/*
Returneaza lista de filme

	pre: true
	post: returneaza lista de filme
*/
const vector<Film>& RepoAbstract::getAll() noexcept 
{
	return filme;
}




/*
Adauga un film in lista

	pre: film - Film
	post: adauga film in lista
	exception: arunca exceptie daca deja exista un film cu acelasi titlu si gen
*/
void ProbabilityRepo::store(const Film& film)
{
	const int randomNumber = rand(); 
	const float rn = static_cast<float>(randomNumber) / RAND_MAX; 
	if (rn < this->prob)  
	{ 
		throw RepoException("\nNu execut operatia :)\n");
	}
	else 
	{
		RepoAbstract::store(film);
	}
}

/*
Sterge un film din lista

	pre: titlu - string nenul
		 gen - string nenul
	post: sterge din lista filmul cu acelasi titlu si gen
	exception: arunca exceptie daca filmul de sters nu exista

*/
void ProbabilityRepo::sterge(string titlu, string gen)
{
	const int randomNumber = rand();
	const float rn = static_cast<float>(randomNumber) / RAND_MAX;
	if (rn < this->prob) 
	{
		throw RepoException("\nNu execut operatia :)\n");
	}
	else 
	{
		RepoAbstract::sterge(titlu, gen);
	}
}


/*
Modifica un film din lista

	pre: titlu - string nenul
		 gen - string nenul
		 film - Film
	post: modifica filmul cu acelasi titlu si gen furnizat cu datele din film
	exception: arunca exceptie daca filmul de modificat nu exista

*/
void ProbabilityRepo::modifica(string titlu, string gen, const Film& film)
{

	const int randomNumber = rand();
	const float rn = static_cast<float>(randomNumber) / RAND_MAX;

	if (rn < this->prob) 
	{
		throw RepoException("\nNu execut operatia :)\n");
	}
	else 
	{
		RepoAbstract::modifica(titlu, gen, film);
	}
}


/*
Returneaza lista de filme

	pre: true
	post: returneaza lista de filme
*/
const vector<Film>& ProbabilityRepo::getAll() noexcept
{
	return RepoAbstract::getAll();
}