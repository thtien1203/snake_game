#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_WIDTH = 47;
const int BOARD_HEIGHT = 34;
const int GRID_SIZE = 25;
const int MAX_FOOD = 6;
const int TURNS = 10;

class Snake {

public:
    Snake(int x, int y, sf::Color color);
    void addSegment(sf::Vector2f position);
    void growSnake(sf::Vector2f direction);
    void snakeMove(sf::Vector2f direction);
    void draw(sf::RenderWindow &window);
    const sf::RectangleShape &getHeadSnake()const;
    const vector<sf::RectangleShape> &getSegment()const;
    bool collisionWithSelf()const;
    bool collisionWithOtherSnake(const Snake &otherSnake);
    bool collisionEgdeOfBoard(const sf::RenderWindow &window);
    void incrementScore() { score++; }
    int getScore()const { return score; }
    void resetScore() { score = 0; };

private:
    sf::RectangleShape shape;
    vector<sf::RectangleShape> segment;
    sf::Color snakeColor;
    int score;
};

class Food {
public:
    Food();
    void spawn();
    const sf::CircleShape &getShape()const;
    void drawFood(sf::RenderWindow &window);

private:
    sf::CircleShape shape;
    sf::Vector2f position;
};

class Screen {
public:
    Screen();
    void displayScreen(sf::RenderWindow &window);
    bool isTextClicked(sf::RenderWindow &window, string &selected);
    bool levelSelected(sf::RenderWindow &window, string& selectedLevel);
    void showSelection(bool show);
    void displayGameOver(sf::RenderWindow &window, Snake snake1, Snake snake2, sf::Text &yesText, sf::Text &noText, const std::string &gameMode);

private:
    sf::Font font;
    sf::Text readyText;
    sf::Text playText;
    sf::Text backGroundText;
    sf::Text chooseLevelText;
    sf::Text singleText;
    sf::Text soloText;
    sf::Text mediumText;
    sf::Text hardText;
    bool displaySelection;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Snake Game");
    bool startScreen = true;
    bool showSelection = false;
    bool gameOver = false;
    string selection;
    string gameMode;
    Screen screen;
    sf::Text yesText, noText;
    while (window.isOpen()) {
        // Initialize game state variables for each new game
        Snake snake1(rand() % 600, rand() % 650, sf::Color::Green);
        Snake snake2(rand() % 700, rand() % 750, sf::Color::Yellow);
        snake1.resetScore();
        snake2.resetScore();
        vector<Food> foods;
        for (int i = 0; i < MAX_FOOD; i++) {
            foods.push_back(Food());
        }
        sf::Vector2f direction1(0.f, 0.f);
        sf::Vector2f direction2(0.f, 0.f);
        float speed = 0;
        int turn = 0;
        gameOver = false;
        startScreen = true;
        showSelection = false;
        while(!gameOver && window.isOpen()) {
            sf::Event event;
            // bool move1 = false, move2 = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                // Game control events
                if (!startScreen) {
                    if (gameMode == "Single") {
                        if (event.type == sf::Event::KeyPressed) {
                            if (((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W)) && (direction1 != sf::Vector2f(0.f, speed))) {
                                direction1 = sf::Vector2f(0.f, -speed);
                            }
                            else if (((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S)) &&  (direction1 != sf::Vector2f(0.f, -speed))) {
                                direction1 = sf::Vector2f(0.f, speed);
                            }
                            else if (((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::A)) && (direction1 != sf::Vector2f(speed, 0.f))) {
                                direction1 = sf::Vector2f(-speed, 0.f);
                            }
                            else if (((event.key.code == sf::Keyboard::Right) || (event.key.code == sf::Keyboard::D)) && (direction1 != sf::Vector2f(-speed, 0.f))) {
                                direction1 = sf::Vector2f(speed, 0.f);
                            }
                        }
                    }
                    else if (gameMode == "2 Players") {
                        // Check key press events for snake movement
                        if (event.type == sf::Event::KeyPressed) {
                            // Handle movement for player 1
                            if ((event.key.code == sf::Keyboard::Up) && (direction1 != sf::Vector2f(0.f, speed))) {
                                direction1 = sf::Vector2f(0.f, -speed);
                            }
                            else if ((event.key.code == sf::Keyboard::Down) && (direction1 != sf::Vector2f(0.f, -speed))) {
                                direction1 = sf::Vector2f(0.f, speed);
                            }
                            else if ((event.key.code == sf::Keyboard::Left) && (direction1 != sf::Vector2f(speed, 0.f))) {
                                direction1 = sf::Vector2f(-speed, 0.f);
                            }
                            else if ((event.key.code == sf::Keyboard::Right) && (direction1 != sf::Vector2f(-speed, 0.f))) {
                                direction1 = sf::Vector2f(speed, 0.f);
                            }

                            // Handle movement for player 2
                            if ((event.key.code == sf::Keyboard::W) && (direction2 != sf::Vector2f(0.f, speed))) {
                                direction2 = sf::Vector2f(0.f, -speed);
                            }
                            else if ((event.key.code == sf::Keyboard::S) && (direction2 != sf::Vector2f(0.f, -speed))) {
                                direction2 = sf::Vector2f(0.f, speed);
                            }
                            else if ((event.key.code == sf::Keyboard::A) && (direction2 != sf::Vector2f(speed, 0.f))) {
                                direction2 = sf::Vector2f(-speed, 0.f);
                            }
                            else if ((event.key.code == sf::Keyboard::D) && (direction2 != sf::Vector2f(-speed, 0.f))) {
                                direction2 = sf::Vector2f(speed, 0.f);
                            }
                        }
                    }
                }

                if (startScreen) {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            string selectionOption;
                            if (screen.isTextClicked(window, selectionOption)) {
                                startScreen = false;
                                showSelection = true;
                                screen.showSelection(true);

                                if (selectionOption == "Single") {
                                    gameMode = "Single";
                                }
                                else if (selectionOption == "2 Players") {
                                    gameMode = "2 Players";
                                }
                            }
                        }
                    }
                }

