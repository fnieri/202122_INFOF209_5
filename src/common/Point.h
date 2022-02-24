#pragma once

#include "Stringable.h"

/**
 * Coordinate in the plan
 *
 * Since the x and y getters a expected to be used
 * very often, a short form was given for them to be less
 * verbose than, for instance, getX().
 */
class Point : public Stringable
{
public:
    constexpr Point(const int &_x = 0, const int &_y = 0)
        : m_x {_x}
        , m_y {_y}
    {
    }

    constexpr inline int x() const noexcept
    {
        return m_x;
    }
    constexpr inline int y() const noexcept
    {
        return m_y;
    }

    constexpr void x(const int &_x) noexcept
    {
        m_x = _x;
    }
    constexpr void y(const int &_y) noexcept
    {
        m_y = _y;
    }

    explicit operator std::string() const noexcept override;

    Point operator+(const Point &) const noexcept;
    Point operator-(const Point &) const noexcept;
    Point operator*(const int &) const noexcept;
    Point operator/(const int &) const;

    bool operator==(const Point &) const noexcept;

protected:
    int m_x;
    int m_y;
};