#include<SFML/Graphics.hpp>
#include <iomanip>
#include <ctime>
#include<iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include "Menu.h"

#define _USE_MATH_DEFINES
double const PI = 3.14159;
float playerRotation(sf::Vector2f worldPos, sf::Vector2f playerPosition, sf::Sprite player) {
    float one = playerPosition.y - worldPos.y;
    float two = playerPosition.x - worldPos.x;
    float tanges = (atan2(one, two) * 180 / PI);
    return tanges;
}

class Bullet {

public:
    float maxSpeed;
    sf::CircleShape bullet;
    sf::Vector2f currVelocity;
    
    Bullet(float radius = 20.f) : currVelocity(0.f, 0.f), maxSpeed(1.4f) {
        this->bullet.setRadius(radius);
    }
    void operator++() {
        maxSpeed += 0.0005f;
    }
    void operator--() {
        maxSpeed -= 0.0005f;
    }
    
 
};
class Enemy {
public:
    sf::RectangleShape enemy;
    sf::Texture spiderman;
    Enemy() {
        this->enemy.setSize(sf::Vector2f(300.f, 300.f));
        spiderman.loadFromFile("spiderman2.png");
        enemy.setTexture(&spiderman);
        
    }
    void EnemyLocation(sf::RectangleShape& kmr) {
        kmr.setPosition(sf::Vector2f(rand() % 6000, rand() % 6000));
    }
};
class Points: public Enemy 
{
private:
    std::set<int>Set = { 100,200,300 };
    int value = 0;
    sf::Texture pointTexture;
public:
    sf::RectangleShape point;
    Points() {
        this->point.setSize(sf::Vector2f(100.f, 100.f));
        this->point.setFillColor(sf::Color::Blue);
        pointTexture.loadFromFile("WHAT.png");
        point.setTexture(&pointTexture);
   }
    void generateRandomValue(int number) {
       this ->value = *std::next(Set.begin(), number);
        std::cout << value << std::endl;
    }
    int getValue() {
        return this->value;
    }

};

    int main()
    {
       
    LOOP:
        {
            int scoreInt = 0;
            //textas
        sf::Text text;
        sf::Text score;
        sf::Font font;
        font.loadFromFile("BIGJOHN.otf");
        if (!font.loadFromFile("BIGJOHN.otf"))
        {
            std::cout << "ERROR" << std::endl;
        }
        text.setFont(font);
        score.setFont(font);
        text.setString("Score: ");
        score.setString("0");
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        score.setCharacterSize(100);
        score.setFillColor(sf::Color::Red);
        score.setStyle(sf::Text::Bold);
        text.setPosition(sf::Vector2f(3600.f, 23.5f));
        score.setPosition(sf::Vector2f(4000.f, 23.5f));

        //saudimo vektoriai
        sf::Vector2f playerCenter;
        sf::Vector2f aimDir;
        sf::Vector2f aimDirNorm;

        std::map<std::string, std::string> textureNames;
        textureNames["zaidejas"] = "1.png";
        textureNames["Aplinka"] = "2.png";
        textureNames["Nuotrauka"] = "3.png";
        //Zaidejas
        sf::Texture texture;
        texture.loadFromFile(textureNames["zaidejas"]);
        sf::Sprite player(texture);

     
        
        srand(time(NULL));

        //Backgroundas
        sf::Texture BlokoTextura;
        BlokoTextura.loadFromFile(textureNames["Aplinka"]);
        sf::Sprite background(BlokoTextura);

        //Vaizdas ir zaidejo startine pozicija
        sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(3000, 3000));
        player.setOrigin(313 / 2, 207 / 2);
        player.setPosition(6008 / 2, 2924 / 2);

        //Kulka
        Bullet b1;
        std::vector<Bullet> bullets;
        double currentTime = 0;

        //Priesas
        Enemy enemy;
        std::vector<Enemy>enemies;
        double spawnTime = 0;
        while (enemies.size() < 30) {
            enemy.EnemyLocation(enemy.enemy);
            enemies.push_back(enemy);
        }

        //Extra Points
        Points point;
        std::vector<Points>points;
       

        
        //MENU SCREEN

        sf::Sprite nice;
        sf::Texture niceTexture;
        niceTexture.loadFromFile(textureNames["Nuotrauka"]);
        nice.setTexture(niceTexture);
        nice.setPosition(50.f, 200.f);
        sf::RenderWindow startWindow(sf::VideoMode(1920, 1080), "KMR", sf::Style::Close | sf::Style::Resize);
        Menu menu(startWindow.getSize().x, startWindow.getSize().y);
        while (startWindow.isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                menu.MoveUp();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                menu.MoveDown();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                if (menu.selectedItemIndexReturn() == 0) {
                    startWindow.close();
                }
                if (menu.selectedItemIndexReturn() == 1) {
                    return 0;
                }

            }
            startWindow.draw(nice);
            menu.draw(startWindow);

            startWindow.display();

        }
        //GAME SCREEN
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "KMR", sf::Style::Close | sf::Style::Resize);
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event evnt;
            while (window.pollEvent(evnt)) {
                switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << "Naujo lango plotis: " << evnt.size.width << " Naujo lango aukstis: " << evnt.size.height << std::endl;
                    printf("Naujo lango plotis= %i , Naujo lango aukstis= %i \n", evnt.size.width, evnt.size.height);
                    break;
                }

            }

            //zaidejo apsukimas pagal pelyte
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
            sf::Vector2f currentMousePosF = sf::Vector2f(sf::Mouse::getPosition(window));
            sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos);
            player.setRotation(playerRotation(worldPos, player.getPosition(), player) + 180);

            //judejimas
            float mapTop = background.getGlobalBounds().top;
            float mapBot = background.getGlobalBounds().top + background.getGlobalBounds().height;
            float mapLeft = background.getGlobalBounds().left;
            float mapRight = background.getGlobalBounds().left + background.getGlobalBounds().width;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player.getGlobalBounds().left >= mapLeft) {

                player.move(-0.4f, 0.0f);
                text.move(-0.4f, 0.0f);
                score.move(-0.4f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (player.getGlobalBounds().left + player.getGlobalBounds().width) <= mapRight) {
                player.move(0.4f, 0.0f);
                text.move(0.4f, 0.0f);
                score.move(0.4f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (player.getGlobalBounds().top >= mapTop)) {
                player.move(0.0f, -0.4f);
                text.move(0.0f, -0.4f);
                score.move(0.0f, -0.4f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && ((player.getGlobalBounds().top + player.getGlobalBounds().height) < mapBot)) {
                player.move(0.0f, 0.4f);
                text.move(0.0f, 0.4f);
                score.move(0.0f, 0.4f);
            }
            //Saudymo vektoriai ir laikas
            sf::Time PraejoLaiko = clock.getElapsedTime();
           
            aimDir = worldPos - playerCenter;
            aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
            playerCenter = player.getPosition();

            //Priesu darymas
            if (enemies.size() < 30 && PraejoLaiko.asSeconds() - spawnTime >= 1) {
                spawnTime = PraejoLaiko.asSeconds();
                enemy.EnemyLocation(enemy.enemy);
                enemies.push_back(enemy);
            }

            //saudymo greicio nustatymas
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add)) {
                ++b1;
                std::cout << b1.maxSpeed << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract)) {
                --b1;
                std::cout << b1.maxSpeed << std::endl;
            }


            //saudymas ir kulku kurimas
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                b1.bullet.setPosition(playerCenter);
                b1.currVelocity = aimDirNorm * b1.maxSpeed;
                if (PraejoLaiko.asSeconds() - currentTime > 0.2) {
                    currentTime = PraejoLaiko.asSeconds();
                    bullets.push_back(b1);
                }


            }
            //Papildomu tasku kurimas
            if (points.size() <= 5) {
                
                point.EnemyLocation(point.point);
                int randomNumber = rand() % 3;
                point.generateRandomValue(randomNumber);
                points.push_back(point);

            }




            // kulku uzribis
            for (int i = 0; i < bullets.size(); i++) {
                bullets[i].bullet.move(bullets[i].currVelocity);

                if (bullets[i].bullet.getPosition().x < 0 || bullets[i].bullet.getPosition().y < 0 || bullets[i].bullet.getPosition().x>6600 || bullets[i].bullet.getPosition().y>6500) {
                    bullets.erase(bullets.begin() + i);
                    break;
                }

            }
            //nusovimas
            for (int i = 0; i < bullets.size(); i++) {
                for (int j = 0; j < enemies.size(); j++) {

                    if (enemies[j].enemy.getGlobalBounds().intersects(bullets[i].bullet.getGlobalBounds())) {
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        scoreInt += rand() % 20 + 30;
                        break;
                    }
                }
            }
            //papildomi taskai palietimas
            for (int i = 0; i < points.size(); i++) {
                if (points[i].point.getGlobalBounds().intersects(player.getGlobalBounds())) {
                    scoreInt += points[i].getValue();
                    points.erase(points.begin() + i);

                }
            }

            //score
            score.setString(std::to_string(scoreInt));

            //piesimas objektu
            view.setCenter(playerCenter);
            window.clear(sf::Color::Black);
            window.setView(view);
            window.draw(background);
            window.draw(player);

            for (int i = 0; i < enemies.size(); i++) {
                window.draw(enemies[i].enemy);
            }
            for (int i = 0; i < bullets.size(); i++) {
                window.draw(bullets[i].bullet);
            }
            for (int i = 0; i < points.size(); i++) {
                window.draw(points[i].point);
            }
            //Close screen
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
              
                window.close();

                goto LOOP;
            }
            //teksto piesimas
            window.draw(text);
            window.draw(score);
            window.display();
        }
        return 0;
    }
    } 
