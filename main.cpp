#include "main.hpp"

// Fenetre de jeu
RenderWindow window;

// Gestion des inputs
Input input;

// Font ou police
Font font;

// texte
Text txt;

// position de raquette 
int posRaquetteLeftX = 50;
int posRaquetteRightX = win_width - 70;
int posRaquetteLeftY = win_height / 2;
int posRaquetteRightY = posRaquetteLeftY;
int raquetteSpeed = 1;
int raquetteHeight = 150;
int raquetteWidth = 20;

// balle
float ballSpeed = 0.2f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
float ballPosX = win_width / 2;
float ballPosY = win_height / 2;

// Score
int scoreJ1 = 0;
int scoreJ2 = 0;

// raquette IA
void raquetteIA()
{
	posRaquetteRightY = ballPosY;
}


int main()
{
	window.create(VideoMode(win_width, win_height), "PONG", Style::Default);

	font.loadFromFile("font/bold.ttf");

	SetText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2)); // to_string : convertit les int en string

	// Preparation des formes
	// Balle
	CircleShape ball(15);
	ball.setPosition(ballPosX, ballPosY);

	// raquette gauche
	RectangleShape raquetteGauche(Vector2f(raquetteWidth, raquetteHeight));
	raquetteGauche.setPosition(posRaquetteLeftX, posRaquetteLeftY);

	// raquette droite
	RectangleShape raquetteDroite(Vector2f(raquetteWidth, raquetteHeight));
	raquetteDroite.setPosition(posRaquetteRightX, posRaquetteRightY);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}

		// Gestion clavier souris
		CheckBtn();
		// IA 
		raquetteIA();
		raquetteGauche.setPosition(posRaquetteLeftX, posRaquetteLeftY);
		raquetteDroite.setPosition(posRaquetteRightX, posRaquetteRightY);

		UpdateBall();
		ball.setPosition(ballPosX, ballPosY);

		window.clear(Color(50,100,50,30));

		window.draw(txt);
		window.draw(raquetteGauche);
		window.draw(raquetteDroite);
		window.draw(ball);
		
		window.display();
	}
	return 0;
}


void SetText(Text& txt, String str)
{
	txt.setFont(font); // police ou font
	txt.setString(str); // Chaine de caractere a afficher
	txt.setCharacterSize(26);
	txt.setFillColor(Color::White);
	txt.setPosition((win_width / 2) - 40, 10);
}

void CheckBtn()
{
	// raquette Gauche
	if (input.GetButton().up == true)
	{
		posRaquetteLeftY -= raquetteSpeed;
		if (posRaquetteLeftY < 0)
		{
			posRaquetteLeftY = 0;
		}
	}

	if (input.GetButton().down)
	{
		posRaquetteLeftY += raquetteSpeed;
		if (posRaquetteLeftY + raquetteHeight > win_height)
		{
			posRaquetteLeftY = win_height - raquetteHeight;
		}
	}

	// raquette droite
	if (input.GetButton().left == true)
	{
		posRaquetteRightY -= raquetteSpeed;
		if (posRaquetteRightY < 0)
		{
			posRaquetteRightY = 0;
		}
	}
	if (input.GetButton().right)
	{
		posRaquetteRightY += raquetteSpeed;
		if (posRaquetteRightY + raquetteHeight > win_height)
		{
			posRaquetteRightY = win_height - raquetteHeight;
		}
	}

	// fermeture
	if (input.GetButton().escape == true)
	{
		window.close();
	}
}

void UpdateBall()
{
	// mvt balle
	ballPosX += ballDir.x * ballSpeed;
	ballPosY += ballDir.y * ballSpeed;

	// contact balle et raquette
	if ((ballPosX < posRaquetteLeftX + raquetteWidth &&
		ballPosX > posRaquetteLeftX &&
		ballPosY + 7 < posRaquetteLeftY + raquetteHeight && // on ajoute 7 car il y a un décallage entre la balle et les raquettes 
		ballPosY + 7 > posRaquetteLeftY)
		||
		ballPosX > posRaquetteRightX - raquetteWidth &&
		ballPosX < posRaquetteRightX &&
		ballPosY + 7 < posRaquetteRightY + raquetteHeight &&
		ballPosY + 7 > posRaquetteRightY)
	{
		ballDir.x *= -1;
	}

	// mur gauche
	if (ballPosX < 0)
	{
		scoreJ2++;
		ballPosX = win_width / 2;
		ballPosY = win_height / 2;
		ballDir.x = fabs(ballDir.x); // valeur absolue
		ballDir.y *= -1;
		SetText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2));
	}

	// mur droit
	if (ballPosX > win_width)
	{
		scoreJ1++;
		ballPosX = win_width / 2;
		ballPosY = win_height / 2;
		ballDir.x = -fabs(ballDir.x); // valeur absolue
		ballDir.y *= -1;
		SetText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2));
	}

	// mur haut et bas
	if (ballPosY > win_height || ballPosY < 0)
	{
		ballDir.y *= -1;
	}
}



