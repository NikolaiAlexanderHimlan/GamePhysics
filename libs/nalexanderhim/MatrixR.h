#ifndef Matrix_h__
#define Matrix_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <stdexcept>
#include "CodingDefines.h"
#include "MathDefines.h"
#include "DebugDefines.h"

class Vector3f;
class VectorNf;
class Quaternion;

class MatrixR
{
	typedef real matType;
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
	MatrixR();
	MatrixR(uint rows, uint columns);
	MatrixR(REF(nah::CountedArray<matType>) inArray);
	virtual ~MatrixR() { clearMatrix();	};

	//Getters
	inline int numRows() const { return mRows;	};
	inline int numCols() const { return mCols;	};
	inline matType getValue(uint index) const { return refValue(index);	};

	//Setters
	// Sets the matrix to be a diagonal matrix with the given coefficients.
	void setDiagonal(matType a, matType b, matType c);
	/**
	* Sets the matrix to be a skew symmetric matrix based on the given vector.
	* The skew symmetric matrix is the equivalent of the vector product.
	* So if a,b are vectors. a x b = A_s b where A_s is the skew symmetric form of a.
	*/
	void setSkewSymmetric(const Vector3f vector);

	//Properties
	inline uint Count() const { return numRows() * numCols();	};
	inline uint getIndex(uint row, uint col) const { return row*col;	};
	VectorNf getRowVector(uint rowIndex) const;
	VectorNf getColVector(uint colIndex) const;
	/**
	* Gets a vector representing one axis (i.e. one column) in the matrix.
	* @param i The row to return. Row 3 corresponds to the position of the transform matrix.
	* @return The vector.
	*/
	Vector3f getAxisVector(int i) const;
	/** Returns a new matrix containing the transpose of this matrix. */
	MatrixR Transpose() const;
	// Returns the determinant of the matrix.
	matType Determinant() const;
	/** Returns a new matrix containing the inverse of this matrix. */
	MatrixR Inverse() const;

	//Modifiers
	void setRowVector(uint rowIndex, REF(VectorNf) newRow);
	void setColVector(uint colIndex, REF(VectorNf) newCol);
	//Sets this matrix to be the rotation matrix corresponding to the given quaternion.
	void setOrientation(REF(Quaternion) q);
	//Sets this matrix to be the rotation matrix corresponding to the given quaternion.
	void setOrientationAndPos(REF(Quaternion) q, REF(Vector3f) pos);

	//Calculations
	//Transforms the given vector by this matrix.
	Vector3f TransformVector(REF(Vector3f) vect) const;
	/**
	* Transform the given direction vector by this matrix.
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param vector The vector to transform.
	*/
	Vector3f transformDirection(REF(Vector3f) vect) const;
	/**
	* Transform the given vector by the transformational inverse
	* of this matrix.
	*
	* @note This function relies on the fact that the inverse of a pure rotation matrix is its transpose.
	* It separates the translational and rotation components, transposes the rotation, and multiplies out.
	* If the matrix is not a scale and shear free transform matrix, then this function will not give correct results.
	*
	* @param vector The vector to transform.
	*/
	/**
	* Transform the given vector by the transpose of this matrix.
	*
	* @param vector The vector to transform.
	*/
	Vector3f transformTranspose(REF(Vector3f) vector) const;
	Vector3f transformInverse(REF(Vector3f) vect) const;
	/**
	* Transform the given direction vector by the transformational inverse of this matrix.
	*
	* @note This function relies on the fact that the inverse of a pure rotation matrix is its transpose.
	* It separates the translational and rotation components, transposes the rotation, and multiplies out.
	* If the matrix is not a scale and shear free transform matrix, then this function will not give correct results.
	*
	* @note When a direction is converted between frames of reference, there is no translation required.
	* @param vector The vector to transform.
	*/
	Vector3f transformInverseDirection(REF(Vector3f) vect) const;

	//Actions
	inline void clearMatrix() { delete[] maMatrixValues;	};

	//Conversions
	/**
	* Fills the given array with this transform matrix, so it is usable as an open-gl transform matrix.
	* OpenGL uses a column major format, so that the values are transposed as they are written.
	*/
	void toGLMatrix(float outArray[16]) const;

	//Operators
		//Math
	MatrixR operator *(REF(MatrixR) rhs) const;
	MatrixR operator *(real rhs) const;

		//Accessors
	inline matType& operator [](uint index) { return refValue(index);	};
	inline matType& operator ()(uint row, uint col) { return refValue(row, col);	};
	inline REF(matType) operator [](uint index) const { return refValue(index);	};
	inline REF(matType) operator ()(uint row, uint col) const { return refValue(row, col);	};

		//Assignment
	REF(MatrixR) operator *=(REF(MatrixR) rhs);

	//Static functions
	inline static MatrixR Identity(uint rows, uint cols) { return MatrixR(rows, cols);	};
	static void LoadIdentity(OUT_PARAM(MatrixR) loadInto);

	static void Invert(MatrixR& mat);

	//Interpolates a couple of matrices.
	static MatrixR linearInterpolate(REF(MatrixR) a, REF(MatrixR) b, real prop);

	static MatrixR Multiply(REF(MatrixR) lhs, REF(MatrixR) rhs);
	static void Multiply(REF(MatrixR) lhs, REF(MatrixR) rhs, OUT_PARAM(MatrixR) result);
	static Vector3f Multiply(REF(MatrixR) lhs, REF(Vector3f) rhs);
};
#endif // Matrix_h__
