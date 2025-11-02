#include "SolarSystem.h"

using namespace std;

SolarSystem::SolarSystem()
{
	// Janela com 1920x1080 pixels
	window = { 1920, 1080 }; 
	// Cria a janela com as dimensões especificadas e título "SolarSystem"
	InitWindow(window.x, window.y, "SolarSystem");
	// Define o frame rate máximo para 60 FPS
	SetTargetFPS(60);
	// Calcula e armazena o centro da tela
	center = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };

	// Configuração dos planetas
	planetRadius = { 80, 110, 165, 225, 310, 430, 515, 565 }; // Define as distâncias orbitais de cada planeta ao Sol
	planetsVelocities = { 1.607f, 1.174f, 1.f, 0.802f, 0.434f, 0.323f, 0.228f, 0.182f }; // Define as velocidades orbitais de cada planeta (mais rápido perto do sol)
	planetSizes = { 10, 15, 20, 18, 60, 55, 25, 22 }; // Define os tamanhos dee cada planeta
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

	// Inicializa todos os ângulos orbitais com o valor zero
	planetAngle.assign(8, 0);
	// Inicializa o ângulo orbital da lua com o valor zero
	moonAngle = { 0 };
	// Loop para encontrar a Terra
	for (size_t i = 0; i < planetSizes.size(); i++)
	{
		// Identifica qual planeta tem tamanho 20
		if (planetSizes[i] == 20)
		{
			// Armazena a posição no array em earthPos
			earthPos = i;
		}
	}

	// Inicializa o modo fullscreen como desativado
	fullScreen = { false };
}

// Loop principal do "jogo"
void SolarSystem::run()
{
	// Executa enquanto a janela não for fechada
	while (!WindowShouldClose())
	{
		// Alterna tela cheia quando F11 é pressionado
		if(IsKeyPressed(KEY_F11))
		{
			fullScreen = !fullScreen;
			if (fullScreen) // Se ativar fullscreen
			{
				int monitor = GetCurrentMonitor();
				SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor)); // Usa resolução do monitor
				ToggleFullscreen(); 
			}
			else
			{
				ToggleFullscreen();
				SetWindowSize(window.x, window.y); // Se desativar, volta para a resolução de 1920x1080 pixels
			}
		}

		// Atualiza ângulos de todos os planetas baseado em suas velocidades
		for (size_t i = 0; i < planetRadius.size(); i++)
		{
			planetAngle[i] += planetsVelocities[i] * 0.02f; // 0.02f é um fator de suavização para controle de velocidade da animação
		}

		// Atualiza o ângulo da lua (mais lento do que dos outros planetas)
		moonAngle += moonVelocity * 0.009f;

		// Inicia o desenho
		BeginDrawing();
		// Limpa a tela com fundo preto
		ClearBackground(BLACK);
		// Desenha o sol no centro, com tamanho 60 e cor amarela
		DrawCircleV(center, sunSize, YELLOW);
		// Para cada planeta
		for (size_t i = 0; i < planetRadius.size(); i++)
		{
			// Desenha a órbita como um anel cinza fino
			DrawRing(center, planetRadius[i] - 1, planetRadius[i] + 1, 0, 360, 100, Color{ 60, 60, 60, 255 });
			// Calcula a posição do planeta usando trigonometria
			Vector2 planetPos = {
				center.x + cos(planetAngle[i]) * planetRadius[i],
				center.y + sin(planetAngle[i]) * planetRadius[i]
			};
			// Desenha o planeta na posição calculada
			DrawCircleV(planetPos, planetSizes[i], colors[i]);

			// Se for o planeta Terra
			if ((int)i == earthPos)
			{
				// Desenha a órbita da Lua
				DrawRing(planetPos, moonRadius - 1, moonRadius + 1, 0, 360, 100, Color{ 60, 60, 60, 255 });

				// Calcula a posição da Lua relativa à Terra
				Vector2 moonPos = {
					planetPos.x + cos(moonAngle) * moonRadius,
					planetPos.y + sin(moonAngle) * moonRadius,
				};

				// Desenha a Lua como um circulo branco
				DrawCircleV(moonPos, moonSize, WHITE);
			}
		}
		// Finaliza o desenho do frame atual
		EndDrawing();
	}
	// Fecha a janela quando o loop termina
	CloseWindow();
}

int runSolarSystem()
{
	// Cria um smart pointer único para o objeto SolarSystem
	auto obj = make_unique<SolarSystem>();

	// Executa o loop principal do sistema solar
	obj->run();

	return 0;
}

int main()
{
	return runSolarSystem();
}
