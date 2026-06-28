#include <maxgl.h>
#include <screen.h>
#include <math.h>

// https://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
/*
void fillBottomFlatTriangle(Point p0, Point p1, Point p2) {
    float invslope1 = (p1.x - p0.x) / (p1.y - p0.y);
    float invslope2 = (p2.x - p0.x) / (p2.y - p0.y);
    float curx1 = p0.x;
    float curx2 = p0.x;

    for (int scanlineY = p0.y; scanlineY <= p1.y; scanlineY++) {
        DrawLine((int)curx1, scanlineY, (int)curx2, scanlineY);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fillTopFlatTriangle(Point p0, Point p1, Point p2) {
    float invslope1 = (p2.x - p0.x) / (p2.y - p0.y);
    float invslope2 = (p2.x - p1.x) / (p2.y - p1.y);
    float curx1 = p2.x;
    float curx2 = p2.x;

    for (int scanlineY = p2.y; scanlineY > p0.y; scanlineY--) {
        DrawLine((int)curx1, scanlineY, (int)curx2, scanlineY);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void DrawTriangleColor(Point p0, Point p1, Point p2)
{
   /* at first sort the three vertices by y-coordinate ascending so p0 is the topmost vertice 
  sortVerticesAscendingByY();

  /* here we know that p0.y <= p1.y <= p2.y
  /* check for trivial case of bottom-flat triangle 
  if (p1.y == p2.y)
  {
    fillBottomFlatTriangle(p0, p1, p2);
  }
  /* check for trivial case of top-flat triangle 
  else if (vt1.y == vt2.y)
  {
    fillTopFlatTriangle(g, vt1, vt2, vt3);
  }
  else
  {
    /* general case - split the triangle in a topflat and bottom-flat one 
    Vertice v4 = new Vertice(
      (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
    fillBottomFlatTriangle(g, vt1, vt2, v4);
    fillTopFlatTriangle(g, vt2, v4, vt3);
  }
}*/

float edgeFunction(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}


void DrawTriangle(Point p0, Point p1, Point p2) {
    const float ABC = edgeFunction(p0, p1, p2);

    if (ABC < 0) {
        //return;
    }

    Point P;
    P.x = 0;
    P.y = 0;

    Color colorA = Color(255, 0, 0);
    Color colorB = Color(0, 255, 0);
    Color colorC = Color(0, 0, 255);

    const float minX = fminf(p0.x, fminf(p1.x, p2.x));
    const float minY = fminf(p0.y, fminf(p1.y, p2.y));
    const float maxX = fmaxf(p0.x, fmaxf(p1.x, p2.x));
    const float maxY = fmaxf(p0.y, fmaxf(p1.y, p2.y));

    for (P.y = minY; P.y < maxY; P.y++) {
    for (P.x = minX; P.x < maxX; P.x++) {
      // Calculate our edge functions
      float ABP = edgeFunction(p0, p1, P);
      float BCP = edgeFunction(p1, p2, P);
      float CAP = edgeFunction(p2, p0, P);

      // Normalise the edge functions by dividing by the total area to get the barycentric coordinates
      float weightA = BCP / ABC;
      float weightB = CAP / ABC;
      float weightC = ABP / ABC;

      // If all the edge functions are positive, the point is inside the triangle
      if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
        // Interpolate the colours at point P
        unsigned char r = colorA.r * weightA + colorB.r * weightB + colorC.r * weightC;
        unsigned char g = colorA.g * weightA + colorB.g * weightB + colorC.g * weightC;
        unsigned char b = colorA.b * weightA + colorB.b * weightB + colorC.b * weightC;
        Color c = Color(r, g, b);
        Color red = Color(255, 0, 0);

        // Draw the pixel
        Screen::SetPixel(P.x, P.y, c);
      }
    }
  }
}