#include"ui.h"
#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::getline;
using namespace std;


void UI::startUI()
{
	while (true)
	{

		cout << "\nMeniu: \n   1. Adaugare\n   2. Stergere\n   3. Modificare\n   4. Afisare\n   5. Cautare\n   6. Filtrare\n   7. Sortare\n";
		cout << "   8. Goleste cos\n   9. Adauga in cos\n   10. Genereaza cos\n   11. Export cos\n   12. Raport\n   13. Undo\n   0. Exit\n\nComanda: ";
		int cmd = 0;

		cin >> cmd;

		if (cmd < 0 || cmd>13)
		{
			cout << "\nComanda invalida!\n";
			continue;
		}
		if (cmd == 0)
		{
			cout << "\nLa revedere!\n";
			break;
		}
		if (cmd == 1)
		{
			string titlu;
			string gen;
			int anAparitie;
			string actorPrincipal;

			cout << "\ntitlu: ";
			cin.ignore();
			getline(cin,titlu);
			cout << "gen: ";
			getline(cin, gen);
			cout << "an aparitie: ";
			cin >> anAparitie;
			cout << "actor principal: ";
			cin.ignore();
			getline(cin, actorPrincipal);

			try
			{
				serv.add(titlu, gen, anAparitie, actorPrincipal);
				cout << "\nFilm adaugat!\n";
			}
			catch (RepoException& e)
			{
				cout <<'\n'<< e.get_message()<<'\n';
			}

			afiseazaCos(serv);
		}
		if (cmd == 2)
		{
			string titlu; 
			string gen; 

			cout << "\ntitlu: "; 
			cin.ignore(); 
			getline(cin, titlu); 
			cout << "gen: "; 
			getline(cin, gen); 


			try
			{
				serv.sterge(titlu, gen); 
				cout << "\nFilm sters!\n";
			}
			catch (RepoException& e) 
			{
				cout << '\n' << e.get_message() << '\n'; 
			}
			
			afiseazaCos(serv); 
		}
		if (cmd == 3)
		{
			string titluModifica; 
			string genModifica;

			string titlu; 
			string gen; 
			int anAparitie; 
			string actorPrincipal; 

			cout << "\ntitlu: "; 
			cin.ignore(); 
			getline(cin, titluModifica); 
			cout << "gen: "; 
			getline(cin, genModifica); 

			cout << "\ntitlu: "; 
			getline(cin, titlu); 
			cout << "gen: "; 
			getline(cin, gen); 
			cout << "an aparitie: "; 
			cin >> anAparitie; 
			cout << "actor principal: "; 
			cin.ignore(); 
			getline(cin, actorPrincipal); 

			int ok = 0;

			if (titluModifica != titlu)
			{
				const vector<Film> filme = serv.getAll();

				//utilizez RANGE FOR pentru a parcurge vectorul filme
				for (const auto& f: filme)
				{
					if (f.get_titlu() == titlu && f.get_gen() == gen) 
					{
						cout << "\nExista deja un film cu aceste date!\n";
						ok = 1;
						break;
					}
				}
			}

			if (ok == 1)
			{
				continue;
			}

			try
			{
				Film film(titlu, gen, anAparitie, actorPrincipal);
				serv.modifica(titluModifica, genModifica, film);
				cout << "\nFilm modificat!\n"; 
			}
			catch (RepoException& e)
			{
				cout << '\n' << e.get_message() << '\n';
			}

			afiseazaCos(serv); 
		}
		if (cmd == 4)
		{ 
			const auto& filme = serv.getAll(); 

			if (filme.size() == 0)
			{
				cout << "\nNu exista filme de afisat!\n";
				continue;
			}

			cout << "\nFilme:\n";
			//utilizez RANGE FOR pentru a parcurge vectorul filme
			for (const auto& f:filme)
			{
				afisare(f);
			}

			afiseazaCos(serv);    
		}
		if (cmd == 5)
		{
			string titlu;

			cout << "\ntitlu: "; 
			cin.ignore(); 
			getline(cin, titlu); 

			const vector<Film> cautare = serv.cauta(titlu);

			if (cautare.size() == 0)
			{
				cout << "\nNu exista filme de afisat!\n";
				continue;
			}

			cout << "\nRezultat cautare:\n";
			//utilizez RANGE FOR pentru a parcurge vectorul cautare
			for (const auto& f:cautare)
			{
				afisare(f);
			}

			afiseazaCos(serv);  
		}
		if (cmd == 6)
		{
			int filtrare;
			string tip;
			cout << "\n1 - dupa titlu\n2 - dupa an aparitie\noptiune: ";
			cin >> filtrare;

			if (filtrare < 1 || filtrare>2)
			{
				cout << "\nOptiune invalida!\n";
				continue;
			}

			if (filtrare == 1)
			{
				cout << "\ntitlu: ";
			}
			else
			{
				cout << "\nan aparitie: ";
			}
			cin.ignore();
			getline(cin, tip);

			const vector<Film> filtrat = serv.filtrare(filtrare, tip);

			if (filtrat.size() == 0)
			{
				cout << "\nNu exista filme de afisat!\n";
				continue;
			}

			cout << "\nFiltrare";
			if (filtrare == 1)
			{
				cout << " dupa titlu:\n";
			}
			if (filtrare == 2)
			{
				cout << " dupa an aparitie:\n";
			}

			//utilizez RANGE FOR pentru a parcurge vectorul filtrat
			for (const auto& f:filtrat)
			{
				afisare(f);
			}

			afiseazaCos(serv);  
		}
		if (cmd == 7)
		{
			int tip;
			cout << "\n1 - dupa titlu\n2 - dupa actor principal\n3 - an aparitie + gen\noptiune: ";
			cin >> tip;

			if (tip < 1 || tip>3)
			{
				cout << "\nOptiune invalida!\n";
				continue;
			}

			const vector<Film> sortat = serv.sortare(tip);

			cout << "\nSortare";
			if (tip == 1)
			{
				cout << " dupa titlu: \n";
			}
			if (tip == 2)
			{
				cout << " dupa actor principal: \n";
			}
			if (tip == 3)
			{
				cout << " dupa an aparitie + gen: \n";
			}

			if (sortat.size() == 0)
			{
				cout << "Nu exista filme de afisat!";
			}

			//utilizez RANGE FOR pentru a parcurge vectorul sortat
			for (const auto& f:sortat)
			{
				afisare(f);
			}

			afiseazaCos(serv);  
		}
		if (cmd == 8)
		{
			try
			{
				serv.delCos();
				cout << "\nCosul a fost golit!\n";
			}
			catch (RepoException& e)
			{
				cout << '\n' << e.get_message() << '\n';
			}

			afiseazaCos(serv);  
		}
		if (cmd == 9)
		{
			string titlu;
			string gen;

			cout << "\ntitlu: ";
			cin.ignore();
			getline(cin, titlu);
			cout << "gen: ";
			getline(cin, gen);

			try
			{
				serv.addCos(titlu, gen);
				cout << "\nFilm adaugat in cos!\n";
			}
			catch (RepoException& e)
			{
				cout << '\n' << e.get_message() << '\n';
			}

			afiseazaCos(serv);  
		}
		if (cmd == 10)
		{
			int numar;
			cout << "numar filme de generat: ";
			cin >> numar;

			if (numar < 1)
			{
				cout << "Numarul trebuie sa fie mai mare decat 0!\n";
				continue;
			}

			const vector<Film> filme = serv.genereazaCos(numar);

			if (filme.size() == 0)
			{
				cout << "Nu exista filme pentru a putea genera cosul!\n";
				continue;
			}

			for (const auto& f : filme) 
			{
				serv.addCos(f.get_titlu(), f.get_gen());
			}

			const vector<Film> generare = serv.getAll(); 

			afiseazaCos(serv);   
		}
		if (cmd == 11)
		{
			string fisier;
			cout << "nume fisier: ";
			cin >> fisier;

			const vector<Film> filme = serv.getAllCos();

			if (fisier.find(".html") == string::npos) 
			{
				fisier += ".html";
			}

			exportHTML(fisier, filme);
		}
		if (cmd == 12)
		{
			map<string, DTOFilm> mp = serv.raport();

			if (mp.size() == 0)
			{
				cout << "Nu exista raport de afisat!\n";
				continue;
			}

			cout << "Raport:\n";
			for (const auto& pair : mp)
			{
				cout << "Gen: " << pair.first;
				cout << "; Numar filme: " << pair.second.getCount() << "\n";
			}
		}
		if (cmd == 13)
		{
			try 
			{
				serv.Undo(); 
				cout << "Undo realizat cu succes!\n";
			}
			catch (RepoException& e) 
			{
				cout << e.get_message() << "\n";
			}
		}
	}
}

