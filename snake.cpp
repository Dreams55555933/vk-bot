#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Point {
    int x, y;
};

class Snake {
private:
    vector<Point> body;
    int direction; // 0 - up, 1 - right, 2 - down, 3 - left
    int width, height;

public:
    Snake(int w, int h) : width(w), height(h), direction(1) {
        body.push_back({w / 2, h / 2});
        body.push_back({w / 2 - 1, h / 2});
        body.push_back({w / 2 - 2, h / 2});
    }

    void changeDirection(int newDir) {
        if ((direction == 0 && newDir != 2) ||
            (direction == 1 && newDir != 3) ||
            (direction == 2 && newDir != 0) ||
            (direction == 3 && newDir != 1)) {
            direction = newDir;
        }
    }

    void move() {
        Point head = body[0];
        switch (direction) {
            case 0: head.y--; break;
            case 1: head.x++; break;
            case 2: head.y++; break;
            case 3: head.x--; break;
        }
        body.insert(body.begin(), head);
        body.pop_back();
    }

    void grow() {
        body.push_back(body.back());
    }

    bool checkCollision() {
        Point head = body[0];
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return true;
        for (size_t i = 1; i < body.size(); i++) {
            if (head.x == body[i].x && head.y == body[i].y)
                return true;
        }
        return false;
    }

    bool checkFood(Point food) {
        return body[0].x == food.x && body[0].y == food.y;
    }

    void draw() {
        system("cls");
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool isSnake = false;
                for (const auto& part : body) {
                    if (part.x == x && part.y == y) {
                        isSnake = true;
                        break;
                    }
                }
                if (isSnake) cout << "O";
                else if (y == 0 || y == height - 1 || x == 0 || x == width - 1) cout << "#";
                else cout << " ";
            }
            cout << endl;
        }
        cout << "Score: " << body.size() - 3 << endl;
        cout << "Controls: W-A-S-D or Arrow Keys. Q to quit." << endl;
    }

    Point getHead() { return body[0]; }
};

Point generateFood(int width, int height, const vector<Point>& snakeBody) {
    Point food;
    bool valid;
    do {
        valid = true;
        food.x = rand() % (width - 2) + 1;
        food.y = rand() % (height - 2) + 1;
        for (const auto& part : snakeBody) {
            if (part.x == food.x && part.y == food.y) {
                valid = false;
                break;
            }
        }
    } while (!valid);
    return food;
}

int main() {
    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);
    
    const int WIDTH = 40;
    const int HEIGHT = 20;
    
    Snake snake(WIDTH, HEIGHT);
    Point food = generateFood(WIDTH, HEIGHT, snake.body);
    
    while (true) {
        snake.draw();
        
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w' || key == 'W' || key == 72) snake.changeDirection(0);
            if (key == 'd' || key == 'D' || key == 77) snake.changeDirection(1);
            if (key == 's' || key == 'S' || key == 80) snake.changeDirection(2);
            if (key == 'a' || key == 'A' || key == 75) snake.changeDirection(3);
            if (key == 'q' || key == 'Q') break;
        }
        
        snake.move();
        
        if (snake.checkCollision()) {
            system("cls");
            cout << "Game Over! Your score: " << snake.getHead().x + snake.getHead().y << endl;
            cout << "Press any key to exit..." << endl;
            _getch();
            break;
        }
        
        if (snake.checkFood(food)) {
            snake.grow();
            food = generateFood(WIDTH, HEIGHT, snake.body);
        }
        
        Sleep(100);
    }
    
    return 0;
}
