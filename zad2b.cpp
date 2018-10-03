//Franjo Matkovic
//0036470672
#include <stdlib.h>
//#include <io.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
//#include <Windows.h>

#define RED 0
#define GREEN 1
#define BLUE 2

//Funkcija koja ispisuje matricu susjedstva
void ispisMatrice(std::vector<std::vector<int>> matrica) {
	for (auto const& linija : matrica) {
		for (auto const& brid : linija) {
			std::cout << brid << ' ';
		}
		std::cout << std::endl;
	}
}

//Klasa kojom je opisan vrh grafa te njegova boja
class PaintedVertex {
	public:
		int vetrex;
		int paint;
};

//funkcija koja provjerava da li u listi vec postoji cvoj obojan bojom
bool checkList(std::vector<PaintedVertex> listPainted, int paint, int cvor){
	PaintedVertex vertex;
	for (int i = 0; i < listPainted.size(); i++) {
		vertex = listPainted[i];
		if (vertex.vetrex == cvor) {
			if (vertex.paint == paint) {
				return false;
			}
		}
	}
	return true;
}

//funkcija koja provjerava da li je sigurno obojati cvor nekom bojom
bool checkIfSafeToPaint(std::vector<std::vector<int>> matrica, std::vector<PaintedVertex> listPainted, int paint, int cvor) {
	std::vector<int> neighbours = matrica[cvor];
	for (int i=0; i < neighbours.size(); i++) {
		if (neighbours[i]) {
			//provjeri da li u listi ima susjeda, kojom su bojom obojani, te može li se ovaj èvor obojati nekom bojom
			if (!checkList(listPainted, paint, i)) {
				return false;
			}
		}
	}
	return true;


}

//funkcija koja provjerava da li je vrh vec obojan
bool checkIfAlreadyInListPainted(std::vector<PaintedVertex> listPainted, int cvor){
	PaintedVertex vertex;
	for (int i = 0; i < listPainted.size(); i++) {
		if (listPainted[i].vetrex == cvor) return true;
	}
	return false;
}

//rekurzivna funkcija kojom se boja graf
int rekurzivnoBojanjeGrafa(std::vector<std::vector<int>> matrica, std::vector<PaintedVertex> listPainted, std::vector<int>colors, int brojCvorova) {

	PaintedVertex vertex;
	if (listPainted.size() == brojCvorova) 
	{
		for(int k=0;k<listPainted.size();k++)
		{
			
			std::cout<<k+1<<" "<<"Vrh: "<<listPainted[k].vetrex<<" Boja: "<<listPainted[k].paint<<std::endl;
		}
		return 1;
	}
	for (int i = 0; i < brojCvorova; i++) {
		for (int color = 0; color < colors.size(); color++) {
			if (!checkIfAlreadyInListPainted(listPainted,i) && checkIfSafeToPaint(matrica, listPainted, color, i)) {
				vertex.vetrex = i;
				vertex.paint = color;
				listPainted.push_back(vertex);
				colors[color]++;
				return rekurzivnoBojanjeGrafa(matrica, listPainted, colors, brojCvorova);
			}
		}
	}
	return 0;
}

//funkcija kojom se inicijalizira lista sa bojama
std::vector<int> initializeColorsList(std::vector<int> colors){
	colors.push_back(0);
	colors.push_back(0);
	colors.push_back(0);
	return colors;
}

//glavna funkcija koja inicijalizira varijable za provjeru obojivosti grafa
int provjeriDaLiJe3Obojiv(std::vector<std::vector<int>> matrica, int brojCvorova) {
	/*
	std::cout << colors[0] << std::endl;
	colors[0]++;
	std::cout << colors[0] << std::endl;
	*/
	bool Obojiv = false;
	//odi po svim vrhovima i probaj obojati graf
	/*
	for (int i = 0; i < brojCvorova; i++) {
		//inicijaliziraj brojac za brojanje 3 vrsnih grafova
		std::vector<int> colors = initializeColorsList();
		std::vector<PaintedVertex> listPainted;
		PaintedVertex vertex;
		vertex.vetrex = i;
		vertex.paint = RED;
		listPainted.push_back(vertex);
		colors[RED]++;
		Obojiv = rekurzivnoBojanjeGrafa(matrica, listPainted, colors, brojCvorova, i);
	}
	*/
	std::vector<int> paintableAll;
	std::vector<int> colors;
	colors = initializeColorsList(colors);
	for (int k=0;k<brojCvorova;k++){
		std::vector<PaintedVertex> listPainted;
		PaintedVertex vertex;
		vertex.vetrex = k;
		vertex.paint = RED;
		listPainted.push_back(vertex);
		colors[RED]++;
		paintableAll.push_back(rekurzivnoBojanjeGrafa(matrica, listPainted, colors, brojCvorova));
	}
	int isPaintable = 0;
	for (int k=0;k<brojCvorova;k++){
		if(paintableAll[k]==1) isPaintable=1;
	}
	return isPaintable;
}





int main(int argc, char** argv) {
	char z;
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

	//OVDJE SE ZOVE FUNKCIJA
	int isAlmost = provjeriDaLiJe3Obojiv(matrica, brojCvorova);

	std::cout << isAlmost << std::endl;
	std::cin >> z;
	return 0;
}
