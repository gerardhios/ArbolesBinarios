#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include<String.h>
using namespace std;
/* Programa: Arbol Binario

Objetivo: 
Realice un programa en C++ en el que:
1. Inserte nodos a un árbol.
2. Muestre el árbol por el Método de Búsqueda Binaria.
3. Busque e indique si existe o no el número que solicite.
4. Obtenga la altura de un nodo
5. Obtenga la altura de todo el árbol
6. Indique cuántos nodos tiene el árbol
7. Realice los recorridos por:
	a) Preorden
	b) Inorden
	c) Postorden
8. Borre un nodo.
9. Borre todo el árbol.
10. Salga del programa.

Datos de entrada: 
-Datos dentro de cada nodo del arbol
-Opcion que eliga el usuario dentro del menú

Datos de salida:
Impresion del arbol con los datos introducidos

Autor(es): Gerardo Gomez Cajero 
	   Jose Pablo Padilla Galindo
*/
//Estructura de cada nodo del arbol

struct Nodo{
	int dato;
	Nodo *der;
	Nodo *izq;
	Nodo *padre;
};
Nodo *arbol = NULL;
int contalt=0;
//Funcion para crear nuevos nodos
Nodo * crearNodo(int n, Nodo *padre){
	Nodo *newnodo = new Nodo();
	newnodo->dato=n;
	newnodo->der=NULL;
	newnodo->izq=NULL;
	newnodo->padre = padre;

	return newnodo;
}

void eliminar (Nodo *, int);
void eliminarNodo(Nodo *);
void destruirNodo(Nodo *);
void reemplazar(Nodo *, Nodo *);
Nodo *minimo(Nodo *);

//Funcion para insertar nodos en el arbol
void insertarNodo(Nodo *&arbol, int n, Nodo *padre){
	if(arbol == NULL){//Si el arbol esta vacio, creamos un nuevo nodo que sera la raiz del arbol
		Nodo *newnodo = crearNodo(n, padre);
		arbol=newnodo;
	}
	else{//Si el arbol ya tiene uno o más nodos
		int valorRaiz = arbol->dato;//Obtenemos el dato de la raiz(nodo padre del nodo actual)
		if(n < valorRaiz){//Si el dato del nodo que queremos insertar es menor al dato del nodo padre. Insertamos el nodo en el lado izquierdo
			insertarNodo(arbol->izq,n, arbol);
		}
		else{//Si el dato del nodo que queremos insertar es mayor al dato del nodo padre. Insertamos el nodo en el lado derecho
			insertarNodo(arbol->der,n, arbol);
		}
	}
}

//Funcion para buscar un nodo e indiciar si existe o no el nodo
bool buscarNodo(Nodo *arbol, int n){
	if(arbol == NULL){//Si el arbol esta vacio regresamos false
		return false;
	}
	else if(arbol->dato == n){//Encontramos el dato en el nodo actual
		return true;
	}
	else if(n<arbol->dato){//Si el nodo que estamos buscando es menor que el nodo actual le pasamos a la funcion el nodo del lado izquierdo
		return buscarNodo(arbol->izq,n);
	}
	else{//si el nodo que estamos buscando es mayor que el nodo actual le pasamos a la funcion el nodo del lado derecho
		return buscarNodo(arbol->der,n);
	}
}

//Funcion para mostrar la altura de un nodo especifico
void alturaNodo(Nodo *arbol, int n){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{
		contalt++;
		if(n == arbol->dato){
			cout<<"\n Dato "<<n<<" encontrado en la altura "<<contalt;
			return;
		}
		else if(n < arbol->dato){
			alturaNodo(arbol->izq,n);
		}
		else{
			alturaNodo(arbol->der,n);
		}
	}
}

//Función para mostrar el arbol completo
void mostrarArbol(Nodo *arbol, int cnt){
	if (arbol == NULL){//Si el árbol esta vacio
 		return;
 	}
 	else {
 		mostrarArbol(arbol->der,cnt+1);
 		for(int i=0; i<cnt;i++)
 		{
 			cout<<" "; //da espacios entre nodos con 3 dígitos
 		}
 	cout<<arbol->dato<<endl;
 	mostrarArbol(arbol->izq, cnt+1);
 	}
}

void eliminar (Nodo *arbol, int n){
	if(arbol == NULL){
		return; //Arbol vacío, no se hace nada
	}
	else if(n < arbol->dato){//Si el valor es menor, irse a la izquierda
		eliminar(arbol->izq, n);
	}
	else if(n > arbol->dato){ //Si el valor es mayor, se busca a la derecha.
		eliminar(arbol->der, n);
	}
	else{ //Aquí se va cuando se encontró el elemento
		eliminarNodo(arbol);
	}
}

