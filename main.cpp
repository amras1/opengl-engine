#include "GLIncludes.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Image.h"
#include "Camera.h"
#include "Skybox.h"
#include "ParticleSystem.h"
#include "LSystem.h"
#include "Model.h"
#include "Logger.h"
#include "Texture.h"
#include "Utils.h"

Texture grass, water, snow, fireworks;
Camera cam, oldcam;
Skybox box;
Fountain fountain;
Plant plant;
//SimplePlant simple_plant;
Point3f fountain_pos(0.0, 0.0, -5.0);
const int NUM_PLANTS = 4;
Point3f plant_pos[NUM_PLANTS];
bool cam_saved = false;
const int WIDTH = 700, HEIGHT = 550;
float zoom = 1.0;
//Model model;

void cleanUp()
{
    delete loggerPtr;
    delete textureManagerPtr;
}

Point3f random(Point3f p)
{
    return Point3f(randInRange(p.getX()), randInRange(p.getY()), randInRange(p.getZ()));
}

void setPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 * zoom, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    new Logger;
    new TextureManager;
    srand(time(0));
    plant.parse();
    //simple_plant.parse();
    cam.advance(-10.0);
    setPerspective();
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    Image front, back, right, left, up, down;
    ERR_CODE ret;
#define CHECK_RET_NAME(x, name) if ((ret = x.load(name ".tga")) != NONE) { logger.logln(LOG_USER, "Error while loading " name ".tga: " + errString(ret)); exit(0); }
#define CHECK_RET(x) CHECK_RET_NAME(x, #x)
    CHECK_RET(front);
    CHECK_RET(back);
    CHECK_RET(right);
    CHECK_RET(left);
    CHECK_RET(up);
    CHECK_RET(down);

    Image img_grass, img_water, img_snow, img_fireworks;
    CHECK_RET_NAME(img_grass, "grass");
    CHECK_RET_NAME(img_water, "water");
    CHECK_RET_NAME(img_snow, "snow");
    CHECK_RET_NAME(img_fireworks, "fireworks");
    grass = textureManager.load(img_grass);
    water = textureManager.load(img_water);
    snow = textureManager.load(img_snow);
    fireworks = textureManager.load(img_fireworks);

    box.init(front, left, back, right, up, down);
    atexit(cleanUp);

    Point3f bounds(5.0, 0.0, 5.0);

    for (int i = 0; i < NUM_PLANTS; ++i)
        plant_pos[i] = random(bounds);

    //model.load("untitled.model");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.orientBefore();
    box.render(Vector3f(5.0, 5.0, 5.0));
    glLoadIdentity();
    cam.orient();

    textureManager.bind(grass);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1000.0, -1.0, -1000.0);
    glTexCoord2f(0.0, 200.0);
    glVertex3f(-1000.0, -1.0, 1000.0);
    glTexCoord2f(200.0, 200.0);
    glVertex3f(1000.0, -1.0, 1000.0);
    glTexCoord2f(200.0, 0.0);
    glVertex3f(1000.0, -1.0, -1000.0);
    glEnd();

    glTranslatef(0.0, 0.0, -10.0);
    glPushMatrix();
    glTranslatef(fountain_pos.getX(), fountain_pos.getY(), fountain_pos.getZ());
    textureManager.bind(water);
    fountain.render();
    glPopMatrix();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    for (int i = 0; i < NUM_PLANTS; ++i)
    {
        glPushMatrix();
        glTranslatef(plant_pos[i].getX(), plant_pos[i].getY() - 1, plant_pos[i].getZ());
        plant.render();
        glPopMatrix();
    }

    //model.render();
    glPopAttrib();
    glFlush();
}

#include <cstdlib>

void keys(unsigned char key, int x, int y)
{
    bool show = true, p = false;

    switch (key)
    {
    case 'a':
        cam.rotateY(-1.5);
        break;
    case 'd':
        cam.rotateY(1.5);
        break;
    case 'w':
        cam.rotateX(1.5);
        break;
    case 's':
        cam.rotateX(-1.5);
        break;
    case 't':
        if (zoom > 0.4)
            zoom -= 0.02;
        p = true;
        break;
    case 'g':
        if (zoom < 1.6)
            zoom += 0.02;
        p = true;
        break;
    case 27:
        exit(0);
        break;
    default:
        show = false;
    }

    if (p)
        setPerspective();

    if (show)
        display();
}

