#pragma once

#include<stdio.h>
#include<stdlib.h>

namespace Engine {
	class Point2D
	{
	public:
		Point2D(float i_X, float i_Y) :
			m_x(i_X),
			m_y(i_Y)
		{}

	Point2D(): m_x(0), m_y(0)
	{}

		//getters
		float X() const {
			return m_x;
		}

		float Y() const {
			return m_y;
		}

		//setters
		void X(float i_X) {
			m_x = i_X;
		}

		void Y(float i_Y) {
			m_y = i_Y;
		}

		Point2D operator+(Point2D& addn);
		Point2D operator-(Point2D& subsn);
		Point2D operator*(int mult);
		Point2D operator/(int divi);
		Point2D operator-();

		Point2D operator+=(Point2D other);
		Point2D operator-=(Point2D other);
		Point2D operator*=(int other);
		Point2D operator/=(int other);
		bool operator==(Point2D other);
		bool operator!=(Point2D other);
		
	private:
		float m_x, m_y;
	};

	Point2D operator*(int first, Point2D& second);
}
