// This project uses the CMake build system.
#include <iostream>
#include <SFML/Graphics.hpp>
#include "geometric_objects/Line.h"
#include "geometric_objects/Point.h"
#include "geometric_objects/Circle.h"
#include "geometric_objects/Rectangle.h"

int main() {
    // Create a window
    float width = 1200;
    float height = 900;
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "SFML window");
    sf::View view(sf::FloatRect(-1 * width / 2, height / 2, width, -height)); // Corrected
    window.setView(view);

    std::shared_ptr<Line> x_axis = std::make_shared<Line>(std::make_shared<Point>(-1.0 * width / 2, 0), std::make_shared<Point>(width / 2.0, 0.0));
    std::shared_ptr<Line> y_axis = std::make_shared<Line>(std::make_shared<Point>(0.0, height / 2.0), std::make_shared<Point>(0.0, -1.0 * height / 2.0));
    std::shared_ptr<Rectangle> boundries = std::make_shared<Rectangle>(std::make_shared<Point>(-1.0 * width / 2 + 1, height / 2 - 1.0), std::make_shared<Point>(width / 2 - 1, -1.0 * height / 2 + 1));
    double rotation = 0.002;
    // Create points
    std::shared_ptr<Point> p1 = std::make_shared<Point>(3.0, 4.0);
    std::shared_ptr<Point> p2 = std::make_shared<Point>(6.0, 8.0);
    std::shared_ptr<Point> p3 = std::make_shared<Point>(10.0, 10.0);
    std::shared_ptr<Point> p4 = std::make_shared<Point>(15.0, 15.0);
    // Create a line
    std::shared_ptr<Line> l1 = std::make_shared<Line>(p1, p2);
    std::shared_ptr<Line> l2 = std::make_shared<Line>(p3, p4);
    // Scale the line
    l1->scale(50);
    l2->scale(20);


    std::shared_ptr<Circle> circle = std::make_shared<Circle>(std::make_shared<Point>(40, 30), 50);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        // Draw the x and y axes
        window.draw(*x_axis->to_vertex_array());
        window.draw(*y_axis->to_vertex_array());
        window.draw(*boundries->to_vertex_array(sf::Color::Transparent, sf::Color::White, 3.0));

        // Draw the shapes you want here
        window.draw(*l1->to_vertex_array());
        window.draw(*l2->to_vertex_array());
        if (l1->is_intersecting(*l2)) {
            std::shared_ptr<Point> intersection = l1->intersection(*l2);
            if (l2->between_bounds(*intersection)) {
                window.draw(*intersection->point_to_circle_shape());
            }
        }
        window.draw(*circle->to_circle_shape(sf::Color::Green));
        // Rotate the line
        l1->rotate_center(rotation);
        // rotation += 0.0001;


        // Dispaly the window on screen
        window.display();

    }
   return 0;
}

// to run:
// cmake -S . -B build
// cmake --build build
// ./build/PhysicsSimulator