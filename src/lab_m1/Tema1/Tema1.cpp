
#include "lab_m1/Tema1/Tema1.h"
#include<array>
#include <vector>
#include <iostream>
#include<random>
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2DTema.h"
using namespace std;
using namespace m1;

struct MeshC {
    glm::vec3 p;
    Mesh* m;
    glm::vec3 c;
    Mesh* m2;
};
struct Enemy {
    glm::vec3 position;
    MeshC newmesh;
    int n = 3;

    bool value;
    bool starCreated;
    glm::vec3 col;
};
struct Star {
    glm::vec3 position;
    MeshC newmesh;
    Mesh* color;
    bool value;
    int initial;
    glm::vec3 col;
};
int numarstele = 10;
int numaradunat = 0;
std::vector<Star> stars;
std::vector<Star> stars2;
std::vector<Star> stars3;
std::vector<Enemy> enemies;
Star selStar;
std::array<glm::vec3, 4> positionvec;

std::array<bool, 11> values;
float lastSpawn = 2;
float timeSinceLastSpawn = 0.0f; 
float spawnCooldown = 2.0f;
struct Diamond {
    glm::vec3 position; 
    Mesh* color;
    bool starCreated;
    glm::vec3 col;
    int ind;
    bool exist;
    int temp=3;
};
std::vector<Diamond> diamonds2;
std::vector<Diamond> diamonds;
struct GreenSquare {
    glm::vec3 position; 
    Mesh* color;
    bool occup;
 
};

std::vector<GreenSquare> greens;
std::vector<GreenSquare> greens2;
std::vector<GreenSquare> red3;


std::array<glm::vec3, 4> Colors = {
    glm::vec3(0, 1, 1), 
    glm::vec3(0, 0, 1), 
    glm::vec3(1, 1, 0), 
    glm::vec3(1, 0, 1) 
};
float nextEnemy = 0;

Diamond selectedDiamond;
Diamond selectedDiamond2;
int mesh = 1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}



