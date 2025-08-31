#include <stdlib.h>
#include "aquario.h"

Peixe* peixes = NULL;
int numPeixes = 0;

void atualizarPeixes() {
    for (int i = 0; i < numPeixes; i++) {
        Peixe* p = &peixes[i];
        
        p->posX += p->dirX * p->velocidade;
        p->posY += p->dirY * p->velocidade;
        p->posZ += p->dirZ * p->velocidade;

        float margem = p->tamanho / 2.0f;
        float x_min = -LARGURA_AQUARIO/2 + margem;
        float x_max = LARGURA_AQUARIO/2 - margem;
        float y_min = -2.0f + margem;  // Base do aquário
        float y_max = (-2.0f + ALTURA_AGUA) - margem;
        float z_min = -PROFUNDIDADE_AQUARIO/2 + margem;
        float z_max = PROFUNDIDADE_AQUARIO/2 - margem;

        // Verifica colisão com as paredes e inverte direção se necessário
        if (p->posX < x_min || p->posX > x_max) {
            p->dirX *= -1;
            p->posX = (p->posX < x_min) ? x_min : x_max;
        }
        if (p->posY < y_min || p->posY > y_max) {
            p->dirY *= -1;
            p->posY = (p->posY < y_min) ? y_min : y_max;
        }
        if (p->posZ < z_min || p->posZ > z_max) {
            p->dirZ *= -1;
            p->posZ = (p->posZ < z_min) ? z_min : z_max;
        }

        // Atualiza rotação baseada na direção (apenas no eixo Y)
        p->rotacao = atan2f(p->dirX, p->dirZ) * 180.0f / M_PI;
    }
    glutPostRedisplay();
}

void movimentoOciosoPeixes(){
    for(int i = 0; i < numPeixes; i++){
        Peixe* p = &peixes[i];

        float margem = p->tamanho / 2.0f;
        float x_min = -LARGURA_AQUARIO/2 + margem;
        float x_max = LARGURA_AQUARIO/2 - margem;
        float y_min = -2.0f + margem;
        float y_max = (-2.0f + ALTURA_AGUA) - margem;
        float z_min = -PROFUNDIDADE_AQUARIO/2 + margem;
        float z_max = PROFUNDIDADE_AQUARIO/2 - margem;

        float area_ociosa = 2.0f;
        float x_min_ocioso = p->posX - area_ociosa;
        float x_max_ocioso = p->posX + area_ociosa;
        float y_min_ocioso = p->posY - area_ociosa;
        float y_max_ocioso = p->posY + area_ociosa;
        float z_min_ocioso = p->posZ - area_ociosa;
        float z_max_ocioso = p->posZ + area_ociosa;

        x_min_ocioso = (x_min_ocioso < x_min) ? x_min : x_min_ocioso;
        x_max_ocioso = (x_max_ocioso > x_max) ? x_max : x_max_ocioso;
        y_min_ocioso = (y_min_ocioso < y_min) ? y_min : y_min_ocioso;
        y_max_ocioso = (y_max_ocioso > y_max) ? y_max : y_max_ocioso;
        z_min_ocioso = (z_min_ocioso < z_min) ? z_min : z_min_ocioso;
        z_max_ocioso = (z_max_ocioso > z_max) ? z_max : z_max_ocioso;

        if (rand() % 200 < 1) {
            float r1 = (float)rand() / (float)RAND_MAX;
            float r2 = (float)rand() / (float)RAND_MAX;
            float r3 = (float)rand() / (float)RAND_MAX;
            
            p->dirX = r1 * 1.0f - 0.5f;
            p->dirY = r2 * 1.0f - 0.5f;
            p->dirZ = r3 * 1.0f - 0.5f;
            
            float magnitude = sqrt(p->dirX * p->dirX + p->dirY * p->dirY + p->dirZ * p->dirZ);
            if (magnitude > 0) {
                p->dirX /= magnitude;
                p->dirY /= magnitude;
                p->dirZ /= magnitude;
            }
            
        }

        p->posX += p->dirX * p->velocidade;
        p->posY += p->dirY * p->velocidade;
        p->posZ += p->dirZ * p->velocidade;

        // Se sair da área de animação ociosa, volta para o centro
        if (p->posX < x_min_ocioso || p->posX > x_max_ocioso ||
            p->posY < y_min_ocioso || p->posY > y_max_ocioso ||
            p->posZ < z_min_ocioso || p->posZ > z_max_ocioso) {
            
            p->dirX = (p->posX - (x_min_ocioso + x_max_ocioso)/2) > 0 ? -1 : 1;
            p->dirY = (p->posY - (y_min_ocioso + y_max_ocioso)/2) > 0 ? -1 : 1;
            p->dirZ = (p->posZ - (z_min_ocioso + z_max_ocioso)/2) > 0 ? -1 : 1;
            
            // Normalização
            float magnitude = sqrt(p->dirX * p->dirX + p->dirY * p->dirY + p->dirZ * p->dirZ);
            if (magnitude > 0) {
                p->dirX /= magnitude;
                p->dirY /= magnitude;
                p->dirZ /= magnitude;
            }
        }

        // Limites
        if (p->posX < x_min) { p->posX = x_min; p->dirX = fabs(p->dirX); }
        if (p->posX > x_max) { p->posX = x_max; p->dirX = -fabs(p->dirX); }
        if (p->posY < y_min) { p->posY = y_min; p->dirY = fabs(p->dirY); }
        if (p->posY > y_max) { p->posY = y_max; p->dirY = -fabs(p->dirY); }
        if (p->posZ < z_min) { p->posZ = z_min; p->dirZ = fabs(p->dirZ); }
        if (p->posZ > z_max) { p->posZ = z_max; p->dirZ = -fabs(p->dirZ); }

        if (p->dirX != 0 || p->dirZ != 0) {
            p->rotacao = atan2f(-p->dirX, -p->dirZ) * (180.0f / M_PI);
        }
    }
    glutPostRedisplay();
}

