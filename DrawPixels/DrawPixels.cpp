#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Vector.h"
#include "Escalamiento.h"
#include "traslacion.h"
#include "Rotacion.h"
#include "Matriz.h"

using std::cin; using std::cout; using std::endl;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float scaleWidth = 2, scaleHeight = 2, punto;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

Matriz matriz1(2, 2), matriz2(2, 2), matriz3(2, 2);
//traslacion traslacion1(3, 2);
//Rotacion rotacion(20);
//Escalamiento escala(3, 4);
Vector vector3(0, 0), vector4(2, 3, 1), pendiente(0, 0), linea(0, 0), vector1, vector2;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

void pruebaDeMatrices(); 
void pendientesConVectores(Vector&, Vector&); 
void drawPixel(int x, int y);  
void algoritmoDeBresenham();

void digitalDiferentialAnalyzer(Vector&, Vector&); 
void operacionesEntreVectores(Vector&, Vector&); 
void drawCircle(); 
void bezierCurva(Vector&, Vector&, Vector&, Vector&);

void operacionesConMatrices(Matriz&);  
void MatrizTraslacion(Vector& x, Vector& y);  
void MatrizEscalacion(Vector& x, Vector& y); 
void MatrizRotacion(Vector&, Vector&);

unsigned int opc;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Draw vertical line of yellow dots
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);

			for (int i = 0; i < SCREEN_HEIGHT; i += 10)
			{
				SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
			}

			for (int i = 0; i < SCREEN_WIDTH; i += 4)
			{
				SDL_RenderDrawLine(gRenderer, 0, i, SCREEN_WIDTH, i);
			}

			//cambiar el color a las lineas que se encuenrtan a la mitad de la pantalla
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
			SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			
			//Dibujar linea vertical de la pantalla
		   //Generar las divisiones del plano horizontal.
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

			for (int i = 0; i < SCREEN_WIDTH; i += 10) {
				SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
			}

			//Generar las divisiones del plano horizontal.
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

			for (int i = 0; i < SCREEN_WIDTH; i += 10) {
				SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
			}

			
			std::cout << "Que quieres hacer?\n1: dibujar circulo\n2: operaciones con vectores y matrices\n3: curva de bezier\n4: algoritmo de Bresenham\n5: salir\n";
			std::cin >> opc;

				switch (opc) {
				case 1:
					drawCircle();
				break;
				case 2:
					pruebaDeMatrices();
				break;
				case 3:
					bezierCurva(vector1, vector2, vector3, vector4);
				break;
				case 4:
					algoritmoDeBresenham();
				break;
				case 5:
					close();
					return 0;
				}
			

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void pruebaDeMatrices()
{
	bool active = true;
	printf("Introduce el primer vector\n");

	int a, b;
	cin >> a >> b;
	//se le dan valores al primer vector
	Vector vector1(a, b);
	//se imprime el vector en consola
	vector1.Print();
	//se dibuja el vector
	drawPixel(vector1.x, vector1.y);
	
	printf("Introduce el segundo vector\n");

	int c, d;

	cin >> c >> d;
	Vector vector2(c, d);
	vector2.Print();
	printf("\n");
	drawPixel(vector2.x, vector2.y);

	printf("lo quieres en matriz?\n0: Si\n1: No\n");
	int respuesta;
	cin >> respuesta;
	switch (respuesta)
	{
		case 0:
			matriz1.vectorEnMatriz(vector1, vector2);
			matriz1.print();
			operacionesConMatrices(matriz1);
			break;
		case 1:
			operacionesEntreVectores(vector1, vector2);
			break;
	}
}

void pendientesConVectores(Vector& vec1, Vector& vec2) {
	int X1 = vec1.x, X2 = vec2.x, Y1 = vec1.y, Y2 = vec2.y, x, y;

	y = Y1;
	x = X1;

	//printf("Ahora, calculare 'm' y 'c' para ti.\n");
	float m = (Y2 - Y1) / (X2 - X1);
	std::cout << "M: " << m << "\n";

	float c = y - m * x;
	std::cout << "C: " << c << "\n\n";

	if (abs(m) < 1) {
		for (int i = X1; i < X2; i++) {
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			drawPixel(x, y);

			x = x + 1;
			y = (m * x) + c;
		}
	}
	else if (abs(m) > 1) {
		for (int i = Y1; i < Y2; i++) {
			x = (y - c) / m;
			y = y + 1;

			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
		}
	}
	else
		std::cout << "estas mal.\n";
}