                else if (showSelection) {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (screen.levelSelected(window, selection)) {
                                cout << "Level " << selection << endl;
                                showSelection = false;
                                screen.showSelection(false);
                                if (selection == "Medium") {
                                    speed = 22;
                                }
                                else if (selection == "Hard") {
                                    speed = 22;
                                }
                            }
                        }
                    }
                }
            }

            if (startScreen) {

                // Draw start screen
                window.clear(sf::Color::Blue); // Blue background
                screen.displayScreen(window);
            }
            else if (showSelection) {
                window.clear(sf::Color::Blue);
                screen.displayScreen(window);
            }
            else {
                window.clear();
                if (gameMode == "Single") {
                    if (direction1 != sf::Vector2f(0, 0)) {
                        //increment each time when snake moved
                        turn++;
                        snake1.snakeMove(direction1);

                        sf::FloatRect headSnake1 = snake1.getHeadSnake().getGlobalBounds();
                        vector<Food>::iterator it = foods.begin();

                        while(it != foods.end()) {
                            sf::FloatRect food = it->getShape().getGlobalBounds();

                            if (headSnake1.intersects(food)) {
                                //grow the snake
                                snake1.growSnake(-direction1);
                                snake1.incrementScore();
                                it = foods.erase(it);   //then delete that food

                                //reset turn when the snake eaten
                                turn = 0;
                            }
                            else {
                                it++;
                            }
                        }

                        //after 10 turns respawn the food
                        if (turn >= TURNS && foods.size() < MAX_FOOD) {
                            while (foods.size() < MAX_FOOD) {
                                foods.push_back(Food());
                            }
                            turn = 0;
                        }

                        if (snake1.collisionWithSelf() || snake1.collisionEgdeOfBoard(window)) {
                            //cout << "GAME OVER" << endl;
                            gameOver = true;
                            break;
                        }
                    }

                    if (selection == "Medium") {
                        sf::sleep(sf::milliseconds(2000 / 22));
                    }
                    else if (selection == "Hard") {
                        sf::sleep(sf::milliseconds(1500 / 22));
                    }

                    window.clear();

                    snake1.draw(window);

                    // Draw the food
                    for (auto& food : foods) {
                        food.drawFood(window);
                    }
                }

                if (gameMode == "2 Players") {

                    //window.clear();
                    if (direction1 != sf::Vector2f(0, 0)) {
                        //increment each time when snake moved
                        turn++;
                        snake1.snakeMove(direction1);

                        sf::FloatRect headSnake1 = snake1.getHeadSnake().getGlobalBounds();
                        vector<Food>::iterator it = foods.begin();

                        while(it != foods.end()) {

                            sf::FloatRect food = it->getShape().getGlobalBounds();

                            if (headSnake1.intersects(food)) {

                                //grow the snake
                                snake1.growSnake(-direction1);
                                snake1.incrementScore();
                                it = foods.erase(it);   //then delete that food
                                //reset turn when the snake eaten
                                turn = 0;
                            }
                            else {
                                it++;
                            }
                        }

                        //after 10 turns respawn the food
                        if (turn >= TURNS && foods.size() < MAX_FOOD) {
                            while (foods.size() < MAX_FOOD) {
                                foods.push_back(Food());
                            }
                            turn = 0;
                        }
                        if (snake1.collisionWithSelf() || snake1.collisionEgdeOfBoard(window) || snake1.collisionWithOtherSnake(snake2)) {
                            //cout << "GAME OVER" << endl;
                            gameOver = true;
                            break;
                        }
                    }

                    if (direction2 != sf::Vector2f(0, 0))

                    {

                        //increment each time when snake moved

                        turn++;

                        snake2.snakeMove(direction2);

                        

                        sf::FloatRect headSnake2 = snake2.getHeadSnake().getGlobalBounds();

                        

                        vector<Food>::iterator it = foods.begin();

                        while(it != foods.end())

                        {

                            sf::FloatRect food = it->getShape().getGlobalBounds();

                            

                            if (headSnake2.intersects(food))

                            {

                                //grow the snake

                                snake2.growSnake(-direction2);

                                snake2.incrementScore();

                                it = foods.erase(it);   //then delete that food

                                

                                //reset turn when the snake eaten

                                turn = 0;

                            }

                            else

                            {

                                it++;

                            }

                            

                        }

                        

                        //after 10 turns respawn the food

                        if (turn >= TURNS && foods.size() < MAX_FOOD)

                        {

                            while (foods.size() < MAX_FOOD)

                            {

                                foods.push_back(Food());

                            }

                            turn = 0;

                        }

                        

                        if (snake2.collisionWithSelf() || snake2.collisionEgdeOfBoard(window) || snake2.collisionWithOtherSnake(snake1))

                        {

                            //cout << "GAME OVER" << endl;

                            gameOver = true;

                            break;

                        }

                        

                    }

                    if (selection == "Medium")

                    {

                        sf::sleep(sf::milliseconds(2000 / 22));

                    }

                    else if (selection == "Hard")

                    {

                        sf::sleep(sf::milliseconds(1500 / 22));

                    }

                    window.clear();

                                        

                    snake1.draw(window);

                    snake2.draw(window);

                    // Draw the food

                    for (auto& food : foods)

                    {

                        food.drawFood(window);

                    }

                }

            }

            window.display();

        }

        

        

        if (gameOver)

        {

            screen.displayGameOver(window, snake1, snake2, yesText, noText, gameMode);

            bool userChoice = false;

            while (!userChoice && window.isOpen())

            {

                sf::Event event;

                while(window.pollEvent(event))

                {

                    if (event.type == sf::Event::Closed)

                    {

                        window.close();

                    }

                    if (event.type == sf::Event::MouseButtonPressed)

                    {

                        if (event.mouseButton.button == sf::Mouse::Left)

                        {

                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                            

                            if (yesText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

                            {

                                userChoice = true;

                                startScreen = true;

                                break;

                            }

                            

                            if (noText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

                            {

                                window.close();

                                break;

                            }

                            

                        }

                        

                    }

                    

                }

                

            }

            

        }

        

    }



    return 0;

}



