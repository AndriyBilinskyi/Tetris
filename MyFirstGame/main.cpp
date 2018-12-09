#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourcePath.hpp"
#include <math.h>
#include <cstdlib>

using namespace sf;
using namespace std;
float recSize = 50.f;



class TetrisShape {
private:
    RectangleShape rectangles [4];

    void move(int n, int x, int y){
        rectangles[n].move(x * recSize,y * recSize);
    }
    void move(){
        int currentSquare = 0;
        for(int i=0;i<sizeX;i++){
            for(int j=0;j<sizeY;j++){
                if(data[j*sizeX+i]) {
                    move(currentSquare++,i,j);
                }
            }
        }
    }

    TetrisShape(TetrisShape& t){
        throw "Tetris  Shape copy not allowed";
    }


public:
    int number;
    int sizeX;
    int sizeY;
    int* heights;
    bool* data = nullptr;

    bool& dataGet(int x, int y){
        return data[x+y*sizeX];
    }

    TetrisShape(int n) {
        number = n;

        for (RectangleShape& rectangle:rectangles) {
            rectangle.setSize(Vector2f(recSize, recSize));
            rectangle.setFillColor(Color::Green);
        }


        switch (number) {
            case 0:
                sizeX = 2;
                sizeY = 2;
                data = new bool[4]{1,1,1,1};
                move();
                heights = new int[4]{2,2,0,0};
                break;
            case 1:
                sizeX = 4;
                sizeY = 1;
                data = new bool[4]{1,1,1,1};
                move();
                heights = new int[4]{1,1,1,1};
                break;
            case 2:
                sizeX = 1;
                sizeY = 4;
                data = new bool[4]{1,1,1,1};
                move();
                heights = new int[4]{4,0,0,0};
                break;
            case 3:

                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,1,0,0,1};
                move();
                heights = new int[4]{1,1,2,0};
                break;
            case 4:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,1,1,0,1,0};
                move();
                heights = new int[4]{3,1,0,0};
                break;
            case 5:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,0,0,1,1,1};
                move();
                heights = new int[4]{2,2,2,0};
                break;
            case 6:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{0,1,0,1,1,1};
                move();
                heights = new int[4]{3,3,0,0};
                break;
            case 7:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,1,1,0,0};
                move();
                heights = new int[4]{2,1,1,0};
                break;
            case 8:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,1,0,1,0,1};
                move();
                heights = new int[4]{1,3,0,0};
                break;
            case 9:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{0,0,1,1,1,1};
                move();
                heights =new int[4]{2,2,2,0};
                break;
            case 10:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,0,1,0,1,1};
                move();
                heights = new int[4]{3,3,0,0};
                break;
            case 11:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,0,0,1,1};
                move();
                heights = new int[4]{1,2,2,0};
                break;
            case 12:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{0,1,1,1,1,0};
                move();
                heights = new int[4]{3,2,0,0};
                break;
            case 13:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{0,1,1,1,1,0};
                move();
                heights = new int[4]{2,2,1,0};
                break;
            case 14:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,0,1,1,0,1};
                move();
                heights = new int [4]{2,3,0,0};
            default:
                sizeX = 0;
                sizeY = 0;
                data = new bool[0]{};
                heights = new int[0]{};
        }

    }

    ~TetrisShape(){
        delete heights;
        delete data;
    }

    void draw(RenderWindow& window){
        for(RectangleShape& rectangleShape:rectangles){
            window.draw(rectangleShape);
        }

    }
    void move(float offsetX, float offsetY){
        for(RectangleShape& rectangleShape:rectangles){
            rectangleShape.move(offsetX,offsetY);
        }
    }

    const Vector2f& getPosition() {
        return rectangles[0].getPosition();
    }

    Vector2f getSize()  {
        return Vector2f(sizeX * recSize, sizeY * recSize);
    }
    void setPosition (float x, float y){
        for(RectangleShape rectangleShape:rectangles){
            rectangleShape.setPosition(x,y);
        }
    }

};


