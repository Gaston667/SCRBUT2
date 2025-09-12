#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>
#include <sys/mman.h>


#define BUFSIZE 1024 // Taille du buffer 


static inline double tstamp(void) 
{                             
	struct timespec tv;
	clock_gettime(CLOCK_REALTIME, &tv);
	return tv.tv_sec + tv.tv_nsec * 1.0e-9;
}

int main(int argc, char *argv[])
{
	//char buf[BUFSIZE];	
    // pointeurs vers la mémoire mappée du fichier source et du fichier destination.
	char * bufin = NULL,
		 * bufout = NULL;


	int fin,
		fout;

	double start, // t debut 
		   end; // t end

	size_t filesize = 0; //  taille du fichier source 

	assert(argc == 3); // defense

	start = tstamp(); // time de debut

	fin = open(argv[1],O_RDONLY); //Ouvre le fichier source en read only
	assert(fin >=0); // verifie que ouverture reussi

    //Ouvre le fichier destionation en lecture ecriture, crée le fichier si existe pa, et le vide sinon 
	fout = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0600);
	assert(fout >=0); // verifie que ouverture reussi

	filesize = lseek(fin,0,SEEK_END);// déplace le curseur à la fin du fichier source. La valeur de retour est la taille du fichier en octets.
	ftruncate (fout,filesize); //Ajuste la taille du fichier destination pour qu’elle corresponde exactement à celle du fichier source. Sinon, impossible de faire un mmap correct.

    // Mapage de page 
    /*
        Mappe le fichier source en mémoire :
        NULL = le système choisit l’adresse.
        filesize = taille à mapper.
        PROT_READ = lecture seule.
        MAP_PRIVATE = modifications locales non propagées au fichier (sécurité).
    */
	bufin = mmap(NULL,filesize,PROT_READ,MAP_PRIVATE,fin,0); 
	assert(bufin != (void*)-1); //Vérifie que le mappage a réussi.


    /*
        Mappe le fichier destination en mémoire :
        PROT_WRITE = autorise l’écriture.
        MAP_SHARED = les modifications seront visibles dans le fichier.
        Vérifie que le mappage a réussi.
    */
	bufout = mmap(NULL,filesize,PROT_WRITE,MAP_SHARED,fout,0);
	assert(bufout != (void*)-1);


	memcpy(bufout,bufin,filesize);

	//munmap(bufin,filesize);
	//munmap(bufout,filesize);

	//ssize_t nb_read = read(fin,buf,sizeof(buf));
	close(fin);
	close(fout);
    //Ferme les descripteurs de fichiers.

	end = tstamp();

	printf("time = %.3lf\n",end - start);
    /*
    Mesure l’instant de fin.
    Affiche la durée de la copie avec 3 chiffres après la virgule.
    Retourne 0 (succès).
    */
	return 0;
}
