#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"

#define SH 1080
#define SW 1920


int inicial(Texture2D background, Sound fx);
int regras();



int main() {

    InitWindow(SW, SH, "MUSICAL");

    SetTargetFPS(60);

    //inicializa o sitema de áudio
    InitAudioDevice();

    ///Carregandoo imagens
    Texture2D joia = LoadTexture("imagens/joia.jpg");
    Texture2D background = LoadTexture("imagens/fundo_tela_geral.png");
    ///

    ///Carregando sons
    Sound fx = LoadSound("sons/game.mp3");
    ///

    //Tocando o som
        PlaySound(fx);

    int def_tela=0;

    while(!WindowShouldClose()) 
    {
        BeginDrawing();

        ClearBackground(GRAY);


        switch (def_tela) 
        {
        case 1:
            def_tela=regras();
            break;
        
        /*case 2:
            def_tela=ajustes();
            break;

        case 3:
            def_tela=iniciar();
            break;

        case 4:
            def_tela=jogo();
            break;

        case 5:
            def_tela=acertou();
            break;

        case 6:
            def_tela=errou();
            break;

        case 7:
            def_tela=resultados();
            break;*/
        
        default:
            def_tela=inicial(background, fx);
            break;
        }

        // DrawTexture(joia,SW/2 - joia.width/2,SH/2 - joia.height/2,WHITE);

        //Verificando se o som acabou para tocá-lo novamente
        if(!IsSoundPlaying(fx)) {
            PlaySound(fx);
        }

        

        
        EndDrawing();

    }

    UnloadTexture(background);

    //UnloadTexture(joia);
    //descarrega o som
    UnloadSound(fx);

    //fecha o sistema de audio
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

    int inicial(Texture2D background, Sound fx) {

            int tela=0;

            DrawTexture(background, 0, 0, WHITE);


            //Verificando se o som acabou para tocá-lo novamente
            if(!IsSoundPlaying(fx)) {
                PlaySound(fx);
            }

            DrawText("Adivinhe a música!", SW/2, SH/3, 100, WHITE );


            return tela;
        }

    int regras() {

        return 0;
    }

    /*
    int ajustes() {

    }

    int iniciar() {

    }

    int jogo() {

    }

    int acertou() {

    }

    int errou() {

    }

    int resultados() {

    }*/