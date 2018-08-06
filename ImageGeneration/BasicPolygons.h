#ifndef BASIC_POLYGONS_H
#define BASIC_POLYGONS_H

#include "Drawable.h"
#include "Point.h"

#include <cmath>
#include <vector>
#include <utility>

class Line : public Drawable
{
public:
    Line();
    Line(const Point& p1, const Point& p2);
    Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
    Line(const Line& other) = default;
    Line(Line&& other) = default;

    Line& operator=(const Line& other) = default;
    Line& operator=(Line&& other) = default;

    void draw(BitmapImg& canvas, const BGRPalette& color) override;

private:

    void plotLineLow (const Point& p1, const Point& p2, BitmapImg &canvas, const BGRPalette &color);
    void plotLineHigh(const Point& p1, const Point& p2, BitmapImg &canvas, const BGRPalette &color);

    Point p1_;
    Point p2_;
};


Line::Line() : p1_(), p2_()
{
}


Line::Line(const Point &p1, const Point &p2)
: p1_(p1), p2_(p2)
{
}


Line::Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
: p1_(x1, y1), p2_(x2, y2)
{
}


void Line::draw(BitmapImg &canvas, const BGRPalette &color)
{
    if (abs(p2_.y() - p1_.y()) < abs(p2_.x() - p1_.x()))
    {
        if (p1_.x() > p2_.x()) {
            plotLineLow(p2_, p1_, canvas, color);
        }
        else {
            plotLineLow(p1_, p2_, canvas, color);
        }
    }
    else
    {
        if (p1_.y() > p2_.y()) {
            plotLineHigh(p2_, p1_, canvas, color);
        }
        else {
            plotLineHigh(p1_, p2_, canvas, color);
        }
    }
}


void Line::plotLineLow(const Point& p1, const Point& p2, BitmapImg &canvas, const BGRPalette &color)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();

    int y_sign = 1;

    if (dy < 0)
    {
        y_sign = -1;
        dy = -dy;
    }

    int approx = 2 * dy - dx;
    unsigned y_step = p1.y();

    for (unsigned x_step = p1.x(); x_step < p2.x(); ++x_step)
    {
        canvas(x_step, y_step) = color;  // TODO add sign + range check

        if (approx > 0)
        {
            y_step = y_step + y_sign;
            approx = approx - 2 * dx;
        }

        approx = approx + 2 * dy;
    }
}


void Line::plotLineHigh(const Point& p1, const Point& p2, BitmapImg &canvas, const BGRPalette &color)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();

    int x_sign = 1;

    if (dx < 0)
    {
        x_sign = -1;
        dx = -dx;
    }

    int approx = 2 * dx - dy;
    unsigned x_step = p1.x();

    for (unsigned y_step = p1.y(); y_step < p2.y(); ++y_step)
    {
        canvas(x_step, y_step) = color;  // TODO add sign + range check

        if (approx > 0)
        {
            x_step = x_step + x_sign;
            approx = approx - 2 * dy;
        }

        approx = approx + 2 * dx;
    }
}



#endif //BASIC_POLYGONS_H