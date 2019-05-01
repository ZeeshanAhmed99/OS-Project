#include<stdio.h> 
#include<string.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>   
int main() 
{ 
   
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
    int arr[5]={1,2,3,4,5};
    int key,flag=0;
   int size=(sizeof(arr))/(sizeof(int));	
    pid_t p; 
    char str1[]="Value is present in array: ";
    char str2[]="Value is not present in an array: "; 
    if (pipe(fd1)==-1) 
    { 
	fprintf( stderr,"Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
 	fprintf(stderr,"Pipe Failed" ); 
        return 1; 
    } 
    p = fork(); 
    if (p < 0) 
    { 
        fprintf( stderr,"fork Failed" ); 
        return 1; 
    } 
    // Parent process 
    else if (p > 0) 
    {  
	char str[50];
  	close (fd1[0]);
	write(fd1[1],arr,sizeof(arr));
	wait(NULL);
	close (fd1[1]);
	close (fd2[1]);
	read(fd2[0],str,sizeof(str));
	close (fd2[0]);
	printf("\n%s\n",str);
	printf("\n");	
    }  
    // child process 
    else
    { 
	int key;
	close (fd1[1]);
	read(fd1[0],arr,sizeof(arr));
	printf("Enter key value to be searched\n: ");
	scanf("%d",&key);
	for(int i=0;i<size;i++)
	{
	 if(key==arr[i])
	 {
	  flag=1;	
	 }
	}
	close (fd1[0]);
	close (fd2[0]);
	if(flag==1)
	{
	  write(fd2[1],str1,sizeof(str1));
	}
	else
	{
	  write(fd2[1],str2,sizeof(str2));	
	}
	close (fd2[1]);	
    } 
} 
