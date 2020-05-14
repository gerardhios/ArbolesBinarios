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
};
Nodo *arbol = NULL;

//Funcion para crear nuevos nodos
Nodo * crearNodo(int n){
	Nodo *newnodo = new Nodo();
	newnodo->dato=n;
	newnodo->der=NULL;
	newnodo->izq=NULL;
	return newnodo;
}

//Funcion para insertar nodos en el arbol
void insertarNodo(Nodo *&arbol, int n){
	if(arbol == NULL){//Si el arbol esta vacio, creamos un nuevo nodo que sera la raiz del arbol
		Nodo *newnodo = crearNodo(n);
		arbol=newnodo;
	}
	else{//Si el arbol ya tiene uno o más nodos
		int valorRaiz = arbol->dato;//Obtenemos el dato de la raiz(nodo padre del nodo actual)
		if(n<valorRaiz){//Si el dato del nodo que queremos insertar es menor al dato del nodo padre. Insertamos el nodo en el lado izquierdo
			insertarNodo(arbol->izq,n);
		}
		else{//Si el dato del nodo que queremos insertar es mayor al dato del nodo padre. Insertamos el nodo en el lado derecho
			insertarNodo(arbol->der,n);
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


// Funcion del Menu
void menu()
{
	int dato, opcion, contador=0;
	do
	{
		cout<<"\t <<<< M E N U >>>>"<<endl;
		cout<<"1. Insertar nodo"<<endl;
		cout<<"2. Mostrar arbol"<<endl;
		cout<<"3. Buscar nodo"<<endl;
		cout<<"4. Salir"<<endl;
		cin>>opcion;
		switch(opcion)
		{
			case 1: 
				cout<<"\n Digite un número: ";
 				cin>>dato;
 				insertarNodo(arbol, dato); //Insertar un nuevo nodo
 				cout<<"\n";
 				system("PAUSE");
 				break;
			case 2: 
				cout<<"\nMostrar Arbol"<<endl<<endl;
				mostrarArbol(arbol,contador);
				cout<<endl;
				system("PAUSE");
				break;
			case 3:
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
				
		}
		system("cls");
	}while(opcion != 4);
}

int main()
{
	setlocale(LC_ALL, "spanish");
	menu();
}
