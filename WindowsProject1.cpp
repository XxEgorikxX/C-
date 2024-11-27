#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Вычисление значения функции

        // Преобразование координат в экранные
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        // Добавление точки в массив вершин
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window for graphs");

    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная для проверки существования пользовательской точки

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);
    coordinatesText.setString("Coordinates: (None)");

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(750, 300); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 550); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 15.0f; // Масштаб 15 по X
                    float mathY = -(mousePos.y - 300) / 15.0f; // Масштаб 15 по Y

                    // Установка новой пользовательской точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем, что точка существует

                    std::string zone;
                    if (mathY == mathX + 9 or mathY == mathX * mathX) {
                        zone = "Border";
                    }
                    else if (mathY > mathX + 9 and mathY < (mathX * mathX) and mathX < 0) {
                        zone = '1';
                    }
                    else if (mathY < mathX + 9 and mathY < (mathX * mathX)) {
                        zone = "2";
                    }
                    else if (mathY < mathX + 9 and mathY >(mathX * mathX)) {
                        zone = "3";
                    }
                    else if (mathY > mathX + 9 and mathY < (mathX * mathX) and mathX > 0) {
                        zone = "4";
                    }
                    else if (mathY > mathX + 9 and mathY > (mathX * mathX)) {
                        zone = "5";
                    }
                    // Обновление текста с координатами точки 
                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ")" + "Zone: " + zone);
                }
            }


            window.clear();

            Бижь - Бужь - Бухъ, [27.11.2024 21:18]
                // Отрисовка осей
                window.draw(xAxis);
            window.draw(yAxis);
            // 5 Отрисовка графика y1 = x+9
            drawGraph(window, [](float x) { return x + 9; }, -10, 10, 15, 15, sf::Color::Red);

            // 5 Отрисовка графика y2 = x * x
            drawGraph(window, [](float x) { return x * x; }, -10, 10, 15, 15, sf::Color::Blue);

            // Отрисовка пользовательской точки, если она существует
            if (userPointExists) {
                window.draw(userPoint);
                window.draw(coordinatesText);
            }

            // Отображение нового кадра
            window.display();
        }
    }
    return 0;
}