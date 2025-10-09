#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"
#include<math.h>

#define SH 1080
#define SW 1920

bool botao(Rectangle retangulo, char *mensagem, Color cor_botao, Color cor_texto, Color encosta);
int inicial(Texture2D background, Sound fx);
int regras(Texture2D,Sound fx);




int main() {

    InitWindow(SW, SH, "MUSICAL");

    SetTargetFPS(60);

    //inicializa o sitema de áudio
    InitAudioDevice();

    ///Carregandoo imagens
    Texture2D joia = LoadTexture("imagens/joia.jpg");
    Texture2D background = LoadTexture("imagens/fundo.png");
    ///

    ///Carregando sons
    Sound fx = LoadSound("sons/game.mp3");
    ///

    //Tocando o som
        PlaySound(fx);

    //variável que define a tela que se encontra o jogo
    int def_tela=0;


    while(!WindowShouldClose()) 
    {
        BeginDrawing();

        ClearBackground(GRAY);


        switch (def_tela) 
        {
        case 1:
            def_tela=regras(background, fx);
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

    //função que cria um botão com um texto
    bool botao(Rectangle retangulo, char *mensagem, Color cor_botao, Color cor_texto, Color encosta ) {

        Rectangle formato={retangulo.x, retangulo.y, retangulo.width, retangulo.height};

        Vector2 mouse = GetMousePosition();

        DrawRectangle(formato.x, formato.y, formato.width, formato.height, cor_botao);

        int largura_texto=MeasureText(mensagem, 0.8*retangulo.height);
        int posicao_x=retangulo.x + (retangulo.width-largura_texto)/2;
        int posicao_y=retangulo.y + (retangulo.height-retangulo.height)/2;

        DrawText(mensagem, posicao_x , posicao_y, 0.8*retangulo.height, cor_texto);

        bool clique = false;

        if(CheckCollisionPointRec(mouse, retangulo)) {

            
            DrawRectangle(formato.x, formato.y, formato.width, formato.height, encosta);
            DrawText(mensagem, posicao_x , posicao_y, 0.8*retangulo.height, cor_texto);

            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

                clique=true;
            }
        }

        return clique;
    }

    //aqui está a tela inicial do jogo
    int inicial(Texture2D background, Sound fx) {

            int tela=0, largura_texto=0;

            DrawTexturePro(
                background,
                 (Rectangle){ 0, 0, (float)background.width, (float)background.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

            largura_texto=MeasureText("Adivinhe a música!", 100);


            //Verificando se o som acabou para tocá-lo novamente
            if(!IsSoundPlaying(fx)) {
                PlaySound(fx);
            }

            DrawText("Adivinhe a música!", (SW-largura_texto)/2, (250 + 50*(sin(GetTime()*2.5))), 100, GOLD );

            int botao_y=(5*SH)/6;
            int botao_w=300;
            int botao_h=botao_w/3;

            if(botao((Rectangle){(SW/6 - botao_w/2), botao_y, botao_w, botao_h},"Regras", BLUE, GOLD, PINK )) {
                tela=1;
            }

            if(botao((Rectangle){(SW/2-botao_w/2), botao_y, botao_w, botao_h}, "Jogar", BLUE, GOLD, PINK)) {
                tela=3;
            }

            if(botao((Rectangle){(5*SW/6-botao_w/2), botao_y, botao_w, botao_h}, "Ajustes", BLUE, GOLD, PINK)) {
                 tela=2;
            }

            return tela;
        }

    

    int regras(Texture2D background, Sound fx) {
        int tela=1, largura_texto_1=MeasureText("REGRAS",50);
        int largura_textos=MeasureText("Uma música irá tocar, você deve ouvir!", 50);


        DrawTexturePro(
                background,
                 (Rectangle){ 0, 0, (float)background.width, (float)background.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

        if(!IsSoundPlaying(fx)) {
            PlaySound(fx);
        }

        DrawText("REGRAS", (SW-largura_texto_1)/2, SH/7, 50, GOLD);
        DrawText("Uma música irá tocar, você deve ouvir!", (SW-largura_textos)/2, 2*SH/7, 50, GOLD);
        DrawText("Se souber, aperte ENTER antes que o tempo acabe", (SW-largura_textos)/2, 3*SH/7, 50, GOLD);
        DrawText("IF acertar: ganha 10 pontos. ELSE: perde 10", (SW-largura_textos)/2, 4*SH/7, 50, GOLD);
        DrawText("No final, receba sua classificação!", (SW-largura_textos)/2, 5*SH/7, 50, GOLD);
        DrawText("  Boa sorte! Ass: Artur Silveira :D", (SW-largura_textos)/2, 6*SH/7, 50, GOLD);

        int botao_y=(5*SH)/6;
        int botao_w=300;
        int botao_h=botao_w/3;

        if(botao((Rectangle){(SW/6 - botao_w/2), botao_y, botao_w, botao_h},"Voltar", BLUE, GOLD, PINK )) {
            tela=0;
        }


        return tela;
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