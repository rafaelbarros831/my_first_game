#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

float posiCircX = 0.0f;
float posiCircY = 100.0f;

struct Balas{

	bool desenha = false;

sf::CircleShape bala;
float psX = 150.0f, psY = 100;
sf::FloatRect colisao_bal;

};

struct Asteroide{

	bool desenha = true;

	sf::CircleShape obgt;
	sf::FloatRect caixa_colisao;

};

std::vector<float>noX;
std::vector<float>noY;
std::vector<Asteroide> vets;
std::vector<Balas> tiros;


void sorteioX() {

	for (int posiX = 0; posiX < 3; posiX++) {
		std::random_device aleat;
		std::mt19937 caos(aleat());
		 
		std::uniform_real_distribution<float> sorteio(400.0f, 450.0f);

		float result = sorteio(caos);

		noX.push_back(result);
	}

}

void sorteioY(){
	
	for (int posiY = 0; posiY < 3; posiY++) {
		std::random_device semente;
		std::mt19937 caos(semente());

		std::uniform_real_distribution<float> sorteioS(-40.0f, 240.0f);

		float posi_sort = sorteioS(caos);

		noY.push_back(posi_sort);
	}
}

void Cria() {
	
	for (int c = 0; c < 3; c++) {

		Asteroide astr;

		astr.obgt.setRadius(15);
		astr.obgt.setFillColor(sf::Color::Yellow);

		vets.push_back(astr);

	}

}



