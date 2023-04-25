#include <stdio.h>

int main(void) {
    char command[100];  // assuming maximum command length is 100 characters
    
    while (1) {  // infinite loop to keep prompting for commands
        printf("$ ");  // print the prompt
        fgets(command, sizeof(command), stdin);  // read the user's command
        
        printf("%s", command);  // print the user's command
    }
    
    return 0;
}
