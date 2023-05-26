#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <QColorDialog>
#include <iostream>
#include <algorithm>

using namespace std;

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im=QImage(1000, 500, QImage::Format_RGB32);
    im.fill(0);
    obrazek=QImage(":/zdj/galio.jpg");
    kolor=QColor::fromRgb(255,255,255);
    resetScene();

}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);

}


void Ekran::mousePressEvent(QMouseEvent *e)
{

    if(e->button()==Qt::LeftButton)
    {
        p1.x=e->pos().x();
        p1.y=e->pos().y();
        if(p1.x<498)
        {
            if(lista1.size()==3)
            {
                resetScene();
            }
            drawPunkt(p1.x,p1.y,203,206,212);
            lista1.push_back({p1.x,p1.y});
            if(lista1.size()==3)
            {
                drawTriangleLines(lista1);
            }
        }
        else if(p1.x>502)
        {
            if(lista2.size()==3)
            {
                resetScene();
            }
            drawPunkt(p1.x,p1.y,203,206,212);
            lista2.push_back({p1.x,p1.y});
            if(lista2.size()==3)
            {
                drawTriangleLines(lista2);
            }
        }
        if(lista1.size()==3&&lista2.size()==3)
        {
            drawTriangle(lista2[0].x,lista2[0].y,lista2[1].x,lista2[1].y,lista2[2].x,lista2[2].y,lista1[0].x,lista1[0].y,lista1[1].x,lista1[1].y,lista1[2].x,lista1[2].y);
        }
        update();

    }

}

void Ekran::drawPixel(int x,int y,int r,int g,int b,QImage *img)
{
    if((x<img->width()&&x>=0)&&(y<img->height()&&y>=0))
    {
        uchar *pix=img->scanLine(y)+4*x;
        pix[0]=b;
        pix[1]=g;
        pix[2]=r;
    }
}

void Ekran::getPixel(int x, int y, int &r, int &g, int &b,QImage *img)
{
    if((x<img->width()&&x>=0)&&(y<img->height()&&y>=0))
    {
        uchar *pix=img->scanLine(y)+4*x;
        b=pix[0];
        g=pix[1];
        r=pix[2];
    }
}

void Ekran::drawPunkt(int x,int y,int r,int g,int b)
{
    for(int i=y-2;i<=y+2;i++)
    {
        for(int j=x-2;j<=x+2;j++)
        {
          drawPixel(j,i,r,g,b,&im);
        }
    }
    update();
}

void Ekran::linia(int x1,int y1,int x2, int y2,int r,int g,int b)
{
    if(abs(y2-y1)<=abs(x2-x1))
    {
            float y=y1;
            float a=(float)(y2-y1)/(x2-x1);
            if(x1<x2)
            {
                for(int i=x1;i<=x2;i++)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b,&im);
                    y+=a;
                }
            }
            else
            {
                for(int i=x1;i>=x2;i--)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b,&im);
                    y-=a;
                }
            }
        }
        else
        {
            float x=x1;
            float a=(float)(x1-x2)/(y1-y2);
            if(y1<y2)
            {
                for(int i=y1;i<=y2;i++)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b,&im);
                    x+=a;
                }
            }
            else
            {
                for(int i=y1;i>=y2;i--)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b,&im);
                    x-=a;
                }
            }
        }
    update();
}

