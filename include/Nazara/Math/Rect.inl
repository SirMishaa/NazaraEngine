// Copyright (C) 2024 Jérôme "SirLynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Math module"
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <Nazara/Core/StringExt.hpp>
#include <NazaraUtils/MathUtils.hpp>
#include <algorithm>
#include <cstring>
#include <sstream>

namespace Nz
{
	/*!
	* \ingroup math
	* \class Nz::Rect
	* \brief Math class that represents an axis-aligned rectangle in two dimensions
	*
	* \remark The basis is said to be "left-hand". It means that with your left hand, the thumb is X positive, the index finger Y positive pointing to the bottom
	*/

	/*!
	* \brief Constructs a Rect object from its width and height
	*
	* \param Width Width of the rectangle (following X)
	* \param Height Height of the rectangle (following Y)
	*
	* \remark Position will be (0, 0)
	*/
	template<typename T>
	constexpr Rect<T>::Rect(T Width, T Height) :
	x(0),
	y(0),
	width(Width),
	height(Height)
	{
	}

	/*!
	* \brief Constructs a Rect object from its position, width and height
	*
	* \param X X position
	* \param Y Y position
	* \param Width Width of the rectangle (following X)
	* \param Height Height of the rectangle (following Y)
	*/
	template<typename T>
	constexpr Rect<T>::Rect(T X, T Y, T Width, T Height) :
	x(X),
	y(Y),
	width(Width),
	height(Height)
	{
	}

	/*!
	* \brief Constructs a Rect object from a vector representing its length
	* The position will be set to zero
	*
	* \param lengths (Width, Height) of the rect
	*/
	template<typename T>
	constexpr Rect<T>::Rect(const Vector2<T>& lengths) :
	Rect(Vector2<T>::Zero(), lengths)
	{
	}

	/*!
	* \brief Constructs a Rect object from two vector representing position and lengths
	*
	* \param pos (X, Y) of the rect
	* \param lengths (Width, Height) of the rect
	*/
	template<typename T>
	constexpr Rect<T>::Rect(const Vector2<T>& pos, const Vector2<T>& lengths) :
	x(pos.x),
	y(pos.y),
	width(lengths.x),
	height(lengths.y)
	{
	}

	/*!
	* \brief Constructs a Rect object from another type of Rect
	*
	* \param rect Rect of type U to convert to type T
	*/

	template<typename T>
	template<typename U>
	constexpr Rect<T>::Rect(const Rect<U>& rect) :
	x(static_cast<T>(rect.x)),
	y(static_cast<T>(rect.y)),
	width(static_cast<T>(rect.width)),
	height(static_cast<T>(rect.height))
	{
	}

	template<typename T>
	constexpr bool Rect<T>::ApproxEqual(const Rect& rect, T maxDifference) const
	{
		return NumberEquals(x, rect.x, maxDifference) && NumberEquals(y, rect.y, maxDifference) &&
		       NumberEquals(width, rect.width, maxDifference) && NumberEquals(height, rect.height, maxDifference);
	}

	/*!
	* \brief Tests whether the rectangle contains the provided point inclusive of the edge of the rectangle
	* \return true if inclusive
	*
	* \param X X position of the point
	* \param Y Y position of the point
	*
	* \see Contains
	*/
	template<typename T>
	constexpr bool Rect<T>::Contains(T X, T Y) const
	{
		return X >= GetMinX() && X < GetMaxX() &&
		       Y >= GetMinY() && Y < GetMaxY();
	}

	/*!
	* \brief Tests whether the rectangle contains the provided rectangle inclusive of the edge of the rectangle
	* \return true if inclusive
	*
	* \param rect Other rectangle to test
	*
	* \see Contains
	*/
	template<typename T>
	constexpr bool Rect<T>::Contains(const Rect<T>& rect) const
	{
		return Contains(rect.GetMinX(), rect.GetMinY()) &&
		       Contains(rect.GetMaxX(), rect.GetMaxY());
	}

