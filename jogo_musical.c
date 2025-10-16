#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"
#include<math.h>
#include<stdbool.h>

#define SH 1080
#define SW 1920
#define MAX_MUSICAS 1
#define MAX_TEXTO 25


bool botao(Rectangle retangulo, char *mensagem, Color cor_botao, Color cor_texto, Color encosta);
int inicial(Texture2D background, Sound fx);
int regras(Texture2D,Sound fx);
int ajustes(Texture2D background,Sound fx,float *altura_som);
int iniciar(Sound beep, float altura_som);
int jogo(Texture2D game, char **nome_musicas, Sound *sons, char *resposta, int tamanho);
int errou(Texture2D errada, Sound erou, int *pontuacao, float altura_som, bool marcador_ponto);
int correto(Texture2D joia, Sound acertou, int *pontuacao, float altura_som, bool marcador_ponto);

int reset_int(int variavel, int valor_certo);
float reset_float(float variavel, float valor_certo);

int SO=0;


int main() {
    

    #ifdef _WIN32
         SO=1;

    #else 
        SO=2;
    #endif

    InitWindow(SW, SH, "MUSICAL");

    SetTargetFPS(60);

    //inicializa o sitema de áudio
    InitAudioDevice();

    ///Carregandoo imagens
    Texture2D joia = LoadTexture("imagens/joia.jpg");
    Texture2D background = LoadTexture("imagens/fundo.png");
    Texture2D game = LoadTexture("imagens/fundo_game.png");
    Texture2D duvida = LoadTexture("imagens/duvida.png");
    Texture2D errada = LoadTexture("imagens/errou.jpg");
    ///

    ///Carregando sons
    Sound fx = LoadSound("sons/funk_faustao.mp3");
    Sound beep = LoadSound("sons/beep.mp3");
    Sound erou = LoadSound("sons/faustao-errou.mp3");
    Sound acertou = LoadSound("sons/faustao-acertou.mp3");
    Sound miseravi = LoadSound("sons/miseravi-acertou.mp3");
    Sound caneta_azul = LoadSound("sons/caneta_azul.mp3");
    ///

    //variável que define a tela que se encontra o jogo
    int def_tela=0, pontuacao=0;
    float altura_som=0.5;
    bool marcador=true;
    char *nome_musicas[MAX_TEXTO]={"CANETA AZUL"};
    Sound sons[MAX_MUSICAS]={caneta_azul};

    char resposta[MAX_TEXTO+1]="";
    int tamanho_palavra=0;


        

    //Altura do som
    SetSoundVolume(fx, altura_som);


    while(!WindowShouldClose()) 
    {
        BeginDrawing();

        ClearBackground(GRAY);


        switch (def_tela) 
        {
        case 1:
            def_tela=regras(background, fx);
            break;
        
        case 2:
            def_tela=ajustes(background, fx, &altura_som);
            break;

        
        case 3:
            def_tela=iniciar(beep, altura_som);
            break;

            
        case 4:
            def_tela=jogo(game, nome_musicas, sons, resposta, tamanho_palavra);
            break;

            
        case 5:
            def_tela=errou(errada, erou, &pontuacao, altura_som, marcador=true);
            break;

            
        case 6:
            def_tela=correto(joia, acertou, &pontuacao, altura_som, marcador=true);
            break;

            /*
        case 7:
            def_tela=resultados();
            break;*/
        
        default:
            def_tela=inicial(background, fx);
            break;
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
                
                if(IsSoundPlaying(fx)) {

                    StopSound(fx);
                }
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

    
    int ajustes(Texture2D background, Sound fx, float *altura_som) {

        int tela=2;

        if(!IsSoundPlaying(fx)) {
                PlaySound(fx);
            }
        SetSoundVolume(fx, *altura_som);


         DrawTexturePro(
                background,
                 (Rectangle){ 0, 0, (float)background.width, (float)background.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

            char volume[8];

            for(int i=0;i<=3;i++) {
                volume[i]='\0';
            }
            
            sprintf(volume, "%.2f", 10*(*altura_som));
            int tamanho_texto=MeasureText("Volume:", 100);
            int botao_wh=100;
            int botao_y=(SH/2) - (botao_wh/2);

            DrawText("Volume:", SW/2 - tamanho_texto/2, SH/7, 100, GOLD);
        

            if(botao((Rectangle){SW/3 - botao_wh/2, botao_y, botao_wh, botao_wh},"-",BLUE, GOLD, PINK) && *altura_som>0) {
                *altura_som-=0.1;
            }

            if(botao((Rectangle){SW/2 - (botao_wh+200)/2, botao_y, botao_wh+200, botao_wh},volume,BLUE, GOLD, BLUE)) {
                //kkkkk
            }

            if(botao((Rectangle){2*SW/3 - botao_wh/2, botao_y, botao_wh, botao_wh},"+",BLUE, GOLD, PINK) && *altura_som<=1) {
                *altura_som+=0.1;
            }

            if(botao((Rectangle){(SW/6 - 300/2),5*SH/6,300, 100},"Voltar", BLUE, GOLD, PINK )) {
                tela=0;
            }

            return tela;
    }

    
    int iniciar(Sound beep, float altura_som) {

        ClearBackground(BLACK);

        SetSoundVolume(beep, altura_som);

        int tamanho=0, tela=3, tempo_int=0;
        static int ultimo_som=5;
        char texto_tempo[8];
        static float tempo=4;

        texto_tempo[0]='\0';

        tempo-=GetFrameTime();

        tempo_int=(int)ceilf(tempo);


        if(tempo_int < ultimo_som && tempo_int > 0){
            
            PlaySound(beep);
            ultimo_som = tempo_int;
        }

        sprintf(texto_tempo, "%d", tempo_int);
        tamanho=MeasureText(texto_tempo, 400);

        DrawText(texto_tempo, (SW/2 - tamanho/2),SH/2 - 200, 400, WHITE);

        if(tempo<=0) {

            ultimo_som=reset_int(ultimo_som, 5);
            tempo=reset_float(tempo, 4);

            tela=4;
        }

        return tela;
    }

    
    int jogo(Texture2D game, char **nome_musicas, Sound *sons, char *resposta, int tamanho) {

        DrawTexturePro(
                game,
                 (Rectangle){ 0, 0, (float)game.width, (float)game.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

        int tela=4, tempo_int=0, tamanho_texto=0;
        static float tempo=10;
        char tempo_texto[8];

        tempo-=GetFrameTime();

        tempo_texto[0]='\0';

        tempo_int=(int)ceilf(tempo);

        sprintf(tempo_texto, "%d", tempo_int);

        tamanho_texto=MeasureText("Tempo: ", 100);

        DrawText("Tempo: ", SW/9 - tamanho_texto/2, SH/12, 100, PINK );
        DrawText(tempo_texto, (SW/9 - tamanho_texto/2) + 400, SH/12, 100, PINK );


        int key= GetCharPressed();


        while(key>0) {
            if(tamanho<MAX_TEXTO) {

                resposta[tamanho]=(char)key;
                tamanho++;
                resposta[tamanho]='\0';
            }

            key= GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && tamanho > 0) {
            tamanho--;
            resposta[tamanho] = '\0';
        }

        DrawText(resposta, 2*SW/5 ,3*SH/4,100, WHITE);

        
        if(tempo<=0) {

            tempo=reset_float(tempo, 30);

            tela=5;
        }
        
        return tela;
    }

    
    int errou(Texture2D errada, Sound erou, int *pontuacao, float altura_som, bool marcador_ponto) {

        DrawTexturePro(
                errada,
                 (Rectangle){ 0, 0, (float)errada.width, (float)errada.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

        SetSoundVolume(erou, altura_som);
        
        
        int tela=5, tempo_int=0, tamanho_texto=0, pontos=*pontuacao;
        static float tempo=4;
        char tempo_texto[8], pontuacao_texto[8];
        static int pontuacao_atualizada=1;

        if(pontuacao_atualizada==1) {

            *pontuacao-=10;
            pontuacao_atualizada=0;
            PlaySound(erou);
        }

        tempo-=GetFrameTime();

        pontuacao_texto[0]='\0';
        tempo_texto[0]='\0';

        tempo_int=(int)ceilf(tempo);

        sprintf(tempo_texto, "%d", tempo_int);
        sprintf(pontuacao_texto, "%d", *pontuacao);

        tamanho_texto=MeasureText("Pontuação: ", 50);

        if(*pontuacao>0) {
            DrawText("Pontuação: ", SW/9 - tamanho_texto/2, SH/12, 100, GREEN );
            DrawText(pontuacao_texto, (SW/9 - tamanho_texto/2) + 600, SH/12, 100, GREEN );
        } else {
            DrawText("Pontuação: ", SW/9 - tamanho_texto/2, SH/12, 100, RED );
            DrawText(pontuacao_texto, (SW/9 - tamanho_texto/2) + 600, SH/12, 100, RED );
        }
        
        if(tempo<=0) {

            tempo=reset_float(tempo, 4.00);
            pontuacao_atualizada=reset_int(pontuacao_atualizada, 1);
            tela=3;
        }
        
        return tela;
    }

    
    int correto(Texture2D joia, Sound acertou, int *pontuacao, float altura_som, bool marcador_ponto) {

        DrawTexturePro(
                joia,
                 (Rectangle){ 0, 0, (float)joia.width, (float)joia.height }, // Parte da imagem que será usada
                 (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, // Área da tela onde será desenhado
                 (Vector2){ 0, 0 }, // Origem
                 0.0f, // Rotação
                 WHITE // Cor (sem alteração)
            );

        SetSoundVolume(acertou, altura_som);
        
        int tela=6, tempo_int=0, tamanho_texto=0, pontos=*pontuacao;
        static float tempo=4;
        char tempo_texto[8], pontuacao_texto[8];
        static int pontuacao_atualizada=1;

        if(pontuacao_atualizada==1) {

            *pontuacao+=10;
            pontuacao_atualizada=0;
            PlaySound(acertou);
        }

        tempo-=GetFrameTime();

        pontuacao_texto[0]='\0';
        tempo_texto[0]='\0';

        tempo_int=(int)ceilf(tempo);

        sprintf(tempo_texto, "%d", tempo_int);
        sprintf(pontuacao_texto, "%d", *pontuacao);

        tamanho_texto=MeasureText("Pontuação: ", 50);

        if(*pontuacao>0) {
            DrawText("Pontuação: ", SW/9 - tamanho_texto/2, SH/12, 100, GREEN );
            DrawText(pontuacao_texto, (SW/9 - tamanho_texto/2) + 600, SH/12, 100, GREEN );
        } else {
            DrawText("Pontuação: ", SW/9 - tamanho_texto/2, SH/12, 100, RED );
            DrawText(pontuacao_texto, (SW/9 - tamanho_texto/2) + 600, SH/12, 100, RED );
        }
        
        if(tempo<=0) {

            tempo=reset_float(tempo, 4.00);
            pontuacao_atualizada=reset_int(pontuacao_atualizada, 1);
            tela=3;
        }

        return tela;
    }

    /*
    int resultados() {

    }*/

    int reset_int(int variavel, int valor_certo) {

        if(variavel!= valor_certo) {

            variavel=valor_certo;
        }

        return variavel;
    }

    float reset_float(float variavel, float valor_certo) {

        if(variavel!= valor_certo) {

            variavel=valor_certo;
        }

        return variavel;
    }