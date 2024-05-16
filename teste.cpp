#include"teste.h"
#include"service.h"
#include"repo.h"
#include"assert.h"
#include<iostream>
using namespace std;


//Test pentru add()
void testAdd()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC }; 

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);

	rep.emptyFile(); 
}

//Test pentru sterge()
void testSterge()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);

	serv.sterge("Harry Potter", "fantasy");
	const auto& filme2 = serv.getAll();
	assert(filme2.size() == 0);

	try
	{
		serv.sterge("Harry Potter", "fantasy");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	rep.emptyFile(); 
}

//Test pentru modifica()
void testModifica()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	Film f("Cinderella", "desene animate", 2000, "-");

	serv.modifica("Harry Potter", "fantasy", f);
	
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);
	assert(filme.at(0).get_titlu() == "Cinderella");

	try
	{
		serv.modifica("Harry Potter", "fantasy", f);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	rep.emptyFile(); 
}

//Test pentru store()
void testStore()
{
	FilmRepo rep;

	Film f{ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" };
	rep.store(f);
	const auto& filme = rep.getAll();
	assert(filme.size() == 1);

	try
	{
		rep.store(f);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	rep.store({ "Cruella", "desene animate", 2020, "Cruella Devil" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);
}

//Test pentru get_message()
void testGetMessage()
{
	RepoException re("exceptie");

	assert(re.get_message()=="exceptie");

}

//Test pentru get_anAparitie()
void testeGetAnAparitie()
{
	Film f("a", "b", 2000, "c");

	assert(f.get_anAparitie() == 2000);
}

//Test pentru get_actorPrincipal()
void testeGetActorPrincipal()
{
	Film f("a", "b", 2000, "c");

	assert(f.get_actorPrincipal() == "c");
}

//Test pentru cauta()
void testCauta()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC }; 

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<Film> cautare = serv.cauta("Harry");
	assert(cautare.size() == 2);

	vector<Film> cautare2 = serv.cauta("Ana");
	assert(cautare2.size() == 0);

	rep.emptyFile(); 
}

//Test pentru filtrare()
void testFiltrare()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<Film> filtrareTitlu = serv.filtrare(1,"Harry"); 
	assert(filtrareTitlu.size() == 2); 

	vector<Film> filtrareAn = serv.filtrare(2, "2000");
	assert(filtrareAn.size() == 3);

	rep.emptyFile(); 
}

//Test pentru sortare() dupa titlu
void testSortareDupaTitlu()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "c", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "c", "desene animate", 2020, "-" });
	rep.store({ "a", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "z", "fantasy", 2000, "Alex Russo" });
	rep.store({ "e", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<string> rezultat = { "a","c","c","e","z" };

	vector<Film> sortat = serv.sortare(1);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_titlu() == rezultat.at(i));
		i++;
	}

	rep.emptyFile();
}

//Test pentru sortare() dupa actor principal
void testSortareDupaActorPrincipal()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "c" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "c" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "a" });
	rep.store({ "Magicienii", "fantasy", 2000, "e" });
	rep.store({ "Cinderella", "desene animate", 2000, "z" });

	assert(filme.size() == 5);

	vector<string> rezultat = { "a","c","c","e","z" };

	vector<Film> sortat = serv.sortare(2);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_actorPrincipal() == rezultat.at(i));
		i++;
	}

	rep.emptyFile();
}

//Test pentru sortare() dupa an aparitie + gen
void testSortareDupaAnAparitieGen()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" }); 

	assert(filme.size() == 5);

	vector<int> rez1 = { 2000, 2000, 2000, 2010, 2020 };
	vector<string> rez2 = { "desene animate", "fantasy", "fantasy", "desene animate", "desene animate" };

	vector<Film> sortat = serv.sortare(3);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_anAparitie() == rez1.at(i));
		assert(f.get_gen() == rez2.at(i));
		i++;
	}

	rep.emptyFile();
}

void testSetters() 
{
	Film film("Initial Titlu", "Initial Gen", 2000, "Initial Actor");

	film.setTitlu("Noul Titlu");
	film.setGen("Noul Gen");
	film.setAnAparitie(2021);
	film.setActorPrincipal("Noul Actor");

	assert(film.get_titlu() == "Noul Titlu");
	assert(film.get_gen() == "Noul Gen");
	assert(film.get_anAparitie() == 2021);
	assert(film.get_actorPrincipal() == "Noul Actor");

}


//Test pentru delCos()
void testDel()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	try
	{
		serv.delCos();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	serv.add("Harry Potter 2", "desene animate", 2020, "-" );
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil");
	serv.add("Cinderella", "desene animate", 2000, "Cinderella");
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo");

	vector<Film> filme = rep.getAll(); 

	serv.addCos("Harry Potter", "fantasy");
	serv.addCos("Harry Potter 2", "desene animate");
	serv.addCos("Cinderella", "desene animate");

	vector<Film> filmeCos = serv.getAllCos();
	assert(filmeCos.size() == 3);

	repoC.del(); 

	auto cos = serv.getAllCos();
	assert(cos.size() == 0);

	rep.emptyFile();
}