void Ekran::drawTriangle(int xA,int yA,int xB,int yB,int xC,int yC,int xAt,int yAt,int xBt,int yBt,int xCt,int yCt)
{
    color pix;
    int ymax=lista2[0].y,ymin=lista2[0].y;
    float v,w,u;
    int xt,yt;
    int a1,a2,b;
    float dolnadelta=1/(float)((xB-xA)*(yC-yA)-(yB-yA)*(xC-xA));
    QVector<wsp> wspl;
    QVector<int> tabX;
    for(coord i:lista2)
    {
        if(i.y>ymax)
        {
            ymax=i.y;
        }
        if(i.y<ymin)
        {
            ymin=i.y;
        }
    }
    for(int i=1;i<lista2.size();i++)
    {
        a1=lista2[i].y-lista2[i-1].y;
        a2=lista2[i].x-lista2[i-1].x;
        b=lista2[i].y*a2-lista2[i].x*a1;
        wspl.push_back({a1,a2,b});
    }
    a1=lista2[0].y-lista2[lista2.size()-1].y;
    a2=lista2[0].x-lista2[lista2.size()-1].x;
    b=lista2[0].y*a2-lista2[0].x*a1;
    wspl.push_back({a1,a2,b});
    for(int i=ymin;i<=ymax;i++)
    {
        tabX.clear();
        for(int j=1;j<lista2.size();j++)
        {
            check(tabX,wspl,j-1,j,i);
        }
        check(tabX,wspl,lista2.size()-1,0,i);
        sort(tabX.begin(),tabX.end());
        for(int j=1;j<tabX.size();j+=2)
        {
            p1.x=tabX[j-1];
            p2.x=tabX[j];
            for(int k=p1.x;k<=p2.x;k++)
            {
                v=dolnadelta*((k-xA)*(yC-yA)-(i-yA)*(xC-xA));
                w=dolnadelta*((xB-xA)*(i-yA)-(yB-yA)*(k-xA));
                u=1-v-w;
                xt=u*xAt+v*xBt+w*xCt;
                yt=u*yAt+v*yBt+w*yCt;
                xt-=50;
                yt-=100;
                xt=xt%obrazek.width();
                yt=yt%obrazek.height();
                if(xt<0)
                {
                    xt+=obrazek.width();
                }
                if(yt<0)
                {
                    yt+=obrazek.height();
                }
                getPixel(xt,yt,pix.red,pix.green,pix.blue,&obrazek);
                drawPixel(k,i,pix.red,pix.green,pix.blue,&im);
            }
        }

    }
    drawTriangleLines(lista2);
}


void Ekran::maxMin(int &l1,int &l2)
{
    int pom;
    if(l1<l2)
    {
       pom=l1;
       l1=l2;
       l2=pom;
    }
}


void Ekran::check(QVector<int> &tabX,QVector <wsp> wspl,int index1,int index2,int i)
{
    int x;
    int point1,point2;
    point1=lista2[index1].y;
    point2=lista2[index2].y;
    maxMin(point1,point2);
    if(i<point1&&i>=point2)
    {
        if(wspl[index1].a1!=0)
        {
            x=(i*wspl[index1].a2-wspl[index1].b)/(float)wspl[index1].a1;
            point1=lista2[index1].x;
            point2=lista2[index2].x;
            maxMin(point1,point2);
            if(x<=point1&&x>=point2)
            {
                tabX.push_back(x);
            }
        }
    }
}

void Ekran::drawGranica()
{
    linia(498,0,498,500,158,154,142);
    linia(499,0,499,500,158,154,142);
    linia(500,0,500,500,158,154,142);
    linia(501,0,501,500,158,154,142);
    linia(502,0,502,500,158,154,142);
}

void Ekran::resetScene()
{
    color pix;
    lista1.clear();
    lista2.clear();
    im.fill(0);
    for(int i=0;i<obrazek.height();i++)
    {
        for(int j=0;j<obrazek.width();j++)
        {
            getPixel(j,i,pix.red,pix.green,pix.blue,&obrazek);
            drawPixel(j+50,i+100,pix.red,pix.green,pix.blue,&im);
        }
    }
    drawGranica();
}


void Ekran::drawTriangleLines(QVector<coord> lista)
{
    for(int i=1;i<=2;i++)
    {
        linia(lista[i].x,lista[i].y,lista[i-1].x,lista[i-1].y,255,255,255);
    }
    linia(lista[2].x,lista[2].y,lista[0].x,lista[0].y,255,255,255);
}


