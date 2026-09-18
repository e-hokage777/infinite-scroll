#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include <vector>
#include "glad/gl.h"
#include "primitive.h"
#include "drawable.h"

using namespace std;

class Plane: public Drawable
{
protected:
    float width;
    float height;

public:
    glm::vec3 position;
    Plane(float width, float height)
    {
        this->width = width;
        this->height = height;

        initMesh();
    }

    void Draw(Shader shader)
    {

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);

        shader.uniformMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

protected:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    // vector<Texture> textures;

private:
    void initMesh()
    {
        // defining vertices
        this->vertices = {
            {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{width, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f/12.0f, 0.0f}},
            {{0.0f, height, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f/10.0f}},
            {{width, height, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f/12.0f, 1.0f/10.0f}}};

        this->indices = {
            0, 1, 3,
            0, 2, 3};

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};