//Test pentru addCos()
void testAddCos()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	serv.add("Harry Potter 2", "desene animate", 2020, "-");
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil");
	serv.add("Cinderella", "desene animate", 2000, "Cinderella");
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo");

	vector<Film> filme = rep.getAll();

	serv.addCos("Harry Potter", "fantasy");
	serv.addCos("Harry Potter 2", "desene animate");
	serv.addCos("Cinderella", "desene animate");

	vector<Film> filmeCos = serv.getAllCos();
	assert(filmeCos.size() == 3);

	try
	{
		serv.addCos("Tom & Jerry", "desene animate");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	vector<Film> filmeCos2 = serv.getAllCos(); 
	assert(filmeCos2.size() == 3); 

	rep.emptyFile();
}


//Test pentru genereazaCos()
void testGenereaza()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	vector<Film> genereazaVid = serv.genereazaCos(2);
	assert(genereazaVid.size() == 0);

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff"); 
	serv.add("Harry Potter 2", "desene animate", 2020, "-"); 
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil"); 
	serv.add("Cinderella", "desene animate", 2000, "Cinderella"); 
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo"); 

	vector<Film> filme = rep.getAll(); 

	int cate = 0;

	vector<Film> generat = serv.genereazaCos(7);

	for (const auto& f : filme)
	{
		for (const auto& g : generat)
		{
			if (f.get_titlu() == g.get_titlu())
			{
				cate++;
			}
		}
	}

	assert(cate == 7);

	rep.emptyFile();
}

//Test pentru raport()
void testRaport()
{
	//FilmRepo rep; - repo pentru filme (fara fisiere)
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff"); 
	serv.add("Harry Potter 2", "desene animate", 2020, "-"); 
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil"); 
	serv.add("Cinderella", "desene animate", 2000, "Cinderella"); 
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo"); 

	map<string, DTOFilm> mp = serv.raport();

	assert(mp.size() == 2);

	rep.emptyFile();
}


//Adauga in "FileTeste.txt" filme
void scrieInFisier()
{
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere 
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	serv.add("Harry Potter 2", "desene animate", 2020, "-");
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil");
	serv.add("Cinderella", "desene animate", 2000, "Cinderella");
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo");

}


//Test pentru loadFile()
void testLoadFile()
{
	scrieInFisier();

	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere  
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC }; 

	vector<Film> filme = rep.getAll();

	Film f1("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	Film f2("Harry Potter 2", "desene animate", 2020, "-"); 
	Film f3("101 dalmatieni", "desene animate", 2010, "Cruella Devil"); 
	Film f4("Cinderella", "desene animate", 2000, "Cinderella"); 
	Film f5("Magicienii", "fantasy", 2000, "Alex Russo"); 

	vector<Film> filme2 = { f1,f2,f3,f4,f5 };

	int i = 0;
	for (const auto& f : filme)
	{
		assert(f.get_titlu() == filme2.at(i).get_titlu());
		assert(f.get_gen() == filme2.at(i).get_gen());
		i++;
	}

	rep.emptyFile();
}

//Test pentru undo - adaugare
void testUndoAdauga()
{
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere  
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC };

	vector<Film> filme = serv.getAll();
	assert(filme.size() == 0); // verific ca nu exista filme in lista

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff"); // adaug un film
	filme = serv.getAll(); 
	assert(filme.size() == 1); // verific ca filmul a fost adaugat

	serv.Undo();
	filme = serv.getAll(); 
	assert(filme.size() == 0); // verific ca s-a realizat undo-ul

	try
	{
		serv.Undo();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	rep.emptyFile();  
}


//Test pentru undo - stergere
void testUndoSterge()
{
	scrieInFisier(); 

	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere   
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC }; 

	vector<Film> filme = serv.getAll(); 
	assert(filme.size() == 5); // verific sa existe doar cele 5 filme in lista

	serv.sterge("Harry Potter", "fantasy"); // sterg un film

	filme = serv.getAll(); 
	assert(filme.size() == 4); // verific ca filmul a fost sters

	serv.Undo();
	filme = serv.getAll(); 
	assert(filme.size() == 5); // verific ca s-a realizat undo-ul

	rep.emptyFile(); 
}


