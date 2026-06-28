#include <stdio.h>
#include <maxgl.h>
#include <cstdlib>
#include <cmath>


Point NDCtoScreen (Point p) {
    int width, height;
    GetResolution(&width, &height);
    // -1 - 1 to 0 - 2 to 0 - 1 to 0 - w
    return Point(
        (p.x + 1) / 2 * width,
        (p.y + 1) / 2 * height
    );
}

Point ProjectVector(Vector v) {
    return Point(
        v.x / v.z,
        v.y / v.z
    );
}

Vector TranslateZ(Vector v, float dz) {
    return Vector(
        v.x,
        v.y,
        v.z + dz
    );
}

Vector Translate(Vector v, Vector translation) {
    return Vector(
        v.x + translation.x,
        v.y + translation.y,
        v.z + translation.z
    );
}

Vector RotateXZ(Vector v, float angle) {
    const float c = cos(angle);
    const float s = sin(angle);
    return Vector(
        v.x * c - v.z * s,
        v.y,
        v.x * s + v.z * c
    );
}

typedef unsigned int Triangle[3];

int main(void) {
    
    if (Initialize()) {
        return -1;
    }

    ClearScreen();
    
    int width, height;
    GetResolution(&width, &height);

    //SetDrawColor(Color(255, 0, 0));
    //DrawLine( width - 10, height - 10, 10, 10);
    //SetDrawColor(Color(0, 255, 0));
    //DrawLine(width - 10, 10, 10, height - 10);

    /*for (int i = 0; i < height; i++) {
        SetDrawColor(Color(rand(), rand(), rand()));
        DrawLine(0, i, width, i);
    }*/

    SetDrawColor(Color(255, 0, 0));
    Point p0 = Point(10, 10);
    Point p1 = Point(10, height - 10);
    Point p2 = Point(width - 10, height - 10);
    Point p3 = Point(width - 10, 10);

    DrawLine(p0, p1);
    SetDrawColor(Color(255, 128, 0));
    DrawLine(p1, p2);
    SetDrawColor(Color(128, 128, 0));
    DrawLine(p2, p3);
    SetDrawColor(Color(0, 128, 255));
    DrawLine(p3, p0);

    SetDrawColor(Color(0, 0, 255));
    DrawLine(p3, p1);

    SetDrawColor(Color(255, 0, 255));
    DrawLine(p0, p2);

    Point zero = Point(0, 0.5);
    zero = NDCtoScreen(zero);
    SetDrawColor(Color(255, 255, 255));
    DrawPixel(zero);



    /*for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            SetDrawColor(Color(-i, i, j));
            DrawPixel(i, j);
        }
    }*/

    Vector translations[4] = {
        Vector(0.5, 0.5, 2),
        Vector(-0.5, 0.5, 2),
        Vector(0.5, -0.5, 2),
        Vector(-0.5, -0.5, 2)
    };

    const int vtxCount = 8;
    Vector vertices[vtxCount] = {
        Vector(0.25, 0.25, 0.25),
        Vector(-0.25, 0.25, 0.25),
        Vector(-0.25, -0.25, 0.25),
        Vector(0.25, -0.25, 0.25),

        Vector(0.25, 0.25, -0.25),
        Vector(-0.25, 0.25, -0.25),
        Vector(-0.25, -0.25, -0.25),
        Vector(0.25, -0.25, -0.25)
    };

    Color colors[vtxCount] = {
        Color(255, 255, 255),
        Color(255, 255, 255),
        Color(255, 0, 0),
        Color(255, 255, 255),
        Color(255, 255, 255),
        Color(255, 255, 255),
        Color(255, 255, 255),
        Color(255, 255, 255)
    };

    /*Triangle triangles[12] = {
        {0, 1, 2},
        {0, 3, 2},
        {4, 5, 6},
        {4, 6, 7},
        {4, 0, 3},
        {4, 3, 7},
        {7, 3, 2},
        {7, 2, 6},
        {1, 5, 6},
        {1, 6, 2},
        {4, 0, 1},
        {4, 1, 5}
    };*/

    Triangle triangles[12] = {
        // Front Face (+Z) - Looking at it, CW is 0->3->2->1
        {0, 3, 2},
        {0, 2, 1},

        // Back Face (-Z) - Looking at it from behind, CW is 4->5->6->7
        {4, 5, 6},
        {4, 6, 7},

        // Right Face (+X) - Looking from the right, CW is 0->4->7->3
        {0, 4, 7},
        {0, 7, 3},

        // Bottom Face (-Y) - Looking from the bottom, CW is 3->7->6->2
        {3, 7, 6},
        {3, 6, 2},

        // Left Face (-X) - Looking from the left, CW is 1->2->6->5
        {2, 6, 1},
        {1, 6, 5},

        // Top Face (+Y) - Looking from the top, CW is 0->1->5->4
        {0, 1, 5},
        {0, 5, 4}
    };

    float dz = 2;
    float angle = 0;
    while(!Update()){
        float dt = GetDeltaTime();
        //dz += 0.1 * dt;
        angle += 0.25 * 3.14 * dt;
        ClearScreen();

        

        Point p0;
        Point p1;
        Point p2;
        for (int tr = 0; tr < 4; tr++) {
            for (int i = 0; i < 12; i++) {
                Triangle *t = &triangles[i];
                const Vector a = vertices[(*t)[0]];
                const Vector b = vertices[(*t)[1]];
                const Vector c = vertices[(*t)[2]];
                p0 = NDCtoScreen(ProjectVector(Translate(RotateXZ(a, angle), translations[tr])));
                p1 = NDCtoScreen(ProjectVector(Translate(RotateXZ(b, angle), translations[tr])));
                p2 = NDCtoScreen(ProjectVector(Translate(RotateXZ(c, angle), translations[tr])));
                DrawTriangle(p0, p1, p2);
            }
        

            /*Point screenpoint;
            for (int i = 0; i < vtxCount; i++) {
                screenpoint = NDCtoScreen(ProjectVector(Translate(RotateXZ(vertices[i], angle), translations[tr])));
                SetDrawColor(colors[i]);
                DrawPixel(screenpoint);
            }*/
        }

    }

    Cleanup();
    return 0;
}