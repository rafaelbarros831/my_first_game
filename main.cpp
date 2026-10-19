#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <vector>
#include "nave.hpp"
#include "objestruturas.hpp"

using namespace std;
using namespace sf;

float posiFundo = 0.0f;
float posiFundo2 = 500.0f;

int main() {
	
	RenderWindow janela(VideoMode({500, 300}), "ShootStrike");

	janela.setFramerateLimit(1000);

	ControlNave Controle;

	Music ASkyFullStars;

	ASkyFullStars.openFromFile("musica/A_Sky_Full_of_Stars_ColdPlay.mp3");

	Texture TextInicio("Sprites/Letreiro_final.png");
	Sprite TelaInicio(TextInicio);
	TelaInicio.setPosition(Vector2f(0.0f, 0.0f));

	Texture TextOver("Sprites/GameOver-0001.png");
	Sprite Tela_GameOver(TextOver);
	Tela_GameOver.setPosition(Vector2f(0.0f, 0.0f));

	Texture textura_nave("Sprites/Nave.png");
	Sprite nave(textura_nave);
	nave.setPosition(Vector2f(Controle.posiNaviX, Controle.posiNaviY));
	nave.setScale(Vector2f(1.5f, 1.5f));
	FloatRect caixa_colisaoNave = nave.getGlobalBounds();

	Texture BackGroundTx("Sprites/backGround.png");
	Sprite Fundo(BackGroundTx);
	Fundo.setPosition(Vector2f(posiFundo, 0.0f));

	Texture BackGroundTx2("Sprites/backGround.png");
	Sprite Fundo2(BackGroundTx2);
	Fundo2.setPosition(Vector2f(posiFundo2, 0.0f));

	ASkyFullStars.setLooping(true);	
	ASkyFullStars.setVolume(40.0f);

	SorteioX();
	SorteioY();
	Cria();

	while (janela.isOpen() == true) {

		if (Estado_Game == INICIO) {

			while (optional evento = janela.pollEvent()) {

				if (evento.has_value() == true) {

					Event tipo_evento = evento.value();

					if (tipo_evento.is<Event::Closed>()) {
						janela.close();
					}
					else if (tipo_evento.is<Event::KeyPressed>()) {

						Event::KeyPressed* pressao_tecla = tipo_evento.getIf<Event::KeyPressed>();

						if (pressao_tecla->code == Keyboard::Key::Enter) {

							Estado_Game = JOGANDO;
							ASkyFullStars.play();


						}

					}

					janela.clear();
					janela.draw(TelaInicio);
					janela.display();

				}
			}
		}

		if (Estado_Game == JOGANDO) {

			while (optional evento = janela.pollEvent()) {

				if (evento.has_value() == true) {

					Event tipo_evento = evento.value();

					if (tipo_evento.is<Event::Closed>()) {
						janela.close();
					}
					else if (tipo_evento.is<Event::KeyPressed>()) {

						Event::KeyPressed* pressao_tecla = tipo_evento.getIf<Event::KeyPressed>();

						if (pressao_tecla->code == Keyboard::Key::Enter) {
							Bala tiro;
							tiro.bala.setSize(Vector2f(70.0f, 2.0f));
							tiro.bala.setFillColor(Color::Green);
							tiro.psX = Controle.posiNaviX + 80.0f;
							tiro.psY = Controle.posiNaviY + 65.0f;

							tiro.caixa_colisaoBala = tiro.bala.getGlobalBounds();

							tiros.push_back(tiro);
						}

					}

				}

			}

			janela.clear();

			janela.draw(Fundo);
			janela.draw(Fundo2);

			posiFundo -= 0.15f;
			posiFundo2 -= 0.15f;

			if (posiFundo < -500.0f) {
				posiFundo = 500.0f;
			}
			else if (posiFundo2 < -500.0f) {
				posiFundo2 = 500.0f;
			}

			Fundo.setPosition(Vector2f(posiFundo, 0.0f));
			Fundo2.setPosition(Vector2f(posiFundo2, 0.0f));


			Controle.Movimento();
			nave.setPosition(Vector2f(Controle.posiNaviX, Controle.posiNaviY));
			caixa_colisaoNave = nave.getGlobalBounds();

			GrAsteroides[0].setPosition(Vector2f(noX[0], noY[0]));
			ColisoresAstr[0] = GrAsteroides[0].getGlobalBounds();

			GrAsteroides[1].setPosition(Vector2f(noX[1], noY[1]));
			ColisoresAstr[1] = GrAsteroides[1].getGlobalBounds();

			GrAsteroides[2].setPosition(Vector2f(noX[2], noY[2]));
			ColisoresAstr[2] = GrAsteroides[2].getGlobalBounds();

			GrAsteroides[3].setPosition(Vector2f(noX[3], noY[3]));
			ColisoresAstr[3] = GrAsteroides[3].getGlobalBounds();

			GrAsteroides[4].setPosition(Vector2f(noX[4], noY[4]));
			ColisoresAstr[4] = GrAsteroides[4].getGlobalBounds();

			GrAsteroides[5].setPosition(Vector2f(noX[5], noY[5]));
			ColisoresAstr[5] = GrAsteroides[5].getGlobalBounds();

			GrAsteroides[6].setPosition(Vector2f(noX[6], noY[6]));
			ColisoresAstr[6] = GrAsteroides[6].getGlobalBounds();

			GrAsteroides[7].setPosition(Vector2f(noX[7], noY[7]));
			ColisoresAstr[7] = GrAsteroides[7].getGlobalBounds();

			GrAsteroides[8].setPosition(Vector2f(noX[8], noY[8]));
			ColisoresAstr[8] = GrAsteroides[8].getGlobalBounds();

			GrAsteroides[9].setPosition(Vector2f(noX[9], noY[9]));
			ColisoresAstr[9] = GrAsteroides[9].getGlobalBounds();


			for (int c = 0; c < tiros.size(); c++) {

				tiros[c].psX += 0.5f;
				tiros[c].bala.setPosition(Vector2f(tiros[c].psX, tiros[c].psY));
				tiros[c].caixa_colisaoBala = tiros[c].bala.getGlobalBounds();

				for (int i = 0; i < tiros.size(); i++) {
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[0])) ControlesAstr[0].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[1])) ControlesAstr[1].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[2])) ControlesAstr[2].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[3])) ControlesAstr[3].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[4])) ControlesAstr[4].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[5])) ControlesAstr[5].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[6])) ControlesAstr[6].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[7])) ControlesAstr[7].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[8])) ControlesAstr[8].desenha = false;
					if (tiros[i].caixa_colisaoBala.findIntersection(ColisoresAstr[9])) ControlesAstr[9].desenha = false;
				}

				janela.draw(tiros[c].bala);

			}


			for (int c = 0; c < 10; c++) {
				noX[c] -= 0.04f;
				GrAsteroides[c].setPosition(Vector2f(noX[c], noY[c]));
				ColisoresAstr[c] = GrAsteroides[c].getGlobalBounds();
			}

			for (int c = 0; c < 10; c++) {
				if (ControlesAstr[c].desenha != false) {
					janela.draw(GrAsteroides[c]);
				}
				else {
					GrAsteroides[c].setPosition(Vector2f(-100.0f, 100.0f));
				}
			}

			ColisoresAstr[0] = GrAsteroides[0].getGlobalBounds();
			ColisoresAstr[1] = GrAsteroides[1].getGlobalBounds();
			ColisoresAstr[2] = GrAsteroides[2].getGlobalBounds();
			ColisoresAstr[3] = GrAsteroides[3].getGlobalBounds();
			ColisoresAstr[4] = GrAsteroides[4].getGlobalBounds();
			ColisoresAstr[5] = GrAsteroides[5].getGlobalBounds();
			ColisoresAstr[6] = GrAsteroides[6].getGlobalBounds();
			ColisoresAstr[7] = GrAsteroides[7].getGlobalBounds();
			ColisoresAstr[8] = GrAsteroides[8].getGlobalBounds();
			ColisoresAstr[9] = GrAsteroides[9].getGlobalBounds();

		
			if (caixa_colisaoNave.findIntersection(ColisoresAstr[0]) || caixa_colisaoNave.findIntersection(ColisoresAstr[1]) || caixa_colisaoNave.findIntersection(ColisoresAstr[2]) || caixa_colisaoNave.findIntersection(ColisoresAstr[3]) || caixa_colisaoNave.findIntersection(ColisoresAstr[4]) || caixa_colisaoNave.findIntersection(ColisoresAstr[5]) || caixa_colisaoNave.findIntersection(ColisoresAstr[6]) || caixa_colisaoNave.findIntersection(ColisoresAstr[7]) || caixa_colisaoNave.findIntersection(ColisoresAstr[8]) || caixa_colisaoNave.findIntersection(ColisoresAstr[9])) {
				Estado_Game = GAME_OVER;
				Controle.posiNaviX = 0.0f;
				Controle.posiNaviY = 100.0f;

				tiros.clear();
				GrAsteroides.clear();
				ControlesAstr.clear();
				ColisoresAstr.clear();

				ASkyFullStars.pause();
			}

			janela.draw(nave);

			if (noX[0] < -100.0f) {
				tiros.clear();
				GrAsteroides.clear();
				ControlesAstr.clear();
				ColisoresAstr.clear();
				noX.clear();
				noY.clear();

				SorteioX();
				SorteioY();
				Cria();

			}

			janela.display();
		}

		if (Estado_Game == GAME_OVER) {
			while (optional evento = janela.pollEvent()) {

				if (evento.has_value() == true) {

					Event tipo_evento = evento.value();

					if (tipo_evento.is<Event::Closed>()) {
						janela.close();
					}
					
					janela.clear();
					janela.draw(Tela_GameOver);

					janela.display();

				}
			}
		}
		
	}

return 0;
}