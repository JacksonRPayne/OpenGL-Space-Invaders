#include "Game.h"

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
    // TODO: render background
    // 
    
    // Renders each gameobject in the scene
    for (GameObject* go : GameObject::GameObjects) {
        go->Render(renderer);
    }
}

void Game::Update(float dt) {
    // Calls update on each gameobject
    for (int i = 0; i < GameObject::GameObjects.size(); i++) {
        GameObject::GameObjects[i]->Update(dt);
    }
}

// Called whenever a key is pressed or released
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Sets pressed boolean for pressed or released key
    ResourceManager::keys[key] = action == GLFW_RELEASE ? false : true;
}

// Called when window is resized
void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SpriteRenderer::projection = glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 1.0f);
}

void Game::InitializeWindow(GLFWwindow* window) {
    // Checks for glfw window creation error
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    // Specifies functions to handle key events and window resize
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
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
    // Locks window aspect ratio
    glfwSetWindowAspectRatio(window, width, height);
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
    Player Mike(ResourceManager::textureMap["Mike"], glm::vec2(400.0f, 525.0f), glm::vec2(100.0f, 75.0f), 0.0f);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 9; x++) {
            Enemy* ethan = new Enemy(ResourceManager::textureMap["Ethan"], glm::vec2(42 + (SCREEN_START_WIDTH / 9) * x, 
                50 + (SCREEN_START_HEIGHT/5) * y), glm::vec2(85.0f, 150.0f), 0.0f);
            Enemy::Enemies.push_back(ethan);
        }
    }
   
    // Game loop
    while (!glfwWindowShouldClose(window)) {

        // Calculate delta time
        float currFrame = (float)glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        // TODO: delete print framerate
        //std::cout << 1 / deltaTime << std::endl;

        glClear(GL_COLOR_BUFFER_BIT);
        // Updates gameobjects
        Update(deltaTime);
        // Renders frame here
        Render(rend);

        glfwSwapBuffers(window);
        // Window events (input, resize, etc.)
        glfwPollEvents();
    }

    for (int i = 0; i < Enemy::Enemies.size(); i++) delete Enemy::Enemies[i];

    glfwTerminate();

}