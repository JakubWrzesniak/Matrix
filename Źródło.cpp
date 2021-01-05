#include <iostream>
#include "CMatrix.h"

using namespace std;

void MatrixTest() {
	CMatrix<int>* matrix1 = new CMatrix<int>(2, 4);
	CMatrix<int>* matrix2 = new CMatrix<int>(3, 3);
	CMatrix<int>* matrix3;
	CMatrix<double>* matrix4;
	CMatrix<double>* matrix5 = new CMatrix<double>(2, 3);
	CMatrix<float>* matrix6 = new CMatrix<float>(3, 4);
	CMatrix<int>* vector1 = new CMatrix<int>(1, 3);
	CMatrix<int>* vector2 = new CMatrix<int>(3, 1);

	matrix1->vPrintMatrix();
	matrix1->bSetValueAt(0, 0, 1);
	matrix1->bSetValueAt(1, 0, 1);
	matrix1->bSetValueAt(1, 1, 1);
	matrix1->bSetValueAt(0, 3, 5);
	matrix1->vPrintMatrix();
	matrix1->bCreateMatrix(3, 3);
	matrix1->vPrintMatrix();
	cout << matrix1->tGetValuFrom(0, 0) << endl;;
	matrix1->bSetIdentityMatrix();
	matrix1->vPrintMatrix();

	matrix2->bSetValueAt(0,0,4);
	matrix2->bSetValueAt(1,0,4);
	matrix2->bSetValueAt(2,0,4);
	matrix2->bSetValueAt(0,1,4);
	matrix2->bSetValueAt(1,1,4);
	matrix2->bSetValueAt(2,1,4);
	matrix2->bSetValueAt(0,2,4);
	matrix2->bSetValueAt(1,2,4);
	matrix2->bSetValueAt(2,2,4);

	matrix5->bSetValueAt(0,0,2.5);
	matrix5->bSetValueAt(1,0,2.5);
	matrix5->bSetValueAt(0,1,2.5);
	matrix5->bSetValueAt(1,1,2.5);
	matrix5->bSetValueAt(0,2,2.5);
	matrix5->bSetValueAt(1,2,2.5);

	matrix6->bSetValueAt(0,0,1);
	matrix6->bSetValueAt(0,1,2);
	matrix6->bSetValueAt(0,2,3);
	matrix6->bSetValueAt(0,3,4);
	matrix6->bSetValueAt(1,0,5);
	matrix6->bSetValueAt(1,1,6);
	matrix6->bSetValueAt(1,2,7);
	matrix6->bSetValueAt(1,3,8);
	matrix6->bSetValueAt(2,0,9);
	matrix6->bSetValueAt(2,1,10);
	matrix6->bSetValueAt(2,2,11);
	matrix6->bSetValueAt(2,3,12);

	vector1->bSetValueAt(0, 0, 1);
	vector1->bSetValueAt(0, 1, 3);
	vector1->bSetValueAt(0, 2, -5);

	vector2->bSetValueAt(0, 0, 4);
	vector2->bSetValueAt(1, 0, -2);
	vector2->bSetValueAt(2, 0, -1);

	matrix2->vPrintMatrix();
	matrix3 = *matrix1 + *matrix2;
	matrix3->vPrintMatrix();
	matrix3 = *matrix3 - *matrix2;
	matrix3->vPrintMatrix();
	matrix4 = *matrix3 * 4.5;
	matrix4->vPrintMatrix();
	matrix3 = *matrix3 * 4;
	matrix3->vPrintMatrix();
	matrix4 = *matrix4 * 3;
	matrix4->vPrintMatrix();
	matrix5->vPrintMatrix();
	matrix6->vPrintMatrix();
	(*matrix5 * *matrix6)->vPrintMatrix();

	(*vector1 * *vector2)->vPrintMatrix();
	matrix6->ctTranspose()->vPrintMatrix();
	cout << vector1->iScalarProduct(*(vector2->ctTranspose())) << endl;
	matrix6->bRedMatrixFromFilme("data1.txt");
}

int main(int argc, char* argv[]) {
	MatrixTest();
	return 0;
}

