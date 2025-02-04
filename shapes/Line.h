#ifndef LINE_H
#define LINE_H

#include "Point.h"



class Line : public Shape, public std::enable_shared_from_this<Line> {
    private:
        std::shared_ptr<Point> start;
        std::shared_ptr<Point> end;
        double m; // slope
        double c; // intercept

    public:
        Line(std::shared_ptr<Point> start, std::shared_ptr<Point> end);
        std::shared_ptr<Point> get_start() const;
        std::shared_ptr<Point> get_end() const;
        double get_slope() const;
        double get_intercept() const;
        std::shared_ptr<Line> set_start(std::shared_ptr<Point> start);
        std::shared_ptr<Line> set_end(std::shared_ptr<Point> end);
        double length() const;
        std::string to_string() const;
        std::shared_ptr<Line> clone() const;
        std::shared_ptr<Line> set(const std::shared_ptr<Point> start, const std::shared_ptr<Point> end);
        std::shared_ptr<Line> set(const std::shared_ptr<Line> other);
        std::shared_ptr<Line> move(const std::shared_ptr<Point> offset);
        std::shared_ptr<Line> scale(const double factor);
        std::shared_ptr<Line> extend(const double factor);
        std::shared_ptr<Line> rotate_around(const std::shared_ptr<Point> center, const double angle);
        std::shared_ptr<Line> rotate_origin(const double angle);
        std::shared_ptr<Line> rotate_center(const double angle);
        void calculate_slope_intercept();
        bool on_extended_line(const std::shared_ptr<Point> point) const;
        bool is_parallel(const std::shared_ptr<Line> other) const;
        bool is_perpendicular(const std::shared_ptr<Line> other) const;
        bool is_intersecting(const std::shared_ptr<Line> other) const;
        bool between_bounds(const std::shared_ptr<Point> point) const;
        std::shared_ptr<Point> intersection(const std::shared_ptr<Line> other) const;
        std::shared_ptr<Line> get_perpendicular_line(const std::shared_ptr<Point> point) const;
        double evaluate_y(const double x) const;
        double evaluate_x(const double y) const;
        bool is_equal(const std::shared_ptr<Line> other) const;
        std::shared_ptr<sf::VertexArray> to_vertex_array() const;
};



#endif // LINE_H