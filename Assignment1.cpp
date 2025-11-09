#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void createSphere(float radius, int sectorCount, int stackCount,
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices)
{
    vertices.clear();
    indices.clear();
    float x, y, z, xy;                           // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius; // normals (optional)
    float s, t;                                  // texture coords (optional)
    float sectorStep = 2 * 3.1415 / sectorCount;
    float stackStep = 3.1415 / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = 3.1415 / 2 - i * stackStep;   // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // optional color (random or fixed)
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Function to capture screen
void dump_framebuffer_to_ppm(std::string prefix, unsigned int width, unsigned int height) {
    int pixelChannel = 3;
    int totalPixelSize = pixelChannel * width * height * sizeof(GLubyte);
    GLubyte* pixels = new GLubyte[totalPixelSize];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    std::string file_name = prefix + ".ppm";
    std::ofstream fout(file_name);
    fout << "P3\n" << width << " " << height << "\n" << 255 << std::endl;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            size_t cur = pixelChannel * ((height - i - 1) * width + j);
            fout << (int)pixels[cur] << " " << (int)pixels[cur + 1] << " " << (int)pixels[cur + 2] << " ";
        }
        fout << std::endl;
    }
    delete[] pixels;
    fout.flush();
    fout.close();
}

int cameraPosition = 1;

// Interactive keys
void processInput(GLFWwindow* window)
{
    // Escape to exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Number keys to change camera position
    /*
    // Used for task 1
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        cameraPosition = 1;
        std::cout << "Camera Position 1 (2, 7, 3)" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cameraPosition = 2;
        std::cout << "Camera Position 2 (-3, -3, -3)" << std::endl;
    }
    */

    /*
    // Used for task 2
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        cameraPosition = 1;
        std::cout << "Camera Position 1 (0, 0, 120)" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cameraPosition = 2;
        std::cout << "Camera Position 2 (0, 218, 1)" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        cameraPosition = 3;
        std::cout << "Camera Position 3 (-180, 70, 20)" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        cameraPosition = 4;
        std::cout << "Camera Position 4 (-120, 100, 80)," << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        cameraPosition = 5;
        std::cout << "Camera Position 5 (70, 80, 90)" << std::endl;
    }
    */

    // Used for task 4
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        cameraPosition = 1;
        std::cout << "Looking at the Sun" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cameraPosition = 2;
        std::cout << "Looking at the Earth" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        cameraPosition = 3;
        std::cout << "Looking at the Moon" << std::endl;
    }

    // P to capture screen
    /*
    // Used to capture screen for task 1
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Capture Window " << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        if (cameraPosition == 1)
            dump_framebuffer_to_ppm("oct1.ppm", buffer_width, buffer_height);
        else
            dump_framebuffer_to_ppm("oct2.ppm", buffer_width, buffer_height);
    }
    */

    /*
    // Used to capture screen for task 2
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Capture Window " << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        if (cameraPosition == 1)
            dump_framebuffer_to_ppm("static_front.ppm", buffer_width, buffer_height);
        else if (cameraPosition == 2)
            dump_framebuffer_to_ppm("static_top.ppm", buffer_width, buffer_height);
        else if (cameraPosition == 3)
            dump_framebuffer_to_ppm("static_left.ppm", buffer_width, buffer_height);
        else if (cameraPosition == 4)
            dump_framebuffer_to_ppm("static_sun.ppm", buffer_width, buffer_height);
        else if (cameraPosition == 5)
            dump_framebuffer_to_ppm("static_moon.ppm", buffer_width, buffer_height);
    }
    */

    /*
    // Used to capture screen for task 3
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Capture Window " << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        dump_framebuffer_to_ppm("rotate_d365_earth.ppm", buffer_width, buffer_height); // Name manually changed for corresponding screenshot in task 3

    }
    */
    
}

