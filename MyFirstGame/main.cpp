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
    srand (time(NULL));
    // Create the main window
    RenderWindow window(VideoMode(800, 600), "SFML window");
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

        //Text text("Shape # "+ to_string(currentShapeNumber), font, 50);

        if(currentShape== nullptr){
            currentShape = new TetrisShape(currentShapeNumber);//rand() % 15
            currentShapeNumber++; if(currentShapeNumber>14) currentShapeNumber =0;
        }




        //text.setFillColor(Color::Blue);


        int x = TetrisContainer::floatToIntPerContainerGrid(currentShape->getPosition().x);
        int y = TetrisContainer::floatToIntPerContainerGrid(currentShape->getPosition().y);

        int nextX=x;
        int nextY=y;

        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                speed = fallSpeed;
            }


            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
                nextX=x+1;
                if(container.checkIfShapeFits(*currentShape,nextX,nextY)){
                    currentShape->move(TetrisContainer::recSize,0);
                    x=nextX;
                } else {
                    nextX = x;
                }
            }

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
                nextX=x-1;
                if(container.checkIfShapeFits(*currentShape,nextX,nextY)){
                    currentShape->move(-TetrisContainer::recSize,0);
                    x=nextX;
                } else {
                    nextX = x;
                }
            }




        }


        window.clear();

       // window.draw(sprite);

       //window.draw(text);

        //window.draw(rectangle);


        float nextYF=currentShape->getPosition().y+speed;
        nextY = TetrisContainer::floatToIntPerContainerGrid(nextYF);

        if(container.checkIfShapeFits(*currentShape,nextX,nextY)){
            currentShape->move(0.f,speed);
            currentShape->draw(window);
        } else {
            container.addShape(*currentShape,x,y);
            delete (currentShape);
            currentShape = nullptr;
            speed = initialSpeed;
        }


        container.draw(window);


        window.display();

        //auto windowHeight = window.getSize().y;
        //std::cout << windowHeight << std::endl;


    }

    return EXIT_SUCCESS;
}
