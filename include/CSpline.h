/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003 Tommy van der Vorst

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
--------------------------------------------------------------------------------------------------------------------------------------------------- */
#ifndef __CACTUS_CSPLINE_H
#define __CACTUS_CSPLINE_H

/**  A very simple spline class which implements the Catmull-Rom class of splines. 
@remarks
	Splines are bendy lines. You define a series of points, and the spline forms a smoother line between the 
	points to eliminate the sharp angles.
@par
	Catmull-Rom splines are a specialisation of the general Hermite spline. With a Hermite spline, you define the start 
	and end point of a spline and 2 tangents. The Catmull-Rom spline simplifies this by just asking you to define 
	a series of points. The tangents will be created for you.
**/

class CACTUS_API CSpline {
	public:
		CSpline();
		~CSpline();

		/// Adds a control point to the spline
		void AddPoint(const CVector& p);

		/// Returns a single point on the line
		const CVector& GetPoint(unsigned short index) const;

		/// Returns the number of points defined
		unsigned short CountPoints(void) const;

		/// Clears all defined points
		void Clear(void);

		/// Updates the defined point at the specified index
		void UpdatePoint(unsigned short index, const CVector& value);

		/** Returns an interpolated point based on a parametric value over the whole series. 
		@remarks
			Given a t value between 0 and 1 representing the parametric distance along the whole length
			of the spline, this method returns an interpolated point.
		@param t Parametric value between 0 and 1 **/
		CVector Interpolate(float t);

		/** Interpolates a single segment of the spline given a parametric value. 
		@param fromIndex The point index to treat as t=0. fromIndex+1 is deemed to be t=1 
		@param t Parametric value between 0 and 1 **/
		CVector Interpolate(unsigned int fromIndex, float t);

		/** Tells the spline whether it should recalculate tangents when a new control point is added. **/
		void SetAutoCalculate(bool a);

		/** Recalculate all tangents
		@remarks
			If you call SetAutoCalculate(false); on a spline, you will have to call this after completing your
			updates to the spline points.**/
		void RecalculateTangents();
	protected:
		bool _autoCalculate;
		std::vector<CVector> _points;
		std::vector<CVector> _tangents;
		CMatrix _coeffs;

	private: 
		CMatrix _matrix;
};

#endif