// Used for task 2
// Create octahedrons
void generateOctahedronData(float size,
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices) {
    float h = size * 0.5f;

    glm::vec3 A(-h, 0, 0), B(0, 0, h), C(h, 0, 0),
        D(0, 0, -h), E(0, h, 0), F(0, -h, 0);

    // Colours
    glm::vec3 RED(1, 0, 0), GREEN(0, 1, 0), BLUE(0, 0, 1), GREY(0.5f, 0.5f, 0.5f);
    glm::vec3 FUCHSIA(1, 0, 1), YELLOW(1, 1, 0), AQUA(0, 1, 1), WHITE(1, 1, 1);

    struct Face { glm::vec3 p0, p1, p2, color; };
    std::vector<Face> faces = {
        {A,B,E, RED},     // ABE
        {B,C,E, GREEN},   // BCE
        {C,D,E, BLUE},    // CDE
        {D,A,E, GREY},    // DAE
        {B,A,F, FUCHSIA}, // BAF
        {C,B,F, YELLOW},  // CBF
        {D,C,F, AQUA},    // DCF
        {A,D,F, WHITE}    // ADF
    };

    vertices.clear(); indices.clear();
    unsigned int idx = 0;
    for (auto& f : faces) {
        glm::vec3 ps[3] = { f.p0,f.p1,f.p2 };
        for (int i = 0; i < 3; ++i) {
            vertices.push_back(ps[i].x);
            vertices.push_back(ps[i].y);
            vertices.push_back(ps[i].z);
            vertices.push_back(f.color.r);
            vertices.push_back(f.color.g);
            vertices.push_back(f.color.b);
            indices.push_back(idx++);
        }
    }
}

// Rotation angle functions
float day = 0.0f;
// Sun
float get_sun_rotate_angle_around_itself(float day) {
    return (360.0f / 27.0f) * day;
}

// Earth
float get_earth_rotate_angle_around_sun(float day) {
    return (360.0f / 365.0f) * day;
}

float get_earth_rotate_angle_around_itself(float day) {
    return 360.0f * day;
}

// Moon
float get_moon_rotate_angle_around_earth(float day) {
    return (360.0f / 28.0f) * day;
}

float get_moon_rotate_angle_around_itself(float day) {
    return (360.0f / 28.0f) * day;
}

// Shader
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 vertexColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main(){
       gl_Position = projection * view * model * vec4(aPos, 1.0);
       vertexColor = aColor;
     }

)";

const char* fragmentShaderSource = R"(
    #version 330 core 
    out vec4 FragColor;
    in vec3 vertexColor;

    void main(){
        FragColor = vec4(vertexColor, 1.0);
    }
)";



