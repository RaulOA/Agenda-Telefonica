#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

// ----------------------------------------- Estructura ------------------------------------------------------------------------------------------------------------------------

struct nodo {
	struct nodo * anterior;
	int telefono;
	string nombre;
	string empresa;
	string direccion;
	int dia;
	int mes;
	int year;
	int edad;
	string cumple;
	struct nodo * siguiente;
};

typedef struct nodo * Tlista;

// ----------------------------------------- Menus ------------------------------------------------------------------------------------------------------------------------------

void menu_principal() {

    cout<<"\n\t Menu de opciones Agenda telefonica\n\n";
    cout<<" 1. Ingresar datos       "<<endl;
    cout<<" 2. Imprimir datos       "<<endl;
    cout<<" 3. Eliminar datos       "<<endl;
    cout<<" 4. Modificar datos      "<<endl;
    cout<<" 5. Consultar datos      "<<endl;
    cout<<" 6. Salir                "<<endl;
    cout<<" \n Ingrese una opcion:  ";
}

void menu_secundario() {
    cout<<"\n\t Sub Menu de opciones de consulta\n\n";
    cout<<" 1. Consultar por Telefono             "<<endl;
    cout<<" 2. Consultar por Nombre               "<<endl;
    cout<<" 3. Consultar por Empresa              "<<endl;
    cout<<" 4. Consultar por Edad                  "<<endl;
    cout<<" 5. Consultar por Cumpleannos           "<<endl;
    cout<<" 6. Volver               "<<endl;
    cout<<" \n Ingrese una opcion:  ";
}


// ----------------------------------------- Funciones -------------------------------------------------------------------

// ------------ Calcular Edad (Int)------------<<<<<<<<<

int calcular_edad(int dia_nacimiento, int mes_nacimiento, int year_nacimiento) {
	int dia_actual, mes_actual, year_actual, edad;
	time_t hoy;
	time( & hoy);
	struct tm * local = localtime( & hoy);
	dia_actual = local -> tm_mday; // get day of month (1 to 31)
	mes_actual = local -> tm_mon + 1; // get month of year (0 to 11)
	year_actual = local -> tm_year + 1900; // get year since 1900
	edad = year_actual - year_nacimiento;
	if (mes_nacimiento > mes_actual || (mes_nacimiento == mes_actual && dia_nacimiento > dia_actual)) {
		edad = edad - 1;
	}
	return edad;
}


// ------------ Cumpleaños (Boleana) ------------<<<<<<<<<<

bool cumple(int dia_nacimiento, int mes_nacimiento) {
	int dia_actual, mes_actual;
	time_t hoy;
	time( & hoy);
	struct tm * local = localtime( & hoy);
	dia_actual = local -> tm_mday;
	mes_actual = local -> tm_mon + 1;
	return dia_nacimiento == dia_actual && mes_nacimiento == mes_actual;
}


// ------------ Insertar ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void insertar(Tlista & inicio, int xtelefono, string xnombre, string xempresa, string xdireccion, int dd, int mm, int aa) {
	Tlista ptr, aux, pos;
	ptr = new(struct nodo);
	ptr -> anterior = NULL;
	ptr -> siguiente = NULL;
	ptr -> telefono = xtelefono;
	ptr -> nombre = xnombre;
	ptr -> empresa = xempresa;
	ptr -> direccion = xdireccion;
	ptr -> dia = dd;
	ptr -> mes = mm;
	ptr -> year = aa;
	ptr -> edad = calcular_edad(dd, mm, aa);
	
	if (cumple(dd, mm)) {
		ptr -> cumple = "Feliz cumple!";
	} else {
		ptr -> cumple = "Hoy no es tu cumple :(";
	}
	if (inicio == NULL) {
		inicio = ptr;
	} else {
		aux = inicio;
		while (aux -> siguiente != NULL) {
			aux = aux -> siguiente;
		}
		if (aux -> siguiente == NULL) {
			aux -> siguiente = ptr;
			ptr -> anterior = aux;
		}
	}
}

// ------------ Imprimir Todo ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<

