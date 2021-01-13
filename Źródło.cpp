#include <iostream>
#include <vector>
#include "CMatrix.h"

using namespace std;
CMatrix<int> ciMatrix1(2, 3);
CMatrix<int> ciMatrix2(2, 3);
CMatrix<int> ciMatrix3(3, 2);
CMatrix<double> cdMatrix1(2, 3);
CMatrix<double> cdMatrix2(2, 3);
CMatrix<double> cdMatrix3(3, 2);
void fillIntMatrix(CMatrix<int>* ciMatrix, int v) {
	for (int i = 0; i < ciMatrix->iGetIMSize(); i++)
		for (int j = 0; j < ciMatrix->iGetINSize(); j++)
			ciMatrix->bSetValueAt(i, j, (i + j)*v);
}
void fillDoubleMatrix(CMatrix<double>* cdMatrix, double v) {
	for (int i = 0; i < cdMatrix->iGetIMSize(); i++)
		for (int j = 0; j < cdMatrix->iGetINSize(); j++)
			cdMatrix->bSetValueAt(i, j, (i+j)*v );
}
void Constructor() {
	CMatrix<int> cMatrix1;
	cMatrix1.vPrintMatrix();
}
void AddMatrix() {
	ciMatrix1.vPrintMatrix();
	cout << endl;
	ciMatrix2.vPrintMatrix();
	cout << endl;
	(ciMatrix1.cAdd(ciMatrix2)).vPrintMatrix();
	cout << endl;
	(ciMatrix1 + ciMatrix2).vPrintMatrix();
	cout << endl;
	cdMatrix1.vPrintMatrix();
	cout << endl;
	cdMatrix2.vPrintMatrix();
	cout << endl;
	(cdMatrix1.cAdd(cdMatrix2)).vPrintMatrix();
	cout << endl;
	(cdMatrix1 + cdMatrix2).vPrintMatrix();
	cout << endl;
}

void SubMatrix() {
	ciMatrix1.vPrintMatrix();
	cout << endl;
	ciMatrix2.vPrintMatrix();
	cout << endl;
	(ciMatrix1.cSub(ciMatrix2)).vPrintMatrix();
	cout << endl;
	(ciMatrix1 - ciMatrix2).vPrintMatrix();
	cout << endl;
	cdMatrix1.vPrintMatrix();
	cout << endl;
	cdMatrix2.vPrintMatrix();
	cout << endl;
	(cdMatrix1.cSub(cdMatrix2)).vPrintMatrix();
	cout << endl;
	(cdMatrix1 - cdMatrix2).vPrintMatrix();
	cout << endl;
}

void MultMatrix() {
	ciMatrix1.vPrintMatrix();
	cout << endl;
	(ciMatrix1.cMult(3)).vPrintMatrix();
	cout << endl;
	(ciMatrix1 * 2).vPrintMatrix();
	cout << endl;
	cdMatrix1.vPrintMatrix();
	cout << endl;
	(cdMatrix1.cMult(2.5)).vPrintMatrix();
	cout << endl;
	(cdMatrix1 * 2.5).vPrintMatrix();
	cout << endl;
}

void MultMatrixByMatrix() {
	ciMatrix1.vPrintMatrix();
	cout << endl;
	ciMatrix3.vPrintMatrix();
	cout << endl;
	(ciMatrix1.cMult(ciMatrix3)).vPrintMatrix();
	cout << endl;
	(ciMatrix1 * ciMatrix3).vPrintMatrix();
	cout << endl;
	cdMatrix1.vPrintMatrix();
	cout << endl;
	cdMatrix3.vPrintMatrix();
	cout << endl;
	(cdMatrix1.cMult(cdMatrix3)).vPrintMatrix();
	cout << endl;
	(cdMatrix1 * cdMatrix3).vPrintMatrix();
	cout << endl;
}

void MatrixFromFile() {
	CMatrix<double> mFromFile("data1.txt");
	mFromFile.vPrintMatrix();
}
void GetOperator() {
	ciMatrix1.vPrintMatrix();
	cout<< "GetOperator: "  << ciMatrix1[1][1] << endl;;
	ciMatrix1[1][1] = 100;
	ciMatrix1.vPrintMatrix();
	cout << "GetOperator: " << ciMatrix1[1][1] << endl;;
}
void MatrixTest() {

	fillIntMatrix(&ciMatrix1, 1);
	fillIntMatrix(&ciMatrix2, 2);
	fillIntMatrix(&ciMatrix3, 1);
	fillDoubleMatrix(&cdMatrix1, 1.5);
	fillDoubleMatrix(&cdMatrix2, 0.5);
	fillDoubleMatrix(&cdMatrix3, 1.5);

	//AddMatrix();
	//SubMatrix();
	//MultMatrix();
	//MultMatrixByMatrix();
	//Constructor();
	//MatrixFromFile();
	GetOperator();
}

int main(int argc, char* argv[]) {
	MatrixTest();
	return 0;
}

