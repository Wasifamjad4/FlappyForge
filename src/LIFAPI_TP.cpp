// apps/LIFAPI/LIFAPI_TP.cpp

/*D'abord écrit le draw et le main
Puis ajouter les chose suivants :
                                -Update: qui affiche juste la particule et les obstacle en continue.
                                -Collisions: pour qu'il reinitialise lorsqu'on touche l'obstacle ou le bord de fenetre(0 ou DIMW).
                                -Main: pour verifié que les collisions fonctionne bien.
                                -Ensuite ajouter la vitesse dans le world et initialiser dans le init.
                                -la fonction Keypressed dans le Update pour qu'il monte et declarer un autre variable dt pour qu'il fasse une parabole (et pas juste monté).
                                -ecrit le main pour tester tous sa.
Commencer a ajouter des images.*/

#include<Grapic.h>

using namespace grapic;

const int g = 9.81;
const int NB_OBS = 4;
const int DIMW = 500;

struct vec2
{
    float x;
    float y;
};

vec2 make_vec2(float x, float y)
{
    vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

vec2 operator+(vec2 a, vec2 b)
{
return make_vec2(a.x + b.x, a.y + b.y);
}

vec2 operator+(vec2 a, float k)
{
    return make_vec2(a.x + k, a.y + k);
}

vec2 operator-(vec2 a, vec2 b)
{
    return make_vec2(a.x - b.x, a.y - b.y);
}

vec2 operator-(vec2 a, float k)
{
    return make_vec2(a.x - k, a.y - k);
}

vec2 operator*(vec2 a, float lambda)
{
    return make_vec2(a.x * lambda, a.y * lambda);
}

vec2 operator*(float lambda, vec2 a)
{
    return make_vec2(a.x * lambda, a.y * lambda);
}

vec2 operator*(vec2 a, vec2 b)
{
    return make_vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

vec2 operator/(vec2 a, float lambda)
{
    return make_vec2(a.x / lambda, a.y / lambda);
}

vec2 operator/(float k, vec2 a)
{
    return make_vec2(k/a.x, k/a.y);
}

float distance(vec2 a, vec2 b)
{
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}


struct Obstacle
{
    float x;
    float trou_y;
};

struct World
{
    vec2 joueur;
    Image bird;
    Obstacle obs[NB_OBS];
    float vit_y;
    float dt;
    float last_time = 0;
    int score;
    bool game_over;
};

void init(World &w)
{
    w.joueur.x = DIMW/4;
    w.joueur.y = DIMW/2;

    w.bird = image("data/bird1.png");

    w.score = 0;
    w.vit_y = 0;
    w.dt = 0.01;
    w.game_over = false;

    for(int i = 0; i < NB_OBS; i++)
    {
        w.obs[i].x = 400 + i * 200;
        w.obs[i].trou_y = 100 + rand() % 300;
    }
}

void update(World &w)
{
    float now = elapsedTime();
    float DT = 5000*(now - w.last_time);

    w.vit_y -= 0.4*w.dt*DT;

    if(isKeyPressed(SDLK_UP))
    {
        w.vit_y += 0.9*w.dt*DT;
    }

    w.joueur.y += w.vit_y*w.dt*DT;

    for(int i = 0; i < NB_OBS; i++)
    {
        w.obs[i].x -= 0.02*DT;

        if(w.obs[i].x < DIMW/4 -40)
        {
            w.score++;

            int max_x = -100000;
            for (int j = 0; j < NB_OBS; j++)
                if (max_x < w.obs[j].x)
                   {
                       max_x = w.obs[j].x;
                   }

            w.obs[i].x = max_x + 180;
            w.obs[i].trou_y = 200 + rand() % 300;
        }

    }
    w.last_time = now;
}


void draw(World &w)
{
    /*color(255, 255, 0);
    circleFill(w.joueur.x, w.joueur.y, 10);*/

    image_draw(w.bird,w.joueur.x - 30, w.joueur.y - 30, 60, 60);

    color(0, 255, 0);

    for(int i = 0; i < NB_OBS; i++)
    {
        float x = w.obs[i].x;
        float trou = w.obs[i].trou_y;

        float taille_trou = 100;

        rectangleFill(x, 0, x + 40, trou - taille_trou/2);

        rectangleFill(x, trou + taille_trou/2, x + 40, 500);
    }

    color(0,0,0);
    print(DIMW - 60, DIMW - 40, w.score);
}

bool collision(World &w)
{
    float rayon = 10;

    for(int i = 0; i < NB_OBS; i++)
    {
        float x = w.obs[i].x;
        float trou = w.obs[i].trou_y;
        if(w.joueur.x + rayon > x && w.joueur.x - rayon < x + 40)
        {
            float taille_trou = 100;
            if(w.joueur.y - rayon < trou - taille_trou/2)
                return true;
            if(w.joueur.y + rayon > trou + taille_trou/2)
                return true;
        }
    }

    if(w.joueur.y < 0 || w.joueur.y > DIMW)
        return true;

    return false;
}

int main(int, char** )
{
    winInit("Flappy Bird", DIMW, DIMW);
    Menu m;
    srand(time(NULL));

    World w;
    init(w);

    setKeyRepeatMode(true);

    bool stop = false;

    menu_add(m, "PERDU");
    menu_add(m, "REJOUER");
    menu_add(m, "SCORE");

    while(!stop)
    {
        winClear();

        draw(w);

        if(!w.game_over) {
                update(w);
                if(collision(w)){
                    w.game_over = true;
                }
        }

        else {
        /*color(255,0,0);
        print(DIMW/2 - 40, DIMW/2, "PERDU");

        color(0,0,0);
        print(DIMW/2 - 120, DIMW/2 -20, "To Play Again : Click Space");
        if(isKeyPressed(SDLK_SPACE)){
            w.game_over = false;
            init(w);
            }*/
        menu_draw(m, DIMW/2-50, DIMW/2-40, DIMW/2+50, DIMW/2+40);

        if(menu_select(m)==1){
            w.game_over = false;
            init(w);
            menu_setSelect(m,0);
        }

        if(menu_select(m)==2){
            w.game_over = true;
            color(0,0,0);
            fontSize(20);
            print(DIMW - 60, DIMW - 40, w.score);
            menu_setSelect(m,0);
        }
        }

        stop = winDisplay();
    }

    winQuit();
    return 0;
}