void imprimir_todo(Tlista & inicio) {

	int i=0;
	Tlista ptr;
	ptr = inicio; 
	while (ptr->siguiente!= NULL){
		cout<<' '<<i+1 <<")\t Telefono: "<< ptr->telefono 
						<< "\n\t Nombre: " << ptr->nombre 
						<< "\n\t Empresa: " << ptr->empresa 
						<< "\n\t Direccion: " << ptr->direccion 
						<< "\n\t Dia nacimiento: " << ptr->dia 
						<< "\n\t Mes nacimiento: " << ptr->mes 
						<< "\n\t Anno nacimiento: " << ptr->year 
						<< "\n\t " << ptr->cumple <<endl;
						cout << "\n\n" <<endl;
		ptr= ptr->siguiente;	
		i++;
	}
	cout<<' '<<i+1 <<")\t Telefono: "<< ptr->telefono 
						<< "\n\t Nombre: " << ptr->nombre 
						<< "\n\t Empresa: " << ptr->empresa 
						<< "\n\t Direccion: " << ptr->direccion 
						<< "\n\t Dia nacimiento: " << ptr->dia 
						<< "\n\t Mes nacimiento: " << ptr->mes 
						<< "\n\t Anno nacimiento: " << ptr->year 
						<< "\n\t " << ptr->cumple <<endl;
						cout << "\n\n" <<endl;
}


// ------------ Buscar Telefono (Boleana)------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool buscar_telefono(Tlista & inicio, int xtelefono) {
	bool bandera = false;
	Tlista aux;
	aux = inicio;
	while (aux != NULL) {
		if (aux -> telefono == xtelefono) {
			bandera = true;
			break;
		} else {
			aux = aux -> siguiente;
		}
	}
	return bandera == true;
}

// ------------ Eliminar Por Telefono ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void eliminar_por_telefono(Tlista & inicio, int xtelefono) {
	Tlista aux;
	aux = inicio;
	if (inicio -> telefono == xtelefono) {
		// Caso de que el telefono se encuentre en inicio
		if (inicio -> siguiente != NULL) {
			// Caso en que el telefono se encuentre en inicio y tenga algo a su derecha
			inicio = inicio -> siguiente;
			inicio -> anterior = NULL;
			delete(aux);
		} else {
			// Caso de que el telefono se encuentre en inicio y este solo
			delete(aux);
			inicio = NULL;
		}
	} else {
		// Caso de que el telefono no se encuentre en inicio
		while (aux != NULL) {
			if (aux -> telefono == xtelefono) {
				if (aux -> telefono == xtelefono && aux -> siguiente == NULL) {
					// Caso de que el telefono se encuentre al final
					aux -> anterior -> siguiente = NULL;
					delete(aux);
				} else {
					// Caso de que el telefono se encuentre en medio
					aux -> anterior -> siguiente = aux -> siguiente;
					aux -> siguiente -> anterior = aux -> anterior;
					delete(aux);
				}
			} else {
				aux = aux -> siguiente;
			}
		}
	}
}

// ------------ Consultar Por Telefono------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void consultar_telefono(Tlista & inicio, int xtelefono) {

	bool bandera = false;
	int i= 1; 
	Tlista aux;
	aux = inicio;
	cout << "\n Resultado por telefono:" << endl;
	while (aux != NULL) {
		if (aux -> telefono == xtelefono) {
			cout<<' '<<i <<")\t Telefono: "<< aux->telefono 
						<< "\n\t Nombre: " << aux->nombre 
						<< "\n\t Empresa: " << aux->empresa 
						<< "\n\t Direccion: " << aux->direccion 
						<< "\n\t Dia nacimiento: " << aux->dia 
						<< "\n\t Mes nacimiento: " << aux->mes 
						<< "\n\t Anno nacimiento: " << aux->year 
						<< "\n\t " << aux->cumple <<endl;
						cout << "\n\n" <<endl;
			bandera = true;
			break;
		} else {
			aux = aux -> siguiente;
		}
	}
	if(!bandera) {
		cout << "\n Ups! Este numero no se encuentra en nuestros registros." << endl;
	}
}

// ------------ Consultar Por Nombre ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void consultar_nombre(Tlista & inicio, string xnombre) {

	bool bandera = false;
	int i = 1;
	Tlista aux;
	aux = inicio;
	cout << "\n Resultados por nombre:" << endl;
	while (aux != NULL) {
		if (aux -> nombre == xnombre) {
			cout<<' '<<i <<")\t Telefono: "<< aux->telefono 
						<< "\n\t Nombre: " << aux->nombre 
						<< "\n\t Empresa: " << aux->empresa 
						<< "\n\t Direccion: " << aux->direccion 
						<< "\n\t Dia nacimiento: " << aux->dia 
						<< "\n\t Mes nacimiento: " << aux->mes 
						<< "\n\t Anno nacimiento: " << aux->year 
						<< "\n\t " << aux->cumple <<endl;
						cout << "\n\n" <<endl;
			bandera = true;
			i++;
			aux = aux -> siguiente;
		} else {
			aux = aux -> siguiente;
		}
	}
	if(!bandera) {
		cout << "\n Ups! Este nombre no se encuentra en nuestros registros." << endl;
	}
}

