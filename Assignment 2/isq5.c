#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

void childFunction(char* line)
{
    write(1, "I am a child working for my parent\n", 36);

    int number1, number2, result=0;
    char operation, n1, n2;
    char buffer[20];
    sscanf(line, "%d%c%d", &number1, &operation, &number2);
    sscanf(line, "%c%c%c", &n1, &operation, &n2);

    //wrong statement
    if (number1 != (int)(n1) || number2 != (int)(n2))   // 
        exit(50);
    else
    {
        switch (operation)
        {       
            case '+':
                result = number1 + number2;
                break;

            case '-':
                result = number1 - number2;
                break;
            
            case '*':
                result = number1 * number2;
            
            case '/':
                if (number2 == 0) //division by 0 case handle
                    exit(100);
                else
                    result = number1 / number2;
            
            default:
                exit(200); //in case of wrong operator
                break;            
        }
    }
    sprintf(buffer, "%d %c %d = %d \n", number1, operation, number2, result);
    printf("%s", buffer);
    exit(0);
    
}

int main(int argc, char const *argv[])
{
    /* 0 = STDIN_FILENO
    1 = STDOUT_FILENO
    2 = STDERR_FILENO   */
    
    write(STDOUT_FILENO, "This program makes simple arithmetics.\n", 40); 
    while (true)
    {
        char input[50];
        write(1, "Enter an arithmetic statement without spaces, e.g., 34+132 \n", 61);
        int nread = read(0, input, sizeof(input)-1);
        //write(1, input, nread);   for testing
        int status;
        if (fork() == 0)
        {
            //child process
            childFunction(input);
        }
        else
        {
            //parent process
            char msg[] = "Created a child to make your operation, waiting\n";
            write(1, msg, sizeof(msg)-1); 

            wait(&status);     
            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status) == 50)
                    printf("Prgram exited. Wrong statement\n");
                else if (WEXITSTATUS(status) == 100)
                    printf("Program exited. Division by zero\n");
                else if (WEXITSTATUS(status) == 200)
                    printf("Program exited. Wrong operator\n");              
            }       
        }
    }
    exit(0);
    return 0;
}