void digitalDiferentialAnalyzer(Vector& vec1, Vector& vec2) {
	int  X1 = vec1.x, X2 = vec2.x, Y1 = vec1.y, Y2 = vec2.y;
	float x, y;

	x = X1;
	y = Y1;

	int  incremento = 0;
	float xIncremento = 0.0f, yIncremento = 0.0f, dx = 0, dy = 0, DENO;

	//Calulos de dx y dy
	dx = abs(X2 - X1);
	dy = abs(Y2 - Y1);

	cout << "\n\nDX: " << dx << "\nDY: " << dy << "\n\n";

	//Obtencion del denominador
	//sí es mayor dx a dy, DENO es dx
	if (dx > dy) {
		DENO = dx;
	}

	//sí es mayor o igual dy a dx, DENO es dy
	if (dy >= dx) {
		DENO = dy;
	}

	//ahora podemos conseguir xINCRMNT y yINCRMNT
	xIncremento = dx / DENO;
	yIncremento = dy / DENO;

	//Impresion de valores anteriores
	cout << "Incremento en X: " << xIncremento << "\n";
	cout << "Incremento en Y: " << yIncremento << "\n";

	//empezamos un ciclo para dibujar la linea por medio de pixeles.
	while (incremento <= DENO) {
		drawPixel(x, y);
		linea.setValues(x, y, 0);
		linea.Print();
		x = x + xIncremento;
		y = y + yIncremento;
		incremento++;
	}
}

void operacionesEntreVectores(Vector& vec1, Vector& vec2) {
	vec1.z = 1;
	vec2.z = 1;

	printf("Ahora, que quieres hacer con ellos?.\n0: Sumar\n1: Restar\n2: Producto Cruz\n3: Producto Punto\n4: Escalar\n5: Dividir\n6: Pendiente\n"
		"7: DDA\n8: Trasladar\n9: Escalar\n10: Rotacion\n\n");

	int respuesta; cin >> respuesta;

	//Booleanos para controlar lo que el usuario realizara
	printf("\n");
	switch (respuesta) {
	case 0:
		vector3.Print();

		vector3 = vec1 + vec2;

		drawPixel(vector3.x, vector3.y);
		break;
	case 1:
		vector3 = vec1 - vec2;

		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;
	case 2:
		vector3 = vec1.productoCruz(vec2);
		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;
	case 3:
		punto = vec1.productoPunto(vec2);

		drawPixel(vector3.x, vector3.y);
		break;
	case 4:
		int numero;

		printf("Introduce el numero con el que quieres escalar los vectores.\n");
		cin >> numero;
		printf("Numero:%f ", numero);

		//multiplicar el vector por el numero
		vec1 = vec1 * numero;
		vec2 = vec2 * numero;

		//impresion de vectores
		vec1.Print();
		vec2.Print();

		//dibujar pixeles
		drawPixel(vec1.x, vec1.y);
		drawPixel(vec2.x, vec2.y);
		break;
	case 5:
		int numero2;

		printf("Introduce el numero con el que quieres dividir los vectores.\n");
		cin >> numero;
		printf("Numero:%f ", numero);

		//multiplicar el vector por el numero
		vec1 = vec1 / numero;
		vec2 = vec2 / numero;

		//impresion de vectores
		vec1.Print();
		vec2.Print();

		//dibujar pixeles
		drawPixel(vec1.x, vec1.y);
		drawPixel(vec2.x, vec2.y);
		break;
	case 6:
		pendientesConVectores(vec1, vec2);
		break;
	case 7:
		digitalDiferentialAnalyzer(vec1, vec2);
		break;
	case 8:
		printf("Para esto, es necesario utilizar una matriz de traslacion: \n 1 0 vx \n 0 1 vy \n 0 0 1\nNecesito que me ingreses los valores de vx y vy.\nVx: ");
		MatrizTraslacion(vec1, vec2);
		break;
	case 9:
		printf("Para esto, es necesario utilizar una matriz de escala: \n 1 0 sx \n 0 1 sy \n 0 0 1\nNecesito que me ingreses los valores de sx y sy.\nSx: ");

		MatrizEscalacion(vec1, vec2);
		break;
	case 10:
		printf("Para esto, es necesario utilizar una matriz de rotacion: \n cos(O) sin(O) 0 \n -sin(O) cos(O) 0 \n 0 0 1\nNecesito que me ingreses el angulo por el cual debe girar.\n"
			"\nAngulo: ");
		MatrizRotacion(vec1, vec2);
		break;
	}
}

void operacionesConMatrices(Matriz& matrz) {
	printf("Para realizar operaciones con otra Matriz, necesitas ingresar los valores de esta\n");
	matriz2.modificarMatriz();
	matriz2.print();

	printf("Que operacion quieres realizar con las matrices?\nSumar = 0\nRestar = 1\nMultiplicar = 2\nTransponer = 3\nSacar identidad = 4\n\n");
	int respuesta;

	cin >> respuesta;

	switch (respuesta)
	{
	case 0:
		matriz3 = matrz + matriz2;
		printf("Resultado:\n");
		matriz3.print();
		break;
	case 1:
		matriz3 = matrz - matriz2;
		printf("Resultado:\n");
		matriz3.print();
		break;
	case 2:
		matriz3 = matrz * matriz2;
		printf("Resultado:\n");
		matriz3.print();
		break;
	case 3:
		matrz = matrz.transpuesta();
		printf("Resultado M1:\n");
		matrz.print();
		matriz2.transpuesta();
		printf("\n\nResultado M2:\n");
		matriz2.print();
		break;
	case 4:
		matrz = matrz.identidad();
		printf("Resultado M1:\n");
		matrz.print();
		matriz2.identidad();
		printf("\n\nResultado M2:\n");
		matriz2.print();
		break;
	}
}

