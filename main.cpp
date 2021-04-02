#include <iostream>
#include "src/Matrix.h"
#include "src/visual/Visual.h"
#include "src/visual/Mesh.h"
#include <glm/glm.hpp>
#include <unistd.h>

static const int WIDTH = 800;
static const int HEIGHT = 400;
static const unsigned int sec = 1000000;  // 1 sec

int main() {

    std::vector<Vertex> vertices;
    vertices.resize(2);
    vertices[0] = glm::vec3(-0.5,0,0);
    vertices[1] = glm::vec3(-0.5,0.5,0);

    Matrix<float> M(300,300);
    M.fillRand();

    Visual<float> visual_circle(vertices);  // initialize visual buffer for circles
    visual_circle.frame(WIDTH, HEIGHT);  // update frame for buffer

    Visual<float> visual_chess(M);  // initialize visual buffer for chess board
    visual_chess.frame(WIDTH, HEIGHT);  // update frame for buffer
    visual_chess.loadConfig();


//    visual_chess.showChess();
    Display display(WIDTH, HEIGHT, "TestShow");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!display.IsClosed()) {
        glClear(GL_COLOR_BUFFER_BIT);
        visual_circle.drawCircles(0.1);

        M.fillRand();
        visual_chess.loadConfig();
        visual_chess.drawChess();

        usleep(sec / 60);  // restrict framerate

        display.Update();
    }



    return 0;
}
