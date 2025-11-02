#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
    // Janela com 1920x1080 pixels
    window = { 1920, 1080 };

    // Cria a janela com as dimensões especificadas e título "SolarSystem"
    InitWindow(window.x, window.y, "3DSolarSystem");
    
    // Limita a 60 quadros por segundo
    SetTargetFPS(60); 

    // Calcula e armazena o centro da tela
    center = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };

    // Configuração da câmera 3D:
    camera = { 0 };
    camera.position = { 30.0f, 20.0f, 30.0f }; // Posição inicial da câmera no espaço 3D
    camera.target = { 0.0f, 0.0f, 0.0f }; // Ponto para onde a câmera está olhando (centro do sistema solar)
    camera.up = { 0.0f, 1.0f, 0.0f }; // Vetor "para cima" da câmera
    camera.fovy = 45.0f; // Campo de visão (45 graus)
    camera.projection = CAMERA_PERSPECTIVE; // Tipo de projeção (perspectiva)

    // Dados dos planetas 
    planetRadius = { 5.0f, 7.0f, 10.0f, 13.0f, 18.0f, 23.0f, 27.0f, 29.0f }; // Distâncias: De 5.0f (mais próximo) a 29.0f (mais distante)
    planetSizes = { 0.3f, 0.5f, 0.6f, 0.5f, 1.5f, 1.3f, 0.8f, 0.7f }; // Tamanhos: Variando de 0.3f a 1.5f
    planetsVelocities = { 1.607f, 1.174f, 1.f, 0.802f, 0.434f, 0.323f, 0.228f, 0.182f }; // Velocidades: Mais rápido perto do Sol, mais lento longe do Sol
    colors = { // Define as cores RGBA de cada planeta
      {115, 147, 179, 255}, // Mercúrio - azul acinzentado
      {255, 87, 51, 255},	// Vênus - laranja avermelhado
      {30, 144, 255, 255},	// Terra - azul
      {178, 34, 34, 255},	// Marte - vermelho
      {210, 105, 30, 255},	// Júpiter - marrom
      {220, 20, 60, 255},	// Saturno - rosa avermelhado
      {72, 209, 204, 255},	// Urano - azul esverdeado
      {65, 105, 225, 255}	// Netuno - azul royal
    };

    // Inicialização de variáveis:
    planetAngle.assign(8, 0);
    moonAngle = 0;
    cameraAutoRotate = true;
    globalRotation = 0;
    earthPos = 0;

    // Encontra o índice do planeta com tamanho 0.6f (Terra)
    for (size_t i = 0; i < planetSizes.size(); i++)
        if (planetSizes[i] == 0.6f) earthPos = i;
}

void SolarSystem::updateCamera()
{
    // Alterna rotação automática com barra de espaço
    if (IsKeyPressed(KEY_SPACE))
        cameraAutoRotate = !cameraAutoRotate;

    // Move a câmera em círculo ao redor do sistema solar
    if (cameraAutoRotate)
    {
        globalRotation += 0.2f * GetFrameTime(); // Garante movimento suave independente do FPS
        camera.position.x = cos(globalRotation) * 30.0f;
        camera.position.z = sin(globalRotation) * 30.0f;
    }

    // Processa controles de mouse/teclado para câmera livre
    UpdateCamera(&camera, CAMERA_FREE);
}

void SolarSystem::run()
{
    // Executa enquanto janela não for fechada
    while (!WindowShouldClose())
    {
        // Atualiza a câmera a cada frame
        updateCamera();

        // Atualiza órbitas: Incrementa ângulos baseado nas velocidades e tempo
        for (size_t i = 0; i < planetRadius.size(); i++)
            planetAngle[i] += planetsVelocities[i] * GetFrameTime();

        moonAngle += moonVelocity * GetFrameTime();

        // Inicia o desenho
        BeginDrawing();

        // Limpa a tela com preto
        ClearBackground(BLACK);

        // Inicia modo 3D
        BeginMode3D(camera);

        // Desenha o Sol: Esfera amarela com contorno laranja
        DrawSphere({ 0, 0, 0 }, SUN_SIZE, YELLOW);
        DrawSphereWires({ 0, 0, 0 }, SUN_SIZE, 16, 16, ORANGE);

        // Calcula posição do planeta: Usa trigonometria para posição orbital
        for (size_t i = 0; i < planetRadius.size(); i++)
        {
            Vector3 planetPos = {
                cos(planetAngle[i]) * planetRadius[i],
                0.0f,
                sin(planetAngle[i]) * planetRadius[i]
            };

            // Desenha órbita como círculo 3D
            DrawCircle3D({ 0, 0, 0 }, planetRadius[i], { 1, 0, 0 }, 90.0f, Fade(GRAY, 0.3f));

            // Desenha planeta: Esfera colorida com contorno branco translúcido
            DrawSphere(planetPos, planetSizes[i], colors[i]);
            DrawSphereWires(planetPos, planetSizes[i], 8, 8, Fade(WHITE, 0.3f));

            // Sistema Terra-Lua: Desenha órbita e lua apenas para a Terra
            if ((int)i == earthPos)
            {
                Vector3 moonPos = {
                    planetPos.x + cos(moonAngle) * moonRadius,
                    planetPos.y,
                    planetPos.z + sin(moonAngle) * moonRadius
                };

                DrawCircle3D(planetPos, moonRadius, { 1, 0, 0 }, 90.0f, Fade(LIGHTGRAY, 0.3f));
                DrawSphere(moonPos, moonSize, WHITE);
            }
        }

        // Grade de referência
        DrawGrid(50, 1.0f);

        // Finaliza modo 3D
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
}

int runSolarSystem()
{
    SolarSystem system;
    system.run();
    return 0;
}

int main()
{
    return runSolarSystem();
}