void MatrizTraslacion(Vector& vec1, Vector& vec2) {
	int vx = 0, vy = 0;

	cin >> vx;

	printf("VY: ");

	cin >> vy;

	traslacion traslacion1(vx, vy);

	//trasladando el vector 1
	printf("\nTrasladar vector 1\n");
	vector3 = traslacion1 * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//trasladando el vector 2
	printf("\nTrasladar vector2\n");
	vector4 = traslacion1 * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);
}

void MatrizEscalacion(Vector & vec1, Vector & vec2)
{
	int sx = 0, sy = 0;

	cin >> sx;
	printf("SY: ");
	cin >> sy;
	Escalamiento escala(sx, sy);

	escala.print();
	//Escalando vector 1
	printf("\nEscalando vector 1\n");
	vector3 = escala * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//Escalando vector 2
	printf("\nTrasladar vector2\n");
	vector4 = escala * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);
}

void MatrizRotacion(Vector& vec1, Vector&vec2) {
	float angulo = 0.0f;

	cin >> angulo;

	Rotacion rotando(angulo);
	rotando.print();

	//Escalando vector 1
	printf("\nAngulo en vector 1\n");
	vector3 = rotando * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//Escalando vector 2
	printf("\nAngulo en vector2\n");
	vector4 = rotando * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);
}

void algoritmoDeBresenham()
{
	float X1, X2, Y1, Y2, dx, dy, incremento, x, y;
	float P;

	printf("Introduce los valores de X1, X2, Y1, Y2: \nX1: ");
	cin >> X1;

	printf("Y1: "); cin >> Y1;
	printf("X2: "); cin >> X2;
	printf("Y2: "); cin >> Y2;

	x = X1; y = Y1;
	dx = X2 - X1;

	cout << "\n\nDX: " << dx << "\n\n";
	dy = Y2 - Y1;

	cout << "\nDY: " << dy << "\n\n";

	P = 2 * dy - dx;

	cout << "\nP: " << P << "\n\n";

	for (int i = 0; i <= dx; i++) {
		if (P < 0) {
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			x = x + 1;
			y = y;
			P = P + 2 * dy;
			cout << P << endl;
		}
		else if (P >= 0) {
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();

			x = x + 1;
			y = y + 1;
			P = P + 2 * dy - 2 * dx;

			cout << P << endl;
		}
	}
}

void drawPixel(int x, int y)
{
	SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT / 2 - y);
}

void drawCircle()
{
	//centro del círculo
	int Xc, Yc;

	//pixeles, radio y parametro.
	int x, y, radio, perimetro;

	cout << "Introduce los valores del centro del circulo.\nXC: ";
	cin >> Xc;
	cout << "YC: ";
	cin >> Yc;

	cout << "Ahora introduce el valor del radio.\nRadio: ";
	cin >> radio;

	x = 0;
	y = radio;
	perimetro = 1 - radio;

	for (int i = 0; x <= y; i++) {
		drawPixel(x + Xc, y + Yc);
		if (perimetro <= 0) {
			x = x + 1;
			y = y;
			perimetro = perimetro + 2 * x + 3;
		}
		else if (perimetro > 0) {
			x = x + 1;
			y = y - 1;
			perimetro = 2 * x - 2 * y + 5 + perimetro;
		}

		drawPixel(x + Xc, -y + Yc);
		drawPixel(-x + Xc, y + Yc);
		drawPixel(-x + Xc, -y + Yc);
		drawPixel(y + Xc, x + Yc);
		drawPixel(y + Xc, -x + Yc);
		drawPixel(-y + Xc, x + Yc);
		drawPixel(-y + Xc, -x + Yc);
	}
}

void bezierCurva(Vector& vec1, Vector& vec2, Vector& vec3, Vector& vec4) {

	cout << "Vector1 X y Y: "; cin >> vec1.x; cin >> vec1.y;
	cout << "Vector2 X y Y: "; cin >> vec2.x; cin >> vec2.y;
	cout << "Vector3 X y Y: "; cin >> vec3.x; cin >> vec3.y;
	cout << "Vector4 X y Y: "; cin >> vec4.x; cin >> vec4.y;

	//int t = 1;
	double x = 0.0, y = 0.0;

	Vector temp;

	for (double i = 0.0; i <= 1; i += 0.0001) {
		temp.x = pow(1 - i, 3) * vec1.x + (3 * i)*(pow(1 - i, 2) * vec2.x) + (3 * pow(i, 2))*(1 - i * vec3.x) + (pow(i, 3))*(vec4.x);
		temp.y = pow(1 - i, 3) * vec1.y + (3 * i)*(pow(1 - i, 2) * vec2.y) + (3 * pow(i, 2))*(1 - i * vec3.y) + (pow(i, 3))*(vec4.y);
		drawPixel(temp.x, temp.y);
	}
}