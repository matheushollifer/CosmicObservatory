#pragma once
#include <vector>
#include <cmath>
#include "raylib.h"

using namespace std;

class SolarSystem
{
private:

    /*
        Vector2: É um tipo da Raylib com capos x e y
        window: Armazena as dimensõesda janela (largura, altura)
        center: Armazena as coordenadas do centro da tela
    */
    Vector2 window;

    // Constante que define o raio da esfera do Sol (2.0 unidades)
    const float SUN_SIZE = 2.0f;
    /*
        planetRadius: Distância de cada planeta ao Sol
        planetSizes: Tamanhos (raios) dos planetas
        planetsVelocities: Velocidades de rotação dos planetas
        planetAngle: Ângulo atual de cada planeta em sua órbita
    */
    vector<float> planetRadius, planetSizes, planetsVelocities, planetAngle;
    vector<Color> colors; // colors: Cores de cada planeta

    /*
        moonSize: Tamanho da Lua
        moonRadius: Distância da Lua à Terra
        moonVelocity: Velocidade orbital da Lua
        moonAngle: Ângulo atual da Lua em sua órbita
        earthPos: Índice do planeta Terra no array
    */
    const float moonSize = 0.2f, moonRadius = 1.0f, moonVelocity = 10.f;
    float moonAngle;
    size_t earthPos;

    /*
        camera: Objeto que controla a visualização 3D
        cameraAutoRotate: Flag para rotação automática da câmera
        globalRotation: Ângulo de rotação global da câmera
    */
    Camera3D camera; 
    bool cameraAutoRotate;
    float globalRotation;

public:
    SolarSystem();
    void run();
    void updateCamera();
};

int runSolarSystem();