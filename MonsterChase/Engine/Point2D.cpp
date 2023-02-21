#include "Math/Point2D.h"

#include <stdio.h>
#include<stdlib.h>

namespace Engine 
{
		Point2D Point2D::operator+(Point2D& addn)
		{
			return Point2D(m_x + addn.X(), m_y + addn.Y());
		}
		

		Point2D Point2D::operator-(Point2D& subn)
		{
			return Point2D(m_x - subn.X(), m_y - subn.Y());
		}

		Point2D Point2D::operator/(int other)
		{
			return Point2D(m_x / other, m_y / other);
		}

		Point2D Point2D::operator-()
		{
			return Point2D(-m_x, -m_y);
		}

		Point2D Point2D::operator*(int other)
		{
			return Point2D(m_x * other, m_y * other);
		}

		Point2D Point2D::operator+=(Point2D other)
		{
			m_x += other.X();
			m_y += other.Y();
			return *this;
		}
		Point2D Point2D::operator-=(Point2D other)
		{
			m_x -= other.X();
			m_y -= other.Y();
			return *this;
		}
		Point2D Point2D::operator*=(int other)
		{
			m_x *= other;
			m_y *= other;
			return *this;
		}
		Point2D Point2D::operator/=(int other)
		{
			m_x /= other;
			m_y /= other;
			return *this;
		}
		bool Point2D::operator==(Point2D other)
		{
			if (m_x == other.X() && m_y == other.Y())
			{
				return true;
			}
			else
				return false;

		}
		bool Point2D::operator!=(Point2D other)
		{
			if (m_x != other.X() || m_y != other.Y())
			{
				return true;
			}
			else
				return false;
		}		

		Point2D operator*(int first, Point2D& second)
		{
			return Point2D(second * first);
		}
}