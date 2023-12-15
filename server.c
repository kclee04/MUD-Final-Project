#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888
#define MAX_LEN 1024

const char* opposite(const char* direction) {
    if (strcmp(direction, "north") == 0) {
        return "south";
    } else if (strcmp(direction, "south") == 0) {
        return "north";
    } else if (strcmp(direction, "east") == 0) {
        return "west";
    } else if (strcmp(direction, "west") == 0) {
        return "east";
    } else {
        // If the direction is not recognized, return the same direction
        return direction;
    }
}

const char* getCurrentDirectoryName(const char *path) {
    // Find the last occurrence of the directory separator
    char *lastSlash = strrchr(path, '/');

    // If found, return the name after the last separator
    if (lastSlash != NULL) {
        return lastSlash + 1;
    } else {
        // If no separator is found, the current directory is the root
        return path;
    }
}

void daemonize() {
  pid_t pid = fork();           // create child process
  if (pid < 0) {
    perror("Fork failed");
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);         // exit parrent process if fork was successful
  }

  // create new session
  if (setsid() < 0) {
    perror("Setsid failed");
    exit(EXIT_FAILURE);
  }
  // change working directory
  if (chdir("/home/jimmyn6565/mud_game") < 0) {
    perror("Chdir failed");
    exit(EXIT_FAILURE);
  }

  // close stdin, stdout, and stderr
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
}

int main() {
    daemonize();

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Creating UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Binding socket with address and port
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // infinite loop until start_room is created
    while (chdir("start_room") != 0) {
      printf("Failed to enter start room.\n");
      sleep(1);     // sleep for 1 second before checking for start_room
    }
    // output the first desc.txt of starting room
    system("mosquitto_pub -h jimmynguyen.duckdns.org -t mud -f desc.txt");

    char path[100];

    while (1) {
        char buffer[MAX_LEN];
        int n;
        socklen_t len;
        len = sizeof(cliaddr);

        n = recvfrom(sockfd, (char *)buffer, MAX_LEN, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        // check if the received message is quit from the server
        if (strncmp(buffer, "quit", 4) == 0) {
            printf("Server has quit. Exiting the program.\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }

        getcwd(path, 100);
        const char* currentDir = getCurrentDirectoryName(path);

        size_t realLength = strcspn(buffer, "\n");
        buffer[realLength] = '\0';

        if (chdir(buffer) == 0) {
          system("mosquitto_pub -h jimmynguyen.duckdns.org -t mud -f desc.txt");
        } else if (strcmp(buffer, opposite(currentDir)) == 0) {
          chdir("..");
          system("mosquitto_pub -h jimmynguyen.duckdns.org -t mud -f desc.txt");
        } else {
          system("mosquitto_pub -h jimmynguyen.duckdns.org -t mud -m \"Ow! There\'s a wall here.\"");
        }

    }

    // program should never reach
    return 0;
}