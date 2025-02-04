#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle : public Shape, public std::enable_shared_from_this<Triangle> {
    private:
        std::shared_ptr<Point> p1;
        std::shared_ptr<Point> p2;
        std::shared_ptr<Point> p3;
        
    public:
        Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3);
        std::shared_ptr<Point> get_p1() const;
        std::shared_ptr<Point> get_p2() const;
        std::shared_ptr<Point> get_p3() const;
        void set_p1(std::shared_ptr<Point> p1);
        void set_p2(std::shared_ptr<Point> p2);
        void set_p3(std::shared_ptr<Point> p3);
        double calculate_perimeter() const;
        double calculate_area() const;
        double calculate_area(const std::shared_ptr<Point> a_, const std::shared_ptr<Point> b_, const std::shared_ptr<Point> c_) const;
        std::vector<double> angles() const;
        double angles(std::shared_ptr<Point> a_, std::shared_ptr<Point> b_, std::shared_ptr<Point> c_) const;
        std::shared_ptr<Triangle> clone() const;
        std::shared_ptr<Triangle> move(const std::shared_ptr<Point> offset);
        std::shared_ptr<Triangle> scale(const double factor);
        std::shared_ptr<Triangle> extend(const double factor);
        std::shared_ptr<Triangle> rotate(const std::shared_ptr<Point> center, const double angle);
        std::shared_ptr<Triangle> rotate_origin(const double angle);
        std::shared_ptr<Triangle> rotate_center(const double angle);
        std::shared_ptr<Point> center(std::shared_ptr<Point> a_, std::shared_ptr<Point> b_, std::shared_ptr<Point> c_) const;
        std::shared_ptr<Point> centroid() const;
        bool is_equal(const std::shared_ptr<Triangle> other) const;
        std::shared_ptr<sf::ConvexShape> to_convex_shape(const sf::Color& color_fill, const sf::Color& color_outline, const double outline_thickness) const;
        std::string to_string() const;
};


#endif // TRIANGLE_H