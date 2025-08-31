#include <GL/glut.h>
#include "aquario.h"

void desenhaCeu() {
    desabilitarIluminacao();

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

    habilitarIluminacao();
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
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa,  profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa,  profundidade_mesa/2);
        
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_mesa/2, topo_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(largura_mesa/2, topo_mesa, -profundidade_mesa/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(largura_mesa/2, topo_mesa - espessura_mesa, -profundidade_mesa/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(largura_mesa/2, topo_mesa - espessura_mesa, profundidade_mesa/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(largura_mesa/2, topo_mesa, profundidade_mesa/2);

        glNormal3f(0.0f, -1.0f, 0.0f);
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
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);

        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-largura_areia/2, topo_areia,  profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( largura_areia/2, topo_areia, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( largura_areia/2, topo_areia,  profundidade_areia/2);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( largura_areia/2, fundo_aquario, -profundidade_areia/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( largura_areia/2, fundo_aquario,  profundidade_areia/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-largura_areia/2, fundo_aquario,  profundidade_areia/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // ABACAXI (CASA DO BOB ESPONJA)
    float x_abacaxi = - (LARGURA_AQUARIO/2 * 0.01f);
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
        glTranslatef(x_abacaxi, base_abacaxi + 0.55f, z_abacaxi);
        glRotatef(i * (360.0f/numFolhas), 0.0f, 1.0f, 0.0f);
        glRotatef(-25.0f + (i%3)*8, 1.0f, 0.0f, 0.0f);

        GLUquadric* leaf = gluNewQuadric();
        gluQuadricTexture(leaf, GL_FALSE);
        gluQuadricNormals(leaf, GLU_SMOOTH);
        gluCylinder(leaf, 0.08f, 0.001f, 0.5f, 8, 1);
        gluDeleteQuadric(leaf);
        glPopMatrix();
    }

    // PEDRA (CASA DO PATRICK)
    float x_pedra = - (LARGURA_AQUARIO/2 * 0.6f);
    float z_pedra = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_pedra = fundo_aquario;

    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
    glTranslatef(x_pedra, base_pedra, z_pedra);

    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.4f, 0.4f, 0.6f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPedra);

    GLUquadric* pedra = gluNewQuadric();
    gluQuadricTexture(pedra, GL_TRUE);
    gluQuadricNormals(pedra, GLU_SMOOTH);
    gluSphere(pedra, 1.0, 32, 32);
    gluDeleteQuadric(pedra);

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Detalhe superior
      
        // Cilindro vertical
    glPushMatrix();
    float topo_pedra = base_pedra + (1.0f * 0.6f);
    glTranslatef(x_pedra, topo_pedra , z_pedra);

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaMadeira);

    GLUquadric* cilindro_vertical = gluNewQuadric();
    gluQuadricTexture(cilindro_vertical, GL_TRUE);
    gluQuadricNormals(cilindro_vertical, GLU_SMOOTH);
    gluCylinder(cilindro_vertical, 0.01f, 0.008f, 0.1f, 16, 4); 

    gluDeleteQuadric(cilindro_vertical);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

        // Cilindro horizontal
    glPushMatrix();
    float topo_cilindro = topo_pedra + 0.1f;
    glTranslatef(x_pedra - 0.1f, topo_cilindro, z_pedra);

    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaMadeira);

    GLUquadric* cilindro_horizontal = gluNewQuadric();
    gluQuadricTexture(cilindro_horizontal, GL_TRUE);
    gluQuadricNormals(cilindro_horizontal, GLU_FLAT);
    gluCylinder(cilindro_horizontal, 0.01f, 0.01f, 0.2f, 16, 4);

    gluDeleteQuadric(cilindro_horizontal);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

        // Cilindros cruzando o horizontal
    float x_cilindro_cruzado;
    float z_cilindro_cruzado = z_pedra - 0.045f;
    
    for(int i = 0; i < 2; i++){
        glPushMatrix();

        x_cilindro_cruzado = x_pedra + (0.07f - 0.03*i);
        glTranslatef(x_cilindro_cruzado, topo_cilindro, z_cilindro_cruzado);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaMadeira);

        GLUquadric* cilindro_cruzado = gluNewQuadric();
        gluQuadricTexture(cilindro_cruzado, GL_TRUE);
        gluQuadricNormals(cilindro_cruzado, GLU_FLAT);
        gluCylinder(cilindro_cruzado, 0.007f, 0.007f, 0.09f, 16, 4);

        gluDeleteQuadric(cilindro_cruzado);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

        // Setas
    float x_cilindro_seta = x_pedra - 0.1f;
    float z_cilindro_seta;

    for(int i = 0; i < 2; i++){
        glPushMatrix();

        z_cilindro_seta = z_pedra;
        glTranslatef(x_cilindro_seta, topo_cilindro, z_cilindro_seta);
        glRotatef(135.0f - 90*i, 0.0f, 1.0f, 0.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaMadeira);

        GLUquadric* cilindro_seta = gluNewQuadric();
        gluQuadricTexture(cilindro_seta, GL_TRUE);
        gluQuadricNormals(cilindro_seta, GLU_FLAT);
        gluCylinder(cilindro_seta, 0.007f, 0.007f, 0.09f, 16, 4);

        gluDeleteQuadric(cilindro_seta);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    // PEDRA (CASA DO LULA MOLUSCO)

    float x_moai = 2 * x_abacaxi - x_pedra;
    float z_moai = - (PROFUNDIDADE_AQUARIO/2 * 0.7f);
    float base_moai = fundo_aquario;

    glPushMatrix();

    glTranslatef(x_moai, base_moai, z_moai);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.4f, 0.4f, 0.6f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaMoaiPedra);

    GLUquadric* cilindro_moai = gluNewQuadric();
    gluQuadricTexture(cilindro_moai, GL_TRUE);
    gluQuadricNormals(cilindro_moai, GLU_SMOOTH);

    gluCylinder(cilindro_moai, 0.8f, 0.6f, 1.6f, 16, 4);

    glBindTexture(GL_TEXTURE_2D, texturaMoaiTopo);
    glTranslatef(0.0f, 0.0f, 1.6f);
    gluDisk(cilindro_moai, 0, 0.6f, 16, 1);

    glTranslatef(0.0f, 0.0f, -1.6f);

    // Orelhas
    float largura_orelha = 0.15f;
    float altura_orelha = 0.6f;
    float profundidade_orelha = 0.5f;
    float pos_y_base = 0.5f;

    for(int i = 0; i < 2; i++) {
        glPushMatrix();
        
        float pos_x = (i == 0) ? 0.7f : -0.7f;
        glTranslatef(pos_x, 0.0f, 1.0f);
        glRotatef(93.0f, 1.0f, 0.0f, 0.0f);

        glScalef(largura_orelha, altura_orelha, profundidade_orelha);
        glutSolidCube(1.0f);
        
        glPopMatrix();
    }

    // Nariz
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(largura_orelha, altura_orelha, profundidade_orelha);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Sobrancelhas
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 1.0f);
    glTranslatef(0.0f, 0.0f, altura_orelha/2);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(altura_orelha + 0.3f, largura_orelha, profundidade_orelha);
    glutSolidCube(1.0f);
    glPopMatrix();

    gluDeleteQuadric(cilindro_moai);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // PEIXES
    for (int i = 0; i < numPeixes; i++) {
        desenharPeixe(&peixes[i]);
    }
    
    // ÁGUA
    float largura_agua = LARGURA_AQUARIO - 0.01;
    float profundidade_agua = PROFUNDIDADE_AQUARIO - 0.01; 
    glColor4f(0.1f, 0.1f, 0.8f, 0.4f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA,  profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA,  profundidade_agua/2);
        
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f( largura_agua/2, fundo_aquario, -profundidade_agua/2);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(-largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(largura_agua/2, fundo_aquario, -profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario + ALTURA_AGUA, -profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario + ALTURA_AGUA, profundidade_agua/2);
        glVertex3f(largura_agua/2, fundo_aquario, profundidade_agua/2);
    glEnd();
    
    // VIDRO
    glColor4f(0.6f, 0.8f, 1.0f, 0.3f);
    glBegin(GL_QUADS);
        // Frente
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);

        // Trás
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f( LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);

        // Esquerda
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, -PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, PROFUNDIDADE_AQUARIO/2);
        glVertex3f(-LARGURA_AQUARIO/2, fundo_aquario + ALTURA_AQUARIO, -PROFUNDIDADE_AQUARIO/2);

        // Direita
        glNormal3f(1.0f, 0.0f, 0.0f);
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