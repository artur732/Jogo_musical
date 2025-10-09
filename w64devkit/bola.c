#include "raylib.h"
#include<stdio.h>
#include<stdlib.h>

#define ALTURATELA 1080
#define LARGURATELA 1920

int main() {

    //Iniciar janela gráfica
    InitWindow(LARGURATELA, ALTURATELA,"BALL");

    //setar o FPS
    SetTargetFPS(60);


    int altura_ret=50, largura_ret=100, ret_x=1700, ret_y=(ALTURATELA/2);
    int bola_x=(LARGURATELA/2), bola_y=(ALTURATELA/2);
    int point=0;
    char placar[100];
    int toque=0;

    //Repetição daquilo que deve ficar se repetindo
    while (!WindowShouldClose())
    {
        
        BeginDrawing();

            ClearBackground(GRAY);

            DrawRectangle(ret_x,ret_y,largura_ret,altura_ret,BLACK);

            DrawCircle(bola_x,bola_y,20,RED);

            sprintf(placar,"PLacar: %d", point);

            DrawText(placar,100,100,32,PINK);

            /*IsKeyPressed -> caso seja uma vez pressionado*/
            //fixamente pressionado
            if(IsKeyDown(KEY_RIGHT)) {

                bola_x+=4;
            }

            if(IsKeyDown(KEY_LEFT)) {

                bola_x-=4;
            }

            if(IsKeyDown(KEY_UP)) {

                bola_y-=4;
            }

            if(IsKeyDown(KEY_DOWN)) {

                bola_y+=4;
            }

            if(CheckCollisionCircleRec((Vector2){bola_x,bola_y},20,(Rectangle){ret_x,ret_y,largura_ret,altura_ret}) && toque==0) {

                point++;
                toque=1;
            } 

            if(!(CheckCollisionCircleRec((Vector2){bola_x,bola_y},20,(Rectangle){ret_x,ret_y,largura_ret,altura_ret})) && toque==1) {

                toque=0;
            } 



        EndDrawing();

    }
    



    //Fechar o programa, a janela
    CloseWindow();
}