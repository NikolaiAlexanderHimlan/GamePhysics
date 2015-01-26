/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: pa 4
Certification of Authenticity:
I certify that this class is essentially a copy of the Vector2D class provided to our class by Dean Lawson.
*/

#pragma once

/* Vector2D is a generally usable 2D vector.  Most of the operator overloading code is patterned after the notes from 
California Institute of Technology site: http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html .  
Exact author unknown.
May be missing some important functions but this should be enough to do most things.

by Dean Lawson
Champlain College
2011
*/

//#include <cfloat>
#include <string>
//#include <Trackable.h>
//#include <Vector2D.h>

class Vector2D;//#include IntCoord should not #include Vector2D

//Nikolai Alexander-Himlan
namespace nah
{
	//TODO: struct or class?
	class IntCoord
		//: public Trackable
	{
	private:
		int mX;
		int mY;

	public:
		IntCoord( int x = 0, int y = 0 );//constructor
		IntCoord( int coord[2] );
		IntCoord( Vector2D coord );
		IntCoord( const IntCoord& rhs );//copy constructor
		~IntCoord();//destructor

#pragma region getters and setters
		inline int getX() const { return mX;	};
		inline int getY() const { return mY;	};
		inline void setX( int x ) { mX = x;	};
		inline void setY( int y ) { mY = y;	};
		inline IntCoord& setData(int newX, int newY) { setX(newX); setY(newY); return *this;	}
		inline IntCoord& setData(const IntCoord& newValue) { return setData(newValue.getX(), newValue.getY());	}
		inline int* ptrX() { return &mX;	};
		inline int* ptrY() { return &mY;	};
#pragma endregion

#pragma region math functions
		//using this-> to make it explicit what is happening
		inline const IntCoord add(const IntCoord& rhs) const
		{ return IntCoord(this->getX() + rhs.getX(), this->getY() + rhs.getY());	}
		inline const IntCoord subtract(const IntCoord& rhs) const
		{ return IntCoord(this->getX() - rhs.getX(), this->getY() - rhs.getY());	}
		inline const IntCoord add(int addThis) const
		{ return IntCoord(this->getX() + addThis, this->getY() + addThis);	}
		inline const IntCoord subtract(int subtractThis) const
		{ return IntCoord(this->getX() - subtractThis, this->getY() - subtractThis);	}
		inline const IntCoord multiply(float multiplyBy) const
		{ return IntCoord(int(this->getX()*multiplyBy), int(this->getY()*multiplyBy));	}
		inline const IntCoord divide(float divideBy) const
		{ return IntCoord(int(this->getX()/divideBy), int(this->getY()/divideBy));		}

		const IntCoord absGet() const;//get an IntCoord which is the absolute version of this coord
		inline IntCoord& absSet();//make this IntCoord absolute
#pragma endregion

#pragma region math operators
		inline const IntCoord operator+(const IntCoord& rhs) const { return add(rhs);	}
		inline const IntCoord operator-(const IntCoord& rhs) const { return subtract(rhs);	}
		inline const IntCoord operator+(int rhs) const { return add(rhs);	}
		inline const IntCoord operator-(int rhs) const { return subtract(rhs);	}
		inline const IntCoord operator*(float rhs) const { return multiply(rhs);	}
		inline const IntCoord operator/(float rhs) const { return divide(rhs);		}

		inline IntCoord& operator = ( const IntCoord& rhs ) { return setData(rhs);	}
		inline IntCoord& operator += ( const IntCoord& rhs ){ return setData(add(rhs));	}
		inline IntCoord& operator -= ( const IntCoord& rhs ){ return setData(subtract(rhs));	}
		inline IntCoord& operator += ( int rhs ){ return setData(add(rhs));	}
		inline IntCoord& operator -= ( int rhs ){ return setData(subtract(rhs));	}
		inline IntCoord& operator *= ( float rhs ) { return setData(multiply(rhs));	}
		inline IntCoord& operator /= ( float rhs ) { return setData(divide(rhs));		}
#pragma endregion

#pragma region comparison operators
		inline bool operator > ( const IntCoord& rhs ) const { return greaterThan(rhs);	}
		inline bool operator < ( const IntCoord& rhs ) const { return lessThan(rhs);	}
		inline bool operator >= ( const IntCoord& rhs ) const { return greaterThanOrEquals(rhs);	}
		inline bool operator <= ( const IntCoord& rhs ) const { return lessThanOrEquals(rhs);		}
		inline bool operator == ( const IntCoord& rhs ) const;// { return equals(rhs);		}
		inline bool operator != ( const IntCoord& rhs ) const { return !equals(rhs);	}
		inline bool operator == ( int rhs ) const { return equals(rhs);		}
		inline bool operator != ( int rhs ) const { return !equals(rhs);	}

		//comparison functionality
		inline bool greaterThan( const IntCoord& otherCoord ) const {
			//it is okay if one value is equal so long as are not both equal
			if (equals(otherCoord)) return false;//if both values are equal, this coord is NOT greater than the other
			return greaterThanOrEquals(otherCoord);//since the coords are not equal, this will return if greater than or not
		}
		inline bool lessThan( const IntCoord& otherCoord ) const {
			//it is okay if one value is equal so long as are not both equal
			if (equals(otherCoord)) return false;//if both values are equal, this coord is NOT less than the other
			return lessThanOrEquals(otherCoord);//since the coords are not equal, this will return if less than or not
		}
		inline bool greaterThanOrEquals( const IntCoord& otherCoord ) const
		{ return getX() >= otherCoord.getX() && getY() >= otherCoord.getY();	}
		inline bool lessThanOrEquals( const IntCoord& otherCoord ) const
		{ return getX() <= otherCoord.getX() && getY() <= otherCoord.getY();	}
		inline bool equals( const IntCoord& otherCoord ) const { return (getX()==otherCoord.getX()) && (getY()==otherCoord.getY());	}
		inline bool equals( int otherValue ) const { return (getX()==otherValue) && (getY()==otherValue);	}
#pragma endregion

#pragma region type operators
		IntCoord& operator= (const int params[2]);//to be used when passing in function parameters //hopefully an implicit conversion from an array of 2 integers
		operator Vector2D (void) const;
#pragma endregion

#pragma region length functions
		bool hasNonZeroLength(void) const;
		float getLength(void) const;
		float getLengthSquared(void) const;//more efficient than get length - use when comparing distances and actual distance is not needed
		//void normalize(void);//makes vector a unit vector (length of 1)
		//TODO: normalized(void);//returns a unit vector (length of 1)

		inline int combineToSingleInt() const { return getX() + getY(); }//TODO: rename
#pragma endregion

#pragma region specific coord values
		static inline IntCoord zero(void){ return IntCoord(0,0);	}
		static inline IntCoord one(void){ return IntCoord(1,1);		}
#pragma endregion

#pragma region feedback functions
		//Returns the data stored in the IntCoord as a string with the format "{mX, mY}"
		//	There is a minor bug where using a buffer greater than 1 will result in an extra 0 if one of the stored values is 0
		std::string toString(int buffer = 1) const;
		//TODO: std::string operator

#pragma region functionality from my C♯ XNA IntCoord class
		/*Reference
		//NikolaiA-H Methods
		/// <summary>Constrains the value of the current IntCoord to the given rectangle.
		/// </summary>
		/// <param name="bounds">Rectangle to constrain to.</param>
		/// <returns>How much the IntCoord was changed.</returns>
		public IntCoord Clamp(Microsoft.Xna.Framework.Rectangle bounds)
		{
			if (bounds.Contains(X, Y)) return IntCoord.Zero;//check if this is within the rectangle in the first place
			return new IntCoord(
			TypeAddon.Clamp(ref X, bounds.Right, bounds.Left),
			TypeAddon.Clamp(ref Y, bounds.Bottom, bounds.Top));
		}

		//Vector2 method copies
		#pragma region Operators
		/// <summary>
		/// Explicit cast from Vector2 to IntCoord
		/// </summary>
		/// <param name="vect">Vector2 to cast as an IntCoord</param>
		/// <returns>IntCoord of the same value with the decimal cut off</returns>
		public static explicit operator IntCoord(Vector2 vect)
		{
			IntCoord castCoord = new IntCoord((int)vect.X, (int)vect.Y);
			return castCoord;
		}
		/// <summary>
		/// Explicitly cast from IntCoord to Vector2
		/// </summary>
		/// <param name="coord">IntCoord to cast as a Vector2</param>
		/// <returns>Vector2 of the same value</returns>
		public static explicit operator Vector2(IntCoord coord)
		{
			Vector2 castVect = new Vector2(coord.X, coord.Y);
			return castVect;
		}
		public static implicit operator IntCoord(Point point)//freely convert from Point, lose no functionality or value
		{
			IntCoord castCoord = new IntCoord(point.X, point.Y);
			return castCoord;
		}
		public static explicit operator Point(IntCoord coord)
		{
			Point castPoint = new Point(coord.X, coord.Y);
			return castPoint;
		}
		/// <summary>Adds two integer coordinates.
		/// </summary>
		/// <param name="value1">Source integer coordinate.</param>
		/// <param name="value2">Source integer coordinate.</param>
		/// <returns></returns>
		public static IntCoord operator +(IntCoord value1, IntCoord value2)
		{ return Add(value1, value2); }
		/// <summary>Adds an integer to both values of an integer coordinate
		/// </summary>
		/// <param name="value1">Source integer coordinate.</param>
		/// <param name="value2">Source integer.</param>
		/// <returns></returns>
		public static IntCoord operator +(IntCoord value1, int value2)
		{ return Add(value1, value2); }
		/// <summary>Adds a vector and integer coordinate.
		/// </summary>
		/// <param name="value1"></param>
		/// <param name="value2"></param>
		/// <returns>A Vector2 so the float precision isn't lost.</returns>
		public static Vector2 operator +(Vector2 value1, IntCoord value2)
		{ return Add(value1, value2); }
		public static Vector2 operator +(IntCoord value1, Vector2 value2)
		{ return Add(value2, value1); }//order doesn't matter for addition
		// Summary:
		//     Returns a vector pointing in the opposite direction.
		//
		// Parameters:
		//   value:
		//     Source vector.
		public static IntCoord operator -(IntCoord value)
		{ return new IntCoord(-value.X, -value.Y); }
		//
		// Summary:
		//     Subtracts a vector from a vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     source vector.
		public static IntCoord operator -(IntCoord value1, IntCoord value2)
		{ return Subtract(value1, value2); }
		public static IntCoord operator -(IntCoord value1, int value2)
		{ return Subtract(value1, value2); }
		/// <summary>Multiplies a vector by a scalar value.
		/// </summary>
		/// <param name="scaleFactor">Scalar value.</param>
		/// <param name="value"> Source vector.</param>
		/// <returns>IntCoord result of multiplication.</returns>
		public static IntCoord operator *(float scaleFactor, IntCoord value)
		{ return Multiply(value, scaleFactor); }
		//
		// Summary:
		//     Multiplies a vector by a scalar value.
		//
		// Parameters:
		//   value:
		//     Source vector.
		//
		//   scaleFactor:
		//     Scalar value.
		public static IntCoord operator *(IntCoord value, float scaleFactor)
		{ return Multiply(value, scaleFactor); }
		//
		// Summary:
		//     Multiplies the components of two vectors by each other.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static IntCoord operator *(IntCoord value1, IntCoord value2)
		{ return Multiply(value1, value2); }
		public static Vector2 operator *(IntCoord value1, Vector2 value2)//return Vector 2 so precision isn't inherently lost
		{ return Multiply(value1, value2); }
		public static Vector2 operator *(Vector2 value1, IntCoord value2)//return Vector 2 so precision isn't inherently lost
		{ return Multiply(value2, value1); }
		//
		// Summary:
		//     Divides a vector by a scalar value.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   divider:
		//     The divisor.
		public static IntCoord operator /(IntCoord value1, float divider)
		{ return Divide(value1, divider); }
		//
		// Summary:
		//     Divides the components of a vector by the components of another vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Divisor vector.
		public static IntCoord operator /(IntCoord value1, IntCoord value2)
		{ return Divide(value1, value2); }
		//
		// Summary:
		//     Tests vectors for equality.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static bool operator ==(IntCoord value1, IntCoord value2)
		{
			//return Equals(value1, value2); 
			//Alternatively
			if (value1.X != value2.X)
				return false;
			if (value1.Y != value2.Y)
				return false;
			return true;
		}
		//
		// Summary:
		//     Tests vectors for inequality.
		//
		// Parameters:
		//   value1:
		//     Vector to compare.
		//
		//   value2:
		//     Vector to compare.
		public static bool operator !=(IntCoord value1, IntCoord value2)
		{
			//return !Equals(value1, value2); 
			//Alternatively
			if (value1.X != value2.X)
				return true;
			if (value1.Y != value2.Y)
				return true;
			return false;
		}
		#pragma endregion
		///<TODO>
		///	*figure out how Vector2 versions of remaining methods work
		///		-implement these that way
		///</TODO>
		#pragma region Presets
		// Summary:
		//     Returns a IntCoord with both of its components set to one.
		public static IntCoord One { get { return new IntCoord(Vector2.One); } }
		//
		// Summary:
		//     Returns the unit vector for the x-axis.
		public static IntCoord UnitX { get { return new IntCoord(Vector2.UnitX); } }
		//
		// Summary:
		//     Returns the unit vector for the y-axis.
		public static IntCoord UnitY { get { return new IntCoord(Vector2.UnitY); } }
		//
		// Summary:
		//     Returns a IntCoord with all of its components set to zero.
		public static IntCoord Zero { get { return new IntCoord(0, 0); } }
		#pragma endregion
		#pragma region Static Return Methods
		//TODO: create non-static versions that alter the instance data   
		/// <summary>Adds two integer coordinates.
		/// </summary>
		/// <param name="value1">Source integer coordinate.</param>
		/// <param name="value2">Source integer coordinate.</param>
		/// <returns>IntCoord result</returns>
		public static IntCoord Add(IntCoord value1, IntCoord value2)
		{ return new IntCoord(value1.X + value2.X, value1.Y + value2.Y); }
		/// <summary>Adds an integer to both values of an integer coordinate
		/// </summary>
		/// <param name="value1">Source integer coordinate.</param>
		/// <param name="value2">Source integer.</param>
		/// <returns></returns>
		public static IntCoord Add(IntCoord value1, int value2)
		{ return new IntCoord(value1.X + value2, value1.Y + value2); }
		public static Vector2 Add(Vector2 value2, IntCoord value1)
		{ return new Vector2(value1.X + value2.X, value1.Y + value2.Y); }
		//
		// Summary:
		//     Adds two vectors.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] Sum of the source vectors.
		public static void Add(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a IntCoord containing the 2D Cartesian coordinates of a point specified
		//     in barycentric (areal) coordinates relative to a 2D triangle.
		//
		// Parameters:
		//   value1:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 1 of the triangle.
		//
		//   value2:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 2 of the triangle.
		//
		//   value3:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 3 of the triangle.
		//
		//   amount1:
		//     Barycentric coordinate b2, which expresses the weighting factor toward vertex
		//     2 (specified in value2).
		//
		//   amount2:
		//     Barycentric coordinate b3, which expresses the weighting factor toward vertex
		//     3 (specified in value3).
		public static IntCoord Barycentric(IntCoord value1, IntCoord value2, IntCoord value3, float amount1, float amount2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a IntCoord containing the 2D Cartesian coordinates of a point specified
		//     in barycentric (areal) coordinates relative to a 2D triangle.
		//
		// Parameters:
		//   value1:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 1 of the triangle.
		//
		//   value2:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 2 of the triangle.
		//
		//   value3:
		//     A IntCoord containing the 2D Cartesian coordinates of vertex 3 of the triangle.
		//
		//   amount1:
		//     Barycentric coordinate b2, which expresses the weighting factor toward vertex
		//     2 (specified in value2).
		//
		//   amount2:
		//     Barycentric coordinate b3, which expresses the weighting factor toward vertex
		//     3 (specified in value3).
		//
		//   result:
		//     [OutAttribute] The 2D Cartesian coordinates of the specified point are placed
		//     in this IntCoord on exit.
		public static void Barycentric(ref IntCoord value1, ref IntCoord value2, ref IntCoord value3, float amount1, float amount2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a Catmull-Rom interpolation using the specified positions.
		//
		// Parameters:
		//   value1:
		//     The first position in the interpolation.
		//
		//   value2:
		//     The second position in the interpolation.
		//
		//   value3:
		//     The third position in the interpolation.
		//
		//   value4:
		//     The fourth position in the interpolation.
		//
		//   amount:
		//     Weighting factor.
		public static IntCoord CatmullRom(IntCoord value1, IntCoord value2, IntCoord value3, IntCoord value4, float amount)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a Catmull-Rom interpolation using the specified positions.
		//
		// Parameters:
		//   value1:
		//     The first position in the interpolation.
		//
		//   value2:
		//     The second position in the interpolation.
		//
		//   value3:
		//     The third position in the interpolation.
		//
		//   value4:
		//     The fourth position in the interpolation.
		//
		//   amount:
		//     Weighting factor.
		//
		//   result:
		//     [OutAttribute] A vector that is the result of the Catmull-Rom interpolation.
		public static void CatmullRom(ref IntCoord value1, ref IntCoord value2, ref IntCoord value3, ref IntCoord value4, float amount, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Restricts a value to be within a specified range.
		//
		// Parameters:
		//   value1:
		//     The value to clamp.
		//
		//   min:
		//     The minimum value.
		//
		//   max:
		//     The maximum value.
		public static IntCoord Clamp(IntCoord value1, IntCoord min, IntCoord max)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Restricts a value to be within a specified range.
		//
		// Parameters:
		//   value1:
		//     The value to clamp.
		//
		//   min:
		//     The minimum value.
		//
		//   max:
		//     The maximum value.
		//
		//   result:
		//     [OutAttribute] The clamped value.
		public static void Clamp(ref IntCoord value1, ref IntCoord min, ref IntCoord max, out IntCoord result)
		{ throw new NotImplementedException(); }
		/// <summary>Clamps a value to the bounds of a given rectangle.
		/// </summary>
		/// <param name="value">value to clamp</param>
		/// <param name="bounds">boundaries for the value</param>
		/// <returns>How much value was changed by.</returns>
		public static IntCoord Clamp(ref IntCoord value, Microsoft.Xna.Framework.Rectangle bounds)
		{ return value.Clamp(bounds); }
		//
		// Summary:
		//     Calculates the distance between two vectors.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static int Distance(IntCoord coord1, IntCoord coord2)
		{ return Distance(coord1.X, coord2.X, coord1.Y, coord2.Y); }
		private static int Distance(IntCoord coord1, int x2, int y2)//STYLE: should the actual coord be first or second?
		{ return Distance(coord1.X, x2, coord1.Y, y2); }
		private static int Distance(int x1, int x2, int y1, int y2)//STYLE: should it be row1,col1,row2,col2 or row1,row2,col1,col2
		{ return Math.Abs(x1 - x2) + Math.Abs(y1 - y2); }
		//
		// Summary:
		//     Calculates the distance between two vectors.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The distance between the vectors.
		public static void Distance(ref IntCoord value1, ref IntCoord value2, out float result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the distance between two vectors squared.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static float DistanceSquared(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the distance between two vectors squared.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The distance between the vectors squared.
		public static void DistanceSquared(ref IntCoord value1, ref IntCoord value2, out float result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Divides a vector by a scalar value.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   divider:
		//     The divisor.
		public static IntCoord Divide(IntCoord value1, float divider)
		{ return new IntCoord((float)value1.X / divider, (float)value1.Y / divider); }
		//
		// Summary:
		//     Divides the components of a vector by the components of another vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Divisor vector.
		public static IntCoord Divide(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Divides a vector by a scalar value.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   divider:
		//     The divisor.
		//
		//   result:
		//     [OutAttribute] The result of the division.
		public static void Divide(ref IntCoord value1, float divider, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Divides the components of a vector by the components of another vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     The divisor.
		//
		//   result:
		//     [OutAttribute] The result of the division.
		public static void Divide(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the dot product of two vectors. If the two vectors are unit vectors,
		//     the dot product returns a floating point value between -1 and 1 that can
		//     be used to determine some properties of the angle between two vectors. For
		//     example, it can show whether the vectors are orthogonal, parallel, or have
		//     an acute or obtuse angle between them.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static float Dot(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the dot product of two vectors and writes the result to a user-specified
		//     variable. If the two vectors are unit vectors, the dot product returns a
		//     floating point value between -1 and 1 that can be used to determine some
		//     properties of the angle between two vectors. For example, it can show whether
		//     the vectors are orthogonal, parallel, or have an acute or obtuse angle between
		//     them.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The dot product of the two vectors.
		public static void Dot(ref IntCoord value1, ref IntCoord value2, out float result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a value that indicates whether the current instance is equal to a
		//     specified object.
		//
		// Parameters:
		//   obj:
		//     Object to make the comparison with.
		public override bool Equals(object obj)
		{
			if (obj == null || GetType() != obj.GetType())
				return false;

			IntCoord cor = (IntCoord)obj;
			return (X == cor.X) && (Y == cor.Y);
			//throw new NotImplementedException(); 
		}
		//
		// Summary:
		//     Determines whether the specified Object is equal to the IntCoord.
		//
		// Parameters:
		//   other:
		//     The Object to compare with the current IntCoord.
		public bool Equals(IntCoord other)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Gets the hash code of the vector object.
		public override int GetHashCode()
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a Hermite spline interpolation.
		//
		// Parameters:
		//   value1:
		//     Source position vector.
		//
		//   tangent1:
		//     Source tangent vector.
		//
		//   value2:
		//     Source position vector.
		//
		//   tangent2:
		//     Source tangent vector.
		//
		//   amount:
		//     Weighting factor.
		public static IntCoord Hermite(IntCoord value1, IntCoord tangent1, IntCoord value2, IntCoord tangent2, float amount)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a Hermite spline interpolation.
		//
		// Parameters:
		//   value1:
		//     Source position vector.
		//
		//   tangent1:
		//     Source tangent vector.
		//
		//   value2:
		//     Source position vector.
		//
		//   tangent2:
		//     Source tangent vector.
		//
		//   amount:
		//     Weighting factor.
		//
		//   result:
		//     [OutAttribute] The result of the Hermite spline interpolation.
		public static void Hermite(ref IntCoord value1, ref IntCoord tangent1, ref IntCoord value2, ref IntCoord tangent2, float amount, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the length of the vector.
		public float Length()
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Calculates the length of the vector squared.
		public float LengthSquared()
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a linear interpolation between two vectors.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   amount:
		//     Value between 0 and 1 indicating the weight of value2.
		public static IntCoord Lerp(IntCoord value1, IntCoord value2, float amount)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Performs a linear interpolation between two vectors.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   amount:
		//     Value between 0 and 1 indicating the weight of value2.
		//
		//   result:
		//     [OutAttribute] The result of the interpolation.
		public static void Lerp(ref IntCoord value1, ref IntCoord value2, float amount, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector that contains the highest value from each matching pair
		//     of components.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static IntCoord Max(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector that contains the highest value from each matching pair
		//     of components.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The maximized vector.
		public static void Max(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector that contains the lowest value from each matching pair of
		//     components.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static IntCoord Min(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector that contains the lowest value from each matching pair of
		//     components.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The minimized vector.
		public static void Min(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		/// <summary>Multiplies a vector by a scalar value.
		/// </summary>
		/// <param name="value1">Source vector.</param>
		/// <param name="scaleFactor"> Scalar value.</param>
		/// <returns></returns>
		public static IntCoord Multiply(IntCoord value1, float scaleFactor)
		{ return new IntCoord(value1.X * scaleFactor, value1.Y * scaleFactor); }
		//
		// Summary:
		//     Multiplies the components of two vectors by each other.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static IntCoord Multiply(IntCoord value1, IntCoord value2)
		{ throw new NotImplementedException(); }
		public static Vector2 Multiply(IntCoord value1, Vector2 value2)//return Vector 2 so precision isn't inherently lost
		{ return (Vector2)value1 * value2; }
		//
		// Summary:
		//     Multiplies a vector by a scalar value.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   scaleFactor:
		//     Scalar value.
		//
		//   result:
		//     [OutAttribute] The result of the multiplication.
		public static void Multiply(ref IntCoord value1, float scaleFactor, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Multiplies the components of two vectors by each other.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The result of the multiplication.
		public static void Multiply(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector pointing in the opposite direction.
		//
		// Parameters:
		//   value:
		//     Source vector.
		public static IntCoord Negate(IntCoord value)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Returns a vector pointing in the opposite direction.
		//
		// Parameters:
		//   value:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] Vector pointing in the opposite direction.
		public static void Negate(ref IntCoord value, out IntCoord result)
		{ throw new NotImplementedException(); }

		/// <summary>Turns the current vector into a unit vector. The result is a vector one unit in length pointing in the same direction as the original vector.
		/// </summary>
		public void Normalize()
		{ throw new NotImplementedException(); }
		/// <summary>Creates a unit vector from the specified vector. The result is a vector one unit in length pointing in the same direction as the original vector.
		/// </summary>
		/// <param name="value">Source IntCoord.</param>
		/// <returns>unit vector</returns>
		public static IntCoord Normalize(IntCoord value)
		{ throw new NotImplementedException(); }
		/// <summary>Creates a unit vector from the specified vector, writing the result to a user-specified variable. The result is a vector one unit in length pointing in the same direction as the original vector.
		/// </summary>
		/// <param name="value">Source IntCoord.</param>
		/// <param name="result">[OutAttribute] Normalized vector.</param>
		public static void Normalize(ref IntCoord value, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Determines the reflect vector of the given vector and normal.
		//
		// Parameters:
		//   vector:
		//     Source vector.
		//
		//   normal:
		//     Normal of vector.
		public static IntCoord Reflect(IntCoord vector, IntCoord normal)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Determines the reflect vector of the given vector and normal.
		//
		// Parameters:
		//   vector:
		//     Source vector.
		//
		//   normal:
		//     Normal of vector.
		//
		//   result:
		//     [OutAttribute] The created reflect vector.
		public static void Reflect(ref IntCoord vector, ref IntCoord normal, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Interpolates between two values using a cubic equation.
		//
		// Parameters:
		//   value1:
		//     Source value.
		//
		//   value2:
		//     Source value.
		//
		//   amount:
		//     Weighting value.
		public static IntCoord SmoothStep(IntCoord value1, IntCoord value2, float amount)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Interpolates between two values using a cubic equation.
		//
		// Parameters:
		//   value1:
		//     Source value.
		//
		//   value2:
		//     Source value.
		//
		//   amount:
		//     Weighting value.
		//
		//   result:
		//     [OutAttribute] The interpolated value.
		public static void SmoothStep(ref IntCoord value1, ref IntCoord value2, float amount, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Subtracts a vector from a vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		public static IntCoord Subtract(IntCoord value1, IntCoord value2)
		{ return new IntCoord(value1.X - value2.X, value1.Y - value2.Y); }
		/// <summary>Subtracts an integer from both values in an integer coordinate
		/// </summary>
		/// <param name="value1"></param>
		/// <param name="value2"></param>
		/// <returns></returns>
		public static IntCoord Subtract(IntCoord value1, int value2)
		{ return new IntCoord(value1.X - value2, value1.Y - value2); }
		//
		// Summary:
		//     Subtracts a vector from a vector.
		//
		// Parameters:
		//   value1:
		//     Source vector.
		//
		//   value2:
		//     Source vector.
		//
		//   result:
		//     [OutAttribute] The result of the subtraction.
		public static void Subtract(ref IntCoord value1, ref IntCoord value2, out IntCoord result)
		{ throw new NotImplementedException(); }
		//
		// Summary:
		//     Retrieves a string representation of the current object.
		public override string ToString()
		{
			//return String.Format('{'+"X:{0} Y:{1}"+'}',X,Y);
			return "{X:" + X + " Y:" + Y + "}";
			//throw new NotImplementedException(); 
		}

		/*Transformation Functions (have dependancies which are a not included)
		//
		// Summary:
		//     Transforms the vector (x, y, 0, 1) by the specified matrix.
		//
		// Parameters:
		//   position:
		//     The source vector.
		//
		//   matrix:
		//     The transformation matrix.
		//public static IntCoord Transform(IntCoord position, Matrix matrix);
		public static IntCoord Transform(IntCoord position)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms a single IntCoord, or the vector normal (x, y, 0, 0), by a specified
		//     Quaternion rotation.
		//
		// Parameters:
		//   value:
		//     The vector to rotate.
		//
		//   rotation:
		//     The Quaternion rotation to apply.
		//public static IntCoord Transform(IntCoord value, Quaternion rotation);
		public static IntCoord Transform(IntCoord value, MissingType Quaternion)
		{ throw new MissingMemberException("Has not added Quaternion"); }
		//
		// Summary:
		//     Transforms a IntCoord by the given Matrix.
		//
		// Parameters:
		//   position:
		//     The source IntCoord.
		//
		//   matrix:
		//     The transformation Matrix.
		//
		//   result:
		//     [OutAttribute] The IntCoord resulting from the transformation.
		//public static void Transform(ref IntCoord position, ref Matrix matrix, out IntCoord result);
		public static IntCoord Transform(IntCoord position, out IntCoord result)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms a IntCoord, or the vector normal (x, y, 0, 0), by a specified Quaternion
		//     rotation.
		//
		// Parameters:
		//   value:
		//     The vector to rotate.
		//
		//   rotation:
		//     The Quaternion rotation to apply.
		//
		//   result:
		//     [OutAttribute] An existing IntCoord filled in with the result of the rotation.
		//public static void Transform(ref IntCoord value, ref Quaternion rotation, out IntCoord result);
		public static void Transform(ref IntCoord value, out IntCoord result)
		{ throw new MissingMemberException("Has not added Quaternion"); }
		//
		// Summary:
		//     Transforms an array of IntCoords by a specified Matrix.
		//
		// Parameters:
		//   sourceArray:
		//     The array of IntCoords to transform.
		//
		//   matrix:
		//     The transform Matrix to apply.
		//
		//   destinationArray:
		//     An existing array into which the transformed IntCoords are written.
		//public static void Transform(IntCoord[] sourceArray, ref Matrix matrix, IntCoord[] destinationArray);
		public static void Transform(IntCoord position, IntCoord[] destinationArray)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms an array of IntCoords by a specified Quaternion.
		//
		// Parameters:
		//   sourceArray:
		//     The array of IntCoords to transform.
		//
		//   rotation:
		//     The transform Matrix to use.
		//
		//   destinationArray:
		//     An existing array into which the transformed IntCoords are written.
		//public static void Transform(IntCoord[] sourceArray, ref Quaternion rotation, IntCoord[] destinationArray);
		public static void Transform(IntCoord[] sourceArray, IntCoord[] destinationArray)
		{ throw new MissingMemberException("Has not added Quaternion"); }
		//
		// Summary:
		//     Transforms a specified range in an array of IntCoords by a specified Matrix
		//     and places the results in a specified range in a destination array.
		//
		// Parameters:
		//   sourceArray:
		//     The source array.
		//
		//   sourceIndex:
		//     The index of the first IntCoord to transform in the source array.
		//
		//   matrix:
		//     The Matrix to transform by.
		//
		//   destinationArray:
		//     The destination array into which the resulting IntCoords will be written.
		//
		//   destinationIndex:
		//     The index of the position in the destination array where the first result
		//     IntCoord should be written.
		//
		//   length:
		//     The number of IntCoords to be transformed.
		//public static void Transform(IntCoord[] sourceArray, int sourceIndex, ref Matrix matrix, IntCoord[] destinationArray, int destinationIndex, int length);
		public static void Transform(IntCoord[] sourceArray, int sourceIndex, IntCoord[] destinationArray, int destinationIndex, int length)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms a specified range in an array of IntCoords by a specified Quaternion
		//     and places the results in a specified range in a destination array.
		//
		// Parameters:
		//   sourceArray:
		//     The source array.
		//
		//   sourceIndex:
		//     The index of the first IntCoord to transform in the source array.
		//
		//   rotation:
		//     The Quaternion rotation to apply.
		//
		//   destinationArray:
		//     The destination array into which the resulting IntCoords are written.
		//
		//   destinationIndex:
		//     The index of the position in the destination array where the first result
		//     IntCoord should be written.
		//
		//   length:
		//     The number of IntCoords to be transformed.
		//public static void Transform(IntCoord[] sourceArray, int sourceIndex, ref Quaternion rotation, IntCoord[] destinationArray, int destinationIndex, int length);
		public static void Transform(IntCoord[] sourceArray, int sourceIndex, ref MissingType Quaternion, IntCoord[] destinationArray, int destinationIndex, int length)
		{ throw new MissingMemberException("Has not added Quaternion"); }
		//
		// Summary:
		//     Transforms a 2D vector normal by a matrix.
		//
		// Parameters:
		//   normal:
		//     The source vector.
		//
		//   matrix:
		//     The transformation matrix.
		//public static IntCoord TransformNormal(IntCoord normal, Matrix matrix);
		public static IntCoord TransformNormal(IntCoord normal)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms a vector normal by a matrix.
		//
		// Parameters:
		//   normal:
		//     The source vector.
		//
		//   matrix:
		//     The transformation matrix.
		//
		//   result:
		//     [OutAttribute] The IntCoord resulting from the transformation.
		//public static void TransformNormal(ref IntCoord normal, ref Matrix matrix, out IntCoord result);
		public static void TransformNormal(ref IntCoord normal, out IntCoord result)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms an array of IntCoord vector normals by a specified Matrix.
		//
		// Parameters:
		//   sourceArray:
		//     The array of vector normals to transform.
		//
		//   matrix:
		//     The transform Matrix to apply.
		//
		//   destinationArray:
		//     An existing array into which the transformed vector normals are written.
		//public static void TransformNormal(IntCoord[] sourceArray, ref Matrix matrix, IntCoord[] destinationArray);
		public static void TransformNormal(IntCoord[] sourceArray, IntCoord[] destinationArray)
		{ throw new MissingMemberException("Has not added Matrix"); }
		//
		// Summary:
		//     Transforms a specified range in an array of IntCoord vector normals by a specified
		//     Matrix and places the results in a specified range in a destination array.
		//
		// Parameters:
		//   sourceArray:
		//     The source array.
		//
		//   sourceIndex:
		//     The index of the first IntCoord to transform in the source array.
		//
		//   matrix:
		//     The Matrix to apply.
		//
		//   destinationArray:
		//     The destination array into which the resulting IntCoords are written.
		//
		//   destinationIndex:
		//     The index of the position in the destination array where the first result
		//     IntCoord should be written.
		//
		//   length:
		//     The number of vector normals to be transformed.
		//public static void TransformNormal(IntCoord[] sourceArray, int sourceIndex, ref Matrix matrix, IntCoord[] destinationArray, int destinationIndex, int length);
		public static void TransformNormal(IntCoord[] sourceArray, int sourceIndex, IntCoord[] destinationArray, int destinationIndex, int length)
		{ throw new MissingMemberException("Has not added Matrix"); }
		*/
	};
}