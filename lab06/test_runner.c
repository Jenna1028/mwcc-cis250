#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_LINE 256

//prototypes
void display_test_results(void);
void display_summary(int total, int passed, int failed);
int run_test(char *args[]);

int main(void) {
	
	FILE *testplan_file;
	char line[MAX_LINE];

	int total_tests = 0;
	int passed_tests = 0;
	int failed_tests = 0;
	testplan_file = fopen("tests.txt", "r");

	if (testplan_file == NULL) {
		perror("Unable to open tests.txt");
		return 1;

	}

	//Read each command from the test plan
	while (fgets(line, sizeof(line), testplan_file) != NULL) {
		
		line[strcspn(line, "\n")] = '\0';
		
		//skip blank lines and comments
		if (line[0] == '\0' || line[0] == '#') {
			continue;
		}
		
		char *args[32];
		int i = 0;
		
		//Seperate the command into arguments for execvp
		char *token = strtok(line, " \t");

		while (token != NULL && i < 31) {
			args[i] = token;
			i++;
			token = strtok(NULL, " \t");


		args[i] = NULL;
		}

		if (args[0] == NULL) {
			continue;
		}
		
		//Display the command and starting message
		printf("\nTest command: ");

		for (int j = 0; args[i] != NULL; j++) {
			printf("%s ", args[j]);
		}

		printf("\n");
		printf("Starting test...\n");
		fflush(stdout);

		total_tests++;
		
		//keep track of passed and failed tests
		if (run_test(args) == 0) {
			passed_tests++;
		}
		else {
			failed_tests++;
		}


	}


	fclose(testplan_file);

	display_summary(total_tests, passed_tests, failed_tests);

	return 0;
}

int run_test(char *args[])
{

	//Create a child process to execute the test
	pid_t pid = fork();
	
	if (pid < 0)
	{
		perror("fork");
		return 1;
	}

	if (pid == 0)
	{
		execvp(args[0], args);

		//only runs if execvp fails
		perror("execvp");
		_exit(1);
	}

	int status;

	//Wait for the child process to finish
	if (wait(&status) == -1)
	{
		perror("wait");
		return 1;
	}

	//check if test passed or failed
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{

			printf("PASS: %s\n", args[0]);
			return 0;
		}

		else
		{
			printf("FAIL: %s (exit status %d)\n",
				args[0], WEXITSTATUS(status));
			return 1;
		}
	}
	else
	{
		printf("FAIL: %s (terminated abnormally)\n", args[0]);
		return 1;
	}
}

//Dipslay the final test summary
void display_summary(int total, int passed, int failed)
{
	printf("\n==================================\n");
	printf("\n");
	printf("TEST SUMMARY\n");
	printf("\n==================================\n");
	printf("Tests executed: %d\n", total);
	printf("Tests passed:   %d\n", passed);
	printf("Tests failed:   %d\n", failed);
	printf("====================================\n");
}

