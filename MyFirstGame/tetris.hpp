#include <SFML/Graphics.hpp>
using namespace sf;

class TetrisShape {
private:
    RectangleShape rectangles [4];
    Vector2f position = Vector2f(0.0f,0.0f);;

    void move(int n, int x, int y);
    void move();

    TetrisShape(TetrisShape& t);


public:
    int number;
    int sizeX;
    int sizeY;
    bool* data = nullptr;

    bool& dataGet(int x, int y);

    TetrisShape(int n);

    ~TetrisShape();

    void draw(RenderWindow& window);
    void move(float offsetX, float offsetY);

    const Vector2f& getPosition();

};


class TetrisContainer{
private:
    TetrisContainer(TetrisContainer& c);
    bool& dataGetInner(int x, int y);
public:

    static const float recSize;
    bool* data;

    long long sizeX;
    long long sizeY;

    bool dataGet(int x, int y);
    void addShape(TetrisShape& shape,int x,int y);
    bool checkIfShapeFits(TetrisShape& shape,int x, int y);


    TetrisContainer(long long x, long long y);
    ~TetrisContainer();

    void draw(RenderWindow& window);

    static int floatToIntPerContainerGrid(float x);
};

