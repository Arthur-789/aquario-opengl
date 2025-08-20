#include <GL/gl.h>
#include <GL/glu.h>
#include "aquario.h"

static GLfloat luzAmbiente[4]  = { 0.20f, 0.20f, 0.20f, 1.0f };
static GLfloat luzDifusa[4]    = { 0.80f, 0.80f, 0.80f, 1.0f };
static GLfloat luzEspecular[4] = { 1.00f, 1.00f, 1.00f, 1.0f };
static GLfloat posicaoLuz[4]   = { 5.0f, 6.0f, 5.0f, 1.0f };

void inicializarIluminacao(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    GLfloat ambienteGlobal[4] = { 0.05f, 0.05f, 0.05f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambienteGlobal);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void habilitarIluminacao(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void desabilitarIluminacao(void) {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void atualizarPosicaoLuz(float x, float y, float z, float w) {
    posicaoLuz[0] = x;
    posicaoLuz[1] = y;
    posicaoLuz[2] = z;
    posicaoLuz[3] = w;
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void configurarIntensidade(float ambient, float diffuse, float specular) {
    for (int i = 0; i < 3; ++i) {
        luzAmbiente[i]  = ambient * 0.25f;
        luzDifusa[i]    = diffuse;
        luzEspecular[i] = specular;
    }
    glLightfv(GL_LIGHT0, GL_AMBIENT,  luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
}

void configurarBrilhoMaterial(float shininess) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void usarTexturaModulate(int usar) {
    if (usar) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    else     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}