int main()
{
    // Instantiate the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window object
    GLFWwindow* window = glfwCreateWindow(1024, 576, "Assignment 1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compiling and linking shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Face culling and depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    /*
    // Used for task 1
    // Octahedron geomertry
    float vertices[] = {
        // Top half
        -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,    // Face ABE
        0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,
        0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,

        0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,    // Face BCE 
        1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,    // Face CDE
        0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

        0.0f,  0.0f, -1.0f,  0.5f, 0.5f, 0.5f,    // Face DAE
       -1.0f,  0.0f,  0.0f,  0.5f, 0.5f, 0.5f,
        0.0f,  1.0f,  0.0f,  0.5f, 0.5f, 0.5f,

        // Bottom half
        0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 1.0f,    // Face BAF
       -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
        0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,

        1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,    // Face CBF
        0.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.0f,
        0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,

        0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,    // Face DCF
        1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

       -1.0f, -0.0f,  0.0f,  1.0f, 1.0f, 1.0f,    // Face ADF
        0.0f,  0.0f, -1.0f,  1.0f, 1.0f, 1.0f,
        0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9,10,11,
    12,13,14,
    15,16,17,
    18,19,20,
    21,22,23
    };
    */
    
    // Generate Sun, Moon, and Earth
    std::vector<float> vertices_sun, vertices_earth, vertices_moon;
    std::vector<unsigned int> indices_sun, indices_earth, indices_moon;

    generateOctahedronData(18.0f, vertices_sun, indices_sun);
    generateOctahedronData(10.0f, vertices_earth, indices_earth);
    generateOctahedronData(6.0f, vertices_moon, indices_moon);

    // Make circlce
    std::vector<float> vertices_sphere;
    std::vector<unsigned int> indices_sphere;
    createSphere(10.0f, 36, 18, vertices_sphere, indices_sphere);

   
    /*
    // Used for task 1
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */

    // Circle
    unsigned int VAO_sphere, VBO_sphere, EBO_sphere;
    glGenVertexArrays(1, &VAO_sphere);
    glGenBuffers(1, &VBO_sphere);
    glGenBuffers(1, &EBO_sphere);

    glBindVertexArray(VAO_sphere);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere);
    glBufferData(GL_ARRAY_BUFFER, vertices_sphere.size() * sizeof(float), vertices_sphere.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_sphere);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sphere.size() * sizeof(unsigned int), indices_sphere.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    // Used for task 2, 3, & 4
    unsigned int VAO_sun, VBO_sun, EBO_sun;
    glGenVertexArrays(1, &VAO_sun);
    glGenBuffers(1, &VBO_sun);
    glGenBuffers(1, &EBO_sun);

    glBindVertexArray(VAO_sun);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sun);
    glBufferData(GL_ARRAY_BUFFER, vertices_sun.size() * sizeof(float), vertices_sun.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_sun);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sun.size() * sizeof(unsigned int), indices_sun.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int VAO_earth, VBO_earth, EBO_earth;
    glGenVertexArrays(1, &VAO_earth);
    glGenBuffers(1, &VBO_earth);
    glGenBuffers(1, &EBO_earth);

    glBindVertexArray(VAO_earth);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_earth);
    glBufferData(GL_ARRAY_BUFFER, vertices_earth.size() * sizeof(float), vertices_earth.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_earth);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_earth.size() * sizeof(unsigned int), indices_earth.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int VAO_moon, VBO_moon, EBO_moon;
    glGenVertexArrays(1, &VAO_moon);
    glGenBuffers(1, &VBO_moon);
    glGenBuffers(1, &EBO_moon);

    glBindVertexArray(VAO_moon);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_moon);
    glBufferData(GL_ARRAY_BUFFER, vertices_moon.size() * sizeof(float), vertices_moon.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_moon);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_moon.size() * sizeof(unsigned int), indices_moon.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f); // Background colour

    float day = 0, inc = 1.0f / 96;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        day += inc;

        // Camera positions / projection
        /*
        // Used for task 1
        glm::mat4 view;
        if (cameraPosition == 1)
            view = glm::lookAt(glm::vec3(2.0f, 7.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        else
            view = glm::lookAt(glm::vec3(-3.0f, -3.0f, -3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        */

        /*
        // Used for task 2
        glm::mat4 view;
        if (cameraPosition == 1)
            view = glm::lookAt(glm::vec3(0.0f, 0.0f, 120.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        else if (cameraPosition == 2)
            view = glm::lookAt(glm::vec3(0.0f, 218.0f, 1.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        else if (cameraPosition == 3)
            view = glm::lookAt(glm::vec3(-180.0f, 70.0f, 20.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        else if (cameraPosition == 4)
            view = glm::lookAt(glm::vec3(-120.0f, 100.0f, 80.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        else if (cameraPosition == 5)
            view = glm::lookAt(glm::vec3(70.0f, 80.0f, 90.0f),
                glm::vec3(45.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
        */

        /*
        // Used for task 3
        glm::mat4 view = glm::lookAt(glm::vec3(60.0f, 30.0f, 80.0f),
            glm::vec3(30.0f, 0.0f, 0.0f), // Manually changed to look at either the earth's center or sun's center
            glm::vec3(0.0f, 1.0f, 0.0f));
        */

        // Calculate Earth and Moon rotations 
        // Used for task 4
        glm::mat4 rotate_earth_around_sun = glm::rotate(glm::mat4(1.0f),
            glm::radians(get_earth_rotate_angle_around_sun(day)),
            glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 earthPos = glm::vec3(rotate_earth_around_sun * glm::vec4(30.0f, 0.0f, 0.0f, 1.0f));

        glm::mat4 rotate_moon_around_earth = glm::rotate(glm::mat4(1.0f),
            glm::radians(get_moon_rotate_angle_around_earth(day)),
            glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec4 moonLocal = rotate_moon_around_earth * glm::vec4(15.0f, 0.0f, 0.0f, 1.0f);
        glm::vec3 moonPos = glm::vec3(rotate_earth_around_sun * (glm::vec4(30.0f, 0.0f, 0.0f, 1.0f) + moonLocal));

        glm::vec3 cameraWorldPos(30.0f, 20.0f, 90.0f); 
        glm::vec3 lookTarget(0.0f, 0.0f, 0.0f);
         
        if (cameraPosition == 1) {
            lookTarget = glm::vec3(0.0f, 0.0f, 0.0f); 
        }
        else if (cameraPosition == 2) {
            lookTarget = earthPos; 
        }
        else if (cameraPosition == 3) {
            lookTarget = moonPos;  
        }

        glm::mat4 view = glm::lookAt(cameraWorldPos, lookTarget, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);

        //glm::mat4 model = glm::mat4(1.0f); // Used for task 1

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

        /*
        // Used for task 1
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); 
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        */

        /*
        // Used for task 2
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Sun
        glBindVertexArray(VAO_sun);
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indices_sun.size(), GL_UNSIGNED_INT, 0);

        // Earth
        glBindVertexArray(VAO_earth);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(30.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(23.4f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indices_earth.size(), GL_UNSIGNED_INT, 0);

        // Moon
        glBindVertexArray(VAO_moon);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(45.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indices_moon.size(), GL_UNSIGNED_INT, 0);
        */

        
        // Used for task 3
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // Sun
        glBindVertexArray(VAO_sun);
        glm::mat4 model_sun = glm::mat4(1.0f);
        model_sun = glm::rotate(model_sun, glm::radians(get_sun_rotate_angle_around_itself(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_sun));
        glDrawElements(GL_TRIANGLES, indices_sun.size(), GL_UNSIGNED_INT, 0);

        // Earth
        glBindVertexArray(VAO_earth);
        glm::mat4 model_earth = glm::mat4(1.0f);
        model_earth = glm::rotate(model_earth, glm::radians(get_earth_rotate_angle_around_sun(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        model_earth = glm::translate(model_earth, glm::vec3(30.0f, 0.0f, 0.0f));
        model_earth = glm::rotate(model_earth, glm::radians(23.4f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_earth = glm::rotate(model_earth, glm::radians(get_earth_rotate_angle_around_itself(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_earth));
        glDrawElements(GL_TRIANGLES, indices_earth.size(), GL_UNSIGNED_INT, 0);

        // Moon
        glBindVertexArray(VAO_moon);
        glm::mat4 model_moon = glm::mat4(1.0f);
        model_moon = glm::rotate(model_moon, glm::radians(get_earth_rotate_angle_around_sun(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        model_moon = glm::translate(model_moon, glm::vec3(30.0f, 0.0f, 0.0f));
        model_moon = glm::rotate(model_moon, glm::radians(get_moon_rotate_angle_around_earth(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        model_moon = glm::translate(model_moon, glm::vec3(15.0f, 0.0f, 0.0f)); 
        model_moon = glm::rotate(model_moon, glm::radians(get_moon_rotate_angle_around_itself(day)), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_moon));
        glDrawElements(GL_TRIANGLES, indices_moon.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO_sphere);
        glm::mat4 model_circle = glm::mat4(1.0f);
        model_circle = glm::translate(model_circle, glm::vec3(20.0f, 20.0f, 0.0f)); // center position
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_circle));
        glDrawElements(GL_TRIANGLES, indices_sphere.size(), GL_UNSIGNED_INT, 0);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Releasing resources 
    /*
    // Used for task 1
    glDeleteVertexArrays(1, &VAO); 
    glDeleteBuffers(1, &VBO); 
    glDeleteBuffers(1, &EBO); 
    glDeleteProgram(shaderProgram);
    */

    // Used for task 2, 3, & 4
    glDeleteVertexArrays(1, &VAO_sun);
    glDeleteVertexArrays(1, &VAO_earth);
    glDeleteVertexArrays(1, &VAO_moon);
    glDeleteBuffers(1, &VBO_sun);
    glDeleteBuffers(1, &VBO_earth);
    glDeleteBuffers(1, &VBO_moon);
    glDeleteBuffers(1, &EBO_sun);
    glDeleteBuffers(1, &EBO_earth);
    glDeleteBuffers(1, &EBO_moon);
    glDeleteProgram(shaderProgram);
   
    glfwTerminate();

    return 0;
}



