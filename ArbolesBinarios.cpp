#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include<String.h>
#include<windows.h>
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
int contalt=0, contnodos=0, nodoencontrado=0;
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
Nodo *minimo(Nodo *);
void destruirNodo(Nodo *);
void reemplazar(Nodo *, Nodo *);

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
void alturaNodo(Nodo *arbol, int n, int op){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{
		contalt++;//Siempre iniciar esta variable antes de utilizar esta funcion
		if(n == arbol->dato){
			if(op==0)
				cout<<"\n Dato "<<n<<" encontrado en la altura "<<contalt;
			return;
		}
		else if(n < arbol->dato){
			alturaNodo(arbol->izq,n,op);
		}
		else{
			alturaNodo(arbol->der,n,op);
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
	else if(nodoEliminar->izq){					//Si tiene hijo izquierdo...
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
		if (arbol->padre->izq){
		//al padre se le asigna su nuevo hijo
			if(arbol->dato == arbol->padre->izq->dato){
				arbol->padre->izq = nuevoNodo;  //Si el dato es igual al hijo de la izquierda del padre, aquí se elimina.

			}
		}
		else if(arbol->dato == arbol->padre->der->dato){
			arbol->padre->der = nuevoNodo;	//Si el dato es igual al hijo de la derecha del padre, aquí se elimina.
		}
	}
	if(nuevoNodo){
		//Y al hijo se le asigna su nuevo padre
		nuevoNodo->padre = arbol->padre; 
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


void inOrden(Nodo *arbol){ //Recorrido inorden 
	
	if (arbol == NULL){//Si el árbol esta vacio
 		return;
 	}
 	else {
 		inOrden(arbol->izq);
		cout << arbol->dato << " - ";
		inOrden(arbol->der);
 	}
}

void preOrden (Nodo *arbol){
	if (arbol == NULL){
		return;
	}
	else {
		cout << arbol->dato << " - ";
		preOrden(arbol->izq);
		preOrden(arbol->der);

	}
}

void postOrden (Nodo *arbol){
	if (arbol == NULL){
		return;
	}
	else {
 		postOrden(arbol->izq);
		postOrden(arbol->der);
		cout << arbol->dato << " - ";
	}
}

//Funcion para mostrar el número de nodos que tiene el arbol
void nodosArbol(Nodo *arbol){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{
		contnodos++;
		nodosArbol(arbol->der);
		nodosArbol(arbol->izq);
	}
}

//Funcion para retornar el valor dentro de cada nodo del arbol recorriendolo por preorden
void regresoNodos(Nodo *arbol, int indice){
	if(arbol == NULL){//Revisamos si el nodo actual esta vacio
		return;
	}
	else{
		contalt++;
		if(indice == contalt){//Regresamos el dato dentro del nodo que este en el indice que se pasa por parametro
			nodoencontrado = arbol->dato;
		}
		else{
			regresoNodos(arbol->izq,indice);
			regresoNodos(arbol->der,indice);
		}				
	}
}

//Funcion para mostrar la altura de todo el arbol
void alturaArbol(){
	int i;
	contnodos=0; 
	nodosArbol(arbol);
	int posynodos[contnodos][2];//Generamos una matriz de nfilas y 2 columnas, donde nfilas es el numero de nodos que hay en el arbol
	//En la columna 0 se guardara el dato que este en el nodo actual
	//En la columna 1 se guardara la altura del nodo actual
	for(i=0; i<contnodos; i++){//Ciclo for que nos permite almacenar los datos y su respectiva altura de todos los nodos del arbol en la matriz posynodos
		nodoencontrado = 0; //En cada vuelta se debe reiniciar esta variable;		
		contalt = 0;//En cada vuelta se debe reiniciar esta variable
		regresoNodos(arbol,i+1);
		posynodos[i][0]=nodoencontrado;
		contalt = 0;//Reiniciamos nuevamente la variable para buscar la altura del dato encontrado anteriormente
		alturaNodo(arbol,nodoencontrado,1);
		posynodos[i][1]=contalt;
	}
	//Ordenamos la matriz mediante el metodo de la burbuja de forma descendente para encontrar el nodo con mayor altura
	//La cual sera la altura de todo el arbol
	int temporal,temporal2;//Variables temporales para guardar dos datos
	for (int i = 0 ; i < contnodos; i++){
		for (int j = 0; j < contnodos-1; j++){
			if (posynodos[j][1] < posynodos[j+1][1]){ //Si el número que sigue del número que estamos en el arreglo es mayor
			temporal = posynodos[j][0];
			temporal2 = posynodos[j][1]; 
			posynodos[j][0] = posynodos[j+1][0]; //Cambiamos el número que seguia a la posicion del número en el que estabamos
			posynodos[j][1] = posynodos[j+1][1]; //Cambiamos el número que seguia a la posicion del número en el que estabamos
			posynodos[j+1][0] = temporal;//Ponemos el numero en el que estabamos a la posicion siguiente
			posynodos[j+1][1] = temporal2;//Ponemos el numero en el que estabamos a la posicion siguiente
			}
		}
	}
	cout<<posynodos[0][1]<<endl;
}

//Función para borrar todo el arbol
void borrarArbol(){
	arbol = NULL;
	cout<<endl<<"El arbol a sido borrado";
}

//Funcion para mostrar el arbol en preorden(Raiz,Izquierda,Derecha)
void arbolPreorden(Nodo *arbol){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{
		cout<<" [ "<<arbol->dato<<" ] ";
		Sleep(500);
		arbolPreorden(arbol->izq);
		arbolPreorden(arbol->der);
	}
}

//Funcion para mostrar el arbol en inorden(Izquierda,Raíz,Derecha)
void arbolInorden(Nodo *arbol){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{		
		arbolInorden(arbol->izq);
		cout<<" [ "<<arbol->dato<<" ] ";
		Sleep(500);
		arbolInorden(arbol->der);
	}
}

//Funcion para mostrar el arbol en postorden(Izquierda,Derecha,Raíz)
void arbolPostorden(Nodo *arbol){
	if(arbol == NULL){//Revisamos si el arbol esta vacio
		return;
	}
	else{		
		arbolPostorden(arbol->izq);		
		arbolPostorden(arbol->der);
		cout<<" [ "<<arbol->dato<<" ] ";
		Sleep(500);
	}
}

//Funcion del menu para los recorridos
void menuRecorridos()
{
	int dato, opcion;
	do
	{
		cout << "\t <<<< M E N U >>>>"<<endl;
		cout<<"1. Recorrer el arbol en Preorden(Raíz,Izquierda,Derecha)"<<endl;
		cout<<"2. Recorrer el arbol en Inorden(Izquierda,Raíz,Derecha)"<<endl;
		cout<<"3. Recorrer el arbol en Postorden(Izquierda,Derecha,Raíz)"<<endl;
		cin>>opcion;
		switch(opcion)
		{
			case 1: 
				cout<<"\nRecorrido del arbol en preorden: "<<endl<<endl;
				arbolPreorden(arbol);
				cout<<endl;
				system("PAUSE");
				return;
				break;
			case 2: 
				cout<<"\nRecorrido del arbol en inorden: "<<endl<<endl;
				arbolInorden(arbol);
				cout<<endl;
				system("PAUSE");
				return;
				break;
			case 3: 
				cout<<"\nRecorrido del arbol en postorden: "<<endl<<endl;
				arbolPostorden(arbol);
				cout<<endl<<endl;
				system("PAUSE");
				return;
				break;		
		}
		system("cls");
	}while(opcion != 4);
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
				alturaNodo(arbol,dato,0);
				cout<<endl;
				system("PAUSE");
				break;
			case 5: //Se obtiene la altura del arbol
				cout<<"\nLa altura del arbol es: ";
				alturaArbol();
				cout<<endl<<endl;
				system("PAUSE");
				break;
			case 6: //Indica cuantos nodos tiene el arbol
				cout<<"\nNúmero de nodos en el arbol: ";
				contnodos=0;
				nodosArbol(arbol);
				cout<<contnodos<<endl<<endl;
				system("PAUSE");
				break;
			case 7: //Hace recorridos en preorden, inorden y postorden
				cout<<endl;
				menuRecorridos();
				break;
			case 8: //Borra un nodo.
				contnodos = 0;
				nodosArbol(arbol);
				cout<<"\n Digite el dato que desea buscar: ";
 				cin>>dato;
				if(contnodos > 1){//Si hay más de un dato en el arbol
					if(buscarNodo(arbol,dato)){//Si el nodo existe dentro del arbol
						eliminar(arbol, dato); //Se llama a la función para eliminar el nodo.
 						cout<<"Nodo "<<dato<<" eliminado";
					}
					else{
						cout<<"El nodo "<<dato<<" no esta dentro del arbol";
					}
				}
				else{//Si solo hay un nodo en el arbol
					if(buscarNodo(arbol,dato)){//Si el nodo existe dentro del arbol
						arbol = NULL; //Eliminamos el arbol completo
					}
					else{
						cout<<"El nodo "<<dato<<" no esta dentro del arbol";
					}
				}				
 				cout<<"\n";
 				system("PAUSE");
				break;
			case 9: //Borra todo el arbol
				cout<<"\n Borrando arbol";
				borrarArbol();
				cout<<endl<<endl;
 				system("PAUSE");
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