void exportHTML(const string& fisier, const vector<Film>& filme)
{
	std::ofstream outFile(fisier, std::ios::out | std::ios::trunc);

	if (outFile.is_open())
	{
		outFile << "<!DOCTYPE html>\n";
		outFile << "<html lang=\"ro\">\n";
		outFile << "<head>\n";
		outFile << "<meta charset=\"UTF-8\">\n";
		outFile << "<title>Cos filme</title>\n";
		outFile << "<style>table {border-collapse: collapse; width: 100%;}</style>\n"; // Stilizare pentru tabel
		outFile << "<style>th {background-color: #ff1493; color: #ffffff; text-align: center; border: 1px solid #000;}</style>\n"; // Antetele de coloane: roz inchis, text alb, aliniat in centru, delimitare tabel
		outFile << "<style>td {background-color: #ffc0cb; text-align: center; border: 1px solid #000;}</style>\n"; // Celulele din tabel: roz, text aliniat in centru, delimitare tabel
		outFile << "<style>body {background-color: #ffe4e1;}</style>\n"; // Fundalul paginii: roz deschis
		outFile << "</head>\n";
		outFile << "<body>\n";
		outFile << "<h1 style=\"text-align:center;\">Cos filme</h1>\n"; // Titlul centrare
		outFile << "<table>\n";
		outFile << "<tr><th>Numar</th><th>Titlu</th><th>Gen</th><th>An aparitie</th><th>Actor principal</th></tr>\n";

		int index = 1;
		for (const auto& f : filme)
		{
			outFile << "<tr><td>" << index << "</td><td>" << f.get_titlu() << "</td><td>" << f.get_gen() << "</td><td>" << f.get_anAparitie() << "</td><td>" << f.get_actorPrincipal() << "</td></tr>\n";
			index++;
		}

		outFile << "</table>\n";
		outFile << "</body>\n";
		outFile << "</html>\n";

		outFile.close();
		std::cout << "Exportul a fost realizat cu succes in fisierul " << fisier <<"!\n" << std::endl;
	}
	else
	{
		std::cerr << "Eroare la deschiderea fisierului " << fisier << "!\n" << std::endl;
	}

}

void afiseazaCos(const FilmService& serv)
{
	const vector<Film> filmeCos = serv.getAllCos();

	cout << "\n\n\nCos cumparaturi: "<<filmeCos.size()<<"\n";

	if (filmeCos.size() == 0)
	{
		cout << "Nu sunt filme in cos!\n";
		return;
	}

	//utilizez RANGE FOR pentru a parcurge vectorul filmeCos
	for (const auto& f : filmeCos)
	{
		afisare(f);
	}
}


void afisare(const Film& f)
{
	cout << "titlu: " << f.get_titlu() << "; gen: " << f.get_gen() << "; an aparitie: " << f.get_anAparitie() << "; actor principal: " << f.get_actorPrincipal()<<'\n';
}