int main() {

	sf::RenderWindow janela(sf::VideoMode({500, 300}), "Coisa");//Cria janela de 500 pixels de largura e 300 pixels de altura com o título "Coisa".

	janela.setFramerateLimit(1000);

	sf::RectangleShape quadrado(sf::Vector2f(200.0f, 300.0f));
	quadrado.setPosition(sf::Vector2f(30.0f, 100.0f));

	sf::CircleShape circulo(50.0f);
	circulo.setFillColor(sf::Color::Red);
	circulo.setPosition(sf::Vector2f(posiCircX, posiCircY));

	//sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); <- Posso usar mais tarde.

	sorteioX();
	sorteioY();

	Cria();

	while (janela.isOpen() == true) {//Laço que colore a janela de azul e mostra versão mais recente dela enquana janela estiver aberta.

		while (std::optional evento = janela.pollEvent()) {//Laço que aguarda por um evento.

			/*if (evento->is <sf::Event::Closed>()) {//Verifica se o evento é um fechamento de janela.

				janela.close();//Fecha a janela

			}*/

			if (evento.has_value()) {

				sf::Event tipo_evento = evento.value();//Guarda os dados do evento dentro da variável tipo_evento.

				if (tipo_evento.is<sf::Event::Closed>()) {
					janela.close();
				}
				else if (tipo_evento.is<sf::Event::KeyPressed>()) {
					sf::Event::KeyPressed* pressao_tecla = tipo_evento.getIf<sf::Event::KeyPressed>();

					if (pressao_tecla->code == sf::Keyboard::Key::N) {

						if (tiros.size() > 100) {
							tiros.clear();
						}

						Balas tiro;
						tiro.bala.setRadius(10.0f);
						tiro.bala.setFillColor(sf::Color::Magenta);
						tiro.psX = posiCircX + 70.0f;
						tiro.psY = posiCircY;
						tiro.bala.setPosition(sf::Vector2f(tiro.psX, tiro.psY));

						tiro.colisao_bal = tiro.bala.getGlobalBounds();


						tiros.push_back(tiro);
					}
				}
			}

		}

		
		janela.clear(sf::Color::Cyan);

		janela.draw(circulo);
		//janela.draw(quadrado);

		sf::FloatRect caixa_quad = quadrado.getGlobalBounds();//Cria caixa de colisão ao redor do objeto.


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			posiCircY -= 0.2f;

			circulo.setPosition(sf::Vector2(posiCircX, posiCircY));

			if (posiCircY < -40.0f) {
				posiCircY = -40.0f;
			}
			
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			posiCircY += 0.2f;
			
			circulo.setPosition(sf::Vector2f(posiCircX, posiCircY));

			if (posiCircY > 240.0f) {
				posiCircY = 240.0f;
			}

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			posiCircX += 0.2f;

			circulo.setPosition(sf::Vector2f(posiCircX, posiCircY));

			if (posiCircX > 400.0f) {
				posiCircX = 400.0f;
			}


		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			posiCircX -= 0.2f;

			circulo.setPosition(sf::Vector2f(posiCircX, posiCircY));

			if (posiCircX < 0.0f) {
				posiCircX = 0.0f;
			}
		
		}

		noX[0] -= 0.05f;
		noX[1] -= 0.05f;
		noX[2] -= 0.05f;

		vets[1].obgt.setPosition(sf::Vector2f(noX[0], noY[0]));
		vets[1].caixa_colisao = vets[1].obgt.getGlobalBounds();

		vets[0].obgt.setPosition(sf::Vector2f(noX[2], noY[2]));
		vets[0].caixa_colisao = vets[0].obgt.getGlobalBounds();

		vets[2].obgt.setPosition(sf::Vector2f(noX[1], noY[1]));
		vets[2].caixa_colisao = vets[2].obgt.getGlobalBounds();

		if (vets[1].desenha != false) {
			vets[1].obgt.setPosition(sf::Vector2f(noX[0], noY[0]));
			janela.draw(vets[1].obgt);
		}

		else {
			vets[1].obgt.setPosition(sf::Vector2f(-100.0f, 100.0f));
		}


		if (vets[2].desenha != false) {
			vets[2].obgt.setPosition(sf::Vector2f(noX[1], noY[1]));
			janela.draw(vets[2].obgt);
		}
			else {
			vets[2].obgt.setPosition(sf::Vector2f(-100.0f, 100.0f));
			}


		if (vets[0].desenha != false) {
			vets[0].obgt.setPosition(sf::Vector2f(noX[2], noY[2]));
			janela.draw(vets[0].obgt);
		}
			else {
			vets[0].obgt.setPosition(sf::Vector2f(-100.0f, 100.0f));
			}

		vets[1].caixa_colisao = vets[1].obgt.getGlobalBounds();
		vets[2].caixa_colisao = vets[2].obgt.getGlobalBounds();
		vets[0].caixa_colisao = vets[0].obgt.getGlobalBounds();


		sf::FloatRect caixa_circ = circulo.getGlobalBounds();


		if (caixa_circ.findIntersection(vets[0].caixa_colisao) || caixa_circ.findIntersection(vets[1].caixa_colisao) || caixa_circ.findIntersection(vets[2].caixa_colisao)) {
			break;

		}


		if (caixa_quad.findIntersection(caixa_circ)) {
		
			quadrado.setFillColor(sf::Color::Blue);
			quadrado.setSize(sf::Vector2f(50.0f,  50.0f));
		}

		else {
			quadrado.setFillColor(sf::Color::Green);
			quadrado.setSize(sf::Vector2f(100.0f, 100.0f));
		}	
	

		for (int c = 0; c < tiros.size(); c++) {

			tiros[c].psX += 0.5f;
			tiros[c].bala.setPosition(sf::Vector2f(tiros[c].psX, tiros[c].psY));
			tiros[c].colisao_bal = tiros[c].bala.getGlobalBounds();//Atualizando a posiçaõ da caixa de colisão do tiro atual no vetor.

			for (int i = 0; i < tiros.size(); i++) {
				if (tiros[i].colisao_bal.findIntersection(vets[0].caixa_colisao)) vets[0].desenha = false;
				if (tiros[i].colisao_bal.findIntersection(vets[1].caixa_colisao)) vets[1].desenha = false;
				if (tiros[i].colisao_bal.findIntersection(vets[2].caixa_colisao)) vets[2].desenha = false;
			}

				janela.draw(tiros[c].bala);

		}

		if (noX[1] < -100.0f) {
			noX.clear();
			noY.clear();
			vets.clear();
			tiros.clear();

			sorteioX();
			sorteioY();
			Cria();
		}


		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
			
		}*/


		/*if (desenha != false) {
			sf::CircleShape test(10.0f);
			test.setFillColor(sf::Color::Magenta);
			test.setPosition(sf::Vector2f(testX, testY));
			janela.draw(test);

			testX += 0.5f;
			test.setPosition(sf::Vector2f(testX, testY));

		}*/
		
		std::cout<<tiros.size() << std::endl;

		janela.display();//Exibe a janela em seu estado mais recente.

	}

	

 return 0;

}