std::unordered_map<int, Mesh*> enemyMeshes;
std::unordered_map<int, MeshC> enemyMeshes2;
std::unordered_map<int, MeshC> meshess;
std::unordered_map<int, Mesh*> diamond;
std::unordered_map<int, Mesh*> meshes3;
std::unordered_map<int, Mesh*> green;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<>distrib;
std::random_device rd2;
std::mt19937 gen2(rd2());
std::uniform_int_distribution<>distrib2;

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    float cx = corner.x + squareSide / 2;
    float cy = corner.y + squareSide / 2;

   
    translateX = 0;
    translateY = 0;

   
    scaleX = 1;
    scaleY = 1;

    
    angularStep = 0;

    float centerX = resolution.x / 2;
    float centerY = resolution.y / 2;

    float diamondSide = 120; 
    float one = 10;
    float two = 20;

    float redBarHeight = 480; 
    float redBarWidth = 60;   
    float greenSquareSide = 120; 
    float SquareSide = 90;
  

    glm::vec3 diamondCorner;
    for (int i = 1; i < 5; ++i) {
        Mesh* romb;

        glm::vec3 color;
        float number = sqrt(diamondSide * (diamondSide)-(diamondSide / 2 * diamondSide / 2)) + 20;
        if (i == 1)
        {
            color = glm::vec3(0, 1, 1);

            diamondCorner = glm::vec3(((resolution.x - 77 + 100) * i - diamondSide + 10) - diamondSide / 2 + 15, resolution.y - 100 - (number / 2) - 20, 0);
          
            string starName = "Starn_" + to_string(i);
            Mesh* star = object2DTema::CreateStar(starName, diamondCorner, one, two, glm::vec3(0.3, 0.7, 1)); 
            AddMeshToList(star);

        }

        else  if (i == 2)
        {
            diamondCorner = glm::vec3(((resolution.x - 77 + 100) * i - diamondSide + 10) - diamondSide / 2 + 15, resolution.y - 100 - (number / 2) - 20, 0);
            color = glm::vec3(0, 0, 1);
            for (int j = 1; j < 3; ++j) {

                diamondCorner = diamondCorner + glm::vec3(15, 0, 0);
            
                string starName = "Starnm_" + to_string(j);
                Mesh* star = object2DTema::CreateStar(starName, diamondCorner, one, two, glm::vec3(0.3, 0.7, 1)); 
                AddMeshToList(star);
            }
        }
        else  if (i == 3)
        {
            diamondCorner = glm::vec3(((resolution.x - 77 + 100) * i - diamondSide + 10) - diamondSide / 2 + 15, resolution.y - 100 - (number / 2) - 20, 0);
            color = glm::vec3(1, 1, 0);
            for (int j = 1; j < 3; ++j) {

                diamondCorner = diamondCorner + glm::vec3(15, 0, 0);
              
                string starName = "Starnmp_" + to_string(j);
                Mesh* star = object2DTema::CreateStar(starName, diamondCorner, one, two, glm::vec3(0.3, 0.7, 1)); 
                AddMeshToList(star);
            }
        }
        else  if (i == 4)
        {
            diamondCorner = glm::vec3(((resolution.x - 77 + 100) * i - diamondSide + 10) - diamondSide / 2 + 15, resolution.y - 100 - (number / 2) - 20, 0);
            color = glm::vec3(1, 0, 1);
            for (int j = 1; j < 4; ++j) {

                diamondCorner = diamondCorner + glm::vec3(15, 0, 0);
             
                string starName = "Starnmpq_" + to_string(j);
                Mesh* star = object2DTema::CreateStar(starName, diamondCorner, one, two, glm::vec3(0.3, 0.7, 1));
                AddMeshToList(star);
            }
        }

        diamondCorner = glm::vec3(((number / 2 * (2 * (i - 1) + 1)) + (i - 1) * 90) - (number / 2), (720 - (number / 2) - 10) - (number / 2), 0);
    
        string squareName = "Squarename_" + to_string(i);

        Mesh* greenSquare = object2DTema::CreateSquare(squareName, diamondCorner, number, glm::vec3(1, 0, 0), false);
        AddMeshToList(greenSquare);


    }
    float number = sqrt(diamondSide * (diamondSide)-(diamondSide / 2 * diamondSide / 2)) + 20;

    diamondCorner = glm::vec3((number / 2 * (2 * (1 - 1) + 1)) + 0 * 90, 720 - (number / 2) - 10, 0);
   
    diamond[1] = object2DTema::CreateDiamondWithRectangle("diamond", diamondCorner, diamondSide / 2, (diamondSide - 10) / 2, (diamondSide - 10) / 4, glm::vec3(0, 1, 1), true);

    diamondCorner = glm::vec3((number / 2 * (2 * (2 - 1) + 1)) + 1 * 90, 720 - (number / 2) - 10, 0);
  
    diamond[2] = object2DTema::CreateDiamondWithRectangle("diamond", diamondCorner, diamondSide / 2, (diamondSide - 10) / 2, (diamondSide - 10) / 4, glm::vec3(0, 0, 1), true);

    diamondCorner = glm::vec3((number / 2 * (2 * (3 - 1) + 1)) + 2 * 90, 720 - (number / 2) - 10, 0);
 
    diamond[3] = object2DTema::CreateDiamondWithRectangle("diamond", diamondCorner, diamondSide / 2, (diamondSide - 10) / 2, (diamondSide - 10) / 4, glm::vec3(1, 1, 0), true);
    diamondCorner = glm::vec3((number / 2 * (2 * (4 - 1) + 1)) + 3 * 90, 720 - (number / 2) - 10, 0);
  
    diamond[4] = object2DTema::CreateDiamondWithRectangle("diamond", diamondCorner, diamondSide / 2, (diamondSide - 10) / 2, (diamondSide - 10) / 4, glm::vec3(1, 0, 1), true);

    Mesh* redbar = object2DTema::CreateRectangle("redbar", corner, redBarWidth, redBarHeight, glm::vec3(1, 0, 0));
    AddMeshToList(redbar);

    int x = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            x++;
            glm::vec3 greenSquareCorner1 = corner + glm::vec3(redBarWidth + (greenSquareSide * i) + (redBarWidth * (i + 1)), (greenSquareSide + redBarWidth) * j, 0);
            green[x] = object2DTema::CreateSquare("square", greenSquareCorner1, greenSquareSide, glm::vec3(0, 1, 0), true);
        }
    }

    for (int i = 0; i < 3; ++i) {

    
        glm::vec3 SquareCorner = glm::vec3(850 + i * 120, 600, 0);
        GreenSquare g;
        meshes3[i] = object2DTema::CreateSquare("redSquare", SquareCorner, SquareSide, glm::vec3(1, 0, 0), true);
        g.color = meshes3[i];
        g.position = SquareCorner;

        red3.push_back(g);



    }
    float starSide = 20; 
    float startX = 850; 
    float startY = resolution.y - 130 - starSide; 

   
    for (int i = 0; i < 10; ++i) {
        glm::vec3 starPosition = glm::vec3(850 + i * 35, 570, 0); 
        Star thisstar;
        thisstar.position = starPosition;
        thisstar.color = object2DTema::CreateStar("starName", starPosition, one, two, glm::vec3(0.3, 0.7, 1));
        stars3.push_back(thisstar);
    }

    for (int i = 0; i < 4; i++) {

        glm::vec3 starPosition = glm::vec3(static_cast<float>(rand() % 800 + 1) + 600, static_cast<float>(rand() % 400 + 1) + 100, 0); 
        selStar.color = object2DTema::CreateStar("star", starPosition, one, two, glm::vec3(0.9, 0.4, 0.2));
        selStar.position = starPosition;
        selStar.value = true;
        stars2.push_back(selStar);
    }
}


