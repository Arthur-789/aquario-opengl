#include <GL/glut.h>
#include "aquario.h"

void desenhaCeu() {
    float tamanho = 100.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaCeu);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Desativar teste de profundidade para ficar atrás de tudo
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-tamanho, -tamanho, -tamanho);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( tamanho, -tamanho, -tamanho);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( tamanho,  tamanho, -tamanho);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-tamanho,  tamanho, -tamanho);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

void desenhaCena() {

    // CÉU
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaCeu();

    atualizaCamera();
    
    // MESA
    float largura_mesa = LARGURA_AQUARIO * 1.5f;
    float profundidade_mesa = PROFUNDIDADE_AQUARIO * 1.5f;
    float espessura_mesa = 0.2f;
    float topo_mesa = -ALTURA_AQUARIO/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaMesa);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa,  profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa,  profundidade_mesa/2);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3f(largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(largura_mesa/2, topo_mesa, profundidade_mesa/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa,  profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa,  profundidade_mesa/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // AREIA
    float fundo_aquario = topo_mesa + 0.01;
    float largura_areia = LARGURA_AQUARIO - 0.02;
    float profundidade_areia = PROFUNDIDADE_AQUARIO - 0.02;
    float topo_areia = topo_mesa + 0.07;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaAreia);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // ABACAXI
    float x_abacaxi = - (LARGURA_AQUARIO/2 * 0.8f);
    float z_abacaxi = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_abacaxi = fundo_aquario + 0.35f;

    glPushMatrix();
    glTranslatef(x_abacaxi, base_abacaxi, z_abacaxi);

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.8f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaAbacaxi);

    GLUquadric* obj = gluNewQuadric();
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricNormals(obj, GLU_SMOOTH);
    gluSphere(obj, 0.6, 32, 32);
    gluDeleteQuadric(obj);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Folhas (coroa verde)
    glColor3f(0.0f, 0.6f, 0.2f);
    int numFolhas = 12;
    for(int i = 0; i < numFolhas; i++) {
        glPushMatrix();
        // Ajuste de posição Y considerando a rotação
        glTranslatef(x_abacaxi, base_abacaxi + 0.55f, z_abacaxi);
        glRotatef(i * (360.0f/numFolhas), 0.0f, 1.0f, 0.0f);
        glRotatef(-25.0f + (i%3)*8, 1.0f, 0.0f, 0.0f);
        
        obj = gluNewQuadric();
        gluCylinder(obj, 0.08f, 0.001f, 0.5f, 8, 1);
        gluDeleteQuadric(obj);
        glPopMatrix();
    }

    // PEIXES
    for (int i = 0; i < numPeixes; i++) {
        desenharPeixe(&peixes[i]);
    }
    
    // ÁGUA
    float largura_agua = LARGURA_AQUARIO - 0.01;
    float profundidade_agua = PROFUNDIDADE_AQUARIO - 0.01; 
    glColor4f(0.1f, 0.1f, 0.8f, 0.4f);
    glBegin(GL_QUADS);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA,  profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA,  profundidade_agua/2);
        
        glVertex3f(-largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        
        glVertex3f(-largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario, -profundidade_agua/2);

        glVertex3f(-largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        
        glVertex3f(largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario, profundidade_agua/2);
    glEnd();
    
    // AQUÁRIO
    glColor4f(0.6f, 0.8f, 1.0f, 0.3f);
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);

        // Trás
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);

        // Esquerda
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);

        // Direita
        glVertex3f(LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario,  PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario,  PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario,  PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario,  PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO,  PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO,  PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO,  PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO,  PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
    glEnd();
}

void iniciaCena() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    desenhaCena();
    
    glutSwapBuffers();
}