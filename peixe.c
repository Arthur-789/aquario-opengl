#include <stdlib.h>
#include <math.h>
#include "aquario.h"

#define MAX_PEIXES 20

Peixe* peixes = NULL;
int numPeixes = 0;

void desenharPeixe(Peixe* peixe) {
    if (!peixe) return;

    float tamX = peixe->tamanho;
    float tamY = peixe->tamanho / 2.0f;
    float tamZ = peixe->tamanho / 3.0f;

    float hx = tamX / 2.0f;
    float hy = tamY / 2.0f;
    float hz = tamZ / 2.0f;

    GLuint idTextura = peixe->textura;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    glPushMatrix();

    // posiciona e orienta o peixe (rotacao em graus, em torno de Y)
    glTranslatef(peixe->posX, peixe->posY, peixe->posZ);
    glRotatef(peixe->rotacao, 0.0f, 1.0f, 0.0f);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( hx, -hy,  hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( hx,  hy,  hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx,  hy,  hz);

        glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( hx,  hy, -hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx,  hy, -hz);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glColor3f(peixe->corR, peixe->corG, peixe->corB);

    // Lateral esquerda
    glBegin(GL_QUADS);
        glVertex3f(-hx, -hy, -hz);
        glVertex3f(-hx, -hy,  hz);
        glVertex3f(-hx,  hy,  hz);
        glVertex3f(-hx,  hy, -hz);
    // Lateral direita
        glVertex3f( hx, -hy,  hz);
        glVertex3f( hx, -hy, -hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f( hx,  hy,  hz);
    // Topo
        glVertex3f(-hx,  hy,  hz);
        glVertex3f( hx,  hy,  hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f(-hx,  hy, -hz);
    // Fundo
        glVertex3f(-hx, -hy, -hz);
        glVertex3f( hx, -hy, -hz);
        glVertex3f( hx, -hy,  hz);
        glVertex3f(-hx, -hy,  hz);
    glEnd();
    glPopMatrix();
}

void adicionarPeixe() {
    if (numPeixes >= MAX_PEIXES) {
        return;
    }

    Peixe* novoArray = realloc(peixes, (numPeixes + 1) * sizeof(Peixe));
    if (!novoArray) {
        return;
    }

    peixes = novoArray;
    Peixe* novoPeixe = &peixes[numPeixes];

    float r = (float)rand() / (float)RAND_MAX;
    novoPeixe->velocidade = 0.02f + r * 0.08f; // 0.02 até 0.10
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->tamanho = 0.2f + r * 0.7f; // 0.2 até 1.0

    float margemX = novoPeixe->tamanho / 2.0f + 0.05f;
    float margemZ = novoPeixe->tamanho / 2.0f + 0.05f;
    float margemY = novoPeixe->tamanho / 2.0f + 0.05f;

    // Posição aleatória dentro do aquário (centrado em 0)
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->posX = (r * (LARGURA_AQUARIO - 2.0f * margemX)) - (LARGURA_AQUARIO/2.0f - margemX);

    r = (float)rand() / (float)RAND_MAX;
    float bottomY = -1.99f + margemY;
    float topY = bottomY + ALTURA_AGUA - margemY;
    novoPeixe->posY = bottomY + r * (topY - bottomY);

    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->posZ = (r * (PROFUNDIDADE_AQUARIO - 2.0f * margemZ)) - (PROFUNDIDADE_AQUARIO/2.0f - margemZ);

    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->dirX = r * 2.0f - 1.0f;
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->dirZ = r * 2.0f - 1.0f;
    novoPeixe->dirY = 0.0f;

    // Normalizar e evitar vetor zero
    float comprimento = sqrt(novoPeixe->dirX * novoPeixe->dirX + novoPeixe->dirZ * novoPeixe->dirZ);
    if (comprimento < 1e-4f) {
        // direção quase zero -> direção padrão
        novoPeixe->dirX = 1.0f;
        novoPeixe->dirZ = 0.0f;
        comprimento = 1.0f;
    }
    novoPeixe->dirX /= comprimento;
    novoPeixe->dirZ /= comprimento;
    // Calcular rotação em graus
    // atan2(z, x) retorna ângulo no plano XZ
    novoPeixe->rotacao = atan2f(novoPeixe->dirZ, novoPeixe->dirX) * 180.0f / M_PI;

    int texturaIdx = rand() % 5;
    switch(texturaIdx) {
        case 0: novoPeixe->textura = texturaPeixe1; break;
        case 1: novoPeixe->textura = texturaPeixe2; break;
        case 2: novoPeixe->textura = texturaPeixe3; break;
        case 3: novoPeixe->textura = texturaPeixe4; break;
        default: novoPeixe->textura = texturaPeixe5; break;
    }

    novoPeixe->corR = coresTexturaPeixe[texturaIdx][0];
    novoPeixe->corG = coresTexturaPeixe[texturaIdx][1];
    novoPeixe->corB = coresTexturaPeixe[texturaIdx][2];

    numPeixes++;
}

void inicializarPeixes(int quantidade) {
    for (int i = 0; i < quantidade && numPeixes < MAX_PEIXES; i++) {
        adicionarPeixe();
    }
}