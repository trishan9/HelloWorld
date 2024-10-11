#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 2001
#define LISTENQ 10

int list_s;

typedef struct {
  int returncode;
  char *filename;
} httpRequest;

typedef struct {
  pthread_mutex_t mutexlock;
  int totalbytes;
} sharedVariables;

char *header200 =
    "HTTP/1.0 200 OK\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";
char *header400 =
    "HTTP/1.0 400 Bad Request\nServer: CS241Serv v0.1\nContent-Type: "
    "text/html\n\n";
char *header404 =
    "HTTP/1.0 404 Not Found\nServer: CS241Serv v0.1\nContent-Type: "
    "text/html\n\n";

char *getMessage(int fd) {
  FILE *sstream;

  if ((sstream = fdopen(fd, "r")) == NULL) {
    fprintf(stderr, "Error opening file descriptor in getMessage()\n");
    exit(EXIT_FAILURE);
  }

  size_t size = 1;

  char *block;

  if ((block = malloc(sizeof(char) * size)) == NULL) {
    fprintf(stderr, "Error allocating memory to block in getMessage\n");
    exit(EXIT_FAILURE);
  }

  *block = '\0';

  char *tmp;
  if ((tmp = malloc(sizeof(char) * size)) == NULL) {
    fprintf(stderr, "Error allocating memory to tmp in getMessage\n");
    exit(EXIT_FAILURE);
  }

  *tmp = '\0';

  int end;

  int oldsize = 1;

  while ((end = getline(&tmp, &size, sstream)) > 0) {
    if (strcmp(tmp, "\r\n") == 0) {
      break;
    }

    block = realloc(block, size + oldsize);

    oldsize += size;

    strcat(block, tmp);
  }

  free(tmp);

  return block;
}

int sendMessage(int fd, char *msg) { return write(fd, msg, strlen(msg)); }

char *getFileName(char *msg) {
  char *file;

  if ((file = malloc(sizeof(char) * strlen(msg))) == NULL) {
    fprintf(stderr, "Error allocating memory to file in getFileName()\n");
    exit(EXIT_FAILURE);
  }

  sscanf(msg, "GET %s HTTP/1.1", file);

  char *base;
  if ((base = malloc(sizeof(char) * (strlen(file) + 18))) == NULL) {
    fprintf(stderr, "Error allocating memory to base in getFileName()\n");
    exit(EXIT_FAILURE);
  }

  char *ph = "public_html";

  strcpy(base, ph);

  strcat(base, file);

  free(file);

  return base;
}

httpRequest parseRequest(char *msg) {
  httpRequest ret;

  char *filename;

  if ((filename = malloc(sizeof(char) * strlen(msg))) == NULL) {
    fprintf(stderr, "Error allocating memory to filename in parseRequest()\n");
    exit(EXIT_FAILURE);
  }

  filename = getFileName(msg);

  char *badstring = "..";
  char *test = strstr(filename, badstring);

  int test2 = strcmp(filename, "public_html/");

  FILE *exists = fopen(filename, "r");

  if (test != NULL) {
    ret.returncode = 400;
    ret.filename = "400.html";
  }

  else if (test2 == 0) {
    ret.returncode = 200;
    ret.filename = "public_html/index.html";
  }

  else if (exists != NULL) {
    ret.returncode = 200;
    ret.filename = filename;

    fclose(exists);
  }

  else {
    ret.returncode = 404;
    ret.filename = "404.html";
  }

  return ret;
}

int printFile(int fd, char *filename) {
  FILE *read;
  if ((read = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Error opening file in printFile()\n");
    exit(EXIT_FAILURE);
  }

  int totalsize;
  struct stat st;
  stat(filename, &st);
  totalsize = st.st_size;

  size_t size = 1;

  char *temp;
  if ((temp = malloc(sizeof(char) * size)) == NULL) {
    fprintf(stderr, "Error allocating memory to temp in printFile()\n");
    exit(EXIT_FAILURE);
  }

  int end;

  while ((end = getline(&temp, &size, read)) > 0) {
    sendMessage(fd, temp);
  }

  sendMessage(fd, "\n");

  free(temp);

  return totalsize;
}

void cleanup(int sig) {
  printf("Cleaning up connections and exiting.\n");

  if (close(list_s) < 0) {
    fprintf(stderr, "Error calling close()\n");
    exit(EXIT_FAILURE);
  }

  shm_unlink("/sharedmem");

  exit(EXIT_SUCCESS);
}

int printHeader(int fd, int returncode) {
  switch (returncode) {
    case 200:
      sendMessage(fd, header200);
      return strlen(header200);
      break;

    case 400:
      sendMessage(fd, header400);
      return strlen(header400);
      break;

    case 404:
      sendMessage(fd, header404);
      return strlen(header404);
      break;
  }
}

int recordTotalBytes(int bytes_sent, sharedVariables *mempointer) {
  pthread_mutex_lock(&(*mempointer).mutexlock);

  (*mempointer).totalbytes += bytes_sent;

  pthread_mutex_unlock(&(*mempointer).mutexlock);

  return (*mempointer).totalbytes;
}

int main(int argc, char *argv[]) {
  int conn_s;
  short int port = PORT;
  struct sockaddr_in servaddr;

  (void)signal(SIGINT, cleanup);

  if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "Error creating listening socket.\n");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(list_s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    fprintf(stderr, "Error calling bind()\n");
    exit(EXIT_FAILURE);
  }

  if ((listen(list_s, 10)) == -1) {
    fprintf(stderr, "Error Listening\n");
    exit(EXIT_FAILURE);
  }

  shm_unlink("/sharedmem");

  int sharedmem;

  if ((sharedmem = shm_open("/sharedmem", O_RDWR | O_CREAT | O_EXCL,
                            S_IRUSR | S_IWUSR)) == -1) {
    fprintf(stderr, "Error opening sharedmem in main() errno is: %s ",
            strerror(errno));
    exit(EXIT_FAILURE);
  }

  ftruncate(sharedmem, sizeof(sharedVariables));

  sharedVariables *mempointer;

  mempointer = mmap(NULL, sizeof(sharedVariables), PROT_READ | PROT_WRITE,
                    MAP_SHARED, sharedmem, 0);

  if (mempointer == MAP_FAILED) {
    fprintf(stderr,
            "Error setting shared memory for sharedVariables in "
            "recordTotalBytes() error is %d \n ",
            errno);
    exit(EXIT_FAILURE);
  }

  pthread_mutex_init(&(*mempointer).mutexlock, NULL);

  (*mempointer).totalbytes = 0;

  int addr_size = sizeof(servaddr);

  int headersize;
  int pagesize;
  int totaldata;

  int children = 0;

  pid_t pid;

  while (1) {
    if (children <= 10) {
      pid = fork();
      children++;
    }

    if (pid == -1) {
      fprintf(stderr, "can't fork, error %d\n", errno);
      exit(1);
    }

    if (pid == 0) {
      while (1) {
        conn_s = accept(list_s, (struct sockaddr *)&servaddr, &addr_size);

        if (conn_s == -1) {
          fprintf(stderr, "Error accepting connection \n");
          exit(1);
        }

        char *header = getMessage(conn_s);

        httpRequest details = parseRequest(header);

        free(header);

        headersize = printHeader(conn_s, details.returncode);

        pagesize = printFile(conn_s, details.filename);

        totaldata = recordTotalBytes(headersize + pagesize, mempointer);

        printf(
            "Process %d served a request of %d bytes. Total bytes sent %d  \n",
            getpid(), headersize + pagesize, totaldata);

        close(conn_s);
      }
    }
  }

  return EXIT_SUCCESS;
}
