#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
double childOneProcess ( double x , double y , double dardos , int k , double aC);
double childTwoProcess ( double x , double y , double dardos , int k , double aC2);


void main()
{
	double dardos  = 1000000;
	int k = 0;
	double x; 
	double y;
	double aC = 0;
	double aC2 = 0;
	double j = 0;
	double pi = 0;
	pid_t  pid;
	pid_t ppid;
	FILE *arquivo;
	double *buffer  = malloc(sizeof(double));

	pid = fork();
	
	
	if(pid == 0)
	{
		
		aC = childOneProcess(x, y, dardos, k ,j);
		printf("aC = %f \n" ,aC);
	}
	else if(pid > 0)
	{
	
		ppid = fork();
		
		if(ppid == 0)
		{
			
			aC2 = childTwoProcess ( x, y, dardos, k, j);
			printf("aC2 = %f \n" ,aC2);
			
		}
		else
		{
			sleep(1);
			
			
			

			
			arquivo = fopen("aC.txt" , "rb");
			fread(buffer ,sizeof(double), 1 , arquivo);
			aC = buffer[0];
			
			arquivo = fopen("aC2.txt" , "rb");
			fread(buffer , sizeof(double), 1 , arquivo);
			aC2 = buffer[0];
		
			fclose(arquivo);
			
			pi = 2 * ((aC + aC2)/dardos);
			printf("O valor de Pi é %f \n" , pi);			
		}
		
	
	}
	
	
}

double childOneProcess ( double x , double y , double dardos , int k , double aC)
{
	while (k < dardos )
	{
		x  = (double)rand() / (double) (RAND_MAX );
		y = (double)rand() / (double) (RAND_MAX );

		if( (sqrt( pow(x - 0.5 , 2 ) + pow(y - 0.5 , 2 ) ) )  < 0.5 ) 
		{	
			aC++;
		}

		k++;
	}
	printf("O processo %d efetuou o cálculo dos dardos lançados no centro do circulo \n  " , getpid());

	FILE *arquivo = fopen("aC.txt" , "w");
	fwrite(&aC, sizeof(aC), 1, arquivo);
	fclose(arquivo);
		
	return (aC);
	
}
double childTwoProcess ( double x , double y , double dardos , int k , double aC2)
{
	while (k < dardos )
	{
		x  = (double)rand() / (double) (RAND_MAX );
		y = (double)rand() / (double) (RAND_MAX );

		if( (sqrt( pow(x - 0.5 , 2 ) + pow(y - 0.5 , 2 ) ) )  < 0.5 ) 
		{	
			aC2++;
		}
		
		k++;
	}
	printf("O processo %d efetuou o cálculo dos dardos lançados no centro do circulo \n  " , getpid());
	FILE *arquivo = fopen("aC2.txt", "w");
	fwrite(&aC2, sizeof(aC2), 1, arquivo);
	fclose(arquivo);
	return(aC2);

}




