#include <stdio.h>
#include <string.h>

typedef struct{
    int largura;
    int altura;
    int pixels[640][480];
    int bits_mx;
    char tipo[];
} imagem;

void le_imagem(imagem *img){
    scanf("%s", img->tipo);

    int result = strcmp(img->tipo, "P2");
    
    if (result != 0){
        printf("erro\n");
    }

    int altura;
    int largura;
    int bits;

    scanf("%d%d%d", &largura, &altura, &bits);

    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            scanf("%d", &img->pixels[j][i]);
        }
    }

    img->altura = altura;
    img->largura = largura;
    img->bits_mx = bits;

}

void escreve_imagem(imagem *img){
    // printf("%s\n", img->tipo);
    printf("P2\n");
    printf("%d %d\n", img->largura, img->altura);
    printf("%d\n", img->bits_mx);
    for(int i = 0; i < img->largura; i++){
        for(int j = 0; j < img->altura; j++){
            printf("%d ", img->pixels[j][i]);
        }
    }
}

void limiar(imagem *img, int parametro){
    for(int i = 0; i < img->largura; i++){
        for(int j = 0; j < img->altura; j++){
            if(img->pixels[j][i] < parametro){
                img->pixels[j][i] = 0;
            }else{
                img->pixels[j][i] = img->bits_mx;
            }
        }
    }
}

void crop(imagem *img1, imagem *img2, int largura, int altura){
    img2->largura = largura;
    img2->altura = altura;
    img2->bits_mx = img1->bits_mx;

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            img2->pixels[i][j] = img1->pixels[i][j];
        }
    }
}

void blur(imagem *img1, imagem *img2){
    img2->altura = img1->altura;
    img2->largura = img1->largura;
    img2->bits_mx = img1->bits_mx;

    for(int i = 0; i < img1->altura; i++){
        for(int j  = 0; j < img1->largura; j++){
            int soma = img1->pixels[i][j];
            int qnt = 1;
            if(i - 1 >= 0 && j - 1 >= 0){
                soma = soma + img1->pixels[i -1][j -1];
                qnt++;
            }if(i - 1 >= 0){
                soma = soma + img1->pixels[i -1][j];
                qnt++;
            }if(j - 1 >= 0){
                soma = soma + img1->pixels[i][j -1];
                qnt++;
            }if(i + 1 < img1->altura && j + 1 < img1->largura){
                soma = soma + img1->pixels[i +1][j +1];
                qnt++;
            }if(i + 1 < img1->altura){
                soma = soma + img1->pixels[i +1][j];
                qnt++;
            }if(j + 1 < img1->largura){
                soma = soma + img1->pixels[i][j +1];
                qnt++;
            }

            img2->pixels[i][j] = soma / qnt;
        }
    }
}

void bordas(imagem *img1, imagem *img2){
    img2->altura = img1->altura;
    img2->largura = img1->largura;
    img2->bits_mx = img1->bits_mx;
    
    for(int i = 0; i < img1->altura; i++){
        for(int j  = 0; j < img1->largura; j++){
            int valor4 = 4*img1->pixels[i][j];
            
            if(i - 1 >= 0) valor4 = valor4 - img1->pixels[i -1][j];

            if(j - 1 >= 0) valor4 = valor4 - img1->pixels[i][j -1];

            if(i + 1 < img1->altura) valor4 = valor4 - img1->pixels[i +1][j];
            
            if(j + 1 < img1->largura) valor4 = valor4 - img1->pixels[i][j +1];
            

            if(valor4 < 0) valor4 *=-1;
            if(valor4 > 255) valor4 = 255;

            img2->pixels[i][j] = valor4;
        }
    }
}

int main(){

    imagem image;
    imagem *img;
    img = &image;

    imagem image2;

    le_imagem(img);

    // bordas(img, &image2);

    escreve_imagem(&image2);


    return 0;
}