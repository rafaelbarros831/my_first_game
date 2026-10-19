#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

Texture textura_asteroide("Sprites/Asteroide_0001.png");

struct Bala {

	bool desenha = false;

RectangleShape bala;
float psX = 0.0f, psY = 0.0f;
FloatRect caixa_colisaoBala;

};

struct ControlAsteroide {

bool desenha = true;

};

enum GameState {

	INICIO,
	JOGANDO,
	GAME_OVER

};

GameState Estado_Game = INICIO;

vector<Sprite> GrAsteroides;
vector<FloatRect> ColisoresAstr;
vector<float> noX;
vector<float> noY;
vector<ControlAsteroide> ControlesAstr;
vector<Bala> tiros;

void Cria() {

	

	for (int c = 0; c < 10; c++) {
		Sprite sprite_asteroide(textura_asteroide);
		GrAsteroides.push_back(sprite_asteroide);

		FloatRect colisor_asteroide = GrAsteroides[c].getGlobalBounds();
		ColisoresAstr.push_back(colisor_asteroide);

		ControlAsteroide controle_asteroide;
		ControlesAstr.push_back(controle_asteroide);
	}

}

void SorteioX() {

	for (int posiX = 0; posiX < 10; posiX++) {
		std::random_device aleat;
		std::mt19937 caos(aleat());

		std::uniform_real_distribution<float> sorteio(400.0f, 650.0f);

		float resultsort = sorteio(caos);

		noX.push_back(resultsort);
	}

}

void SorteioY() {

	for (int posiY = 0; posiY < 10; posiY++) {
		std::random_device aleat;
		std::mt19937 caos(aleat());

		std::uniform_real_distribution<float> sorteio(20.0f, 250.0f);

		float resultsort = sorteio(caos);

		noY.push_back(resultsort);
	}
}