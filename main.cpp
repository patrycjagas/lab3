// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iterator>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sort (Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sort(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	srand(time(NULL));
	vectorOfSlavs.push_back(&slavs[0]);

	// Umieść Słowian w losowej kolejności w wektorze.

	for (int i=0; i<n; i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin() + rand()%(vectorOfSlavs.size()), &slavs[i]);

	vectorOfSlavs.pop_back();

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze

	for (vector <Slav *>::iterator it_vectorOfSlavs = vectorOfSlavs.begin(); it_vectorOfSlavs != vectorOfSlavs.end(); it_vectorOfSlavs++)
		cout << (**it_vectorOfSlavs).description() << endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.

	for (vector <Slav *>::iterator it_vectorOfSlavs = vectorOfSlavs.begin(); it_vectorOfSlavs != vectorOfSlavs.end(); it_vectorOfSlavs++)
		setOfSlavs.insert(*it_vectorOfSlavs);

	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	
	set <Slav *>::iterator it_setOfSlavs=setOfSlavs.begin();
 	while(it_setOfSlavs != setOfSlavs.end())
 	{
 		mapOfSlavs[*it_setOfSlavs] = *(it_setOfSlavs = setOfSlavs.erase(it_setOfSlavs));
 		it_setOfSlavs = setOfSlavs.erase(it_setOfSlavs);
 	}

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian

	for(map <Slav *, Slav *>::iterator it_mapOfSlavs = mapOfSlavs.begin(); it_mapOfSlavs != mapOfSlavs.end(); it_mapOfSlavs++)
		cout << (it_mapOfSlavs -> first) -> description() << " " << (it_mapOfSlavs -> second) -> description() << endl;
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.

	for (int i = 0; i < n; i++)
		queueOfSlavs.push(&slavs[i]);
	
	REPORT_ADAPTERS;

	printf("## stack\n");

	// Przenieś Słowian z kolejki do stosu.

	while (!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	while (!stackOfSlavs.empty())
	{
		cout << (*(stackOfSlavs.top())).description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void sort (Slav *slavs, int n)
{
	map <sex, vector <Slav *>> mapOfSlavs;
	
	for(int i = 0; i < n; i++)
		if(slavs[i].sexOfSlav() == male)
			mapOfSlavs[male].push_back(&slavs[i]);
		else
			mapOfSlavs[female].push_back(&slavs[i]);

	vector <Slav *>::iterator it_vector;

	cout << endl << "Males:" << endl;
	for(it_vector = mapOfSlavs[male].begin(); it_vector != mapOfSlavs[male].end(); it_vector++)
		cout << (**it_vector).description() << endl;

	cout << endl << "Females:" << endl;
	for(it_vector = mapOfSlavs[female].begin(); it_vector != mapOfSlavs[female].end(); it_vector++)
		cout << (**it_vector).description() << endl;	
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