// Test pentru undo - modificare
void testUndoModifica()
{
	scrieInFisier(); 

	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere    
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC }; 

	vector<Film> filme = serv.getAll(); 
	assert(filme.size() == 5); // verific sa existe doar cele 5 filme in lista 

	Film film("a", "b", 3, "c");
	serv.modifica("Harry Potter", "fantasy", film); // modific un film

	serv.Undo();

	bool gasit = false;

	for (const auto& f : filme)
	{
		if (f.get_titlu() == "Harry Potter" && f.get_gen() == "fantasy")
		{
			gasit = true;
		}
	}

	assert(gasit == true); // verific ca s-a realizat undo-ul

	rep.emptyFile();
}

// Test pentru store RepoAbstract
void test_store() 
{
	RepoAbstract repo;
	Film film("Titanic", "Drama", 1997, "Leonardo DiCaprio");
	repo.store(film); 

	try 
	{
		repo.store(film);
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}

}

// Test pentru sterge RepoAbstract
void test_sterge() 
{
	RepoAbstract repo;
	Film film("Titanic", "Drama", 1997, "Leonardo DiCaprio");

	try
	{
		repo.sterge("Titanic", "Drama");
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}

	repo.store(film);

	repo.sterge("Titanic", "Drama"); 
}

// Test pentru modifica RepoAbstract
void test_modifica() 
{
	RepoAbstract repo;
	Film film("Titanic", "Drama", 1997, "Leonardo DiCaprio");

	try
	{
		Film film_modificat("Titanic", "Drama", 1998, "Kate Winslet");
		repo.modifica("Titanic", "Drama", film_modificat);
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}

	repo.store(film);

	Film film_modificat2("Titanic", "Drama", 1998, "Kate Winslet");
	repo.modifica("Titanic", "Drama", film_modificat2);
}

// Test pentru getAll RepoAbstract
void test_getAll() 
{
	RepoAbstract repo;
	Film film1("Titanic", "Drama", 1997, "Leonardo DiCaprio");
	Film film2("Inception", "SF", 2010, "Leonardo DiCaprio");

	repo.store(film1);
	repo.store(film2);

	const vector<Film>& filme = repo.getAll();

	assert(filme.size() == 2);
	assert(filme.at(0).get_titlu() == "Titanic");
	assert(filme.at(1).get_titlu() == "Inception");

}



// Test pentru store ProbabilityRepo
void test_store2() 
{
	ProbabilityRepo repo{ 1 };

	Film film("Titanic", "Drama", 1997, "Leonardo DiCaprio");

	try 
	{
		repo.store(film);
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}
}

// Test pentru sterge ProbabilityRepo
void test_sterge2() 
{
	ProbabilityRepo repo{ 1 };

	try 
	{
		repo.sterge("Titanic", "Drama");
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}
}

// Test pentru modifica ProbabilityRepo
void test_modifica2() 
{
	ProbabilityRepo repo{ 1 };

	Film film("Titanic", "Drama", 1997, "Leonardo DiCaprio");

	try 
	{
		repo.modifica("Titanic", "Drama", film);
		assert(false);
	}
	catch (RepoException&) 
	{
		assert(true);
	}
}

// Test pentru getAll ProbabilityRepo
void test_getAll2() 
{
	ProbabilityRepo repo{ 0.0f };

	repo.store(Film("Titanic", "Drama", 1997, "Leonardo DiCaprio"));
	repo.store(Film("Inception", "SF", 2010, "Leonardo DiCaprio"));

	const vector<Film>& filme = repo.getAll();

	assert(filme.size() == 2);
	assert(filme.at(0).get_titlu() == "Titanic");
	assert(filme.at(1).get_titlu() == "Inception");

	repo.sterge("Titanic", "Drama");
	repo.modifica("Inception", "SF", { "Titanic", "Drama", 1997, "Leonardo DiCaprio" });
}




void testAll()
{
	RepoFile rep{ "FileTeste.txt" };  // repo pentru filme cu fisiere
	rep.emptyFile(); // ma asigur ca fisierul cu filmele pentru teste este gol pentru ca testele sa functioneze

	//Teste aplicatie
	testAdd();
	testSterge();
	testModifica();
	testStore();
	testCauta();
	testFiltrare();
	testSortareDupaTitlu();
	testSortareDupaActorPrincipal();
	testSortareDupaAnAparitieGen();
	testRaport();  

	//Teste getters si setters
	testGetMessage(); 
	testeGetAnAparitie(); 
	testeGetActorPrincipal();
	testSetters(); 

	//Teste cos
	testDel();
	testAddCos();
	testGenereaza();

	//Teste fisiere
	testLoadFile();

	rep.emptyFile(); 
	//Teste Undo
	testUndoAdauga();
	testUndoSterge();
	testUndoModifica();

	//Teste pentru RepoAbstract
	test_store();
	test_sterge();
	test_modifica();
	test_getAll();


	//Teste pentru ProbabilityRepo
	test_store2(); 
	test_sterge2();
	test_modifica2();
	test_getAll2();


	std::cout << "\nTestele au avut succes!\n";
}
