//#include <io.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
//#include <Windows.h>


//Funkcija koja ispisuje matricu susjedstva
void ispisMatrice(std::vector<std::vector<int>> matrica) {
	for (auto const& linija : matrica) {
		for (auto const& brid : linija) {
			std::cout << brid << ' ';
		}
		std::cout << std::endl;
	}
}


void printList(std::vector<int> list) {
	std::vector<int>::iterator v = list.begin();
	while (v != list.end()) {
		//std::cout << (*v) << " ";
		v++;
	}
	//std::cout<<std::endl;
}


//pomocna funkcija koja provjerava da li se moze ubaciti u listu
bool checkIfSafe(std::vector<std::vector<int>> matrica, std::vector<int> lista, int Cvor) {

	//provjeri da li je cvor vec u listi
	for (int k=0; k < lista.size(); k++) {
		if (lista[k] == Cvor) {
			return false;
		}
	}
	//provjeri da li se moze cvor spojiti sa zadnjim elementom u listi
	if (matrica[lista.back()][Cvor] == 0) {
		return false;
	}
	return true;

}

//Ako Cvor nema susjeda onda graf nije skoro hamiltonovski ni hamiltonovski
bool checkIfAnyNeighbours(std::vector<std::vector<int>> matrica, int Cvor) {
	std::vector<int> neighbourList = matrica[Cvor];
	bool result = false;
	for (int k = 0; k < neighbourList.size(); k++) {
		if (matrica[k][Cvor] == 1) {
			result = true;
		}
	}
	return result;
}




int RekurzivnoUbacivanjeElemenata(std::vector<std::vector<int>> matrica, std::vector<int> lista, int brojCvorova, int Cvor) {

	//Ako je zadnji u listi, provjeri da li se spaja sa pocetnim cvorom - ako se spaja to je onda hamiltonovski ciklus i vrati false, inace vrati true
	if (lista.size() == brojCvorova) {
		if (matrica[lista.front()][lista.back()]) {
			//Ako je povezan zadnji sa prvim to je onda Hamiltonov ciklus
			return 1;
		}
		else {
			return 2;
			
		}
	}
	//Ubacuj elemente u listu
	for (int l = 0; l < brojCvorova; l++) {
		if (checkIfSafe(matrica, lista, l)) {
			lista.push_back(l);
			int out = RekurzivnoUbacivanjeElemenata(matrica, lista, brojCvorova, l);
			if (out == 2) return 2;
			if (out == 1) return 1;
			lista.pop_back(); 
		}
	
	}
	//printList(lista);
	return 0;


}


bool SkoroHamiltonovskiCiklus(std::vector<std::vector<int>> matrica, int brojCvorova) {

	std::vector<int> listBool;
	bool almostHamilton = false;
	bool hamilton = false;
	//Odi po svim cvorovima i rekurzivno probaj izgraditi skoro Hamiltonovski ciklus
	for (int i = 0; i < brojCvorova; i++) {
		std::vector<int> lista;
		lista.push_back(i);
		listBool.push_back(RekurzivnoUbacivanjeElemenata(matrica, lista, brojCvorova, i));
	}
	
	std::vector<int>::iterator v = listBool.begin();
	while (v != listBool.end()) {
		//std::cout << *v << " ";
		//Ako je 2 onda je skoro hamiltonovski ciklus
		if (*v == 2) almostHamilton = true;
		if (*v == 1) hamilton = true;
		v++;
	}
	//std::cout << std::endl;
	if (almostHamilton && !hamilton) return true;
	return false;

}

int main(int argc, char** argv) {
	//std::cout << argc << std::endl;
	if (argc < 2) {
		std::cout << "Nije navedena ulazna datoteka!" << std::endl;
		exit(1);
	}
	
	std::string line;
	std::ifstream myfile;
	int variable;
	std::vector<std::vector<int>> matrica;
	std::string name(argv[1]);
	myfile.open(name);
	if (!myfile.is_open()) {
		std::cout << "Datoteka se ne moze otvoriti!" << std::endl;
		exit(1);
	}
	//Ucita se prvo broj vrhova
	std::getline(myfile, line);
	int brojCvorova = atoi(line.c_str());

	//Ucitava se matrica povezanosti
	while (std::getline(myfile, line)) {
		std::istringstream iss(line);
		std::vector<int> linija;
		if (line.empty())
		{
			continue;
		}
		while (iss >> variable)
		{
			//std::cout << variable << std::endl;
			linija.push_back(variable);
	}
	matrica.push_back(linija);
	}

	//std::cout << matrica.size() << std::endl;
	int isAlmost = SkoroHamiltonovskiCiklus(matrica, brojCvorova);

	std::cout <<isAlmost <<std::endl;
	char z;
	std::cin >> z;
	return 0;
}
