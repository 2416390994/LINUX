#pragma once
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
static int CreateShm()
{
  key_t key = ftok(".",0x2);
  if(key == -1)
  {
    perror("ftok");
    return -1;
  }
  int ret = shmget(key,1024,IPC_CREAT | 0666);
  if(ret < 0)
  {
    perror("shmget");
    return 1;

  }
  return ret;                                                                                                                      }

