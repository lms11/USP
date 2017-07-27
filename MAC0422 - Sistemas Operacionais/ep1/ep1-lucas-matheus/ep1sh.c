#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define TRUE 1

char promptBuffer[1024];
int argc;
char *argv[32];


/*
	Quebra a entrada na linha de comando em vários argumentos
	@input line String de entrada da linha de comando
*/
void parseInput (char *line) {
	/* Start parsing new values */
	argc = 0;
	char *arg = strtok (line, " ");

	while (arg) {
		argv[argc] = arg;
		argc++;
		arg = strtok (NULL, " ");
	}

	argv[argc] = NULL;
}


/*
	Imprime o caminho atual na variavel "promptBuffer" e retorna ela
*/
char* prompt() {
	memset (promptBuffer, 0, sizeof (promptBuffer));
	snprintf (promptBuffer, sizeof (promptBuffer), "(%s): ", getcwd (NULL, 1023));

	return promptBuffer;
}


/*
	Imprime o prompt e espera uma entrada do usuário
*/
char* get_command() {
	prompt();
	char *line = readline (promptBuffer);

	if (!line) {
		return NULL;
	}

	add_history (line);
	parseInput (line);

	return line;
}


/*
	Executa um comando específico
	@input command Comando a ser executado
	@input args Argumentos (incluindo o comando, no argumento 0)
	@input argsp Argumentos de ambiente
*/
void execute (char *command, char *args[], char *argp[]) {
	if (strcmp (command, "chmod") == 0) {
		int permissions = strtol(args[1], 0, 8);
		if (chmod (args[2], permissions) < 0) {
		  fprintf (stderr, "Erro ao executar \"chmod %s %s\" - %d (%s)\n", argv[1], argv[2], errno, strerror (errno));
    }

	} else if (strcmp (command, "id") == 0 && strcmp (args[1], "-u") == 0) {
		printf ("%d\n", geteuid ());

	} else if (strcmp (command, "exit") == 0) {
		exit(0);

	} else if (strcmp (command, "cd") == 0) {
		chdir (args[1]);

	} else {
		pid_t pid;
		int status;

		if ((pid = fork ()) == 0) {
			execve (command, args, argp);

		} else {
			waitpid (pid, &status, 0);

		}
	}
}


int main (int m_argc, char *m_argv[], char *m_argp[]) {
  while (TRUE) {
		char *line = get_command ();

		if (argv[0] != NULL) {
			execute (argv[0], argv, m_argp);
		}

		free (line);
  }

  return 0;
}