	/*!
	* \brief Tests whether the rectangle contains the provided point inclusive of the edge of the rectangle
	* \return true if inclusive
	*
	* \param point Position of the point
	*
	* \see Contains
	*/
	template<typename T>
	constexpr bool Rect<T>::Contains(const Vector2<T>& point) const
	{
		return Contains(point.x, point.y);
	}

	/*!
	* \brief Extends the rectangle to contain the point in the boundary
	* \return A reference to this rectangle extended
	*
	* \param X X position of the point
	* \param Y Y position of the point
	*
	* \see ExtendTo
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::ExtendTo(T X, T Y)
	{
		width = std::max(GetMaxX(), X);
		height = std::max(GetMaxY(), Y);

		x = std::min(GetMinX(), X);
		y = std::min(GetMinY(), Y);

		width -= x;
		height -= y;

		return *this;
	}

	/*!
	* \brief Extends the rectangle to contain the rectangle
	* \return A reference to this rectangle extended
	*
	* \param rect Other rectangle to contain
	*
	* \see ExtendTo
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::ExtendTo(const Rect& rect)
	{
		width = std::max(GetMaxX(), rect.GetMaxX());
		height = std::max(GetMaxY(), rect.GetMaxY());

		x = std::min(GetMinX(), rect.GetMinX());
		y = std::min(GetMinY(), rect.GetMinY());

		width -= x;
		height -= y;

		return *this;
	}

	/*!
	* \brief Extends the rectangle to contain the point in the boundary
	* \return A reference to this rectangle extended
	*
	* \param point Position of the point
	*
	* \see ExtendTo
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::ExtendTo(const Vector2<T>& point)
	{
		return ExtendTo(point.x, point.y);
	}

	/*!
	* \brief Gets a Vector2 for the center
	* \return The position of the center of the rectangle
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetCenter() const
	{
		return GetPosition() + GetLengths() / T(2.0);
	}

	/*!
	* \brief Gets the Vector2 for the corner
	* \return The position of the corner of the rectangle according to enum RectCorner
	*
	* \param corner Enumeration of type RectCorner
	*
	* \remark If enumeration is not defined in RectCorner, a NazaraError is thrown and a Vector2 uninitialised is returned
	*/
	template<typename T>
	template<CoordinateSystem CS>
	constexpr Vector2<T> Rect<T>::GetCorner(RectCorner corner) const
	{
		if constexpr (CS == CoordinateSystem::Cartesian)
		{
			switch (corner)
			{
				case RectCorner::LeftBottom:
					return Vector2<T>(GetMinX(), GetMinY());

				case RectCorner::LeftTop:
					return Vector2<T>(GetMinX(), GetMaxY());

				case RectCorner::RightBottom:
					return Vector2<T>(GetMaxX(), GetMinY());

				case RectCorner::RightTop:
					return Vector2<T>(GetMaxX(), GetMaxY());
			}
		}
		else if constexpr (CS == CoordinateSystem::Screen)
		{
			switch (corner)
			{
				case RectCorner::LeftBottom:
					return Vector2<T>(GetMinX(), GetMaxY());

				case RectCorner::LeftTop:
					return Vector2<T>(GetMinX(), GetMinY());

				case RectCorner::RightBottom:
					return Vector2<T>(GetMaxX(), GetMaxY());

				case RectCorner::RightTop:
					return Vector2<T>(GetMaxX(), GetMinY());
			}
		}
		else
			static_assert(AlwaysFalseValue<CS>(), "unhandled coordinate system");

		NAZARA_UNREACHABLE();
	}

	template<typename T>
	template<CoordinateSystem CS>
	constexpr EnumArray<RectCorner, Vector2<T>> Rect<T>::GetCorners() const
	{
		return {
			GetCorner<CS>(RectCorner::LeftBottom),
			GetCorner<CS>(RectCorner::LeftTop),
			GetCorner<CS>(RectCorner::RightBottom),
			GetCorner<CS>(RectCorner::RightTop)
		};
	}

