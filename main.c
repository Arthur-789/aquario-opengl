#include "aquario.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Aquario");
    
    inicializar();
    
    glutDisplayFunc(iniciaCena);
    glutReshapeFunc(redimensiona);
    glutMouseFunc(mouse);
    glutMotionFunc(movimentoMouse);
    glutKeyboardFunc(teclado);
    
    glutMainLoop();
    return 0;
}