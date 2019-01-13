#include <SFML/Graphics.hpp>
using namespace sf;
#include <math.h>
#include "tetris.hpp"



    void TetrisShape::move(int n, int x, int y){
        rectangles[n].move(x * TetrisContainer::recSize,y * TetrisContainer::recSize);
    }
    void TetrisShape::move(){
        int currentSquare = 0;
        for(int i=0;i<sizeX;i++){
            for(int j=0;j<sizeY;j++){
                if(data[j*sizeX+i]) {
                    move(currentSquare++,i,j);
                }
            }
        }
    }

    TetrisShape::TetrisShape(TetrisShape& t){
        throw "Tetris  Shape copy not allowed";
    }



    bool& TetrisShape::dataGet(int x, int y){
        if(x<0  || x>=sizeX || y<0 || y>=sizeY){
            throw "Tetris shape illegal index";
        }
        return data[x+y*sizeX];
    }

    TetrisShape::TetrisShape(int n, Color c) {
        number = n;
        color = c;
        for (RectangleShape& rectangle:rectangles) {
            rectangle.setSize(Vector2f(TetrisContainer::recSize, TetrisContainer::recSize));
            rectangle.setFillColor(color);
        }


        switch (number) {
            case 0:
                sizeX = 2;
                sizeY = 2;
                data = new bool[4]{1,1,1,1};

                break;
            case 1:
                sizeX = 4;
                sizeY = 1;
                data = new bool[4]{1,1,1,1};

                break;
            case 2:
                sizeX = 1;
                sizeY = 4;
                data = new bool[4]{1,1,1,1};

                break;
            case 3:

                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,1,0,0,1};

                break;
            case 4:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,1,1,0,1,0};

                break;
            case 5:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,0,0,1,1,1};

                break;
            case 6:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{0,1,0,1,1,1};

                break;
            case 7:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,1,1,0,0};

                break;
            case 8:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,1,0,1,0,1};

                break;
            case 9:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{0,0,1,1,1,1};

                break;
            case 10:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,0,1,0,1,1};

                break;
            case 11:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,0,0,1,1};

                break;
            case 12:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{0,1,1,1,1,0};

                break;
            case 13:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{0,1,1,1,1,0};

                break;
            case 14:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,0,1,1,0,1};

                break;
            case 15:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{0,1,0,1,1,1};

                break;
            case 16:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{1,0,1,1,1,0};

                break;
            case 17:
                sizeX = 3;
                sizeY = 2;
                data = new bool[6]{1,1,1,0,1,0};

                break;
            case 18:
                sizeX = 2;
                sizeY = 3;
                data = new bool[6]{0,1,1,1,0,1};

                break;
            default:
                sizeX = 0;
                sizeY = 0;
                data = new bool[0]{};

                break;
        };
        move();
    }

    TetrisShape::~TetrisShape(){
        delete data;
    }

    void TetrisShape::draw(RenderWindow& window){
        for(RectangleShape& rectangleShape:rectangles){
            window.draw(rectangleShape);
        }

    }
    void TetrisShape::move(float offsetX, float offsetY){
        for(RectangleShape& rectangleShape:rectangles){
            rectangleShape.move(offsetX,offsetY);
        }
        position.x+=offsetX;
        position.y+=offsetY;
    }

    const Vector2f& TetrisShape::getPosition() {
        return position;
    }




    TetrisContainer::TetrisContainer(TetrisContainer& c){
        throw "TetrisContainer copy not allowed";
    }
    Color& TetrisContainer::dataGetInner(int x, int y){
        if(x<0  || x>=sizeX || y<0 || y>=sizeY){
            throw "TetrisContainer illegal index";
        }
        return data[x+y*sizeX];
    }
    const float TetrisContainer::recSize = 40.f;



    bool TetrisContainer::dataGet(int x, int y){
        if(x<0  || x>=sizeX || y<0 || y>=sizeY) return true;
        else return dataGetInner(x,y)!=Color::Transparent;
    }
    void TetrisContainer::addShape(TetrisShape& shape,int x,int y){
        for(int xShape=0;xShape<shape.sizeX;xShape++) for(int yShape=0;yShape<shape.sizeY;yShape++)
                if(shape.dataGet(xShape,yShape)) dataGetInner(x+xShape,y+yShape)=shape.color;
    }
    bool TetrisContainer::checkIfShapeFits(TetrisShape* shape,int x, int y){
        for(int i = 0;i<shape->sizeX;i++){
            for(int j = 0;j<shape->sizeY;j++){
                if(shape->dataGet(i, j) && dataGet(x+i,y+j)){
                    return false;
                }
            }
        }
        return true;
    }


    TetrisContainer::TetrisContainer(long long x, long long y){
        sizeX= x;
        sizeY= y;
        data = new Color[x*y];
        for(int i= 0 ; i<x*y;i++ ){
            data[i]=Color::Transparent;
        }


    }
    TetrisContainer::~TetrisContainer(){
        delete data;
    }

    void TetrisContainer::draw(RenderWindow& window){
        for(long long x=0;x<sizeX;x++) for(auto y=0;y<sizeY;y++) if(dataGet(x,y)){
                    RectangleShape r(Vector2f(recSize,recSize));
                    r.setPosition(x*recSize, y*recSize);
                    r.setFillColor(dataGetInner(x,y));
                    window.draw(r);
                }
    }

    int TetrisContainer::floatToIntPerContainerGrid(float x){
        return static_cast<int>(ceil(x/recSize));
    }

    bool TetrisContainer::removeFilledRow(){
        for(int i = 0;i < sizeY; i++){
            bool noEmptyCellFound = true;
            for(int j = 0;j < sizeX; j++){
                if(!dataGet(j, i)){
                    noEmptyCellFound = false;
                    break;
                }
            }
            if(noEmptyCellFound){
                for(int k = 0;k < sizeX; k++){
                    dataGetInner(k, i) = Color::Transparent;
                }
                moveContainer(i-1);
                return true;
            }
        }
        return false;
    }
    void TetrisContainer::moveContainer(int fromWhichRow) {
        for(int i = fromWhichRow+1; i > 0; i--){
            for(int j = 0; j < sizeX; j++){
                dataGetInner(j, i) = dataGetInner(j, i-1);
            }
        }
    }

    TetrisShape::TetrisShape(TetrisShape* shapeToRotate, int rotationDirection) {
        data = nullptr;
        number = -1;
        sizeX = shapeToRotate->sizeY;
        sizeY = shapeToRotate->sizeX;
        color = shapeToRotate->color;
        for (RectangleShape& rectangle:rectangles) {
            rectangle.setSize(Vector2f(TetrisContainer::recSize, TetrisContainer::recSize));
            rectangle.setFillColor(color);
        }
        data = new bool[sizeX*sizeY];
        for(int i = 0; i < sizeX; i++){
            for(int j = 0; j<sizeY; j++){
                dataGet(i,j) = shapeToRotate->dataGet(j,sizeX - 1 - i);
            }
        }
        move();
        move(shapeToRotate->position.x, shapeToRotate->position.y);

    }

    TetrisShape* TetrisShape::transform() {
        TetrisShape* transformedShape = new TetrisShape(this);
        return transformedShape;
    }

