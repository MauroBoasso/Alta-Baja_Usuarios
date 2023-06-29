#include <iostream>
#include <fstream> //Entrada y salida de un archivo
#include <cstdlib>
#include <string>
#include <windows.h>
using namespace std;

//Menu a modo de interfaz para el usuario.

int menu() {
	int opc;
	system("cls");
	cout << "-----------------------------" << endl;
	cout << "|--------Boasso Mauro--------|" << endl;
	cout << "-----------------------------" << endl;
	cout << endl;
	cout << "______________________________" << endl;
	cout << "|�����������������������������|" << endl;
	cout << "|����������ABM CLIENTES�������|" << endl;
	cout << "______________________________" << endl;
	cout << endl;
	cout << "#1- Agregar Cliente           #" << endl;
	cout << "#2- Ver Listado de Clientes   #" << endl;
	cout << "#3- Buscar Cliente            #" << endl;
	cout << "#4- Modificar Cliente         #" << endl;
	cout << "#5- Eliminar Cliente          #" << endl;
	cout << "#6- Salir                     #" << endl;
	cout << "#_____________________________#" << endl;
	cout << endl;
	cout << "Digite una opci�n: ";
	cin >> opc;
	return opc;
}

//Verificacion de cliente

bool estaElIdDisponible(string id) {
	ifstream leer("Clientes.txt", ios:: in );
	string idCliente;
	
	if(leer.is_open()){
		while (!leer.eof()) {
			leer >> id;
			if (id == idCliente) {
				cout << "El ID ya se encuentra asignado";
				Sleep(1500);
				leer.close();
				return false;
			}
		}
		leer.close();
	}
	return true;
}

//Funcion agregar para a�adir un nuevo cliente al sistema

void agregar() {
	system("cls");
	string nom, ape, id, cod_postal, calle, num_domicilio;
	
	cout << "Indique la ID de cliente: ";
	cin >> id;
	cout << "Indique el Nombre del cliente: ";
	cin >> nom;
	cout << "Indique el Apellido del cliente: ";
	cin >> ape;
	cout << "Indique la Cod_Postal de cliente: ";
	cin >> cod_postal;
	cout << "Indique la Calle del cliente: ";
	cin >> calle;
	cout << "Indique N� de Domicilio del cliente: ";
	cin >> num_domicilio;
	
	if (estaElIdDisponible(id)) {
		ofstream escritura("Clientes.txt", ios::out | ios::app);
		if (escritura.is_open()) {
			escritura << id << " " << nom << " " << ape << " " << cod_postal << " " << calle << " " << num_domicilio << endl;
			escritura.close();
		}
	}
}

//Funcion para ver el listado de los clientes que se registraron dentro del sistema

void verListado() {
	system("cls");
	string nom, ape, id, cod_postal, calle, num_domicilio, espacio;
	ifstream lectura("Clientes.txt", ios:: in );
	
	if (lectura.is_open()) {
		cout << "----------BASE DE DATOS----------\n";
		while (lectura >> id) {
			lectura >> nom;
			lectura >> ape;
			lectura >> cod_postal;
			lectura >> calle;
			lectura >> num_domicilio;
			
			cout << "\nID Cliente: " << id << endl;
			cout << "Nombre: " << nom << endl;
			cout << "Apellido: " << ape << endl;
			cout << "Cod_Postal: " << cod_postal << endl;
			cout << "Direccion: " << calle << " " << num_domicilio << endl;
			cout << "\n ----------------------------------" << endl;
		}
		lectura.close();
	}
	system("pause");
}

//Busqueda de clientes + impresion de sus datos 

