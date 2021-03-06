/*
 ============================================================================
 Name        : Ejercicio-3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 int main()
 {
         //A null terminated array of character
         //pointers
         char *args[]={"./EXEC",NULL};
         execv(args[0],args);

         /*All statements are ignored after execvp() call as this whole
         process(execDemo.c) is replaced by another process (EXEC.c)
         */
         printf("Ending-----");

     return 0;
 }
