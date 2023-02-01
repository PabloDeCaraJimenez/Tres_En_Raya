# include <iostream>
# include <vector>
# include <time.h>
# include <windows.h>
using namespace std;



class Tablero {

private:
	int numFilas;
	int numColum;
	string separador;
	vector<string*> reticula;
	bool haInsertado = false;	// Se usa para la cuenta de datos introducidos de manera aleatoria.
	int turno = 1;
	bool gana = false;
	bool fin = false;

	vector<string*> creaReticula(int nFil, int nCol){
		if (this->reticula.size()>0){
			this->reticula.resize(this->reticula.size() - numFilas);
		}
		int i;
		for (i = 0; i < nFil; i++){
			string* miFila = new string[nCol];
			for (int j = 0; j < nCol; j++){
				miFila[j] = " ";
			}
			this->reticula.push_back(miFila);
		}
	}
	void setNumFilas(int numFilas){
		creaReticula(numFilas, this->numColum);
		this->numFilas = numFilas;
	}
	void setNumColum(int numColum){
		creaReticula(this->numFilas, numColum);
		this->numColum = numColum;
	}
	void delay(int segundos) {
		for(int i = (time(NULL) + segundos); time(NULL) != i; time(NULL));
	}
	void SetColor(int value){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
	  }

public:
	Tablero(int numFilas = 3, int numColum = 3, string separador = "|"){
		creaReticula(numFilas, numColum);
		this->numFilas = numFilas;
		this->numColum = numColum;
		this->separador = separador;
	}
	~Tablero(){
		for (int i = 0; i < numFilas; i++){
			delete this->reticula[i];
		}
		cout << endl << "HASTA OTRA!" << endl;
		delay(2);
	}
	void imprimir(){
			cout << "			-------------";
		cout << endl;
		for (int i = 0; i < this->numFilas; i++){
			cout <<"			" << separador << " ";
			for (int j = 0; j < this->numColum; j++){
				if (this->reticula[i][j] == "O"){
					SetColor(10);
				}
				else if (this->reticula[i][j] == "X"){
					SetColor(12);
				}
				cout << this->reticula[i][j];
				SetColor(7);
				cout << " " << this->separador << " ";
			}
			cout << endl;
				cout << "			-------------";
			cout << endl;
		}
		cout << endl;
	}
	void rellenar(string dato){
		for (int i = 0; i < this->numFilas; i++){
			for (int j = 0; j < this->numColum; j++){
				this->reticula[i][j] = dato;
			}
		}
	}
	void insertar(int casilla){
		string entrada;
		haInsertado = false;
		while (!haInsertado){
			if (casilla<10 and casilla>0){
				int fil = (casilla - 1) / 3;
				int col = (casilla - 1) % 3;
				if (this->reticula[fil][col] == " "){
					if (turno % 2 == 0) this->reticula[fil][col] = "O";
					else this->reticula[fil][col] = "X";
					turno++;
					haInsertado = true;
				}
				else{
					casilla = bloqNum(casilla);
					cout << endl << "La casilla " << casilla << " ya esta ocupada por \"" << this->reticula[fil][col] << "\". Por favor inserte otra casilla: ";
					cin >> entrada;
					if (entrada == "1" or entrada == "2" or entrada == "3" or entrada == "4" or entrada == "5" or entrada == "6" or entrada == "7" or entrada == "8" or entrada == "9") casilla = stoi(entrada);
					else casilla = 0;
					casilla = bloqNum(casilla);
				}
			}
			else{
				cout << endl << "Casilla no valida. Inserte un numero de casilla entre 1 y 9: ";
				cin >> entrada;
				if (entrada == "1" or entrada == "2" or entrada == "3" or entrada == "4" or entrada == "5" or entrada == "6" or entrada == "7" or entrada == "8" or entrada == "9") casilla = stoi(entrada);
				else casilla = 0;
				casilla = bloqNum(casilla);
			}
		}
	}
	void reset(){
		this->turno = 1;
		this->gana = false;
		this->fin = false;
		rellenar(" ");
	}
	void chequeaGanador(){
		if (this->reticula[0][0]==this->reticula[0][1] and this->reticula[0][0]==this->reticula[0][2] and this->reticula[0][0]!=" ") gana=true;
		if (this->reticula[1][0]==this->reticula[1][1] and this->reticula[1][0]==this->reticula[1][2] and this->reticula[1][0]!=" ") gana=true;
		if (this->reticula[2][0]==this->reticula[2][1] and this->reticula[2][0]==this->reticula[2][2] and this->reticula[2][0]!=" ") gana=true;
		if (this->reticula[0][0]==this->reticula[1][0] and this->reticula[0][0]==this->reticula[2][0] and this->reticula[0][0]!=" ") gana=true;
		if (this->reticula[0][1]==this->reticula[1][1] and this->reticula[0][1]==this->reticula[2][1] and this->reticula[0][1]!=" ") gana=true;
		if (this->reticula[0][2]==this->reticula[1][2] and this->reticula[0][2]==this->reticula[2][2] and this->reticula[0][2]!=" ") gana=true;
		if (this->reticula[0][0]==this->reticula[1][1] and this->reticula[0][0]==this->reticula[2][2] and this->reticula[0][0]!=" ") gana=true;
		if (this->reticula[0][2]==this->reticula[1][1] and this->reticula[0][2]==this->reticula[2][0] and this->reticula[0][2]!=" ") gana=true;
	}
	void  chequeaFin(){
		if (this->turno > 9) this->fin = true;
	}
	int bloqNum(int miNumero){
		int casilla = miNumero;
		if (miNumero == 1) casilla = 7;
		if (miNumero == 2) casilla = 8;
		if (miNumero == 3) casilla = 9;
		if (miNumero == 7) casilla = 1;
		if (miNumero == 8) casilla = 2;
		if (miNumero == 9) casilla = 3;
		return casilla;
	}
	void jugar(){
		reset();
		int pongoEn;
		string entrada;
		cout << "	COMENZAMOS!" << endl << endl;
		imprimir();
		while (!gana and !fin){
			if (turno % 2 == 0){
				cout << "	TURNO DE ";
				SetColor(10);
				cout << "O";
				SetColor(7);
				cout << ": ";
			}
			else{
				cout << "	TURNO DE ";
				SetColor(12);
				cout << "X";
				SetColor(7);
				cout << ": ";
			}
			cin >> entrada;
			if (entrada == "1" or entrada == "2" or entrada == "3" or entrada == "4" or entrada == "5" or entrada == "6" or entrada == "7" or entrada == "8" or entrada == "9") pongoEn = stoi(entrada);
			pongoEn = bloqNum(pongoEn);
			insertar(pongoEn);
			imprimir();
			chequeaGanador();
			chequeaFin();
		}
		if (gana){
			if (turno % 2 == 0){
				cout << "		";
				SetColor(12);
				cout << "X";
				cout << " GANADOR!!!" << endl;
				SetColor(7);
			}
			else{
				cout << "		";
				SetColor(10);
				cout << "O";
				cout << " GANADOR!!!" << endl;
				SetColor(7);
			}
		}
		else cout << "		EMPATE!!!" << endl;

		reset();
	}

};


int main(){
	cout << endl << "BIENVENIDO A \"TRES EN RAYA\"" << endl;
	Tablero miTablero(3, 3);
	bool jugamos = true;
	string otra;
	cout << endl;
	cout << "			-------------" << endl;
	cout << "			| 7 | 8 | 9 |" << endl;
	cout << "			-------------" << endl;
	cout << "			| 4 | 5 | 6 |" << endl;
	cout << "			-------------" << endl;
	cout << "			| 1 | 2 | 3 |" << endl;
	cout << "			-------------" << endl;
	cout << endl << "Para colocar su ficha introduzca el numero de casilla (1-9) en la que desea colocarla." << endl << endl;

	while(jugamos){
		otra = "";
		miTablero.jugar();
		while (otra != "s" and otra != "S" and otra != "n" and otra != "N"){
			cout << endl << "OTRA PARTIDA? (S/N) ";
			cin >> otra;
			cout << endl;
			if (otra == "n" or otra == "N") jugamos = false;
			else if (otra == "s" or otra == "S") jugamos = true;
			else cout << "Perdone, no le he entendido." << endl;
		}
	}

	return 0;
}