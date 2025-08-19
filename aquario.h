#ifndef AQUARIO_H
#define AQUARIO_H

// RECURSOS

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define LARGURA_AQUARIO 5.0f
#define ALTURA_AQUARIO 4.0f
#define PROFUNDIDADE_AQUARIO 3.5f
#define ALTURA_AGUA (ALTURA_AQUARIO * 0.95)

#include <GL/glut.h>
#include <GL/glu.h> 
#include <math.h>

extern float raio_camera;
extern float angulo_theta;
extern float angulo_phi;
extern int ultimoX;
extern int ultimoY;
extern int botaoEsquerdoPressionado;
extern GLuint texturaAreia;
extern GLuint texturaMesa;
extern GLuint texturaCeu;
extern GLuint texturaAbacaxi;
extern GLuint texturaPeixe1;
extern GLuint texturaPeixe2;
extern GLuint texturaPeixe3;
extern GLuint texturaPeixe4;
extern GLuint texturaPeixe5;
extern float coresTexturaPeixe[5][3];

GLuint carregaTextura(const char* arquivo);
void inicializar();
void atualizaCamera();
void redimensiona(int largura, int altura);
void mouse(int botao, int estado, int x, int y);
void movimentoMouse(int x, int y);
void teclado(unsigned char tecla, int x, int y);

// CENA

void desenhaCeu();
void desenhaCena();
void iniciaCena();

// PEIXE

typedef struct {
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    float velocidade;
    float tamanho;
    float rotacao;
    GLuint textura;
    float corR, corG, corB;
} Peixe;

extern Peixe* peixes;
extern int numPeixes;

void desenharPeixe(Peixe* peixe);
void adicionarPeixe();
void inicializarPeixes(int quantidade);

#endif