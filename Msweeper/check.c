#include <stdio.h>

void check(int k[]);

int main(){
      int i;
      int k[12];

      for(i = 0; i <= 10; i++){
            k[i] = 0;
      }
      check(k);
      for(i = 0; i <= 10; i++){
            printf("%d",k[i]);
      }
}
void check(int k[]){
      int x=5;
      
      k[x] = 10;
}
