#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include<String.h>
using namespace std;
/* Programa: Serie de numeros con Punteros

Objetivo: Utilizando punteros el programa debe de solicitar al usuario una serie de numeros e inidicar:
-El número mayor
-El número menor
-El promedio de los dos números anteriores

Datos de entrada: 
-Número de elementos a usar
-Los elementos ingresados por el usuario

Datos de salida:
-Número de datos
-Los números introducidos
-Número mayor
-Número menor
-Promedio del número mayor y menor

Autor: Gerardo Gomez Cajero */

int main()
{
	setlocale(LC_ALL, "spanish");
	int nNumeros, nMay, nMen;
	double promedio;
	do{
		system("CLS");
		printf("Cuantos números vas a ingresar?: ");
		cin>>nNumeros;
		if(nNumeros<2) printf("Ingresa más de 1 elemento");
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
	printf("Número de datos: %d",nNumeros);
	imprimirNumeros(ptrserie, nNumeros);
	printf("\nEl número mayor es: %d",nMay);
	printf("\nEl número menor es %d",nMen);
	cout<<"\nEl promedio de los anteriores es: "<<promedio;
}
