#include "bootstrapping_utils.h"
#include <cstdio>
#include <cstring>
extern "C" {
#include <stdlib.h>
}
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


#define COPY_BUFFER_SIZE 1024

void copy_file(char *src_path, char *dst_path)
{
  char buf[BUFSIZ];
  size_t size;

  FILE* source = fopen(src_path, "rb");
  FILE* dest = fopen(dst_path, "wb");

  while ((size = fread(buf, 1, BUFSIZ, source))) {
    fwrite(buf, 1, size, dest);
  }

  fclose(source);
  fclose(dest);
}

int is_dir(char *path) {
  struct stat s;
  return stat(path, &s) == 0 && s.st_mode & S_IFDIR ? 1 : 0;
}

// TODO/FIXME wasteful
int is_file(char *path) {
  struct stat s;
  return stat(path, &s) == 0 && s.st_mode & S_IFREG ? 1 : 0;
}

char *concatenate_path(char *dir, char *name)
{
  char buffer[COPY_BUFFER_SIZE];
  strncpy(buffer, dir, COPY_BUFFER_SIZE);
  strncat(buffer, "/", COPY_BUFFER_SIZE);
  strncat(buffer, name, COPY_BUFFER_SIZE);
  return strdup(buffer);
}

void copy_tree(char *element, char *src_dir, char *dst_dir)
{
  char *src_path = concatenate_path(src_dir, element);
  char *dst_path = concatenate_path(dst_dir, element);
  if(is_file(src_path)) {
    copy_file(src_path, dst_path);
  } else {
    // Create the directory
    struct stat src_stat;
    stat(src_path, &src_stat);
    mkdir(dst_path, src_stat.st_mode);
    // Safely assuming what's not a file is a directory
    fprintf(stderr, "The path to open is: %s\n", src_path);
    DIR *dir = opendir(src_path);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
      if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        fprintf(stderr, "Found: %s\n", entry->d_name);
        copy_tree(entry->d_name, src_path, dst_path);
      }
    }
    closedir(dir);
    
    // List files
    
  }
  free(dst_path);
  free(src_path);
}
