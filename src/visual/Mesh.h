//
// Created by shifeng on 3/18/21.
//

#ifndef MCMC_MESH_H
#define MCMC_MESH_H


#include <glm/glm.hpp>
#include <GL/glew.h>


// class representing data of vertices
class Vertex {
public:
    Vertex() : pos(0,0,0) {};

    Vertex(const glm::vec3& pos) {
        this -> pos = pos;
    }


    Vertex(Vertex& vertex){
        pos = *vertex.GetPos();
    }

// move constructor. Needed in manipulations of std::vector<Vertex>
    Vertex(Vertex&& rhsVertex) : pos(rhsVertex.pos) {}

    void operator=(const Vertex& vec) {
        pos = vec.pos;
//        return *this;
    }

    inline glm::vec3* GetPos() { return &pos; }
private:
    glm::vec3 pos;
};


// class of mesh
class Mesh {
public:
    Mesh();
    Mesh(Vertex* vertices, unsigned int numVertices);
    Mesh(const Mesh& other);
    // Mesh(Mesh&& rhs);
    void operator=(const Mesh& other);
    void draw();  // take the mesh and draw with GPU (drop into pipline and make into image)
    void drawQuads();
    void drawCircle(float r);
    virtual ~Mesh();

private:

    // user-defined data type that consists of integral constants
    enum {
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;  // how many things to draw
};



#endif //MCMC_MESH_H
