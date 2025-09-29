#include <stdio.h>

/*
 * On creer une fonction pour tester car on veut eviter l'optimisation du gcc -O2. 
 * volatile permet aussi deviter l'optimisation et dis au compilateur,
 * en gros elle permet de fire au compilateur " Je suis sûre que cette variable chagera de valeur donc ne fais pas d'optimisation déçu".
 *
*/
void boom(){
    char big_array[100 * 1024 * 1024]; // 100M sur la pile
    big_array[0] = 'A';
    printf("j'ai reussi a allouer un gros tableaux de 100M sur la pile %c! \n", big_array[0]);
}

int main(int argc, char *argv[]){
	boom(); 
	return 0;
}
	/*
	 * Sur la majorité des systeme lunix la pile est limité à 8Mo ulimit -s = 8192 
	 * Donc ici le systeme vas renvoyer un sec fault car on utilise tout le gap 
	 * et Donc on empiete sur le tas.
	*/
