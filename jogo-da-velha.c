#include <raylib.h>
#include <stdio.h>
#define WINDOW_W 480
#define WINDOW_H 480

#define SQUARES 3

void inicializarVetor(char vetor[SQUARES][SQUARES]) {
    int i, j;
    for (i = 0; i < SQUARES; i++) {
        for (j = 0; j < SQUARES; j++) {
            vetor[i][j] = ' ';
        }
    }
}

char jogada(int vez) {
    if (vez % 2 == 0)
        return 'O';
    return 'X';
}

int Win_Horizontal(char a[SQUARES][SQUARES], int vez) {
	int i, j, k;
    char x = jogada(vez);
	for (i = 0; i < SQUARES; i++) {
		k = 0;
		for (j = 0; j < SQUARES; j++) {
			if (a[i][j] == x) {
				k ++;
				if (k == SQUARES) {
					return 1;
				}
			} else {
				break;
			}
		}
	}
	return 0;
}

int Win_Vertical(char a[SQUARES][SQUARES], int vez) {
	int i, j, k;
    char x = jogada(vez);
	for (i = 0; i < SQUARES; i++) {
		k = 0;
		for (j = 0; j < SQUARES; j++) {
			if (a[j][i] == x) {
				k ++;
				if (k == SQUARES) {
					return 1;
				}
			} else {
				break;
			}
		}
	}
	return 0;
}

int Win_Diagonal_Decrescente(char a[SQUARES][SQUARES], int vez) {
	int i, k;
    char x = jogada(vez);
	for (i = 0, k = 0; i < SQUARES; i++) {
		if (a[i][i] == x) {
			k ++;
			if (k == SQUARES) {
				return 1;
			}
		} else {
			break;
		}	
	}
	return 0;
}

int Win_Diagonal_Crescente(char a[SQUARES][SQUARES], int vez) {
	int i, k;
    char x = jogada(vez);
	for (i = 0, k = 0; i < SQUARES; i++) {
		if (a[i][(SQUARES-1)-i] == x) {
			k++;
			if (k == SQUARES) {
				return 1;
			}
		} else {
			break;
		}
	}
	return 0;
}

int main() {
    InitWindow(WINDOW_W, WINDOW_H, "Jogo da Velha");
    
    SetTargetFPS(60);
    
    int squareSize = 100;
    int counterw, counterh;
    const int divisorw = (WINDOW_W - squareSize * SQUARES) / (SQUARES + 1);
    const int divisorh = (WINDOW_H - squareSize * SQUARES) / (SQUARES + 1);
    
    Rectangle squares[SQUARES][SQUARES]; 
    char squaresClicked[SQUARES][SQUARES]; 
    inicializarVetor(squaresClicked);
    
    int i, j, vezDoJogador = 0;
    char text[50];
    sprintf(text, "Jogador: %c", jogada(vezDoJogador));
    
    char victoryMessage[50];
    
    Font fonte = LoadFont("Bluffolk.fnt");
    
    for (i = 0, counterh = divisorh; i < SQUARES; i++, counterh += squareSize + divisorh) {
         for (j = 0, counterw = divisorw; j < SQUARES; j++, counterw += squareSize + divisorw) {
            squares[i][j] = (Rectangle){counterw, counterh, squareSize, squareSize};
         }                 
    } 
    
    while (!WindowShouldClose()) { 
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        
        if (IsKeyPressed(KEY_R)) {
            inicializarVetor(squaresClicked);
            vezDoJogador = 0;
            sprintf(text, "Jogador: %c", jogada(vezDoJogador));
        }
        
        for (i = 0; i < SQUARES && vezDoJogador < SQUARES * SQUARES; i++) {
            for (j = 0; j < SQUARES && vezDoJogador < SQUARES * SQUARES; j++) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                    if (mouseX >= squares[i][j].x && mouseX <= squares[i][j].x + squareSize && mouseY >= squares[i][j].y && mouseY <= squares[i][j].y + squareSize && squaresClicked[i][j] == ' ') {  
                        squaresClicked[i][j] = jogada(vezDoJogador);
                        if (Win_Horizontal(squaresClicked, vezDoJogador) || Win_Vertical(squaresClicked, vezDoJogador) || Win_Diagonal_Crescente(squaresClicked, vezDoJogador) || Win_Diagonal_Decrescente(squaresClicked, vezDoJogador)) {
                            sprintf(victoryMessage, "O Jogador %c venceu!", jogada(vezDoJogador));
                            DrawRectangle(0, 0, WINDOW_W, WINDOW_H, GREEN);
                            DrawTextEx(fonte, victoryMessage, (Vector2){WINDOW_W/5, WINDOW_H/2}, 25, 2, BLACK);
                        }
                        else {
                            vezDoJogador++;
                            sprintf(text, "Jogador: %c", jogada(vezDoJogador));
                        }
                        
                    }  
                }
            }
        }
        
        BeginDrawing(); 
        
        ClearBackground(LIGHTGRAY); 
        
        DrawTextEx(fonte, "Aperte [R] para reiniciar", (Vector2){250, 5}, 15, 2, BLACK);
        
        for (i = 0; i < SQUARES; i++) {
            for (j = 0; j < SQUARES; j++) {
            DrawRectangleLinesEx(squares[i][j], 2, GRAY); 
                if (squaresClicked[i][j] == 'O') { 
                    DrawCircle(squares[i][j].x + squareSize/2, squares[i][j].y + squareSize/2, squareSize/3, BLUE);
                    DrawCircle(squares[i][j].x + squareSize/2, squares[i][j].y + squareSize/2, squareSize/4, LIGHTGRAY);
                } 
                else if (squaresClicked[i][j] == 'X') {
                    DrawRectanglePro((Rectangle){squares[i][j].x + squareSize/2, squares[i][j].y + squareSize/2, 80, 10}, (Vector2){40, 5}, 45, RED);
                    DrawRectanglePro((Rectangle){squares[i][j].x + squareSize/2, squares[i][j].y + squareSize/2, 80, 10}, (Vector2){40, 5}, 315, RED);
                }
            }    
        }
        
        DrawTextEx(fonte, text, (Vector2){5, 5}, 30, 2, BLACK);
        if (Win_Horizontal(squaresClicked, vezDoJogador) || Win_Vertical(squaresClicked, vezDoJogador) || Win_Diagonal_Crescente(squaresClicked, vezDoJogador) || Win_Diagonal_Decrescente(squaresClicked, vezDoJogador)) {
            sprintf(victoryMessage, "O Jogador %c venceu!", jogada(vezDoJogador));
            DrawRectangle(0, 0, WINDOW_W, WINDOW_H, GREEN);
            DrawTextEx(fonte, victoryMessage, (Vector2){WINDOW_W/5, WINDOW_H/2}, 25, 2, BLACK);
            DrawTextEx(fonte, "Aperte [R] para reiniciar", (Vector2){WINDOW_W/4, 300}, 15, 2, BLACK);
  		}
        else if (vezDoJogador == SQUARES * SQUARES) {
            sprintf(victoryMessage, "O Jogo deu Velha!");
            DrawRectangle(0, 0, WINDOW_W, WINDOW_H, GREEN);
            DrawTextEx(fonte, victoryMessage, (Vector2){WINDOW_W/4, WINDOW_H/2}, 25, 2, BLACK);
            DrawTextEx(fonte, "Aperte [R] para reiniciar", (Vector2){WINDOW_W/4, 300}, 15, 2, BLACK);
  		}
            
        EndDrawing(); 
    }
    
    CloseWindow();
    return 0;
}