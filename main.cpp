#include"ui.h"
#include"teste.h"

int main()
{
	testAll();
	
	{
		int cmd;
		cout << "Alegeti optiunea:\n     1. Repo File\n     2. Repo Probability\n     0. Exit\n\nOptiune: ";
		cin >> cmd;

		if (cmd == 1)
		{
			//FilmRepo rep; - repo pentru filme (fara fisiere)
			RepoFile rep{ "filme.txt" };  // repo pentru filme cu fisiere 
			CosRepo repoC{ rep };  // repo pentru cos 
			FilmService serv{ rep, repoC }; 
			UI ui{ serv }; 

			ui.startUI(); 
		}
		if (cmd == 2)
		{
			ProbabilityRepo rep{ 0.5f };
			RepoFile repo{ "filme.txt" };
			CosRepo repoC{ repo };  
			FilmService serv{ rep, repoC };
			UI ui{ serv }; 

			ui.startUI(); 
		}
		if (cmd == 0)
		{
			cout << "\nLa revedere!\n";
		}
	}
	
	if (!_CrtDumpMemoryLeaks()) 
	{
		std::cout << "\n\n\nNU sunt memory leaks!\n";
	}

	return 0;
}