#include "Primitives.h"
#include "Util.h"

Cube::Cube(glm::vec3 position, glm::vec3 _scale, glm::mat4 transform, int shader, int id) {

    GLfloat CubeColors[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };

    GLfloat CubeVerticies[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    face_count = 3 * 12;
    this->position = position;
    this->scale = _scale;
    this->transform = glm::scale(transform, _scale);;
    this->id = id;

    shape_data = new GLfloat[face_count * 3];
    memcpy(shape_data, CubeVerticies, sizeof(GLfloat) * face_count * 3);

    color_data = new GLfloat[face_count * 3];
    memcpy(color_data, CubeColors, sizeof(GLfloat) * face_count * 3);

    normal_data = new GLfloat[face_count * 3];

    for (unsigned int i = 0; i < (face_count * 3) - 9; i += 9)
    {
        glm::vec3 one;
        one.x = shape_data[i];
        one.y = shape_data[i + 1];
        one.z = shape_data[i + 2];

        glm::vec3 two;
        two.x = shape_data[i + 3];
        two.y = shape_data[i + 4];
        two.z = shape_data[i + 5];

        glm::vec3 three;
        three.x = shape_data[i + 6];
        three.y = shape_data[i + 7];
        three.z = shape_data[i + 8];

        glm::vec3 point = Util::calc_normal(one, two, three);

        normal_data[i]     = point.x;
        normal_data[i + 1] = point.y;
        normal_data[i + 2] = point.z;

        normal_data[i + 3] = point.x;
        normal_data[i + 4] = point.y;
        normal_data[i + 5] = point.z;

        normal_data[i + 6] = point.x;
        normal_data[i + 7] = point.y;
        normal_data[i + 8] = point.z;
    }

    MatrixID      = glGetUniformLocation(shader, "MVP");
    ViewMatrixID  = glGetUniformLocation(shader, "V");
    ModelMatrixID = glGetUniformLocation(shader, "M");

    glGenBuffers(1, &verticies);
    glBindBuffer(GL_ARRAY_BUFFER, verticies);
    glBufferData(GL_ARRAY_BUFFER, 36 * 3, CubeVerticies, GL_STATIC_DRAW);

    glGenBuffers(1, &colors);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 36 * 3, CubeColors, GL_STATIC_DRAW);

    glGenBuffers(1, &normals);
    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glBufferData(GL_ARRAY_BUFFER, face_count * sizeof(glm::vec3) * 3, normal_data, GL_STATIC_DRAW);
}

Cube::~Cube() {

}