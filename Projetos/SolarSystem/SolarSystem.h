#pragma once

#include <memory> // Smart pointers
#include <vector> 
#include <cmath> // Seno, cosseno, etc
#include "raylib.h" // Fornece funções para gráficos, entrada, áudio e etc

using namespace std;

// É a classe principal, representa o sistema solar
class SolarSystem
{
private:
	const float sunSize = 60.f; // Tamanho do sol em pixels
	/*
		Vector2: É um tipo da Raylib com capos x e y
		window: Armazena as dimensõesda janela (largura, altura)
		center: Armazena as coordenadas do centro da tela
	*/
	Vector2 window, center;
	/*
		planetRadius: Distância de cada planeta ao sol
		planetSizes: Diâmetro dos planetas
		planetVelocities: Velocidades Orbitais
		planetAngle: Ângulos atuais na órbita
	*/
	vector<float> planetRadius, planetSizes, planetsVelocities, planetAngle;
	vector<Color> colors; // Vector de cores, do tipo Color (da RayLib) para cada planeta

	/*
		moonSize: Tamanho da lua
		moonRadus: Distância orbital da terra
		moonVelocity: Velocidade orbital
	*/
	const float moonSize = 5.f, moonRadius = 30.f, moonVelocity = 10.f;
	float moonAngle; // Ângulo atual da lua em sua órbita ao redor da terra
	int earthPos; // Indice que indica qual planeta no array é a terra // Necessário para posicionar a lua corretamente 

	// Controla se a aplicação está em modo tela cheia
	bool fullScreen;

public:
	// Construtor para inicializar todos os membros
	SolarSystem();

	// Método principal que contém o "jogo"
	void run();
};

int runSolarSystem();

