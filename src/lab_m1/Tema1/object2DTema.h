#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2DTema
{

   
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width,glm::vec3 color, bool fill = true);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateDiamondWithRectangle(const std::string& name, glm::vec3 leftBottomCorner, float diamondLength, float rectangleWidth, float rectangleHeight, glm::vec3 color, bool fill);


    Mesh* CreateStar(const std::string& name, glm::vec3 center, float outerRadius, float innerRadius, glm::vec3 color);

    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float size, glm::vec3 color);

   
   
}
