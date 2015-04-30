/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "MatrixR.h"

#include <stdexcept>
#include "VectorMath.h"
MatrixR MatrixR::operator*(REF(MatrixR) rhs) const
{
	if (numCols() != rhs.numRows())
		LOGIC_ERR(("Cols " + numCols() + " does not match Rows " + rhs.numRows()));

	MatrixR mult = MatrixR(numRows(), rhs.numCols());
	VectorNf curRow;

	for (uint i = 0; i < numRows(); i++)
	{
		curRow = getRowVector(i);
		for (uint j = 0; j < rhs.numCols(); j++)
		{
			mult.refValue(i, j) = Dot(curRow, rhs.getColVector(j));
		}
	}
	return mult;
}