// ------------ Consultar Por Empresa ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


void consultar_empresa(Tlista & inicio, string xempresa) {

	bool bandera = false;
	int i = 1;
	Tlista aux;
	aux = inicio;
	cout << "\n Resultados por empresa:" << endl;
	while (aux != NULL) {
		if (aux -> empresa == xempresa) {
			cout<<' '<<i <<")\t Telefono: "<< aux->telefono 
						<< "\n\t Nombre: " << aux->nombre 
						<< "\n\t Empresa: " << aux->empresa 
						<< "\n\t Direccion: " << aux->direccion 
						<< "\n\t Dia nacimiento: " << aux->dia 
						<< "\n\t Mes nacimiento: " << aux->mes 
						<< "\n\t Anno nacimiento: " << aux->year 
						<< "\n\t " << aux->cumple <<endl;
						cout << "\n\n" <<endl;
			bandera = true;
			i++;
			aux = aux -> siguiente;
		} else {
			aux = aux -> siguiente;
		}
	}
	if(!bandera) {
		cout << "Ups! Esta empresa no se encuentra en nuestros registros." << endl;
	}
}


// ------------ Consultar Por Edad ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void consultar_edad(Tlista & inicio, int xedad) {
	bool bandera = false;
	int i = 1;
	Tlista aux;
	aux = inicio;
	cout << "\n Resultados por edad:" << endl;
	while (aux != NULL) {
		if (aux -> edad == xedad) {
			cout<<' '<<i <<")\t Telefono: "<< aux->telefono 
						<< "\n\t Nombre: " << aux->nombre 
						<< "\n\t Empresa: " << aux->empresa 
						<< "\n\t Direccion: " << aux->direccion 
						<< "\n\t Dia nacimiento: " << aux->dia 
						<< "\n\t Mes nacimiento: " << aux->mes 
						<< "\n\t Anno nacimiento: " << aux->year 
						<< "\n\t " << aux->cumple <<endl;
						cout << "\n\n" <<endl;
			bandera = true;
			i++;
			aux = aux -> siguiente;
		} else {
			aux = aux -> siguiente;
		}
	}
	if(!bandera) {
		cout << "\n Ups! Esta edad no se encuentra en nuestros registros." << endl;
	}
}

// ------------ Consultar Por CumpleaÃ±os ------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void consultar_cumple(Tlista & inicio) {
	bool bandera = false;
	int i = 1;
	Tlista aux;
	aux = inicio;
	cout << "\n Cumples de hoy:" << endl;
	while (aux != NULL) {
		if (aux -> cumple == "Feliz cumple!") {
			cout<<' '<<i <<")\t Telefono: "<< aux->telefono 
						<< "\n\t Nombre: " << aux->nombre 
						<< "\n\t Empresa: " << aux->empresa 
						<< "\n\t Direccion: " << aux->direccion 
						<< "\n\t Dia nacimiento: " << aux->dia 
						<< "\n\t Mes nacimiento: " << aux->mes 
						<< "\n\t Anno nacimiento: " << aux->year 
						<< "\n\t " << aux->cumple <<endl;
						cout << "\n\n" <<endl;
			bandera = true;
			i++;
			aux = aux -> siguiente;
		} else {
			aux = aux -> siguiente;
		}
	}
	if(!bandera) {
		cout << "\n Parece que nadie cumple el dia de hoy."<< endl;
	}
}

// ----------------------------------------- Metodo Main -------------------------------------------------------------------------------------------------------------------

