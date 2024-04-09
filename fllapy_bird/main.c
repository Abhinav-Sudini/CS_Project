/*******************************************************************************************
*
*   raylib [shapes] example - following eyes
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <string.h>

#include <math.h>       // Required for: atan2f()

 

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - following eyes");

Image image2 = LoadImage("resources/flappybirds.png");
    Texture2D flapy_bird_logo = LoadTextureFromImage(image2);
    UnloadImage(image2);
    Image image = LoadImage("resources/background (1)-min (3).png");
    Texture2D scarfy = LoadTexture("resources/winged-sword.png");
    Texture2D bird_ = LoadTexture("resources/bird.png");
    Texture2D back_ground = LoadTextureFromImage(image);
    UnloadImage(image);
    Texture2D ground = LoadTexture("resources/ground.png");
    Texture2D pipe = LoadTexture("resources/pipe.png");
    Texture2D restart = LoadTexture("resources/restart.png");
    
     



    Vector2 player_position =(Vector2){155,350};
    float player_velocity = 0;
    int velocity_factor=1;
    float pixel_count=0;
    int player_alive=1;
    int score=0;



    float pipe_height[6][2]={0};
    int temp;
    for(int ii=0;ii<6;ii++){
        temp = GetRandomValue(220,500);
        pipe_height[ii][0]=temp;
        pipe_height[ii][1]=600+ii*250;
    }
    




    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    char window_state = 'h';
    Vector2 mouse_position={0,0};
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            

        if(window_state=='h'){

            mouse_position = GetMousePosition();

            DrawRectangleGradientV(0, 0, screenWidth, screenHeight,(Color){4, 197, 204,100} ,BLACK);
           
            DrawText("GAME HUB", 280, 85, 80, BLACK);

            DrawTexturePro(flapy_bird_logo,(Rectangle){05,05,95,95},(Rectangle){130,260,100,100},(Vector2){00,00},0.0,WHITE);
              DrawRectangleRoundedLines((Rectangle){130,260,100,100},0.1,0,5,BLACK);
                if(CheckCollisionPointRec(mouse_position,(Rectangle){130,260,100,100})){
                    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        window_state = 'f';
                    }
                }
            DrawTexturePro(scarfy,(Rectangle){00,00,512,512},(Rectangle){330,260,100,100},(Vector2){00,00},0.0,WHITE);
            DrawTexturePro(scarfy,(Rectangle){00,00,512,512},(Rectangle){530,260,100,100},(Vector2){00,00},0.0,WHITE);
            DrawTexturePro(scarfy,(Rectangle){00,00,512,512},(Rectangle){730,260,100,100},(Vector2){00,00},0.0,WHITE);
             

        }

        if(window_state=='f'){
        
          

            player_velocity-=(0.2)*(float)velocity_factor;
            if(player_position.y>600-104&&player_velocity<0){
                player_velocity=0;
            }
            
            player_position.y-=player_velocity;

            

            
         

            DrawTexturePro(back_ground,(Rectangle){00,00,514,600},(Rectangle){0,0,514,600},(Vector2){00,00},0.0,WHITE);
            DrawTexturePro(back_ground,(Rectangle){00,00,514,600},(Rectangle){510,0,514,600},(Vector2){00,00},0.0,WHITE);
           for(int i=0;i<6;i++){
                    DrawTexturePro(pipe,(Rectangle){00,00,138,793},(Rectangle){pipe_height[i][1],pipe_height[i][0],138/2,793/2},(Vector2){00,00},0.0,WHITE);
                    DrawTexturePro(pipe,(Rectangle){00,00,138,793},(Rectangle){pipe_height[i][1],pipe_height[i][0]-175,138/2,793/2},(Vector2){69,00},180,WHITE);
                }


         if(player_alive==1){

            if(IsKeyDown(KEY_SPACE)){
                player_velocity=5;
            }

            for(int i=0;i<6;i++){

                pipe_height[i][1]-=1.5;
                if(pipe_height[i][1]<-75){
                    temp = GetRandomValue(220,500);
                    pipe_height[i][0]=temp;
                    pipe_height[i][1]=1500-76;
                }

                
                
                if(CheckCollisionRecs((Rectangle){player_position.x,player_position.y,55,44},(Rectangle){pipe_height[i][1],pipe_height[i][0],138/2,793/2})||
                CheckCollisionRecs((Rectangle){player_position.x,player_position.y,55,44},(Rectangle){pipe_height[i][1],pipe_height[i][0]-793/2-180,138/2,793/2})){
                    player_alive=0;
                }
                
                
            }
            
            pixel_count-=1.5;
            
         }else{
            mouse_position = GetMousePosition();

            DrawTexture(restart,screenWidth/2-107,screenHeight/2-50,WHITE);
            if(CheckCollisionPointRec(mouse_position,(Rectangle){screenWidth/2-107,screenHeight/2-50,200,70})){
                if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        player_position =(Vector2){155,350};
                        
                        player_alive=1;
                        pixel_count=0;
                        score=0;

                        for(int ii=0;ii<6;ii++){
                            temp = GetRandomValue(220,500);
                            pipe_height[ii][0]=temp;
                            pipe_height[ii][1]=600+ii*250;
                        }
                }
                }
         }
            
            
                
                DrawTexturePro(bird_,(Rectangle){00,00,93,64},(Rectangle){150,player_position.y,64,44},(Vector2){00,00},0.0,WHITE);
                DrawTexturePro(ground,(Rectangle){00,00,2072,2*128},(Rectangle){((int)pixel_count)%37,540,1036,128},(Vector2){00,00},0.0,WHITE);

                if(pixel_count<-500){
                  score = -(pixel_count+660-155)/250+1;
                }
                DrawText(TextFormat("Score : %d",score), 400,50, 40, BLACK);
                    
                

         
        }

        DrawFPS(10,10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    UnloadTexture(flapy_bird_logo);
    UnloadTexture(scarfy);
    UnloadTexture(back_ground);  
    //--------------------------------------------------------------------------------------

    return 0;
}
