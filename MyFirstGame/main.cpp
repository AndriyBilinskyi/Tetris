#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourcePath.hpp"
#include <math.h>
#include <cstdlib>
#include "tetris.hpp"

using namespace sf;
using namespace std;


int main(int, char const**)
{
    bool gameOver = false;
    srand (time(NULL));
    // Create the main window
    RenderWindow window(VideoMode(400, 1000), "SFML window");
    const float windowHeight = window.getSize().y + 0.f;
    const float windowWidth = window.getSize().x + 0.f;

    TetrisContainer container( TetrisContainer::floatToIntPerContainerGrid(windowWidth), TetrisContainer::floatToIntPerContainerGrid(windowHeight));

    Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());







    float initialSpeed = 0.1;
    float fallSpeed = 4.f;
    float speed = initialSpeed;








    TetrisShape* currentShape = nullptr;




    int currentShapeNumber = 0;
    // Create a graphical text to display
    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    /*
    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite sprite(texture);




    Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    music.play();
    */

    while (window.isOpen())
    {

        //

        if(currentShape== nullptr && !gameOver){
            auto getRandomColorComponent = []() -> Uint8 {
                const Uint8 minBrightness = 10;
                return  minBrightness + rand() % (256 - minBrightness);
            };

            auto getRandomShapeNumber = []() -> int {
                return rand() % (TetrisShape::NumberOfShapes+1);
            };

            currentShape = new TetrisShape(getRandomShapeNumber(),Color(getRandomColorComponent(), getRandomColorComponent(), getRandomColorComponent()));
            if(!container.checkIfShapeFits(currentShape, 0, 0)){

                Text text("GAME OVER ", font, 50);
                text.setFillColor(Color::White);
                window.draw(text);
                window.display();
                gameOver = true;

            }
            //currentShapeNumber++; if(currentShapeNumber>18) currentShapeNumber =0;
        }


        int x = TetrisContainer::floatToIntPerContainerGrid(currentShape->getPosition().x);
        int y = TetrisContainer::floatToIntPerContainerGrid(currentShape->getPosition().y);

        int nextX=x;
        int nextY=y;

        Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }


            if (!gameOver) {

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                    speed = fallSpeed;
                }


                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
                    nextX = x + 1;
                    if (container.checkIfShapeFits(currentShape, nextX, nextY)) {
                        currentShape->move(TetrisContainer::recSize, 0);
                        x = nextX;
                    } else {
                        nextX = x;
                    }
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
                    nextX = x - 1;
                    if (container.checkIfShapeFits(currentShape, nextX, nextY)) {
                        currentShape->move(-TetrisContainer::recSize, 0);
                        x = nextX;
                    } else {
                        nextX = x;
                    }
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
                    TetrisShape *shape = currentShape->transform();
                    int xNew = TetrisContainer::floatToIntPerContainerGrid(shape->getPosition().x);
                    int yNew = TetrisContainer::floatToIntPerContainerGrid(shape->getPosition().y);
                    if (container.checkIfShapeFits(shape, xNew, yNew)) {
                        delete currentShape;
                        currentShape = shape;
                        x = xNew;
                        y = yNew;
                    } else delete shape;
                }

            }
        }

        if(!gameOver){

            window.clear();


            float nextYF = currentShape->getPosition().y + speed;
            nextY = TetrisContainer::floatToIntPerContainerGrid(nextYF);

            if (container.checkIfShapeFits(currentShape, nextX, nextY)) {
                currentShape->move(0.f, speed);
                currentShape->draw(window);
            } else {
                container.addShape(*currentShape, x, y);
                while (true) {
                    if (!container.removeFilledRow())break;

                }
                delete (currentShape);
                currentShape = nullptr;
                speed = initialSpeed;
            }

            container.draw(window);
            window.display();
        }





    }

    return EXIT_SUCCESS;
}
