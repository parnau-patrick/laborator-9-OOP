#include "domain.h"


/*
Returneaza titlul filmului

	pre: true
	post: returneaza titlul filmului
*/
const string& Film::get_titlu() const noexcept
{
	return titlu;
}


/*
Returneaza genul filmului

	pre: true
	post: returneaza genul filmului
*/
const string& Film::get_gen() const noexcept
{
	return gen;
}


/*
Returneaza anul aparitiei filmului

	pre: true
	post: returneaza anul aparitiei filmului
*/
int Film::get_anAparitie() const noexcept
{
	return anAparitie;
}


/*
Returneaza actorul principal al filmului

	pre: true
	post: returneaza actorul principal al filmului
*/
const string& Film::get_actorPrincipal() const noexcept
{
	return actorPrincipal;
}


/*
Seteaza titlul filmului

	pre: newTitlu - string nenul
	post: seteaza titlul filmului cu newTitlu
*/
void Film::setTitlu(string newTitlu) 
{
    titlu = newTitlu;
}


/*
Seteaza genul filmului

	pre: newGen - string nenul
	post: seteaza genul filmului cu newGen
*/
void Film::setGen(string newGen) 
{
    gen = newGen;
}


/*
Seteaza anul aparitiei filmului

	pre: newAnAparitie - string nenul
	post: seteaza anul aparitiei filmului cu newAnAparitie
*/
void Film::setAnAparitie(int newAnAparitie) noexcept
{
    anAparitie = newAnAparitie;
}


/*
Seteaza actorul principal al filmului

	pre: newActorPrincipal - string nenul
	post: seteaza actorul principal al filmului cu newActorPrincipal
*/
void Film::setActorPrincipal(string newActorPrincipal) 
{
    actorPrincipal = newActorPrincipal;
}