Screen::Screen()

{

    font.loadFromFile("Arial Unicode.ttf");



    //draw "The snake game" start of screen

    backGroundText.setFont(font);

    backGroundText.setString("THE SNAKE GAME");

    backGroundText.setCharacterSize(60);

    backGroundText.setFillColor(sf::Color::White);

    backGroundText.setPosition(250, 250);

    

    //draw single

    singleText.setFont(font);

    singleText.setString("SINGLE");

    singleText.setCharacterSize(40);

    singleText.setFillColor(sf::Color::White);

    singleText.setPosition(450, 400);

    

    //draw solo

    soloText.setFont(font);

    soloText.setString("2 Players");

    soloText.setCharacterSize(40);

    soloText.setFillColor(sf::Color::White);

    soloText.setPosition(450, 500);

            

    chooseLevelText.setFont(font);

    chooseLevelText.setString("CHOOSE LEVEL");

    chooseLevelText.setCharacterSize(60);

    chooseLevelText.setFillColor(sf::Color::White);

    chooseLevelText.setPosition(250, 200);

    

    //draw Medium option

    mediumText.setFont(font);

    mediumText.setString("MEDIUM");

    mediumText.setCharacterSize(40);

    mediumText.setFillColor(sf::Color::White);

    mediumText.setPosition(430, 450);

    

    //draw Hard option

    hardText.setFont(font);

    hardText.setString("HARD");

    hardText.setCharacterSize(40);

    hardText.setFillColor(sf::Color::White);

    hardText.setPosition(450, 500);

    

    //false to display the selection screen

    displaySelection = false;

}