void menu_handler(int id)
{
    bool show = true;

    switch (id)
    {
    case 1:
        fountain.setColor(RED);
        break;
    case 2:
        fountain.setColor(GREEN);
        break;
    case 3:
        fountain.setColor(FOUNTAIN_COLOR);
        break;
    case 4:
        fountain.setGravity(fountain.getGravity() + 0.005);
        break;
    case 5:
        fountain.setGravity(fountain.getGravity() - 0.005);
        break;
    case 6:
        fountain.setParticleOffset(fountain.getParticleOffset() + 0.008);
        break;
    case 7:
        fountain.setParticleOffset(fountain.getParticleOffset() - 0.008);
        break;
    case 8:
        fountain.setMaxLifetime(fountain.getMaxLifetime() + 15);
        break;
    case 9:
        fountain.setMaxLifetime(fountain.getMaxLifetime() - 15);
        break;
    case 10:
        fountain.setXVar(fountain.getXVar() + 0.015);
        break;
    case 11:
        fountain.setXVar(fountain.getXVar() - 0.015);
        break;
    case 12:
        fountain.setYMax(fountain.getYMax() + 0.05);
        break;
    case 13:
        fountain.setYMax(fountain.getYMax() - 0.05);
        break;
    case 14:
        fountain.setYMin(fountain.getYMin() + 0.05);
        break;
    case 15:
        fountain.setYMin(fountain.getYMin() - 0.05);
        break;
    case 16:
        fountain.setZVar(fountain.getZVar() + 0.015);
        break;
    case 17:
        fountain.setZVar(fountain.getZVar() - 0.015);
        break;
    default:
        show = false;
    }

    if (show)
        display();
}

void update(int)
{
    fountain.update();
    display();
    glutTimerFunc(30, update, 0);
}

void arrows(int key, int, int)
{
    bool show = true;

    switch (key)
    {
    case GLUT_KEY_UP:
        cam.advance(0.5);
        break;
    case GLUT_KEY_DOWN:
        cam.advance(-0.5);
        break;
    case 27:
        exit(0);
    default:
        show = false;
    }

    if (show)
        display();
}

int main(int argc, char **argv)
{
    std::string path = argv[0];
    std::replace(path.begin(), path.end(), '\\', '/');
    set_path(getpath(path));

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Demo");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutTimerFunc(30, update, 0);
    glutSpecialFunc(arrows);

    int color_menu = glutCreateMenu(menu_handler);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    int fountain_size = glutCreateMenu(menu_handler);
    glutAddMenuEntry("Increase fountain width", 10);
    glutAddMenuEntry("Decrease fountain width", 11);
    glutAddMenuEntry("Increase particle max height", 12);
    glutAddMenuEntry("Decrease particle max height", 13);
    glutAddMenuEntry("Increase particle minimum height", 14);
    glutAddMenuEntry("Decrease particle minimum height", 15);
    glutAddMenuEntry("Increase fountain depth (z-axis)", 16);
    glutAddMenuEntry("Decrease fountain depth (z-axis)", 17);

    int attrib_menu = glutCreateMenu(menu_handler);
    glutAddMenuEntry("Increase gravity", 4);
    glutAddMenuEntry("Decrease gravity", 5);
    glutAddMenuEntry("Increase particle size", 6);
    glutAddMenuEntry("Decrease particle size", 7);
    glutAddMenuEntry("Increase particle max lifetime", 8);
    glutAddMenuEntry("Decrease particle max lifetime", 9);
    glutAddSubMenu("Change fountain size", fountain_size);

    glutCreateMenu(menu_handler);
    glutAddSubMenu("Change fountain color", color_menu);
    glutAddSubMenu("Change fountain attributes", attrib_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
