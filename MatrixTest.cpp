#pragma once
#include <iostream>
#include <vector>
#include "CMatrix.h"
using namespace std;

CMatrix<int> ciMatrix1(3, 4);
CMatrix<int> ciMatrix2(3, 4);
CMatrix<int> ciMatrix3(4, 2);
CMatrix<int> ciVector1(1, 3);
CMatrix<int> ciVector2(1, 3);

CMatrix<double> cdMatrix1(3, 4);
CMatrix<double> cdMatrix2(3, 4);
CMatrix<double> cdMatrix3(4, 2);
CMatrix<double> cdVector1(1, 3);
CMatrix<double> cdVector2(1, 3);

CErrorMatrix* errorCode = new CErrorMatrix;

void printErrorCode() {
	if (errorCode->iGetErrorCode() != NO_ERROR)
		cout << "KOD BLEDU: " << errorCode->iGetErrorCode() << endl;;
}

void CreateMatrix() {
	cout << "CONSTRUCTOR TEST" << endl;
	CMatrix<int> newCiMatrix1;
	CMatrix<int> newCiMatrix2(-2, -3);
	CMatrix<double> newCdMatrix1;
	CMatrix<double> newCdMatrix2(-2, -3);
	cout << "Macierz domyœlna int" << endl;
	newCiMatrix1.vPrintMatrix();
	cout << endl;
	cout << "Maceirz int -2 x -3" <<endl;
	newCiMatrix2.vPrintMatrix();
	cout << endl;
	cout << "Macierz domyœlna double" << endl;
	newCdMatrix1.vPrintMatrix();
	cout << endl;
	cout << "Maceirz double -2 x -3" << endl;
	newCdMatrix2.vPrintMatrix();
	cout << endl;
	cout << "Macierz utworzona z Macierzy domyslnej double : 2 x 2";
	cout << newCdMatrix1.bCreateMatrix(2, 2, errorCode) << endl;;
	newCdMatrix1.vPrintMatrix();
	printErrorCode();
	cout << endl;
	cout << "Macierz utworzona z Macierzy domyslnej int : -2 x -2";
	cout << newCdMatrix1.bCreateMatrix(-2, -2, errorCode) << endl;;
	newCdMatrix1.vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void FillGetSetMatrix() {
	ciMatrix1.vFillDefMatrix(1);
	ciMatrix2.vFillDefMatrix(2);
	ciMatrix3.vFillDefMatrix(3);
	cdMatrix1.vFillDefMatrix(1.1);
	cdMatrix2.vFillDefMatrix(2.2);
	cdMatrix3.vFillDefMatrix(3.3);

	cout << "MACIERZ INT 1" << endl;
	ciMatrix1.vPrintMatrix();
	cout << "MACIERZ INT 2" << endl;
	ciMatrix2.vPrintMatrix();
	cout << "MACIERZ INT 3" << endl;
	ciMatrix3.vPrintMatrix();

	cout << "MACIERZ DOUBLE 1" << endl;
	cdMatrix1.vPrintMatrix();
	cout << "MACIERZ DOUBLE 2" << endl;
	cdMatrix2.vPrintMatrix();
	cout << "MACIERZ DOUBLE 3" << endl;
	cdMatrix3.vPrintMatrix();

	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Ustawienie wartosci 9 na maceirzy int 1 na pos: 1x1 " << endl;
	ciMatrix1[1][1] = 9;
	printErrorCode();
	cout << "Ustawienie wartosci 9 na maceirzy int 2 na pos: 2x2" << endl;
	ciMatrix2.bSetValueAt(2, 2, 9, errorCode);
	printErrorCode();
	cout << "Ustawienie wartosci 9 na maceirzy int 3 na pos: 10x10" << endl;
	ciMatrix3.bSetValueAt(10, 10, 9, errorCode);
	printErrorCode();

	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Ustawienie wartosci 9.9 na maceirzy double 1 na pos: 1x1 " << endl;
	cdMatrix1[1][1] = 9.9;
	printErrorCode();
	cout << "Ustawienie wartosci 9.9 na maceirzy double 2 na pos: 2x2 " << endl;
	cdMatrix2.bSetValueAt(2, 2, 9.9, errorCode);
	printErrorCode();
	cout << "Ustawienie wartosci 9.9 na maceirzy double 3 na pos: 10x10 " << endl;
	cdMatrix3.bSetValueAt(10, 10, 9.9, errorCode);
	printErrorCode();

	ciMatrix1.vPrintMatrix(); cout << endl;
	ciMatrix2.vPrintMatrix(); cout << endl;
	ciMatrix3.vPrintMatrix(); cout << endl;
	cdMatrix1.vPrintMatrix(); cout << endl;
	cdMatrix2.vPrintMatrix(); cout << endl;
	cdMatrix3.vPrintMatrix(); cout << endl;

	try {
		cout <<"Wartosc macierzy int 1 z pos: 1x1 \n" << ciMatrix1[1][1] << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Wartosc macierzy int 2 z pos: 2x2 \n" << ciMatrix2.tGetValuFrom(2, 2, errorCode) << endl;
	printErrorCode();
	cout << "Wartosc macierzy int 3 z pos: 10x10 \n" << ciMatrix3.tGetValuFrom(10, 10, errorCode) << endl;
	printErrorCode();
	
	try {
		cout << "Wartosc macierzy double 1 z pos: 1x1 \n" << cdMatrix1[1][1] << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Wartosc macierzy double 2 z pos: 2x2 \n" << cdMatrix2.tGetValuFrom(2, 2, errorCode) << endl;
	printErrorCode();
	cout << "Wartosc macierzy double 3 z pos: 10x10 \n" << cdMatrix3.tGetValuFrom(10, 10, errorCode) << endl;
	printErrorCode();
}

void ScalarProduct() {
	ciVector1.vFillDefMatrix(1);
	ciVector2.vFillDefMatrix(2);
	cdVector1.vFillDefMatrix(1.1);
	cdVector2.vFillDefMatrix(2.2);

	cout << "Wektor int 1" << endl;
	ciVector1.vPrintMatrix();
	cout << "Wektor int 2" << endl;
	ciVector2.vPrintMatrix(); 
	cout << "Wektor double 1" << endl;
	cdVector1.vPrintMatrix();
	cout << "Wektor double 2" << endl;
	cdVector2.vPrintMatrix();

	cout << "Iloczyn skalarny wektor int 1 oraz wektor int 2" << endl;
	errorCode->vSetErrorCode(0);
	cout << ciVector1.tScalarProduct(ciVector2, errorCode) <<endl;
	printErrorCode();

	cout << "Iloczyn skalarny wektor double 1 oraz wektor double 2" << endl;
	errorCode->vSetErrorCode(0);
	cout << cdVector1.tScalarProduct(cdVector2, errorCode) << endl;
	printErrorCode();

	cout << "Iloczyn skalarny maceirzy int  1 oraz wektora int 1" << endl;
	errorCode->vSetErrorCode(0);
	cout << "Macierz int 1" << endl;
	ciMatrix1.vPrintMatrix();
	cout << ciMatrix1.tScalarProduct(ciVector1, errorCode) << endl;
	printErrorCode();
}

void SetIdentyMatrix() {
	cout << "TWORZENIE MACIERZY JEDNOSTKOWEJ" << endl;
	CMatrix<int>* intMatrix1 = new  CMatrix<int>(3, 3);
	CMatrix<int>* intMatrix2 = new  CMatrix<int>(3, 2);
	intMatrix1->vFillDefMatrix(2);
	intMatrix2->vFillDefMatrix(2);
	
	cout << "Macierz int 3x3" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	intMatrix1->vPrintMatrix();
	intMatrix1->bSetIdentityMatrix(errorCode);
	cout << "Maceirz jednostkowa" << endl;
	intMatrix1->vPrintMatrix();
	printErrorCode();

	cout << "Macierz int 3x2" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	intMatrix2->vPrintMatrix();
	intMatrix2->bSetIdentityMatrix(errorCode);
	cout << "Macierz jednostkowa" << endl;
	intMatrix2->vPrintMatrix();
	printErrorCode();

	delete intMatrix1;
	delete intMatrix2;
}

void ReadFromFIle() {
	cout << "ODCZYTYWANIE MACIERZY Z PLIKU" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	CMatrix<int> iMatrix;
	CMatrix<double> dMatrix;
	cout << "Macierz int z prawidlowego pliku" << endl;
	iMatrix.bReadMatrixFromFile("dataInt.txt",errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	cout << "Macierz int z pliku z bledami" << endl;
	iMatrix.bReadMatrixFromFile("dataWrongArgInt.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz int z pliku z brakujacymi elementami" << endl;
	iMatrix.bReadMatrixFromFile("dataMissArgInt.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz int z pliku z pilu double" << endl;
	iMatrix.bReadMatrixFromFile("dataDouble.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();

	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz double z prawidlowego pliku" << endl;
	dMatrix.bReadMatrixFromFile("dataDouble.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	cout << "Macierz double z pliku z bledami" << endl;
	dMatrix.bReadMatrixFromFile("dataWrongArgDouble.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz double z pliku z brakujacymi elementami" << endl;
	dMatrix.bReadMatrixFromFile("dataMissArgDouble.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz double z pliku z pilu int" << endl;
	dMatrix.bReadMatrixFromFile("dataInt.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
}

void vectorFromCol() {
	cout << "WEKTOR Z KOLUMNY" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz 1" << endl;
	ciMatrix1.bSetValueAt(2, 0, 1, errorCode);
	ciMatrix1.bSetValueAt(2, 1, 2, errorCode);
	ciMatrix1.bSetValueAt(2, 2, 3, errorCode);
	ciMatrix1.vPrintMatrix();
	cout << endl;
	cout << "Wektor z 2 (3) kolumny" << endl;
	ciMatrix1.cTColumnVector(2,errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
	cout << "Wektor z 4 (5) kolumny" << endl;
	ciMatrix1.cTColumnVector(4,errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void vectorFromRow() {
	cout << "WEKTOR Z WIERSZA" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "Macierz 1" << endl;
	ciMatrix1.bSetValueAt(2, 0, 1, errorCode);
	ciMatrix1.bSetValueAt(2, 1, 2, errorCode);
	ciMatrix1.bSetValueAt(2, 2, 3, errorCode);
	ciMatrix1.vPrintMatrix();
	cout << endl;
	cout << "Wektor z 2 (3) wierszaw" << endl;
	ciMatrix1.cTRowVector(2, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
	cout << "Wektor z 4 (5) wierszaw" << endl;
	ciMatrix1.cTRowVector(4, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void Transpose() {
	cout << "TRANSPONOWANIE MACIERZY" << endl;
	CMatrix<float> cfMatrix(4,2);
	CMatrix<int>* newMatrix;
	cfMatrix.vFillDefMatrix(3.1);
	cfMatrix[1][1] = 5.5;
	cout << "Maceirz float" << endl;
	cfMatrix.vPrintMatrix();
	cout << "Macierz transponowana" << endl;
	cfMatrix.ctTranspose(errorCode).vPrintMatrix();
	~cfMatrix;
	cfMatrix.vPrintMatrix();
}

void Operators() {
	cout << "OPERATORY" << endl;
	ciMatrix1.vFillDefMatrix(1);
	ciMatrix2.vFillDefMatrix(2);
	ciMatrix3.vFillDefMatrix(3);
	cdMatrix1.vFillDefMatrix(1.1);
	cdMatrix2.vFillDefMatrix(2.2);
	cdMatrix3.vFillDefMatrix(3.3);
	
	cout << "ADD" << endl;
	cout << "Dodawanie" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "maceirz1" << endl; ciMatrix1.vPrintMatrix(); 
	cout << "maceirz2" << endl; ciMatrix2.vPrintMatrix();
	cout << "maceirz3" << endl; ciMatrix3.vPrintMatrix();
	cout << "Operator 1+2" << endl;
	try {
		(ciMatrix1 + ciMatrix2).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e){
		cout << e.what() << endl;
	}
	cout << "metoda 1.cAdd(2) " << endl;
	(ciMatrix1.cAdd(ciMatrix2, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();
	cout << "opeartor 1 + 3 " << endl;
	try {
		(ciMatrix1 + ciMatrix3).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "metoda 1.cAdd(3) " << endl;
	(ciMatrix1.cAdd(ciMatrix3, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	errorCode->vSetErrorCode(NO_ERROR);
	cout << "SUB" << endl;
	cout << "Operator 1 - 2" << endl;
	try {
		(ciMatrix1 - ciMatrix2).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "metoda 1.cSub(2)" << endl;
	(ciMatrix1.cSub(ciMatrix2, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "Operator 1 - 3" << endl;
	try {
		(ciMatrix1 - ciMatrix3).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "metoda 1.cSub(3)" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	(ciMatrix1.cSub(ciMatrix3, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "MULT" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << "operator 1 * 3" << endl;
	try {
		(ciMatrix1 * ciMatrix3).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "metoda 1.cMult(3)" << endl;
	(ciMatrix1.cMult(ciMatrix3, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "operator 1 * 2" << endl;
	try {
		(ciMatrix1 * ciMatrix2).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "metoda 1.cMult(2)" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	(ciMatrix1.cMult(ciMatrix2, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "OPERATOR -=" << endl;
	cout << "1-2" << endl;
	try {
		ciMatrix1 -= ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1-3" << endl;
	try {
		ciMatrix1 -= ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	
	cout << "OPERATOR +=" << endl;
	cout << "1+2" << endl;
	try {
		ciMatrix1 += ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1+3" << endl;
	try {
		ciMatrix1 += ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "operator *=" << endl;
	cout << "1 * 3" << endl;
	try {
		ciMatrix1 *= ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1 * 2" << endl;
	try {
		ciMatrix1 *= ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "Mnozenie maceirzy przez stala 2:" << endl;
	(ciMatrix1 * 2).vPrintMatrix();
	cout << endl;
	(ciMatrix1.cMult(2)).vPrintMatrix();
	cout << endl;
	ciMatrix1 *= 2;
	cout << endl;
	ciMatrix1.vPrintMatrix();
}


void MatrixTest() {
	CreateMatrix();
	FillGetSetMatrix();
	ScalarProduct();
	SetIdentyMatrix();
	ReadFromFIle();
	vectorFromCol();
	vectorFromRow();
	Transpose();
	Operators();
}
int main(int argc, char* argv[]) {
	MatrixTest();
	return 0;
}

