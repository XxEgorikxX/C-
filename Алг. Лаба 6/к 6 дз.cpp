#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
#include <random>
#include <algorithm>

using namespace std;
using namespace sf;

// размер сетки 30x30 клеток
const int GRID_SIZE = 30;
// размер одной клетки в пикселях
const int CELL_SIZE = 25;
// размер окна 750x750 пикселей
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

// минимальный вес клетки
const int MIN_WEIGHT = 1;
// максимальный вес клетки
const int MAX_WEIGHT = 9;

// перечисление типов клеток
enum CellType {
    EMPTY,      // пустая клетка (проходимая)
    OBSTACLE,   // препятствие (стена)
    START,      // стартовая клетка
    END,        // конечная клетка
    IN_QUEUE,   // клетка в очереди на рассмотрение (зелёная)
    VISITED,    // посещённая клетка (красная)
    PATH        // клетка входящая в найденный путь (фиолетовая)
};

// структура для представления клетки
struct Cell {
    int x, y;           // координаты клетки на сетке
    CellType type;      // тип клетки (из перечисления выше)
    int weight;         // вес клетки (стоимость прохождения через неё)
    int g, h, f;        // параметры для a*: g - путь от старта, h - эвристика, f = g + h
    Cell* parent;       // указатель на родительскую клетку

    // конструктор: создаёт клетку с указанными координатами, тип empty, вес 1
    Cell(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
        type = EMPTY;
        weight = 1;
        g = h = f = 0;
        parent = nullptr;
    }

    // устанавливает тип "старт" и обнуляет вес
    void set_start() {
        type = START;
        weight = 0;
    }

    // устанавливает тип "финиш" и обнуляет вес
    void set_end() {
        type = END;
        weight = 0;
    }

    // устанавливает тип "стена"
    void set_wall() {
        type = OBSTACLE;
    }

    // устанавливает тип "путь" (не перезаписываем старт и финиш)
    void set_path() {
        if (type != START && type != END) {
            type = PATH;
        }
    }

    // устанавливает тип "посещённая" (не перезаписываем старт, финиш и клетки в очереди)
    void set_visited() {
        if (type != START && type != END && type != IN_QUEUE) {
            type = VISITED;
        }
    }

    // устанавливает тип "в очереди" (не перезаписываем старт, финиш и посещённые)
    void set_in_queue() {
        if (type != START && type != END && type != VISITED) {
            type = IN_QUEUE;
        }
    }

    // сбрасывает временные типы (путь, очередь, посещена) обратно в empty
    void reset() {
        if (type == PATH || type == VISITED || type == IN_QUEUE) {
            type = EMPTY;
        }
    }

    // проверяет, является ли клетка стеной
    bool is_wall() const {
        return type == OBSTACLE;
    }
};

// функция эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// проверка, находятся ли координаты в пределах сетки
bool isValid(int x, int y) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

// рекурсивный обход в глубину для проверки проходимости карты
void dfs(int x, int y, const vector<vector<Cell>>& grid, vector<vector<bool>>& visited) {
    // если вышли за границы - возвращаемся
    if (!isValid(x, y)) return;
    // если уже посещали эту клетку - возвращаемся
    if (visited[x][y]) return;
    // если клетка - стена - возвращаемся
    if (grid[x][y].is_wall()) return;

    // отмечаем клетку как посещённую
    visited[x][y] = true;

    // рекурсивно проверяем всех 4 соседей
    dfs(x + 1, y, grid, visited);  // сосед справа
    dfs(x - 1, y, grid, visited);  // сосед слева
    dfs(x, y + 1, grid, visited);  // сосед сверху
    dfs(x, y - 1, grid, visited);  // сосед снизу
}

