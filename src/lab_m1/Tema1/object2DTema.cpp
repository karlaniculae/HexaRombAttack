#include "object2DTema.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2DTema::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
     
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2DTema::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
    
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2DTema::CreateDiamond(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;


    float halfDiagonal = length / 2;
    float halfDiagonal2 = sqrt(length * length - (halfDiagonal * halfDiagonal));
    float number = length / 4;
    float number2 = length / 2;
    float width = 2 * sqrt(number2 * number2 - number * number);
   

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner + glm::vec3(-halfDiagonal, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, halfDiagonal2, 0), color), 
        VertexFormat(corner + glm::vec3(halfDiagonal, 0, 0), color), 
        VertexFormat(corner + glm::vec3(0, -halfDiagonal2, 0), color), 
        VertexFormat(corner+ glm::vec3(30, 30, 0) + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(30, 30, 0)+glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(30, 30, 0) + glm::vec3(0, width, 0), color)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
       
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2); 
        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(2); 
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2DTema::CreateDiamondWithRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float diamondLength,
    float rectangleWidth,
    float rectangleHeight,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

   
    float halfDiagonalX = diamondLength / 2;
    float halfDiagonalY = sqrt(diamondLength * diamondLength - (halfDiagonalX * halfDiagonalX));

   
    std::vector<VertexFormat> vertices = {
        VertexFormat(corner + glm::vec3(-halfDiagonalX, 0, 0), color), 
        VertexFormat(corner + glm::vec3(0, halfDiagonalY, 0), color),  
        VertexFormat(corner + glm::vec3(halfDiagonalX, 0, 0), color), 
        VertexFormat(corner + glm::vec3(0, -halfDiagonalY, 0), color), 
    };

    
    glm::vec3 rightMiddle = corner + glm::vec3(halfDiagonalX - 20, -rectangleWidth / 4, 0);
    vertices.push_back(VertexFormat(rightMiddle, color)); 
    vertices.push_back(VertexFormat(rightMiddle + glm::vec3(rectangleWidth, 0, 0), color));
    vertices.push_back(VertexFormat(rightMiddle + glm::vec3(rectangleWidth, rectangleHeight, 0), color)); 
    vertices.push_back(VertexFormat(rightMiddle + glm::vec3(0, rectangleHeight, 0), color));

    Mesh* diamondRectangle = new Mesh(name);

   
    std::vector<unsigned int> indices;
    if (!fill) {
       
        indices = { 0, 1, 2, 3, 0 }; 
        indices.push_back(4); 
        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(4);  
    }
    else {
      
        indices = { 0, 1, 2, 2, 3, 0 }; 
   
        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(7);
    }

    diamondRectangle->InitFromData(vertices, indices);
    return diamondRectangle;
}
Mesh* object2DTema::CreateStar(const std::string& name, glm::vec3 center, float outerRadius, float innerRadius, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    const int numPoints = 10; 
    float angleIncrement = 2 * M_PI / numPoints;

   
    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i < numPoints; ++i) {
      
        float angle = angleIncrement * i;

      
        glm::vec3 vertexPos;
        if (i % 2 == 0) {
           
            vertexPos.x = center.x + outerRadius * cos(angle);
            vertexPos.y = center.y + outerRadius * sin(angle);
        }
        else {
          
            vertexPos.x = center.x + innerRadius * cos(angle);
            vertexPos.y = center.y + innerRadius * sin(angle);
        }
        vertexPos.z = center.z;

  
        vertices.push_back(VertexFormat(vertexPos, color));
    }

   
    for (int i = 1; i < numPoints; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

   
    indices.push_back(0);
    indices.push_back(numPoints);
    indices.push_back(1);

   
    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);
    return star;

 }


Mesh* object2DTema::CreateHexagon(const std::string& name, glm::vec3 center, float size, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

   
    vertices.push_back(VertexFormat(center, color)); 


    for (int i = 0; i < 6; ++i) {
        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180 * angle_deg;
        vertices.push_back(VertexFormat(center + glm::vec3(size * cos(angle_rad), size * sin(angle_rad), 0), color)); 
    }

    for (int i = 1; i <= 6; ++i) {
        indices.push_back(0); 
        indices.push_back(i); 
        indices.push_back(i % 6 + 1);
    }

    Mesh* hexagon = new Mesh(name);
    hexagon->InitFromData(vertices, indices);
    return hexagon;
}


   