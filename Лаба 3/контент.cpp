#include <SFML/Graphics.hpp>


int main() {

    sf::RenderWindow window(sf::VideoMode(500, 500), "Grid of Cells");

    int cellSize = 50;
    int len = 10;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
        cell.setOutlineColor(sf::Color::Black);
        cell.setOutlineThickness(1);

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (i + j < len -1) {
                    cell.setFillColor(sf::Color::Green);
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }
                cell.setPosition(i * cellSize, j * cellSize);
                window.draw(cell);
            }
        }
        window.display();
    }

    return 0;
}