void Tema1::FrameStart()
{
 
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
  
    glViewport(0, 0, resolution.x, resolution.y);
}
int lifes = 3;
float spawnCooldown2 = 5;
float spawnCooldown3 = 0;
void Tema1::Update(float deltaTimeSeconds)
{
    if (lifes == 0 || numaradunat == 15)
    {
        exit(0);
    }

    glm::ivec2 resolution = window->GetResolution();
    timeSinceLastSpawn += deltaTimeSeconds;
    float lastSpawn = 2;

    if (timeSinceLastSpawn >= spawnCooldown2) {
        spawnCooldown2 = timeSinceLastSpawn;
        timeSinceLastSpawn = 0.0f;
        spawnCooldown2 = static_cast<float>(rand() % 5 + 1) + 4;
        for (int i = 0; i < static_cast<float>(rand() % 2 + 1) + 1; i++) {

            Star hey;
            glm::vec3 starPosition = glm::vec3(static_cast<float>(rand() % 800 + 1) + 600, static_cast<float>(rand() % 400 + 1) + 100, 0); 
            hey.color = object2DTema::CreateStar("star", starPosition, 10, 20, glm::vec3(0.9, 0.4, 0.2));
            hey.position = starPosition;
            hey.value = true;
            stars2.push_back(hey);
        }
    }


    for (auto& star : stars2) {


        modelMatrix = glm::mat3(1);


        modelMatrix *= transform2D::Translate(0, 0);

        RenderMesh2D(star.color, shaders["VertexColor"], modelMatrix);

    }

    if (timeSinceLastSpawn >= spawnCooldown && enemies.size() < (static_cast<float>(rand() % 3 + 1))) {
   
        float lastEnemy = -1;
      
        timeSinceLastSpawn = 0.0f;
        spawnCooldown = static_cast<float>(rand() % 5 + 1) + 1;

        Enemy newEnemy;

        float nr = static_cast<float>(rand() % 3);
        glm::vec3 diamondcorner2 = glm::vec3(1280, (120 + 60) * nr + 60, 0);
        newEnemy.col = Colors[static_cast<float>(rand() % 4)];
        newEnemy.newmesh.m = object2DTema::CreateHexagon("enemie", diamondcorner2, 30, newEnemy.col);
        newEnemy.newmesh.m2 = object2DTema::CreateHexagon("enemie", diamondcorner2, 20, glm::vec3(0.2, 0.5, 0.2));

        newEnemy.position = diamondcorner2;
        newEnemy.value = true;
        newEnemy.starCreated = false;
        enemies.push_back(newEnemy);
    }
    for (auto& enemy : enemies) {
        if (enemy.value) {

            if (enemy.position.x < 0) {
                enemy.value = false;
                lifes--;
                if (lifes == 2) {
                    for (auto& red : red3) {
                        red.color = object2DTema::CreateSquare("redSquare", red.position, 90, glm::vec3(0, 0, 0), true);
                        break;
                    }
                }
                else if (lifes == 1) {
                    int l = 0;
                    for (auto& red : red3) {
                        l++;
                        if (l == 2) {
                            red.color = object2DTema::CreateSquare("redSquare", red.position, 90, glm::vec3(0, 0, 0), true);
                            break;
                        }
                    }
                }
                else if (lifes == 0) {
                    int l = 0;
                    for (auto& red : red3) {
                        l++;
                        if (l == 3) {
                            red.color = object2DTema::CreateSquare("redSquare", red.position, 90, glm::vec3(0, 0, 0), true);
                            break;
                        }
                    }
                }
            }


        }
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& enemy) { return !enemy.value; }),
        enemies.end());
    for (auto& diamond2 : diamonds2) {

        glm::vec3 cornerDiamond = glm::vec3(diamond2.position.x, diamond2.position.y, 0);
      
        diamond2.color = object2DTema::CreateDiamondWithRectangle("diamond", cornerDiamond, 120 / 2, 110 / 2, (110 - 10) / 4, diamond2.col, true);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(diamond2.color, shaders["VertexColor"], modelMatrix);


    }
    for (auto& star : stars) {

        if (star.value) {

            star.position.x += 90 * deltaTimeSeconds; 
            modelMatrix = glm::mat3(1);


            modelMatrix *= transform2D::Translate((star.position.x - star.initial), 0);

            RenderMesh2D(star.color, shaders["VertexColor"], modelMatrix);

            if (star.position.x > 1280) { 
                star.value = false; 
            }

        }
    }
    
    stars.erase(std::remove_if(stars.begin(), stars.end(),
        [](const Star& star) { return !star.value; }),
        stars.end());
    for (auto& enemy : enemies) {
        int i = 0;
        if (enemy.value) {
            enemy.position.x -= 50 * deltaTimeSeconds;
           
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy.position.x - 1280, 10);
            RenderMesh2D(enemy.newmesh.m2, shaders["VertexColor"], modelMatrix);
         
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy.position.x - 1280, 10); 
            RenderMesh2D(enemy.newmesh.m, shaders["VertexColor"], modelMatrix);

        }

    }

    if (selectedDiamond.position.x != 0 && selectedDiamond.position.y != 0) {

        glm::vec3 cornerDiamond = glm::vec3(selectedDiamond.position.x, selectedDiamond.position.y, 0);
      
        selectedDiamond.color = object2DTema::CreateDiamondWithRectangle("diamond", cornerDiamond, 120 / 2, 110 / 2, (110 - 10) / 4, Colors[mesh], true);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(selectedDiamond.color, shaders["VertexColor"], modelMatrix);


    }





   

    for (auto& diamond : diamonds2) {
        for (auto& enemy : enemies) {
            if (enemy.value) {

                if (enemy.position.y <= (diamond.position.y + (120 / 2)) && enemy.position.y >= (diamond.position.y - 60) && diamond.position.x < enemy.position.x) {

                    if (enemy.col.x == diamond.col.x && enemy.col.y == diamond.col.y && diamond.col.z == enemy.col.z) {
                     
                        if (diamond.temp == 0) {
                            Star newstar;
                            glm::vec3 star = glm::vec3(diamond.position.x, diamond.position.y, 0);

                            newstar.color = object2DTema::CreateStar("starpin", star, 10, 20, enemy.col);
                            newstar.position.x = diamond.position.x + 70;
                            newstar.position.y = diamond.position.y;
                            newstar.initial = diamond.position.x;
                            newstar.value = true;
                            newstar.col = enemy.col;
                            stars.push_back(newstar);
                            diamond.starCreated = true;
                            enemy.starCreated = true;
                            diamond.temp = 60;
                   
                        }
                        else { diamond.temp--; }
                       
                    }

                }
            }
        }
    }

    for (auto& diamond : diamonds2) {
        for (auto& enemy : enemies) {

            if (enemy.value) {
                if (enemy.position.x >= diamond.position.x - 60 && enemy.position.x <= diamond.position.x + 60) {
                    if (enemy.col.x == diamond.col.x && enemy.col.y == diamond.col.y && diamond.col.z == enemy.col.z) {
                   
                        diamond.exist = false;
                    }
                }


            }
        }
    }
    diamonds2.erase(
        std::remove_if(
            diamonds2.begin(),
            diamonds2.end(),
            [](const Diamond& diamond) { return !diamond.exist; }
        ),
        diamonds2.end()
    );

    for (auto& star : stars) {
        for (auto& enemy : enemies) {

            if (enemy.value) {
                if (enemy.position.x >= star.position.x - 10 && enemy.position.x <= star.position.x + 10) {
                    if (enemy.col.x == star.col.x && enemy.col.y == star.col.y && star.col.z == enemy.col.z) {
                    
                        star.value = false;
                        enemy.n--;
                        if (enemy.n == 0) {
                            enemy.value = false;
                        }
                    }
                }
            }
        }
    }

    stars.erase(
        std::remove_if(
            stars.begin(),
            stars.end(),
            [](const Star& star) { return !star.value; }
        ),
        stars.end()
    );
    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy) { return !enemy.value; }
        ),
        enemies.end()
    );

    for (int i = 1; i < 5; ++i) {
        if (i == 1) {
            modelMatrix = glm::mat3(1);
            string Star = "Starn_" + to_string(i);
        
            modelMatrix *= transform2D::Translate(-1100 * i, 10);
            RenderMesh2D(meshes[Star], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 2) {
            float tr = 0;
            for (int j = 1; j < 3; j++) {
                tr += 20;
                modelMatrix = glm::mat3(1);
                string Star = "Starnm_" + to_string(j);
              
                modelMatrix *= transform2D::Translate(-1100 * 2 + tr, 10);
                RenderMesh2D(meshes[Star], shaders["VertexColor"], modelMatrix);
            }
        }
        else if (i == 3) {
            float tr = 0;
            for (int j = 1; j < 3; j++) {
                tr += 20;
                modelMatrix = glm::mat3(1);
                string Star = "Starnmp_" + to_string(j);
            
                modelMatrix *= transform2D::Translate(-1100 * 3 + tr, 10); 
                RenderMesh2D(meshes[Star], shaders["VertexColor"], modelMatrix);
            }
        }
        else if (i == 4) {
            float tr = 0;
            for (int j = 1; j < 4; j++) {
                tr += 20;
                modelMatrix = glm::mat3(1);
                string Star = "Starnmpq_" + to_string(j);
              
                modelMatrix *= transform2D::Translate(-1100 * 4 + tr, 10); 
                RenderMesh2D(meshes[Star], shaders["VertexColor"], modelMatrix);
            }
        }


        modelMatrix = glm::mat3(1);
        string Sq = "Squarename_" + to_string(i);
   
        modelMatrix *= transform2D::Translate(10, 0);
        RenderMesh2D(meshes[Sq], shaders["VertexColor"], modelMatrix);

        Diamond newdiam;
        float diamondSide = 120;
        float number = sqrt(diamondSide * (diamondSide)-(diamondSide / 2 * diamondSide / 2)) + 20;
        newdiam.position = glm::vec3((number / 2 * (2 * (i - 1) + 1)) + (i - 1) * 90, 720 - (number / 2) - 10, 0);
   
        newdiam.color = diamond[i];
        diamonds.push_back(newdiam);



        for (const auto& diamond : diamonds) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(0, 0); 
            RenderMesh2D(diamond.color, shaders["VertexColor"], modelMatrix);


        }
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 10); 
    RenderMesh2D(meshes["redbar"], shaders["VertexColor"], modelMatrix);



    int x = 0;
    for (int i = 0; i < 3; ++i) {


        for (int j = 0; j < 3; ++j) {
            x++;
            GreenSquare greensq;
            greensq.color = green[x];
            greensq.position = glm::vec3(60 + (120 * i) + (60 * (i + 1)), 180 * j, 0);
            greens.push_back(greensq);



        }

    }x = 0;
    for (int i = 0; i < 3; ++i) {


        for (int j = 0; j < 3; ++j) {
            x++;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(0, 10);  
            RenderMesh2D(green[x], shaders["VertexColor"], modelMatrix);

        }

    }
    int nur;
    if (numarstele > 10)
        nur = 10;
    else nur = numarstele;
    for (auto& star : stars3) {
        if (nur == 0)
            break;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(10, 0);
        RenderMesh2D(star.color, shaders["VertexColor"], modelMatrix);
        nur--;

    }


    for (const auto& red : red3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0); 
        RenderMesh2D(red.color, shaders["VertexColor"], modelMatrix);
    }

}