	/*!
	* \brief Gets a Vector2 for the lengths
	* \return The lengths of the rectangle (width, height)
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetLengths() const
	{
		return Vector2<T>(width, height);
	}

	/*!
	* \brief Gets a Vector2 for the maximum point
	* \return The RectCorner::RightBottom of the rectangle
	*
	* \see GetCorner
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetMaximum() const
	{
		return { GetMaxX(), GetMaxY() };
	}

	template<typename T>
	constexpr T Rect<T>::GetMaxX() const
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			if (IsInfinity(width))
				return Infinity();
		}

		return x + width;
	}

	template<typename T>
	constexpr T Rect<T>::GetMaxY() const
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			if (IsInfinity(height))
				return Infinity();
		}

		return y + height;
	}

	/*!
	* \brief Gets a Vector2 for the minimum point
	* \return The RectCorner::LeftTop of the rectangle
	*
	* \see GetCorner, GetPosition
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetMinimum() const
	{
		return { GetMinX(), GetMinY() };
	}

	template<typename T>
	constexpr T Rect<T>::GetMinX() const
	{
		return x;
	}

	template<typename T>
	constexpr T Rect<T>::GetMinY() const
	{
		return y;
	}

	/*!
	* \brief Computes the negative vertex of one direction
	* \return The position of the vertex on the rectangle in the opposite way of the normal while considering the center. It means that if the normal has one component negative, the component is set to width or height corresponding to the sign
	*
	* \param normal Vector indicating a direction
	*
	* \see GetPositiveVertex
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetNegativeVertex(const Vector2<T>& normal) const
	{
		Vector2<T> neg;
		neg.x = (normal.x < T(0.0)) ? GetMaxX() : GetMinX();
		neg.y = (normal.y < T(0.0)) ? GetMaxY() : GetMinY();

		return neg;
	}

	/*!
	* \brief Gets a Vector2 for the position
	* \return The RectCorner::LeftTop of the rectangle
	*
	* \see GetCorner, GetMinimum
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetPosition() const
	{
		return Vector2<T>(GetMinX(), GetMaxY());
	}

	/*!
	* \brief Computes the positive vertex of one direction
	* \return The position of the vertex on the rectangle in the same way of the normal while considering the center. It means that if the normal has one component positive, the component is set to width or height corresponding to the sign
	*
	* \param normal Vector indicating a direction
	*
	* \see GetNegativeVertex
	*/
	template<typename T>
	constexpr Vector2<T> Rect<T>::GetPositiveVertex(const Vector2<T>& normal) const
	{
		Vector2<T> pos;
		pos.x = (normal.x > T(0.0)) ? GetMaxX() : GetMinX();
		pos.y = (normal.y > T(0.0)) ? GetMaxY() : GetMinY();

		return pos;
	}

	/*!
	* \brief Checks whether or not this rectangle intersects another one
	* \return true if the rectangle intersects
	*
	* \param rect Rectangle to check
	* \param intersection Optional argument for the rectangle which represent the intersection
	*/
	template<typename T>
	constexpr bool Rect<T>::Intersect(const Rect& rect, Rect* intersection) const
	{
		T minX = std::max(GetMinX(), rect.GetMinX());
		T maxX = std::min(GetMaxX(), rect.GetMaxX());
		T minY = std::max(GetMinY(), rect.GetMinY());
		T maxY = std::min(GetMaxY(), rect.GetMaxY());

		if (minX > maxX || minY > maxY)
			return false;

		if (intersection)
		{
			intersection->x = minX;
			intersection->y = minY;
			if constexpr (std::is_floating_point_v<T>)
			{
				intersection->width = (IsInfinity(maxX)) ? Infinity<T>() : maxX - minX;
				intersection->height = (IsInfinity(minY)) ? Infinity<T>() : maxY - minY;
			}
			else
			{
				intersection->width = maxX - minX;
				intersection->height = maxY - minY;
			}
		}

		return true;
	}

