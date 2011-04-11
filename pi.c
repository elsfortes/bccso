#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char * argv[])
{
    int n = 9000000;

    int pid = fork();
    int pid2;

    if(pid == 0)
    {
	pid2 = fork();

	double x = 0;
	double y = 0;
	int count = 0;

	if(pid2 == 0)
	{
	    srand(time(0));
	}
	else
	{
	    sleep(1);
	    srand(time(0));
	}

	for(int i = 0; i < n; i++)
	{
	    x = (double) rand() / (double) RAND_MAX;
	    y = (double) rand() / (double) RAND_MAX;
	
	    if(sqrt(x*x + y*y) <= 1)
	    {
		count++;
	    }
	}
	if(pid2 > 0)
	{
	    FILE * file;
	    file = fopen("pi.txt","w");
	    printf("O filho contou %i\n",count);
	    fprintf(file, "%i",count);
	    fclose(file);
	}
	else
	{
	    FILE * file;
	    file = fopen("pi2.txt","w");
	    printf("O filho contou %i\n",count);
	    fprintf(file,"%i",count);
	    fclose(file);
	}
	return 0;
    }
    else
    {
	wait(NULL);
	wait(NULL);

	int count;
	int count2;
	char c2[16];
	char c[16];
	double pi;
	
	FILE * file;
	FILE * file2;

	file = fopen("pi.txt","r");
	for(int i = 0; i < strlen(c); i++)
	{
	    fscanf(file,"%c",&c[i]);
	}
	count = atoi(c);
	fclose(file);

	file2 = fopen("pi2.txt","r");
	for(int i = 0; i < strlen(c2); i++)
	{
	    fscanf(file2,"%c",&c2[i]);
 	}
	count2 = atoi(c2);
	fclose(file2);

	pi = 2.0*(count+count2)/n;
	printf("O pai achou %i e %i\n",count,count2);
	printf("%f\n", pi);

	return 0;
    }
}