class TetrisContainer{
private:
    TetrisContainer(TetrisContainer& c){
        throw "TetrisContainer copy not allowed";
    }
    void recalculateHeights(TetrisShape& shape, int x,int y){
        for(int i = x;i<x+sizeX;i++){
            for(int j = y;j<y+sizeY;j++){
                if(dataGet(i,j)){
                    heights[i]=sizeY-j;
                    break;
                }
            }
        }
    }

    bool& dataGetInner(int x, int y){
        return data[x+y*sizeX];
    }
public:

    int* heights;
    bool* data;

    long long sizeX;
    long long sizeY;

    bool dataGet(int x, int y){
        if(x<0  || x>=sizeX || y<0 || y>=sizeY) return true;
        else return dataGetInner(x,y);
    }
    void addShape(TetrisShape& shape,int x,int y){
        for(int xShape=0;xShape<shape.sizeX;xShape++) for(int yShape=0;yShape<shape.sizeY;yShape++)
                if(shape.dataGet(xShape,yShape)) dataGetInner(x+xShape,y+yShape)=true;
    }
    bool checkIfShapeFits(TetrisShape& shape,int x, int y){
        for(int i = x;i<x+shape.sizeX;i++){
            for(int j = y;j<y+shape.sizeY;j++){
                if(shape.dataGet(i-x, j-y) && dataGet(i,j)){
                    return false;
                }
            }
        }
        return true;
    }


    TetrisContainer(long long x, long long y){
        sizeX= x;
        sizeY= y;
        data = new bool[x*y];
        for(int i= 0 ; i<x*y;i++ ){
            data[i]=false;
        }
        heights = new int[x];
        for(int i = 0;i<x;i++){
            heights[i]=0;
        }

    }
    ~TetrisContainer(){
        delete data;
        delete heights;
    }

    void draw(RenderWindow& window){
        for(long long x=0;x<sizeX;x++) for(auto y=0;y<sizeY;y++) if(dataGet(x,y)){
                    RectangleShape r(Vector2f(recSize,recSize));
                    r.setPosition(x*recSize, y*recSize);
                    window.draw(r);
                }
    }
};


int main(int, char const**)
{
    srand (time(NULL));
    // Create the main window
    RenderWindow window(VideoMode(800, 600), "SFML window");
    const float windowHeight = window.getSize().y + 0.f;
    const float windowWidth = window.getSize().x + 0.f;

    TetrisContainer container( llround(windowWidth/recSize), llround(windowHeight/recSize));

    Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());







    float initialSpeed = 0.1;
    float fallSpeed = 4.f;
    float speed = initialSpeed;
    int x = 0;
    int y = 0;

    int nextX=x;
    int nextY=y;
    float nextYF=0;





    TetrisShape* currentShape = nullptr;

    int heights[llround(window.getSize().x/recSize)];
    for(auto& i:heights){
        i = 0;
    }


    int i = 0;
    /*
    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite sprite(texture);

    // Create a graphical text to display
    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    Text text("Hello SFML", font, 50);
    text.setFillColor(Color::Black);

    Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    music.play();
    */
    while (window.isOpen())
    {

        if(currentShape== nullptr){
            currentShape = new TetrisShape(i++);//rand() % 15
            if(i>14) i =0;
        }
        x = llround(currentShape->getPosition().x/recSize);
        y = llround(currentShape->getPosition().y/recSize);


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
                    currentShape->move(recSize,0);
                } else {
                    nextX = x;
                }
            }

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
                nextX=x-1;
                if(container.checkIfShapeFits(*currentShape,nextX,nextY)){
                    currentShape->move(-recSize,0);
                } else {
                    nextX = x;
                }
            }




        }


        window.clear();

       // window.draw(sprite);

       // window.draw(text);

        //window.draw(rectangle);
        currentShape->draw(window);
        container.draw(window);

        nextYF=currentShape->getPosition().y+speed;
        nextY = llround(nextYF/recSize);

        if(container.checkIfShapeFits(*currentShape,nextX,nextY)){
            currentShape->move(0.f,speed);
        } else {
            container.addShape(*currentShape,x,y);
            delete (currentShape);
            currentShape = nullptr;
            speed = initialSpeed;
        }


        window.display();

        //auto windowHeight = window.getSize().y;
        //std::cout << windowHeight << std::endl;


    }

    return EXIT_SUCCESS;
}
