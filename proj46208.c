/* Project #4
   EGRE246 Fall 2019
   B. Mayer */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
                      //STORES DV POINTS IN A GRID
int gridSize(int width, int height, int gridOfDv[height+1][width+1],FILE *file){
  int rgb[3];
  for(int i = 1; i <= height; i++){
    for(int j = 1; j <= width; j++){
      for(int k = 0; k < 3; k++){
        fscanf(file,"%d",&rgb[k]);
                    //CHECK FOR INVALID RGB VALUE
        if((rgb[k] < 0)||(rgb[k] > 255)){
          printf("ERROR: INVALID RGB VALUE\n");
          exit(-1);
        }
      }
      gridOfDv[i][j] = (rgb[0]+rgb[1]+rgb[2]);
    }
  }
  return 0;
}

                        //FIND DARKEST SPOT IN THE GRID
int findDarkest(int width, int height, int gridOfDv[height+1][width+1]){
  int largestDarkVal = gridOfDv[1][1];
  for(int i = 1; i <= height; i++){
    for(int j = 1; j <= width; j++){
      if(gridOfDv[i][j] <= largestDarkVal){
      largestDarkVal = gridOfDv[i][j];
      }
    }
  }
  return largestDarkVal;
}

                      //FIND AND PRINT SPOTS WITHIN 30%
void printDark(int width, int height, int gridOfDv[height+1][width+1],int darkest){
  float darkest30 = rintf(((float)darkest * 0.30)+darkest);
  for(int i = 1; i <= height; i++){
    for(int j = 1; j <= width; j++){
      if(gridOfDv[i][j] <= darkest30){
        printf("[%d,%d]", i, j);
      }
    }
  }
}

int main(int argc, char *argv[]){
  FILE *file;
  file = fopen(argv[1], "r");

                   //CHECK IF FILE EXISTS
  if(file == 0){
    printf("ERROR: FILE DOES NOT EXIST");
    exit(-1);
  }

                  //SCAN FOR FIRST 4 VALUES (BASIC INFO)
  char magicNum[5];
  int width[1]={0}, height[1] = {0}, colorVal[1] = {0};
  fscanf(file,"%s",magicNum);
  fscanf(file,"%d",width);
  fscanf(file,"%d",height);

                //CHECK IF VALID GRID SIZE
  if(((width[0])*(height[0])) > 500000){
    printf("ERROR: TOO MANY POINTS IN FILE");
    exit(-1);
  }
  fscanf(file,"%d",colorVal);
  int gridOfDv[width[0]+1][height[0]+1];
  gridSize(width[0], height[0], gridOfDv, file);

                  //PRINT STATEMENTS
  printf("Darkest Part of Sky - B. Mayer 10/2019\n");
  printf("image name: %s\n",argv[1]);
  printf("magic number  = %s\n",magicNum);
  printf("width, height = %d,%d\n",width[0],height[0]);
  printf("color val     = %d\n",colorVal[0]);
  printf("# points      = %d\n",(width[0] * height[0]));
  printf("darkest points of sky within 30.0%% of darkest point: \n");
  int darkest = findDarkest(width[0], height[0], gridOfDv);
  printDark(width[0], height[0], gridOfDv,darkest);
  fclose(file);
  return 0;
}