	/*!
	* \brief Checks whether this rectangle is valid
	* \return true if the rectangle has a positive width and height
	*/
	template<typename T>
	constexpr bool Rect<T>::IsNull() const
	{
		return width <= T(0.0) && height <= T(0.0);
	}

	/*!
	* \brief Checks whether this rectangle is valid
	* \return true if the rectangle has a positive width and height
	*/
	template<typename T>
	constexpr bool Rect<T>::IsValid() const
	{
		return width >= T(0.0) && height >= T(0.0);
	}

	/*!
	* \brief Multiplies the lengths of this rectangle with the scalar
	* \return A reference to this rectangle where lengths are the product of these lengths and the scalar
	*
	* \param scalar The scalar to multiply width and height with
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::Scale(T scalar)
	{
		width *= scalar;
		height *= scalar;

		return *this;
	}

	/*!
	* \brief Multiplies the lengths of this rectangle with the vector
	* \return A reference to this rectangle where width and height are the product of the old width and height with the vec
	*
	* \param vec The vector where component one multiply width and two height
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::Scale(const Vector2<T>& vec)
	{
		width *= vec.x;
		height *= vec.y;

		return *this;
	}

	/*!
	* \brief Multiplies the lengths of this box with the scalar (the box center doesn't move)
	* \return A reference to this box where lengths are the product of these lengths and the scalar
	*
	* \param scalar The scalar to multiply width, height and depth with
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::ScaleAroundCenter(T scalar)
	{
		x -= (width * scalar - width) / T(2.0);
		y -= (height * scalar - height) / T(2.0);

		width *= scalar;
		height *= scalar;

		return *this;
	}

	/*!
	* \brief Multiplies the lengths of this box with the vector but changes the origin (the box center doesn't move)
	* \return A reference to this box where width, height and depth are the product of the old width,  height and depth with the vec
	*
	* \param vec The vector where component one multiply width, two height and three depth
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::ScaleAroundCenter(const Vector2<T>& vec)
	{
		x -= (width * vec.x - width) / T(2.0);
		y -= (height * vec.y - height) / T(2.0);

		width *= vec.x;
		height *= vec.y;

		return *this;
	}

	/*!
	* \brief Gives a string representation
	* \return A string representation of the object: "Rect(x, y, width, height)"
	*/

	template<typename T>
	std::string Rect<T>::ToString() const
	{
		std::ostringstream ss;
		ss << *this;

		return ss.str();
	}

	/*!
	* \brief Translates the rectangle
	* \return A reference to this rectangle translated
	*
	* \param translation Vector2 which is the translation for the position
	*/
	template<typename T>
	constexpr Rect<T>& Rect<T>::Translate(const Vector2<T>& translation)
	{
		x += translation.x;
		y += translation.y;

		return *this;
	}

	/*!
	* \brief Returns the ith element of the rectangle
	* \return A reference to the ith element of the rectangle
	*
	* \remark Access to index greather than 4 is undefined behavior
	*/
	template<typename T>
	constexpr T& Rect<T>::operator[](std::size_t i)
	{
		NazaraAssert(i < 4, "Index out of range");

		return *(&x+i);
	}

	/*!
	* \brief Returns the ith element of the rectangle
	* \return A value to the ith element of the rectangle
	*
	* \remark Access to index greater than 4 is undefined behavior
	*/
	template<typename T>
	constexpr const T& Rect<T>::operator[](std::size_t i) const
	{
		NazaraAssert(i < 4, "Index out of range");

		return *(&x+i);
	}

	/*!
	* \brief Compares the rectangle to other one
	* \return true if the rectangles are the same
	*
	* \param rect Other rectangle to compare with
	*/

	template<typename T>
	constexpr bool Rect<T>::operator==(const Rect& rect) const
	{
		return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
	}