void Tema1::FrameEnd()
{
}




void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
  
}


void Tema1::OnKeyRelease(int key, int mods)
{
   
}


bool isDragging = false;

glm::vec2 lastMousePos;

bool IsMouseOverDiamond(int mouseX, int mouseY, Diamond& diamond) {
    float diamondWidth = 120;
    float diamondHeight = sqrt(diamondWidth * diamondWidth - (diamondWidth / 2 * diamondWidth / 2)) + 20;
    if (mouseX <= diamond.position.x + (diamondHeight / 2) && mouseX >= diamond.position.x - (diamondHeight / 2)
        && mouseY >= diamond.position.y - (diamondHeight / 2) && mouseY <= diamond.position.y + (diamondHeight / 2))
        return true;
    else {

        return false;

    }

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    int sceneY = 720 - mouseY;
   
    int i = 0;
    if (button == 1) {
        for (auto& diamond : diamonds) {
            if (IsMouseOverDiamond(mouseX, sceneY, diamond)) {
                isDragging = true;
                mesh = i;
                selectedDiamond = diamond;
                lastMousePos = glm::vec2(mouseX, sceneY);

                break;
            }

            i++;
        }



    }


}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    if (isDragging) {

        selectedDiamond.position.x = mouseX;
        selectedDiamond.position.y = 720 - mouseY;
    }

}
bool IsGreenSquareOccupied(int greenSquareIndex, const std::vector<Diamond>& diamonds2) {
    for (const auto& diamond : diamonds2) {
        if (diamond.ind == greenSquareIndex) {
            return true;
        }
    }
    return false;
}
void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)

