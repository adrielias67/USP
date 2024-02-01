#include <iostream>
#include <ctime>
#include <experimental/random>
#include <string>
#include <fstream>

using namespace std;



int main(){
	
	srand(time(nullptr));
	
	ofstream file("testegerado.txt");

	int tamanho, partes, tam_max_parte, tam_min_parte, k, tamParte;
	string s;

	cout << "Tamanho da palavra: ";
	cin >> tamanho;

	cout << "Número de partes: ";
	cin >> partes;

	cout << "Tamanho mínimo de cada parte: ";
	cin >> tam_min_parte;

	cout << "Tamanho máximo de cada parte: ";
	cin >> tam_max_parte;

	cout << "k: ";
	cin >> k;

	file << partes << ' ' << k << endl;


	// Monta a palavra original
	for(int i = 0; i < tamanho; i++){

		int numero_letra = experimental::randint(0, 3);
		char letra;

		switch(numero_letra){
			case 0:
				letra = 'A';
				break;

			case 1:
				letra = 'C';
				break;

			case 2:
				letra = 'G';
				break;

			case 3:
				letra = 'T';
				break;
		}

		s.push_back(letra);
	}


	// Pega as substrings da palavra original e coloca no testegerado.txt
	string parte;

	// pega o início da palavra
	int ini = 0;
	tamParte = experimental::randint(tam_min_parte, tam_max_parte);
	
	parte = s.substr(ini, tamParte);
	file << parte << endl;

	// pega aleatório
	for(int i = 1; i < partes - 1; i++){
		parte.resize(0);

		tamParte = experimental::randint(tam_min_parte, tam_max_parte);
		ini = experimental::randint(0, tamanho-1-tamParte);

		parte = s.substr(ini, tamParte);
		file << parte << endl;
	}

	// pega o fim da palavra
	parte.resize(0);

	tamParte = experimental::randint(tam_min_parte, tam_max_parte);
	ini = tamanho - tamParte;

	parte = s.substr(ini, tamParte);
	file << parte << endl;

	file.close();

	cout << s << endl; // Imprime a palavra original no terminal

	return 0;
}