// генерация случайной карты с гарантированной проходимостью
void generateRandomField(vector<vector<Cell>>& grid, int wallPercent = 25) {
    // генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // распределение для стен (0-99)
    uniform_int_distribution<> wallDist(0, 99);
    // распределение для весов (min_weight - max_weight)
    uniform_int_distribution<> weightDist(MIN_WEIGHT, MAX_WEIGHT);

    // флаг, что карта проходима
    bool validMap = false;

    // генерируем карту, пока не получим проходимую
    while (!validMap) {
        // заполнение сетки случайными значениями
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                // создаём новую клетку с координатами
                grid[i][j] = Cell(i, j);
                // присваиваем случайный вес
                grid[i][j].weight = weightDist(gen);
                // если выпало число меньше вероятности - делаем стеной
                if (wallDist(gen) < wallPercent) {
                    grid[i][j].set_wall();
                }
            }
        }

        // установка старта (левый верхний угол)
        grid[0][0].set_start();
        // установка финиша (правый нижний угол)
        grid[GRID_SIZE - 1][GRID_SIZE - 1].set_end();

        // проверяем, можно ли дойти от старта до финиша
        vector<vector<bool>> visited(GRID_SIZE, vector<bool>(GRID_SIZE, false));
        dfs(0, 0, grid, visited);

        // карта проходима, если финиш достигнут
        validMap = visited[GRID_SIZE - 1][GRID_SIZE - 1];
    }
}

// алгоритм поиска пути a* с учётом весов клеток
vector<pair<int, int>> a_star(vector<vector<Cell>>& grid, pair<int, int> startPos, pair<int, int> goalPos) {
    // очистка предыдущего пути
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j].reset();
        }
    }
    // восстанавливаем старт и финиш
    grid[0][0].set_start();
    grid[GRID_SIZE - 1][GRID_SIZE - 1].set_end();
    // компаратор для приоритетной очереди - сравнивает по f (стоимости)
    auto compare = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<0>(a) > get<0>(b);  // чем меньше f, тем выше приоритет
        };
    // приоритетная очередь: хранит (f, x, y) и автоматически сортирует по f
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(compare)> openSet(compare);
    // множество обработанных клеток
    set<pair<int, int>> closedSet;
    // лучшая известная стоимость g для каждой клетки
    map<pair<int, int>, int> gScore;
    // хранит предыдущую клетку для восстановления пути
    map<pair<int, int>, pair<int, int>> cameFrom;
    // эвристика для старта
    int startH = heuristic(grid[startPos.first][startPos.second], grid[goalPos.first][goalPos.second]);
    // добавляем старт в очередь
    openSet.push({ startH, startPos.first, startPos.second });
    // стоимость пути до старта = 0
    gScore[startPos] = 0;
    // 4 направления движения (влево, вправо, вверх, вниз)
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    // основной цикл алгоритма
    while (!openSet.empty()) {
        // берём клетку с минимальным f
        auto [f, x, y] = openSet.top();
        openSet.pop();
        // текущая клетка
        pair<int, int> current = { x, y };
        // если уже обработана - пропускаем
        if (closedSet.count(current)) continue;
        // отмечаем как обработанную
        closedSet.insert(current);
        // визуализация: отмечаем клетку как посещённую (если не старт и не финиш)
        if (grid[x][y].type != START && grid[x][y].type != END) {
            grid[x][y].set_visited();
        }
        // проверка: достигли ли цели?
        if (current == goalPos) {
            // восстановление пути из карты came_from
            vector<pair<int, int>> path;
            pair<int, int> step = goalPos;
            int totalWeight = 0;
            // проходим от финиша к старту
            while (cameFrom.count(step)) {
                path.push_back(step);
                totalWeight += grid[step.first][step.second].weight;
                // отмечаем клетки пути (кроме старта и финиша)
                if (grid[step.first][step.second].type != START && grid[step.first][step.second].type != END) {
                    grid[step.first][step.second].set_path();
                }
                step = cameFrom[step];
            }
            // добавляем старт и разворачиваем путь
            path.push_back(startPos);
            reverse(path.begin(), path.end());
            // выводим стоимость пути в консоль
            cout << "Найденное расстояние: " << totalWeight << endl;
            return path;
        }
        // проверяем всех соседей текущей клетки
        for (auto [dx, dy] : directions) {
            int nx = x + dx;  // координата x соседа
            int ny = y + dy;  // координата y соседа
            pair<int, int> neighbor = { nx, ny };
            // если за границами - пропускаем
            if (!isValid(nx, ny)) continue;
            // если стена - пропускаем
            if (grid[nx][ny].is_wall()) continue;
            // если уже обработан - пропускаем
            if (closedSet.count(neighbor)) continue;
            // стоимость входа в клетку (вес)
            int moveCost = grid[nx][ny].weight;
            // новая стоимость пути до соседа
            int tentative_g = gScore[current] + moveCost;
            // если нашли более дешёвый путь к соседу или ещё не находили
            if (!gScore.count(neighbor) || tentative_g < gScore[neighbor]) {
                // обновляем лучшую стоимость
                gScore[neighbor] = tentative_g;
                // запоминаем, откуда пришли
                cameFrom[neighbor] = current;
                // вычисляем эвристику для соседа
                int h = heuristic(grid[nx][ny], grid[goalPos.first][goalPos.second]);
                // вычисляем новую полную стоимость f
                int fScore = tentative_g + h;
                // добавляем соседа в очередь
                openSet.push({ fScore, nx, ny });
                // визуализация: отмечаем клетку как находящуюся в очереди
                if (grid[nx][ny].type != START && grid[nx][ny].type != END) {
                    grid[nx][ny].set_in_queue();
                }
            }
        }
    }
    // если очередь опустела и цель не найдена
    cout << "Путь не найден!" << endl;
    return {};
}

