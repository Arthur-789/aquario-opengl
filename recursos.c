#include <SOIL/SOIL.h>
#include <stdio.h>
#include <time.h>
#include "aquario.h"

// Parâmetros da câmera
float raio_camera = 8.0f;
float angulo_theta = 0.0f;
float angulo_phi = M_PI/3;

// Controle do mouse
int ultimoX = 0, ultimoY = 0;
int botaoEsquerdoPressionado = 0;

// Texturas
GLuint texturaAreia;
GLuint texturaMesa;
GLuint texturaCeu;
GLuint texturaAbacaxi;
GLuint texturaPedra;
GLuint texturaMadeira;
GLuint texturaPeixe1;
GLuint texturaPeixe2;
GLuint texturaPeixe3;
GLuint texturaPeixe4;
GLuint texturaPeixe5;
float coresTexturaPeixe[5][3] = {
    {1.0f, 0.373f, 0.122f},
    {0.121f, 0.318f, 1.0f},
    {0.059f, 1.0f, 0.314f},
    {1.0f, 0.192f, 0.192f},
    {1.0f, 0.063f, 0.941f}
};

GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura;
    int largura, altura;
    unsigned char* dados;
    
    dados = SOIL_load_image(arquivo, &largura, &altura, 0, SOIL_LOAD_RGB);
    if(!dados) {
        printf("Erro ao carregar textura: %s\n", arquivo);
        return 0;
    }
    
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, largura, altura, GL_RGB, GL_UNSIGNED_BYTE, dados);
    
    SOIL_free_image_data(dados);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return idTextura;
}

void inicializar() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    
    texturaAreia = carregaTextura("texturas/areia.png");
    texturaMesa = carregaTextura("texturas/madeira.png");
    texturaCeu = carregaTextura("texturas/ceu.png");
    texturaAbacaxi = carregaTextura("texturas/abacaxi.png");
    texturaPedra = carregaTextura("texturas/pedra.png");
    texturaMadeira = carregaTextura("texturas/madeira_2.png");
    texturaPeixe1 = carregaTextura("texturas/peixe1.png");
    texturaPeixe2 = carregaTextura("texturas/peixe2.png");
    texturaPeixe3 = carregaTextura("texturas/peixe3.png");
    texturaPeixe4 = carregaTextura("texturas/peixe4.png");
    texturaPeixe5 = carregaTextura("texturas/peixe5.png");

    inicializarIluminacao();

    srand(time(NULL));
    inicializarPeixes(3);
}

void atualizaCamera() {
    float x = raio_camera * sin(angulo_theta) * sin(angulo_phi);
    float y = raio_camera * cos(angulo_phi);
    float z = raio_camera * cos(angulo_theta) * sin(angulo_phi);
    
    gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}

void redimensiona(int largura, int altura) {
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)largura/altura, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON) {
        botaoEsquerdoPressionado = (estado == GLUT_DOWN) ? 1 : 0;
        ultimoX = x;
        ultimoY = y;
    }
    else if (botao == 3) { // Scroll para cima
        raio_camera -= 0.5f;
        raio_camera = fmax(3.0f, raio_camera);
        glutPostRedisplay();
    }
    else if (botao == 4) { // Scroll para baixo
        raio_camera += 0.5f;
        raio_camera = fmin(15.0f, raio_camera);
        glutPostRedisplay();
    }
}

void movimentoMouse(int x, int y) {
    if (botaoEsquerdoPressionado) {
        angulo_theta += 0.01f * (x - ultimoX);
        angulo_phi += 0.01f * (y - ultimoY);
        angulo_phi = fmax(0.1f, fmin(angulo_phi, M_PI - 0.1f));
        
        ultimoX = x;
        ultimoY = y;
        glutPostRedisplay();
    }
}

void teclado(unsigned char tecla, int x, int y) {
    switch(tecla) {
        case 'a':
        case 'A':
            adicionarPeixe();
            glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            removerPeixe();
            glutPostRedisplay();
    }
}