void buscarCliente(ifstream & lectura) {
	system("cls");
	lectura.open("Clientes.txt", ios:: in );
	string nom, ape, id, id_aux, cod_postal, calle, num_domicilio;
	
	bool encontrado = false;
	cout << "Digite la ID: ";
	cin >> id_aux;
	while (lectura >> id) {
		lectura >> nom;
		lectura >> ape;
		lectura >> cod_postal;
		lectura >> calle;
		lectura >> num_domicilio;
		
		if (id == id_aux) {
			system("cls");
			cout << "\nID Cliente: " << id << endl;
			cout << "Nombre: " << nom << endl;
			cout << "Apellido: " << ape << endl;
			cout << "Cod_Postal: " << cod_postal << endl;
			cout << "Direccion: " << calle << " " << num_domicilio << endl;
			cout << "\n ----------------------------------" << endl;
			encontrado = true;
		}
	}
	lectura.close();
	if (!encontrado)
		cout << "Dato no encontrado" << endl;
	system("pause");
}

//Modificacion de los datos almacenados del cliente + a�adir los nuevos

void modificar(ifstream & lectura) {
	system("cls");
	string nom, id, ape, cod_postal, calle, num_domicilio;
	string nomaux, apeaux, idaux, cod_postal_aux, calle_aux, num_domicilio_aux;
	lectura.open("Clientes.txt", ios:: in );
	ofstream aux("auxiliar.txt", ios::out);
	
	if (lectura.is_open() && aux.is_open()) {
		cout << "Indique el Id del Cliente ";
		cin >> idaux;
		system("cls");
		while (lectura >> id) {
			lectura >> nom;
			lectura >> ape;
			lectura >> cod_postal;
			lectura >> calle;
			lectura >> num_domicilio;
			
			if (id == idaux) {
				cout << "\t--Datos nuevos--\n";
				cout << " Nombre: ";
				cin >> nomaux;
				cout << " Apellido: ";
				cin >> apeaux;
				cout << " C�digo Postal: ";
				cin >> cod_postal_aux;
				cout << " Calle: ";
				cin >> calle_aux;
				cout << " N�m. Domicilio: ";
				cin >> num_domicilio_aux;
				
				aux << id << " " << nomaux << " " << apeaux << " " << cod_postal_aux << " " << calle_aux << " " << num_domicilio_aux << endl;
			} else {
				aux << id << " " << nom << " " << ape << " " << cod_postal << " " << calle << " " << num_domicilio << endl;
			}
		}
		lectura.close();
		aux.close();
		remove("Clientes.txt");
		rename("auxiliar.txt", "Clientes.txt");
	} else {
		cout << "No se pudo abrir el archivo o aun no ha sido creado";
	}
	
}

//Eliminacion de un cliente guardado en nuestro sistema y dado de baja todos sus datos almacenados

void eliminar() {
	system("cls");
	string nom, id, ape, idaux, cod_postal, calle, num_domicilio;
	ifstream lectura("Clientes.txt", ios:: in );
	ofstream aux("auxiliar.txt", ios::out);
	
	if (lectura.is_open()) {
		cout << "Digite el Id del Cliente que desea eliminar ";
		cin >> idaux;
		cout << endl;
		while (lectura >> id) {
			lectura >> nom;
			lectura >> ape;
			lectura >> cod_postal;
			lectura >> calle;
			lectura >> num_domicilio;
			
			if (id == idaux) {
				cout << "El registro del usuario se ha Eliminado" << endl;
				Sleep(1500);
			} else {
				aux << id << " " << nom << " " << ape << " " << cod_postal << " " << calle << " " << num_domicilio << endl;
			}
		}
		lectura.close();
		aux.close();
		remove("Clientes.txt");
		rename("auxiliar.txt", "Clientes.txt");
	} else
		cout << "error" << endl;
}

//main en donde se llaman todos los datos de cada funcion almacenada 
//Programa Principal

int main(int argc, char * argv[]) {
	ofstream escritura;
	ifstream lectura;
	struct cliente;
	int opc;
	
	do {
		system("cls");
		opc = menu();
		switch (opc) {
		case 1: agregar(); break;
		case 2:	verListado(); break;
		case 3:	buscarCliente(lectura); break;
		case 4:	modificar(lectura);	break;
		case 5:	eliminar();	break;
		}
	} while (opc != 6);
	
	return 0;
}
