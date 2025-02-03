#ifndef POINT_H
#define POINT_H

#include "Shape.h"

class Point : public Shape, public std::enable_shared_from_this<Point> {
    private:
        double x; 
        double y;

    public:
        Point(double x = 0.0, double y = 0.0);
        double get_x() const;
        double get_y() const;
        void set_x(double x);
        void set_y(double y);

        double distance_to(const std::shared_ptr<Point> other) const;
        
        std::shared_ptr<Point> clone() const;
        std::shared_ptr<Point> set(const double x, const double y);
        std::shared_ptr<Point> set(const std::shared_ptr<Point> other);
        std::shared_ptr<Point> move(const double dx, const double dy);
        std::shared_ptr<Point> add(const std::shared_ptr<Point> other);
        std::shared_ptr<Point> subtract(const std::shared_ptr<Point> other);
        std::shared_ptr<Point> multiply(const double factor);
        std::shared_ptr<Point> divide(const double factor);
        double dot(const std::shared_ptr<Point> other) const;
        double magnitude() const;
        double angle() const;
        std::shared_ptr<Point> reflect_over_x() const;
        std::shared_ptr<Point> reflect_over_y() const;
        std::shared_ptr<Point> reflect_over_origin() const;
        std::shared_ptr<Point> scale(const double factor);
        std::shared_ptr<Point> normalize();
        std::shared_ptr<Point> rotate(const std::shared_ptr<Point> center, const double angle);
        std::shared_ptr<Point> rotate_origin(const double angle);
        std::shared_ptr<Point> mid_point_to(const std::shared_ptr<Point> other) const;
        std::shared_ptr<sf::Vector2f> to_vector2f() const;
        std::shared_ptr<sf::CircleShape> point_to_circle_shape(const sf::Color& color, const double radius = 5.0f) const;
        
        std::string print() const;
        bool is_equal(const std::shared_ptr<Point> other) const;
};



#endif // POINT_H