void desenharPeixe(Peixe* peixe) {
    if (!peixe) return;

    float tamX = peixe->tamanho / 3.0f;
    float tamY = peixe->tamanho / 2.0f;
    float tamZ = peixe->tamanho;

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
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-hx,  hy,  hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx,  hy, -hz);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( hx, -hy,  hz);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( hx,  hy, -hz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( hx,  hy,  hz);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glColor3f(peixe->corR, peixe->corG, peixe->corB);

    // Lateral esquerda
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-hx, -hy,  hz);
        glVertex3f( hx, -hy,  hz);
        glVertex3f( hx,  hy,  hz);
        glVertex3f(-hx,  hy,  hz);
    // Lateral direita
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-hx, -hy, -hz);
        glVertex3f( hx, -hy, -hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f(-hx,  hy, -hz);
    // Topo
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-hx,  hy,  hz);
        glVertex3f( hx,  hy,  hz);
        glVertex3f( hx,  hy, -hz);
        glVertex3f(-hx,  hy, -hz);
    // Fundo
        glNormal3f(0.0f, -1.0f, 0.0f);
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
    novoPeixe->velocidade = 0.0015f + r * 0.003f;
    r = (float)rand() / (float)RAND_MAX;
    novoPeixe->tamanho = 0.2f + r * 0.3f;

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

void removerPeixe(){
    if(numPeixes == 0){
        return;
    }

    Peixe peixeVazio = {0};
    peixes[numPeixes-1] = peixeVazio;
    peixes = realloc(peixes, (numPeixes - 1) * sizeof(Peixe));

    numPeixes--;
}

void inicializarPeixes(int quantidade) {
    for (int i = 0; i < quantidade && numPeixes < MAX_PEIXES; i++) {
        adicionarPeixe();
    }
}