// функция отрисовки всей сетки
void draw_grid(RenderWindow& window, vector<vector<Cell>>& grid) {
    // статический шрифт (загружается один раз)
    static Font font;
    static bool fontLoaded = false;

    // загрузка шрифта
    if (!fontLoaded) {
        font.loadFromFile("arial.ttf");
        fontLoaded = true;
    }

    // проходим по всем клеткам
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            // создаём прямоугольник размером с клетку (без зазоров)
            RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
            // устанавливаем позицию
            cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);

            // выбираем цвет в зависимости от типа клетки
            switch (grid[i][j].type) {
            case EMPTY:
                cell.setFillColor(Color::White);
                break;
            case OBSTACLE:
                cell.setFillColor(Color::Black);
                break;
            case START:
                cell.setFillColor(Color(255, 165, 0));  // оранжевый
                break;
            case END:
                cell.setFillColor(Color(64, 224, 208)); // бирюзовый
                break;
            case IN_QUEUE:
                cell.setFillColor(Color::Green);        // зелёный
                break;
            case VISITED:
                cell.setFillColor(Color::Red);          // красный
                break;
            case PATH:
                cell.setFillColor(Color(139, 0, 255));  // фиолетовый
                break;
            }

            // рисуем клетку
            window.draw(cell);

            // отображение веса цифрой (кроме стен и клеток с весом 0)
            if (grid[i][j].type != OBSTACLE && fontLoaded && grid[i][j].weight > 0) {
                // создаём текстовый объект
                Text text;
                text.setFont(font);
                // устанавливаем текст - вес клетки
                text.setString(to_string(grid[i][j].weight));
                text.setCharacterSize(14);
                text.setFillColor(Color::Black);  // чёрная цифра

                // центрируем текст в клетке
                FloatRect bounds = text.getLocalBounds();
                text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
                text.setPosition(i * CELL_SIZE + CELL_SIZE / 2.0f, j * CELL_SIZE + CELL_SIZE / 2.0f);

                // рисуем цифру
                window.draw(text);
            }
        }
    }
}

// главная функция
int main() {
    // создаём окно
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* алгоритм");
    // создаём сетку клеток
    vector<vector<Cell>> grid(GRID_SIZE, vector<Cell>(GRID_SIZE));

    // генерируем начальную карту
    generateRandomField(grid, 25);

    // координаты старта (левый верхний угол)
    pair<int, int> start = { 0, 0 };
    // координаты финиша (правый нижний угол)
    pair<int, int> goal = { GRID_SIZE - 1, GRID_SIZE - 1 };

    // главный игровой цикл
    while (window.isOpen()) {
        Event event;

        // обработка всех событий
        while (window.pollEvent(event)) {
            // если нажата кнопка закрытия
            if (event.type == Event::Closed) {
                window.close();
            }

            // если нажата клавиша на клавиатуре
            if (event.type == Event::KeyPressed) {
                // если пробел - запуск поиска пути
                if (event.key.code == Keyboard::Space) {
                    a_star(grid, start, goal);
                }
                // если r - перегенерация карты
                if (event.key.code == Keyboard::R) {
                    generateRandomField(grid, 25);
                }
            }
        }

        // очищаем окно белым цветом
        window.clear(Color::White);
        // отрисовываем сетку
        draw_grid(window, grid);
        // отображаем нарисованное на экране
        window.display();
    }

    return 0;
}