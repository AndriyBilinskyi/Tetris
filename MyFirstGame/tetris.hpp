#include <SFML/Graphics.hpp>
using namespace sf;

class TetrisShape {
private:
    RectangleShape rectangles [4];
    Vector2f position = Vector2f(0.0f,0.0f);;

    void move(int n, int x, int y);
    void move();

    TetrisShape(TetrisShape& t);

    TetrisShape(TetrisShape* spateToRotate, int rotationDirection = 1);


public:
    int number;
    int sizeX;
    int sizeY;
    bool* data = nullptr;
    Color color;

    bool& dataGet(int x, int y);

    TetrisShape(int n, Color c);

    ~TetrisShape();

    void draw(RenderWindow& window);
    void move(float offsetX, float offsetY);
    TetrisShape* transform();

    const Vector2f& getPosition();

    static const unsigned char NumberOfShapes;
};


class TetrisContainer{
private:
    TetrisContainer(TetrisContainer& c);
    Color& dataGetInner(int x, int y);
public:

    static const float recSize;
    Color* data;

    long long sizeX;
    long long sizeY;

    bool dataGet(int x, int y);
    void addShape(TetrisShape& shape,int x,int y);
    bool  removeFilledRow();
    bool checkIfShapeFits(TetrisShape* shape,int x, int y);
    void moveContainer(int fromWhichRow);


    TetrisContainer(long long x, long long y);
    ~TetrisContainer();

    void draw(RenderWindow& window);

    static int floatToIntPerContainerGrid(float x);
};