{  

    int sceneY = 720 - mouseY;
    selectedDiamond.position.x = 0;
    selectedDiamond.position.y = 0;
    if (button == 1 && isDragging == true) {
        int i = 0;
        for (auto& green : greens) {
            i++;
            if (mouseX <= (green.position.x + 60) + 60 && mouseX >= (green.position.x + 60) - 60
                && sceneY >= (green.position.y + 60) - 60 && sceneY <= (green.position.y + 60) + 60 && !IsGreenSquareOccupied(i, diamonds2)) {
                if (Colors[mesh] == glm::vec3(0, 1, 1)) {
                    if (numarstele < 1)
                        break;
                }
                else if (Colors[mesh] == glm::vec3(0, 0, 1)) {
                    if (numarstele < 2)
                        break;
                }
                else if (Colors[mesh] == glm::vec3(1, 1, 0)) {
                    if (numarstele < 2)
                        break;
                }
                else if (Colors[mesh] == glm::vec3(1, 0, 1)) {
                    if (numarstele < 3)
                        break;
                }

                Diamond newdiam;
                newdiam = selectedDiamond;
                newdiam.position.x = (green.position.x + 50);
                newdiam.position.y = (green.position.y + 70);
                newdiam.col = Colors[mesh];
                newdiam.starCreated = false;
                newdiam.ind = i;
                newdiam.exist = true;
                if (newdiam.col == glm::vec3(0, 1, 1)) {
                    numarstele--;
                }
                else if (newdiam.col == glm::vec3(0, 0, 1)) {
                    numarstele = numarstele - 2;
                }
                else if (newdiam.col == glm::vec3(1, 1, 0)) {
                    numarstele = numarstele - 2;
                }
                else if (newdiam.col == glm::vec3(1, 0, 1)) {
                    numarstele = numarstele - 3;
                }

                diamonds2.push_back(newdiam);
                break;
            }
        }

        isDragging = false;




    }
    if (button == 2) {
     
        int i = 0;
        for (auto& green : greens) {
            i++;

            if (mouseX <= (green.position.x + 60) + 50 && mouseX >= (green.position.x + 60) - 50
                && sceneY >= (green.position.y + 60) - 50 && sceneY <= (green.position.y + 60) + 50) {
                for (auto& diamond2 : diamonds2) {
                    if (diamond2.ind == i) {
                        diamond2.exist = false;
                        green.occup = false;
                        diamond2.ind = 0;
                        break;
                    }
                }
            }
        
            diamonds2.erase(std::remove_if(diamonds2.begin(), diamonds2.end(),
                [](const Diamond& diamond) { return !diamond.exist; }),
                diamonds2.end());

        }
        for (auto& star : stars2) {
            if (mouseX <= (star.position.x + 10) && mouseX >= (star.position.x - 10)
                && sceneY >= (star.position.y - 10) && sceneY <= (star.position.y + 10)) {

                star.value = false;
                if (numarstele < 10)
                {
                    numarstele++;
                    numaradunat++;
                }
            }



        }

       
        stars2.erase(std::remove_if(stars2.begin(), stars2.end(),
            [](const Star& star) { return !star.value; }),
            stars2.end());

    }
}
void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}