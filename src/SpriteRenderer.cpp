#include "SpriteRenderer.h"

glm::mat4 SpriteRenderer::projection = glm::ortho(0.0f, float(SCREEN_START_WIDTH), float(SCREEN_START_HEIGHT), 0.0f, -1.0f, 1.0f);

SpriteRenderer::SpriteRenderer(Shader& shader) : VAO(0) {
    this->shader = shader;
    
    // Quad vertices
    float vertices[] = {
        // pos       tex
       -0.5f, 0.5f,  0.0f,1.0f,
        0.5f,-0.5f,  1.0f,0.0f,
       -0.5f,-0.5f,  0.0f,0.0f,

       -0.5f, 0.5f,  0.0f, 1.0f,
        0.5f, 0.5f,  1.0f, 1.0f,
        0.5f,-0.5f,  1.0f, 0.0f
    };

    // Creates VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind and load in data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Point to vertex attributes and enable the attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glEnableVertexAttribArray(0);

}


SpriteRenderer::~SpriteRenderer() {

}


void SpriteRenderer::Render(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotate) const{
    // Activate shader and texture
    shader.Use();
    texture.Bind();
    // Initializes the model matrix as an identity matrix
    glm::mat4 model = glm::mat4(1.0f);
    // Moves it to the correct position
    model = glm::translate(model, glm::vec3(position, 0));

    //TODO: rotation
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    // Scales model matrix
    model = glm::scale(model, glm::vec3(size, 1.0f));
    // Sets model uniform
    shader.SetMat4("model", model);
    shader.SetMat4("projection", glm::ortho(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f));
    // Binds VAO
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind VAO?
}