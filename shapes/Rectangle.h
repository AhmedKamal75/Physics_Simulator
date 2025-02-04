#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"


class Rectangle : public Shape, public std::enable_shared_from_this<Rectangle> {
    private:
        std::shared_ptr<Point> upper_left;
        std::shared_ptr<Point> lower_right;
        std::shared_ptr<Point> upper_right;
        std::shared_ptr<Point> lower_left;

    public:
        Rectangle(std::shared_ptr<Point> upper_left, std::shared_ptr<Point> lower_right);
        std::shared_ptr<Point> get_upper_left() const;
        std::shared_ptr<Point> get_lower_right() const;
        std::shared_ptr<Point> get_upper_right() const;
        std::shared_ptr<Point> get_lower_left() const;
        double area() const;
        double perimeter() const;
        std::shared_ptr<Rectangle> clone() const;
        std::shared_ptr<Rectangle> move(const std::shared_ptr<Point> offset);
        std::shared_ptr<Rectangle> scale(const double factor);
        std::shared_ptr<Rectangle> rotate(const std::shared_ptr<Point> center, const double angle);
        std::shared_ptr<Rectangle> rotate_origin(const double angle);
        std::shared_ptr<Rectangle> rotate_center(const double angle);
        bool is_equal(const std::shared_ptr<Rectangle> other) const;
        bool contains(const std::shared_ptr<Point> point) const;
        bool between_bounds(const std::shared_ptr<Point> point) const;
        std::string to_string() const;
        std::shared_ptr<Point> centroid() const;
        std::shared_ptr<sf::ConvexShape> to_convex_shape(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thickness) const;
};


#endif // RECTANGLE_H