int main() {
	Tlista inicio = NULL;
	int opcion_principal, opcion_secundaria, telefono, dia, mes, year, edad;
	string nombre, empresa, direccion;
	insertar(inicio, 87914502, "Gemma", "Intel", "Guapiles", 5, 6, 1998);
	insertar(inicio, 81741748, "Claudia", "Microsoft", "Alajuela", 20, 12, 1994);
	insertar(inicio, 69299370, "Antonio", "Dell", "Heredia", 16, 1, 2000);
	insertar(inicio, 71306016, "Carlos", "HP", "Liberia", 27, 4, 1989);
	insertar(inicio, 85031187, "Cipriano", "MSI", "Naranjo", 20, 12, 1991);
	insertar(inicio, 73127953, "Angustias", "Apple", "Puriscal", 11, 8, 1990);
	insertar(inicio, 65410894, "Mohamed", "Intel", "Acosta", 26, 12, 1997);
	insertar(inicio, 72989043, "Carlos", "MSI", "Escazu", 16, 12, 1998);
	insertar(inicio, 74548523, "Mohamed", "Apple", "Puriscal", 20, 12, 1995);
	insertar(inicio, 78802506, "Carlos", "Microsoft", "Puriscal", 25, 10, 1999);
	
	system("color 0b");
	
	do {
		menu_principal();
		cin >> opcion_principal;
		cout<< "--------------------------------------------------------------------"<<endl;
		
		switch (opcion_principal) {
			case 1:
				cout<< "\n Digite su numero telefonico: "; cin>> telefono;
				
				if (buscar_telefono(inicio, telefono)) {
					cout << "\n Este numero de telefono ya existe en nuestros registros. "<<endl;
					
				} else {
	            	cout<< " Digite su nombre: "; cin>> nombre;
	            	cout<< " Digite el nombre de su empresa: "; cin>> empresa;
	            	cout<< " Digite su direccion: "; cin>> direccion;
	            	cout<< " Digite su dia de nacimiento: "; cin>> dia;
	            	cout<< " Digite su mes de nacimiento: "; cin>> mes;
	            	cout<< " Digite su anno de nacimiento: "; cin>> year;

					insertar(inicio, telefono, nombre, empresa, direccion, dia, mes, year);
					cout << "\n Datos agregados con exito! "<< endl;
				}
			break;
			
			case 2:
				if (inicio == NULL) {
					cout << "\n No hay datos en nuestros registros." << endl;
				} else {
					imprimir_todo(inicio);
				}
			break;
			
			case 3:
				if (inicio == NULL) {
					cout << "\n No hay datos en nuestros registros." << endl;
					
				} else {
					cout << "\n Digite el numero telefonico para eliminar todos los datos asociados a este: "; cin >> telefono;
					
					if (buscar_telefono(inicio, telefono)) {
						eliminar_por_telefono(inicio, telefono);
						cout<< "\n Datos eliminados exitosamente. "<< endl;
						
					} else {
						cout<< "\n El numero de telefono no existe en nuestros registros "<< endl;
					}
				}
				
			break;
			
			case 4:
				if (inicio == NULL) {
					cout << "\n No hay datos en nuestros registros."  << endl;
				} else {
					cout << "\n Digite  numero telefonico del usuario a modificar: "; cin >> telefono;
					
					if (buscar_telefono(inicio, telefono)) {
						eliminar_por_telefono(inicio, telefono);
						cout << "\n Nuevo Telefono: "; cin >> telefono;
						cout << " Nuevo Nombre: "; cin >> nombre;
						cout << " Nueva Empresa: "; cin >> empresa;
						cout << " Nueva Direccion: "; cin >> direccion;
						cout << " Nuevo Dia de nacimiento: "; cin >> dia;
						cout << " Nuevo Mes de nacimiento: "; cin >> mes;
						cout << " Nuevo Anno de nacimiento: ";	cin >> year;
						insertar(inicio, telefono, nombre, empresa, direccion, dia, mes, year);
						cout << "\n Registro modificado! "<< endl;
						
					} else {
						cout << "\n El numero de telefono no existe en nuestros registros. "<< endl;
					}
				}
			break;
			
			case 5:
				do {
					system("cls");
					
					menu_secundario(); cin >> opcion_secundaria;
					cout<< "--------------------------------------------------------------------"<<endl;
					
					switch (opcion_secundaria) {
						
						case 1:
							cout << "\n Digite numero de telefono del usuario:		"; cin >> telefono;
							consultar_telefono(inicio, telefono);
							
						break;
						
						case 2:
							cout << "\n Digite el nombre del usuario(s):		";cin >> nombre;
							consultar_nombre(inicio, nombre);
							
						break;
						case 3:
							cout << "\n Digite la empresa del usuario(s):		"; cin >> empresa;
							consultar_empresa(inicio, empresa);
						break;
						
						case 4:
							cout << "\n Digite la edad del usuario(s):		"; cin >> edad;
							consultar_edad(inicio, edad);
						break;
						
						case 5:
							consultar_cumple(inicio);
						break;
						
						case 6:
							system("cls");
							main();
						break;
					}
					system("pause");
					system("cls");
				} while (opcion_secundaria != 6);
		}
		system("pause");
		system("cls");
	} while (opcion_principal != 6);
	system("pause");
	return 0;
}
