//
// Created by shifeng on 3/18/21.
//

#ifndef MCMC_VISUAL_H
#define MCMC_VISUAL_H

#include "../Matrix.h"
#include "Mesh.h"
#include "Display.h"
#include <glm/glm.hpp>
#include <vector>
#include <omp.h>

template<class T>
class Visual {
public:
    Visual()  : width(800),
                height(800),
                pixel_h(0),
                pixel_w(0),
                indx(0),
                indy(0),
                num2draw(0),
                config(nullptr)
    {}

    // for grid-based global picture
    Visual(Matrix<T>& m)  : width(800),
                            height(800),
                            pixel_h(0),
                            pixel_w(0),
                            indx(0),
                            indy(0),
                            num2draw(0) {
        config = &m;
    }

    // for coordinate-based picture (circle, points, etc)
    Visual(std::vector<Vertex>& vec)  : width(800),
                                        height(800),
                                        pixel_h(0),
                                        pixel_w(0),
                                        indx(0),
                                        indy(0),
                                        num2draw(0) {
        int size = vec.size();
        vertices.reserve(size);
        for (int i = 0; i < size; ++i)
            vertices.emplace_back(vec[i]);
    }

    // Copy constructor
    Visual(Visual& vis) {
        width = vis.width;
        height = vis.height;
        pixel_w = vis.pixel_w;
        pixel_h = vis.pixel_h;
        indx = vis.indx;
        indy = vis.indy;
        num2draw = vis.num2draw;
        config = vis.config;

        vertices.clear();
        int size = vis.vertices.size();
        vertices.reserve(size);
        for (int i = 0; i < size; ++i)
            vertices.emplace_back(vis.vertices[i]);
    }

    virtual ~Visual() {}

//    void frame(int width, int height) {
//        this -> width = width;
//        this -> height = height;
//    }

    void frame(int width, int height) {
        // frame of a chessboard. For plotting matrix
        this -> width = width;
        this -> height = height;
        pixel_w = 2.0 / config -> cols();
        pixel_h = 2.0 / config -> rows();
    }

    void loadConfig();  // load vertex array of 2D configuration from config matrix
    void drawChess();  // draw quads in gl buffer
    void showChess();  // load vertex array and draw a static config using Quads

    void drawCircles(GLfloat r);  // draw circles in gl buffer
    void plot();  // draw a single frame using current vertex array in gl buffer

    void printConfig() {(*config).print();}

private:
    std::vector<int> indx;
    std::vector<int> indy;
    int width;
    int height;
    int num2draw;
    T pixel_w;
    T pixel_h;
    Matrix<T> *config;
    std::vector<Vertex> vertices;
};


// member function definitions
template <class T>
void Visual<T>::loadConfig() {
    indx.clear();
    indy.clear();
    vertices.clear();

    int row = config->rows();
    int col = config->cols();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if ((*config)(i,j) > 0.6) {  // change later
                indx.push_back(i);
                indy.push_back(j);
            }
        }
    }
    num2draw = indx.size();

//    std::cout << num2draw << std::endl;

    vertices.reserve(4*num2draw);
//    vertices.resize(4*num2draw);

//        #pragma omp parallel for num_threads(4) default(none)
    for (int i = 0; i < num2draw; ++i) {
        // thread-unsafe
        vertices.emplace_back(Vertex(glm::vec3(-1 + indx[i] * pixel_w, -1 + indy[i] * pixel_h, 0)));
        vertices.emplace_back(Vertex(glm::vec3(-1 + (indx[i] + 1) * pixel_w, -1 + indy[i] * pixel_h, 0)));
        vertices.emplace_back(Vertex(glm::vec3(-1 + (indx[i] + 1) * pixel_w, -1 + (indy[i] + 1) * pixel_h, 0)));
        vertices.emplace_back(Vertex(glm::vec3(-1 + indx[i] * pixel_w, -1 + (indy[i] + 1) * pixel_h, 0)));
    }
}

template <class T>
void Visual<T>::drawChess()  {
    Mesh mesh(&(vertices[0]), 4*num2draw);
    mesh.drawQuads();
}

template <class T>
void Visual<T>::showChess() {
    loadConfig();
    Display display(width, height, "ShowQuads");
    Mesh mesh(&(vertices[0]), 4*num2draw);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!display.IsClosed()) {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh.drawQuads();
        display.Update();
    }
}


template <class T>
void Visual<T>::drawCircles(GLfloat r) {
    for (auto &vertex : vertices) {
        GLfloat x = vertex.GetPos()->x;
        GLfloat y = vertex.GetPos()->y;
        // GLfloat z = vertex.GetPos()->z;

        // To avoid distortion
        GLfloat rescaler = static_cast<float>(width) / static_cast<float>(height);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center
        for (int i = 0; i <= 360; i++)
            glVertex2f(r / rescaler * cos(M_PI * i / 180.0) + x, r * sin(M_PI * i / 180.0) + y);
        glEnd();

    }
}


#endif //MCMC_VISUAL_H