//Función para eliminar el nodo 
void eliminarNodo(Nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){ //Si el nodo tiene hijo izquierdo e hijo derecho...
		Nodo *menor = minimo(nodoEliminar->der);
		nodoEliminar->dato = menor->dato;		//Se reemplaza el arbol eliminado con el dato menor
		eliminarNodo(menor);					//Se elimina el menor anterior, y se repite el procedimiento si es que es necesario.
	}
	else if(nodoEliminar->izq){
		reemplazar(nodoEliminar, nodoEliminar->izq);
		destruirNodo(nodoEliminar);
	}
	else if (nodoEliminar->der){
		reemplazar(nodoEliminar, nodoEliminar->der);
		destruirNodo(nodoEliminar);
	}
	else{	//Nodo hoja. NO tiene hijos. 
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}
}

void destruirNodo(Nodo *nodo){
	nodo->izq = NULL;
	nodo->der = NULL;
	delete nodo;
}

//Reemplaza dos nodos
void reemplazar(Nodo *arbol, Nodo *nuevoNodo){
	if(arbol->padre){
		//al padre se le asigna su nuevo hijo
		if(arbol->dato == arbol->izq->dato){
			arbol->padre->izq = nuevoNodo;  //Si el dato es igual al hijo de la izquierda del padre, aquí se elimina.
		}
		if(arbol->dato == arbol->der->dato){
			arbol->padre->der = nuevoNodo;	//Si el dato es igual al hijo de la derecha del padre, aquí se elimina.
		}
	}
	if(nuevoNodo){
		//Y al hijo se le asigna su nuevo padre
		nuevoNodo->padre = arbol->padre; //
	}
}

//Función para determinar el nodo más izquierda
Nodo *minimo(Nodo *arbol){
	if(arbol == NULL){ 
		return NULL;					//Arbol vacio=regresa nulo
	}
	if (arbol->izq){		
		return minimo(arbol->izq);		//Hijo izquierdo=sigue buscando a la izquierda y se llama a si misma la funcion 
	}
	else{
		return arbol;					//Sin hijo izquierdo, por lo tanto, fin de la función. Se ha encontrado el mínomo.
	}
}



// Funcion del Menu
void menu()
{
	int dato, opcion, contador=0;
	do
	{
		cout << "\t <<<< M E N U >>>>"<<endl;
		cout << "1. Insertar nodo"<<endl;
		cout << "2. Mostrar arbol"<<endl;
		cout << "3. Buscar nodo"<<endl;
		cout << "4. Altura de un nodo"<<endl;
		cout << "5. Obtenga la altura de todo el árbol" << endl;
		cout << "6. Indica cuántos nodos tiene el arbol" << endl;
		cout << "7. Realiza los recorridos por preorden, inorden o post orden (entrar a otro menú)" << endl;
		cout << "8. Borra un nodo" << endl;
		cout << "9. Borra todo el arbol" << endl;
		cout << "10. Salir"<<endl;
		cin>>opcion;
		switch(opcion)
		{
			case 1: //Inserta un nodo
				cout<<"\n Digite un número: ";
 				cin>>dato;
 				insertarNodo(arbol, dato, NULL); //Insertar un nuevo nodo
 				cout<<"\n";
 				system("PAUSE");
 				break;
			case 2: //Muestra el arbol
				cout<<"\nMostrar Arbol"<<endl<<endl;
				mostrarArbol(arbol,contador);
				cout<<endl;
				system("PAUSE");
				break;
			case 3:	//Busca un nodo
				cout<<"\n Digite el número a buscar: ";
				cin>>dato;
				//Buscamos el dato introducido
				if(buscarNodo(arbol,dato)){//Si se encuentra el dato la funcion buscarNodo regresa true
					cout<<"\nSe encontro el dato: "<<dato;
				}
				else{//Si no se encuentra la funcion regresa un false
					cout<<"\nNo se encontro el dato: "<<dato;					
				}
				cout<<endl;
				system("PAUSE");
				break;
			case 4:	//Se busca la altura de un nodo
				cout<<"\n Digite el número a buscar: ";
				cin>>dato;
				//Buscamos la altura del dato introducido
				contalt=0;
				alturaNodo(arbol,dato);
				cout<<endl;
				system("PAUSE");
				break;
			case 5: //Se obtiene la altura del arbol
			
				break;
			case 6: //Indica cuantos nodos tiene el arbol

				break;
			case 7: //Hace recorridos en preorden, inorden y postorden

				break;
			case 8: //Borra un nodo.
				cout<<"\n Digite el dato que desea buscar: ";
 				cin>>dato;
 				eliminar(arbol, dato); //Se llama a la función para eliminar el nodo.
 				cout<<"\n";
 				system("PAUSE");
				break;
			case 9: //Borra todo el arbol

				break;
			case 10: //Sale del programa
				cout << "Saliendo del programa..." << endl;
				break;
		}
		system("cls");
	}while(opcion != 10);
}

int main()
{
	setlocale(LC_ALL, "spanish");
	menu();
}