	/*!
	* \brief Compares the rectangle to other one
	* \return false if the rectangles are the same
	*
	* \param rect Other rectangle to compare with
	*/
	template<typename T>
	constexpr bool Rect<T>::operator!=(const Rect& rect) const
	{
		return !operator==(rect);
	}

	template<typename T>
	constexpr bool Rect<T>::ApproxEqual(const Rect& lhs, const Rect& rhs, T maxDifference)
	{
		return lhs.ApproxEqual(rhs, maxDifference);
	}

	/*!
	* \brief Sets a Rect object from two vectors representing point of the space
	* (X, Y) will be the components minimum of the two vectors and the width and height will be the components maximum - minimum
	* \return A reference to this rectangle
	*
	* \param vec1 First point
	* \param vec2 Second point
	*/
	template<typename T>
	constexpr Rect<T> Rect<T>::FromExtends(const Vector2<T>& vec1, const Vector2<T>& vec2)
	{
		Rect rect;
		rect.x = std::min(vec1.x, vec2.x);
		rect.y = std::min(vec1.y, vec2.y);
		rect.width = (vec2.x > vec1.x) ? vec2.x - vec1.x : vec1.x - vec2.x;
		rect.height = (vec2.y > vec1.y) ? vec2.y - vec1.y : vec1.y - vec2.y;

		return rect;
	}

	/*!
	* \brief Interpolates the rectangle to other one with a factor of interpolation
	* \return A new rectangle which is the interpolation of two rectangles
	*
	* \param from Initial rectangle
	* \param to Target rectangle
	* \param interpolation Factor of interpolation
	*
	* \see Lerp
	*/
	template<typename T>
	constexpr Rect<T> Rect<T>::Lerp(const Rect& from, const Rect& to, T interpolation)
	{
		Rect rect;
		rect.x = Nz::Lerp(from.x, to.x, interpolation);
		rect.y = Nz::Lerp(from.y, to.y, interpolation);
		rect.width = Nz::Lerp(from.width, to.width, interpolation);
		rect.height = Nz::Lerp(from.height, to.height, interpolation);

		return rect;
	}

	/*!
	* \brief Shorthand for the rectangle (0, 0, 0, 0)
	* \return A rectangle with position (0, 0) and lengths (0, 0)
	*/
	template<typename T>
	constexpr Rect<T> Rect<T>::Invalid()
	{
		return Rect(-1, -1, -1, -1);
	}

	/*!
	* \brief Shorthand for the rectangle (0, 0, 0, 0)
	* \return A rectangle with position (0, 0) and lengths (0, 0)
	*/
	template<typename T>
	constexpr Rect<T> Rect<T>::Zero()
	{
		return Rect(0, 0, 0, 0);
	}

	/*!
	* \brief Serializes a Rect
	* \return true if successfully serialized
	*
	* \param context Serialization context
	* \param rect Input Rect
	*/
	template<typename T>
	bool Serialize(SerializationContext& context, const Rect<T>& rect, TypeTag<Rect<T>>)
	{
		if (!Serialize(context, rect.x))
			return false;

		if (!Serialize(context, rect.y))
			return false;

		if (!Serialize(context, rect.width))
			return false;

		if (!Serialize(context, rect.height))
			return false;

		return true;
	}

	/*!
	* \brief Deserializes a Rect
	* \return true if successfully deserialized
	*
	* \param context Serialization context
	* \param rect Output Rect
	*/
	template<typename T>
	bool Deserialize(SerializationContext& context, Rect<T>* rect, TypeTag<Rect<T>>)
	{
		if (!Deserialize(context, &rect->x))
			return false;

		if (!Deserialize(context, &rect->y))
			return false;

		if (!Deserialize(context, &rect->width))
			return false;

		if (!Deserialize(context, &rect->height))
			return false;

		return true;
	}

	/*!
	* \brief Output operator
	* \return The stream
	*
	* \param out The stream
	* \param rect The rectangle to output
	*/

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Nz::Rect<T>& rect)
	{
		return out << "Rect(" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << ')';
	}
}

