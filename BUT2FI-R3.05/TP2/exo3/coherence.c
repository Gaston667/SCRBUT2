#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/fcntl.h>

#define TESTFILE "coherence-test.txt"

// 1ere Fonction décriture
void write_asr_c_pas_bien() 
{
	FILE* f = fopen(TESTFILE, "w");
	fprintf(f, "L'asr, c'est pas bien!\n"); // ecrit dans le fichier (contenu effacé et remplacé) cette ligne de char
	fclose(f);//  ferme
}

// 2e Fonction décriture
void write_asr_c_bien() 
{
	FILE* f = fopen(TESTFILE, "w");
	fprintf(f, "L'asr, c'est bien!!\n"); /
	fclose(f);
}

// Fonction  de 
void read_using_syscalls() 
{
	write_asr_c_pas_bien(); // ecrit c'est pas bien 

	// open file descriptor
	int fd = open(TESTFILE, O_RDONLY); // ouverture en lecture seule bas niveau

	// read first 12 bytes
	char buf[BUFSIZ]; // BUFSIZ n’est pas une variable du programme, mais une constante définie par la bibliothèque standard C (<stdio.h>). BUFSIZ 8192
	ssize_t nr1 = read(fd, buf, 12); // lit les 12 premiers octets
	assert(nr1 >= 0); //  verifie si tout s'est bien passé

	write_asr_c_bien(); // écrase le fichier avec le nouveau message

	// read rest of file, print to stdout
	ssize_t nr2 = read(fd, buf + nr1, BUFSIZ - nr1);  
	// continue la lecture à partir de la position actuelle dans le fichier
    // lit donc le reste du fichier, mais ATTENTION : fd n’a pas été réouvert
	
	
	close(fd);
	fwrite(buf, 1, nr1 + nr2, stdout); //  afiche ce que l'on a lu
}


void read_using_stdio() 
{
	write_asr_c_pas_bien();

	// open stdio file
	FILE* f = fopen(TESTFILE, "r");

	// read first 12 bytes
	char buf[BUFSIZ];
	size_t nr1 = fread(buf, 1, 12, f);

	write_asr_c_bien();

	// read rest of file, print to stdout
	size_t nr2 = fread(buf + nr1, 1, BUFSIZ - nr1, f); // continue à lire le reste du fichier
	// MAIS : stdio utilise un buffer interne, ça peut donner un autre résultat 
	fclose(f);
	fwrite(buf, 1, nr1 + nr2, stdout);
}


static void usage() 
{
	fprintf(stderr, "Usage: ./coherence -l (linux syscalls)  or  ./coherence -s (stdio)\n");
	exit(1);
}

int main(int argc, char** argv) 
{
	int which = 0;

	int opt;
	while ((opt = getopt(argc, argv, "ls")) != -1) {
		switch (opt) {
			case 's':
				which = 's';
				break;
			case 'l':
				which = 'l';
				break;
			default:
				usage();
		}
	}

	if (which == 's') {
		read_using_stdio();
	} else if (which == 'l') {
		read_using_syscalls();
	} else {
		usage();
	}
}
