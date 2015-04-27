#ifndef Matrix_h__
#define Matrix_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "CodingDefines.h"
#include "MathDefines.h"
#include "DebugDefines.h"

class VectorNf;

class Matrixf
{
	typedef float matType;
protected:
	int mRows, mCols;

	matType* maMatrixValues;

	inline matType& refValue(uint index) const
	{
		if (index >= Count())
			LOGIC_ERR("Invalid Matrix Index!");
		return maMatrixValues[index];
	}
	inline matType& refValue(uint row, uint col) const
	{
		if (row >= numRows())
			LOGIC_ERR("Invalid Matrix Row!");
		if (col >= numCols())
			LOGIC_ERR("Invalid Matrix Column!");
		return refValue(getIndex(row, col));
	}

public:
	Matrixf();
	Matrixf(uint rows, uint columns);
	~Matrixf() { clearMatrix();	};

	//Getters
	inline int numRows() const { return mRows;	};
	inline int numCols() const { return mCols;	};
	inline matType getValue(uint index) const { return refValue(index);	};

	//Properties
	inline uint Count() const { return numRows() * numCols();	};
	VectorNf getRowVector(uint rowIndex) const;
	VectorNf getColVector(uint colIndex) const;

	//Modifiers
	void setRowVector(uint rowIndex, REF(VectorNf) newRow);
	void setColVector(uint colIndex, REF(VectorNf) newCol);

	//Calculations
	inline uint getIndex(uint row, uint col) const { return row*col;	};

	//Actions
	inline void clearMatrix() { delete[] maMatrixValues;	};

	//Operators
	inline Matrixf operator *(const Matrixf& rhs);
	inline matType& operator [](uint index) { return refValue(index);	};
	inline REF(matType) operator [](uint index) const { return refValue(index);	};;
	inline matType& operator ()(uint row, uint col) { return refValue(row, col);	};
	inline REF(matType) operator ()(uint row, uint col) const { return refValue(row, col);	};

	//Static functions
	inline static Matrixf Identity() { return Matrixf();	};

	static Matrixf Inverse(REF(Matrixf) mat);
	static void Invert(Matrixf& mat);

	static Matrixf Multiply(REF(Matrixf) lhs, REF(Matrixf) rhs);
	static void Multiply(REF(Matrixf) lhs, REF(Matrixf) rhs, OUT_PARAM(Matrixf) result);
};

//TODO: move below to source file
#include <stdexcept>//used for LOGIC_ERR, move to .cpp file
#include "VectorMath.h"
Matrixf Matrixf::operator*(REF(Matrixf) rhs)
{
	if (numCols() != rhs.numRows())
		LOGIC_ERR(("Cols " + numCols() + " does not match Rows " + rhs.numRows()));

	Matrixf mult = Matrixf(numRows(), rhs.numCols());
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

#endif // Matrix_h__
