#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include<String.h>
using namespace std;
/* Programa: Serie de numeros con Punteros

Objetivo: Utilizando punteros el programa debe de solicitar al usuario una serie de numeros e inidicar:
-El n�mero mayor
-El n�mero menor
-El promedio de los dos n�meros anteriores

Datos de entrada: 
-N�mero de elementos a usar
-Los elementos ingresados por el usuario

Datos de salida:
-N�mero de datos
-Los n�meros introducidos
-N�mero mayor
-N�mero menor
-Promedio del n�mero mayor y menor

Autor: Gerardo Gomez Cajero */

int main()
{
	setlocale(LC_ALL, "spanish");
	int nNumeros, nMay, nMen;
	double promedio;
	do{
		system("CLS");
		printf("Cuantos n�meros vas a ingresar?: ");
		cin>>nNumeros;
		if(nNumeros<2) printf("Ingresa m�s de 1 elemento");
	}while(nNumeros<1);
	
	int serieNumeros[nNumeros];
	int *ptrserie=(int*)malloc(nNumeros*sizeof(int));
	ptrserie=serieNumeros;
	pedirNumeros(ptrserie, nNumeros);
	nMay=calcularMayor(ptrserie, nNumeros);
	nMen=calcularMenor(ptrserie, nNumeros, nMay);
	promedio=nMen+nMay;
	promedio/=2;
	system("CLS");
	printf("N�mero de datos: %d",nNumeros);
	imprimirNumeros(ptrserie, nNumeros);
	printf("\nEl n�mero mayor es: %d",nMay);
	printf("\nEl n�mero menor es %d",nMen);
	cout<<"\nEl promedio de los anteriores es: "<<promedio;
}
