#include <fcntl.h>
#include <unistd.h>
#include <assert.h> 

#define BLOCK_SIZE 1 //taille du buffer qui est de 1 octet


int main(int argc, char *argv[])
{
    
	int fin,
		fout;
	char buf[BLOCK_SIZE];
    // Prog defense
	assert( argc == 3 );

    // Bloc du buffer(tampon) de taille Block_size
	fin = open(argv[1],O_RDONLY); // Ouvre fichier source en mode read only
	assert( fin >= 0 );// si negatif veut dire  ouverture fermeture mall passer 

    // ouvre ou creer le fichier destination ensuite O_TRUNC vide le fichier si dejq present  et 0600 pemirission rw for proprietaire
	fout = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0600);
	assert( fout >= 0 );// si negatif veut dire  ouverture fermeture mall passer 

	while(1){
		ssize_t nb_read; 
		nb_read = read(fin,buf,BLOCK_SIZE); // lit au max un octet et le place dans buf 
		if (nb_read <= 0) // fin du fichier ou erreur
			break; 
		write(fout,buf,nb_read);// ecrit dans le fichier dest le contenue de buf
	}

	close(fin);
	close(fout);
    //femeture des deux fichier

	return 0; // fin prog
}

