#include "Game.h"

glm::mat4 Game::projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
std::vector<GameObject*> GameObjects = std::vector<GameObject*>();

Game::Game(unsigned int width, unsigned int height) : width(width), height(height){
    // Initializing glfw
    if (!glfwInit()) std::cout << "Failed to initialize glfw" << std::endl;
    // Specifies OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
Game::~Game() {

}


void Game::Render(const SpriteRenderer &renderer) {
    // Renders each gameobject in the scene
    for (GameObject* go : GameObject::GameObjects) {
        go->Render(renderer);
    }
}

void Game::Update(float dt) {
    // Calls update on each gameobject
    for (GameObject* go : GameObject::GameObjects) {
        go->Update(dt);
    }
}

// Called whenever a key is pressed or released
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Sets pressed boolean for pressed or released key
    ResourceManager::keys[key] = action == GLFW_RELEASE ? false : true;
}

void Game::InitializeWindow(GLFWwindow* window) {
    // Checks for glfw window creation error
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    // Specifies function to handle key events
    glfwSetKeyCallback(window, key_callback);
    // After context is created, GLAD can be initialized
    glfwMakeContextCurrent(window);
    // Loads GLAD and checks for errors
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    // Sets size of OpenGL 
    glViewport(0, 0, width, height);
}

void Game::Run(const char* title) {
    // Creates the glfw window 
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    // Sets up glfw and loads glad
    InitializeWindow(window);

    // Loads shaders and textures
    ResourceManager::LoadResources();

    // For calculating time between frames
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Creates our sprite renderer to render the scene
    SpriteRenderer rend = SpriteRenderer(ResourceManager::shaderMap["default"]);

    // Creates gameobjects
    Player Mike(ResourceManager::textureMap["Mike"], glm::vec2(100.0f, 200.0f), glm::vec2(400.0f, 300.0f), 0.0f);
    Enemy Ethan(ResourceManager::textureMap["Ethan"], glm::vec2(500.0f, 200.0f), glm::vec2(400.0f, 300.0f), 0.0f);


    while (!glfwWindowShouldClose(window)) {

        // Calculate delta time
        float currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        // TODO: delete print framerate
        std::cout << 1 / deltaTime << std::endl;

        glClear(GL_COLOR_BUFFER_BIT);
        // Updates gameobjects
        Update(deltaTime);
        // Renders frame here
        Render(rend);

        glfwSwapBuffers(window);
        // Window events (input, resize, etc.)
        glfwPollEvents();
    }

    glfwTerminate();

}