void Screen::displayScreen(sf::RenderWindow &window)

{

    //draw level text

    if (displaySelection)

    {

        window.draw(chooseLevelText);

        window.draw(mediumText);

        window.draw(hardText);

    }

    else

    {

        window.draw(backGroundText);

        window.draw(singleText);

        window.draw(soloText);

    }

}



bool Screen::isTextClicked(sf::RenderWindow &window, string &selected)

{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    sf::FloatRect single = singleText.getGlobalBounds();

    sf::FloatRect solo = soloText.getGlobalBounds();

    

    if (single.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

    {

        selected = "Single";

        return true;

    }

    if (solo.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

    {

        selected = "2 Players";

        return true;

    }

    return false;



}



bool Screen::levelSelected(sf::RenderWindow &window, string& selectedLevel)

{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    

    if (mediumText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

    {

        selectedLevel = "Medium";

        return true;

    }

    else if (hardText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))

    {

        selectedLevel = "Hard";

        return true;

    }

    return false;

}



void Screen::showSelection(bool show)

{

    displaySelection = show;

}



void Screen::displayGameOver(sf::RenderWindow &window, Snake snake1, Snake snake2, sf::Text &yesText, sf::Text &noText, const std::string &gameMode)

{

    window.clear(sf::Color::Blue);

    

    sf::Text gameOverText;

    gameOverText.setFont(font);

    gameOverText.setCharacterSize(50);

    gameOverText.setFillColor(sf::Color::White);

    gameOverText.setPosition(100, 100);



    if (gameMode == "Single")

    {

        gameOverText.setString("GAME OVER\nScore: \nSnake: " + to_string(snake1.getScore()) + "\n\nPLAY AGAIN?");

    }

    else if (gameMode == "2 Players")

    {

        gameOverText.setString("GAME OVER\nScore: \nSnake 1: " + to_string(snake1.getScore()) + "\nSnake 2: " + to_string(snake2.getScore()) + "\n\nPLAY AGAIN?");

    }

    

    yesText.setFont(font);

    yesText.setString("YES");

    yesText.setCharacterSize(30);

    yesText.setFillColor(sf::Color::White);

    yesText.setPosition(500, 500);

    

    noText.setFont(font);

    noText.setString("NO");

    noText.setCharacterSize(30);

    noText.setFillColor(sf::Color::White);

    noText.setPosition(500, 550);

    



    window.draw(gameOverText);

    window.draw(yesText);

    window.draw(noText);

    window.display();

}



Snake::Snake(int x, int y, sf::Color color) : snakeColor(color)

{

    shape.setSize(sf::Vector2f(22, 22));

    addSegment(sf::Vector2f(x, y));

}



void Snake::addSegment(sf::Vector2f position)

{

    sf::RectangleShape newSegment(sf::Vector2f(22, 22));



    if (!segment.empty())

    {

        // Calculate the position of the new segment based on the last segment and direction

        sf::Vector2f lastPosition = segment.back().getPosition();

        sf::Vector2f growDirection = position - lastPosition;

        sf::Vector2f newPos = lastPosition + growDirection;

        newSegment.setPosition(newPos);

    }

    else

    {

        newSegment.setPosition(position);

    }



    newSegment.setFillColor(snakeColor);

    segment.push_back(newSegment);

}



void Snake::growSnake(sf::Vector2f direction)

{

    //sf::CircleShape newSegment(11.f);

    sf::RectangleShape newSegment(sf::Vector2f(22, 22));

    newSegment.setFillColor(snakeColor);



    sf::Vector2f lastPositon;

    sf::Vector2f secondLastPos;

    if (segment.size() >= 2)

    {

        lastPositon = segment.back().getPosition();

        secondLastPos = segment[segment.size() - 2].getPosition();



        sf::Vector2f growDirection = lastPositon - secondLastPos;

        sf::Vector2f newPosition = lastPositon + growDirection;

        newSegment.setPosition(newPosition);

    }

    else if (!segment.empty())

    {

        lastPositon = segment.back().getPosition();

        newSegment.setPosition(lastPositon + direction);

    }

    else

    {

        newSegment.setPosition(direction);

    }

    segment.push_back(newSegment);

    

}



void Snake::snakeMove(sf::Vector2f direction)

{

    if (segment.empty())

        return;



    // Store the previous position of the head

    sf::Vector2f previousPosition = segment[0].getPosition();



    // Move the head

    segment[0].setPosition(previousPosition + direction);



    // Move the rest of the body

    for (size_t i = 1; i < segment.size(); ++i)

    {

        // Store the previous position of the segment

        sf::Vector2f temp = segment[i].getPosition();



        // Move the segment to the position of the previous segment

        segment[i].setPosition(previousPosition);



        // Update the previous position of the segment for the next iteration

        previousPosition = temp;

    }

}



const sf::RectangleShape &Snake::getHeadSnake()const

{

    return segment.front();

}



void Snake::draw(sf::RenderWindow &window)

{

    vector<sf::RectangleShape>::iterator itr;

    for (itr = segment.begin(); itr != segment.end(); itr++)

    {

        window.draw(*itr);

    }



}



const vector<sf::RectangleShape> &Snake::getSegment()const

{

    return segment;

}



Food::Food()

{

    shape.setRadius(10.f);

    shape.setFillColor(sf::Color::Red);

    spawn();

}



void Food::spawn()

{

    int x = rand() % BOARD_WIDTH * (GRID_SIZE - 10);

    int y = rand() % BOARD_HEIGHT * (GRID_SIZE - 10);

    shape.setPosition(x, y);

}



const sf::CircleShape &Food::getShape()const

{

    return shape;

}



void Food::drawFood(sf::RenderWindow &window)

{

    window.draw(shape);

}



bool Snake::collisionWithSelf()const

{

    if (segment.size() < 2)

    {

        return false;

    }



    const sf::FloatRect &head = segment.front().getGlobalBounds();

    for (size_t i = 1; i < segment.size(); i++)

    {

        if (head.intersects(segment[i].getGlobalBounds()))

        {

            return true;

        }

    }



    return false;

}

bool Snake::collisionWithOtherSnake(const Snake &otherSnake)

{

    if (segment.empty() || otherSnake.segment.empty())

    {

        return false;

    }



    sf::FloatRect headBounds = segment[0].getGlobalBounds();



    for (const auto &seg : otherSnake.segment)

    {

        if (headBounds.intersects(seg.getGlobalBounds()))

        {

            return true;

        }

    }



    return false;

}



bool Snake::collisionEgdeOfBoard(const sf::RenderWindow &window)

{

    sf::Vector2f headPosition = segment[0].getPosition();



    // Get the size of the game window

    sf::Vector2u windowSize = window.getSize();



    // Check if the head of the snake is outside the bounds of the window

    if (headPosition.x < 0 || headPosition.x >= windowSize.x ||

        headPosition.y < 0 || headPosition.y >= windowSize.y)

    {

        return true;

    }



    return false;

}