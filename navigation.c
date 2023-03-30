#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START 'S'
#define DESTINATION 'D'
#define PATH '+'
#define WALL '#'
#define UNSEEN '.'
#define SEEN '~'


typedef struct{
    char *grid;
    int maxX;
    int maxY;
} navigation_t;

typedef struct{
    int x;
    int y;
} position_t;

void newGrid(navigation_t *nav){
    printf("Number of rows? ");
    scanf(" %i", &(nav->maxY));
    printf("Number of columns? ");
    scanf(" %i", &(nav->maxX));
}

void cleanNav(navigation_t nav){
    if(nav.grid != NULL){
        free((&nav)->grid);
        nav.maxX = 0;
        nav.maxY = 0;
    }
}

void inputGrid(navigation_t nav){
    int score = 0;
    int output = 0;
    for(int j = 0; j < nav.maxY; j++){
        printf("Input row %i: ", j);
        for(int i = 0; i < nav.maxX; i++){
            scanf(" %c", &nav.grid[i + j*nav.maxX]);
            if(nav.grid[i + j*nav.maxX] == 'S'){
                score++;
            }
            if(score > 1){
                nav.grid[i + j*nav.maxX] = '#';
                score = 1;
                output = 1;
            }        
        }
        if(output == 1){
            printf("Extra starting point\n");
            output = 0;
        }
    }
}


void printGrid(navigation_t nav){
    for(int i = 0; i < nav.maxY; i++){
            for(int j = 0; j < nav.maxX; j++){
                printf("%c", nav.grid[i * nav.maxX+j]);    }
        printf("\n");    
    }
}

position_t findStart(navigation_t nav){
    position_t pos; 
    pos.x = -1;
    pos.y = -1;
    for(int i = 0; i < nav.maxY; i++){
        for(int j = 0; j < nav.maxX; j++){
            if(nav.grid[i * nav.maxX+j] == 'S'){
                pos.x = i;
                pos.y = j;
                return pos;
            }    
        }
    }
    return pos;
}

void resetPath(navigation_t nav){
    for(int i = 0; i < nav.maxX * nav.maxY; i++) {
        if(nav.grid[i] == '~' || nav.grid[i] == '+' ){
            nav.grid[i] = '.'; 
        }
    }   
}

int findPath(navigation_t nav, int x, int y, int length){
    int nlength = 0, slength = 0, wlength = 0, elength = 0;
    int finish = 0;
    if(x < 0 || y < 0 || x >= nav.maxX || y >= nav.maxY){
        return 0;
    };
    if(nav.grid[x+y*nav.maxX] == 'D'){
        finish++;
        return length;
    };
    if(nav.grid[x+y*nav.maxX] == '#'){
        return 0;
    };
    if(nav.grid[x+y*nav.maxX] == '+' || nav.grid[x+y*nav.maxX] == '~'){
        return 0;
    };
    if(nav.grid[x+y*nav.maxX] == 'S' && length != 0){
        return 0;
    };
    if(nav.grid[x+y*nav.maxX] == '.'){
        nav.grid[x+y*nav.maxX] = '~';
    }
    
    if((elength = findPath(nav, x + 1, y, length + 1))){
        if(nav.grid[x+y*nav.maxX] == '~'){
            nav.grid[x+y*nav.maxX] = '+';
        }
        return elength;
    }
    
    if((nlength = findPath(nav, x, y+1, length + 1))){
        if(nav.grid[x+y*nav.maxX] == '~'){
            nav.grid[x+y*nav.maxX] = '+';
        }
        return nlength;
    }
    if((slength = findPath(nav, x, y-1, length + 1))){
        if(nav.grid[x+y*nav.maxX] == '~'){
            nav.grid[x+y*nav.maxX] = '+';
        }
        return slength;
    }
    if((wlength = findPath(nav, x - 1, y, length + 1))){
        if(nav.grid[x+y*nav.maxX] == '~'){
            nav.grid[x+y*nav.maxX] = '+';
        }
        return wlength;
    }

    
    
    
    
    
    
    
    
    /*if(nav.grid[x+y*nav.maxX] == '.'){
        nav.grid[x+y*nav.maxX] = '+';
        
        printf("\n%i\n%i\n%i\n%i\n", slength, nlength, wlength, elength);
        if(slength == 0 && nlength == 0 && elength == 0 && wlength == 0){
            nav.grid[x+y*nav.maxX] = '~';
            return 0;
        } else{
            nav.grid[x+y*nav.maxX] = '+';
            int arr[4] = {wlength, elength, slength, nlength};
            int smallest = 0;
            for (int i = 0; i < 4; i++){
                if(arr[i] != 0){
                    smallest = arr[i];
                }
            }
            for (int i = 0; i < 4; i++){
                if(arr[i] != 0 && smallest >= arr[i]){
                    smallest = arr[i];
                }
            }
            return smallest;
        }
    };
    if(nav.grid[x+y*nav.maxX] == 'S' && length == 0){
        wlength = findPath(nav, x - 1, y, length + 1);
        elength = findPath(nav, x + 1, y, length + 1);
        slength = findPath(nav, x, y - 1, length + 1);
        nlength = findPath(nav, x, y + 1, length + 1);
        if(slength > 0 && slength >= wlength && slength >= nlength && slength >= elength){
            return slength;
        }
        if(wlength > 0 && wlength >= slength && wlength >= nlength && wlength >= elength){
            return wlength;
        }
        if(elength > 0 && elength >= slength && elength >= nlength && elength >= wlength){
            return elength;
        }
        if(nlength > 0 && nlength >= wlength && nlength >= slength && nlength >= elength){
            return nlength;
        }
    } else if (nav.grid[x+y*nav.maxX] == 'S' && length != 0){
        return 0;
    }*/
    return 0;
};


int main(void){
    char cmd;
    navigation_t nav = {NULL, 0, 0};
    position_t posit = {0,0};
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 's':
                if(nav.grid != NULL){
                    posit = findStart(nav);
                } else{
                    printf("Grid contains no starting point\n");
                    printf("Grid contains no destination\n");
                    break;
                }
                if(posit.x == -1 || posit.y == -1){
                    printf("Grid contains no starting point\n");
                    printf("Grid contains no destination\n");
                    break;
                } else {
                    printf("The start is at x=%i and y=%i\n", posit.y, posit.x);
                    break;
                }
            case 'f':
                if(nav.grid == NULL){
                    break;
                } else {
                    int length = findPath(nav, posit.y, posit.x, 0);
                    if(length == 0){
                       printf("No path found\n"); 
                    } else {
                        printf("Found a path of length %i\n", length);
                    }
                    printGrid(nav);
                    break;
                }
            case 'i':
                cleanNav(nav);
                newGrid(&nav);
                if(nav.maxY < 2 || nav.maxX < 2){
                    printf("The number of rows and columns must be at least two\n");
                    break;
                } else {
                    nav.grid = (char *) malloc (nav.maxY * nav.maxX  * sizeof(char));  
                    inputGrid(nav);
                }
                break;
            case 'p':
                printGrid(nav);
                break;
            case 'r':
                resetPath(nav);
                break;
            case 'q':
                cleanNav(nav);
                break;
            default:
                printf("Unknown command '%c'\n", cmd);
                break;
            }
    } while(cmd != 'q');
    printf("Bye!\n");
}