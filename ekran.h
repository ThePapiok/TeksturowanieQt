#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QColor>

struct color
{
    int red;
    int green;
    int blue;
};

struct coord
{
    int x;
    int y;
};

struct wsp
{
    int a1;
    int a2;
    int b;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
        explicit Ekran(QWidget *parent = nullptr);
        void linia(int x1,int y1, int x2,int y2,int r,int g,int b);
        void drawPixel(int x,int y,int r, int g,int b,QImage *img);
        void drawPunkt(int x,int y,int r, int g,int b);
        void maxMin(int &l1,int &l2);
        void check(QVector<int> &tabX,QVector <wsp> wspl,int index1,int index2,int i);
        void drawGranica();
        void resetScene();
        void drawTriangle(int xA,int yA,int xB,int yB,int xC,int yC,int xAt,int yAt,int xBt,int yBt,int xCt,int yCt);
        void drawTriangleLines(QVector<coord> lista);
        void getPixel(int x,int y,int &r,int &g,int &b,QImage *img);
protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
private:
        QImage im,obrazek;
        QVector <coord> lista1,lista2;
        coord p1,p2;
        int tryb=0;
        int id;
        color colorDraw={255,255,255};
        QColor kolor;
signals:

};

#endif // EKRAN_H
