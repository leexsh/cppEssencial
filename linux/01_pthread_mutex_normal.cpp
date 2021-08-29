#include "errno.h"
#include "pthread.h"
#include "stdio.h"
#include "unistd.h"

pthread_mutex_t mymutex;
int resourceNo = 0;

void *work_thread(void *param) {
  pthread_t threadID = pthread_self();
  printf("thread start, threadId is :%d\n", threadID);
  while (true) {
    pthread_mutex_lock(&mymutex);
    printf("Mutex lock, rescourceNo: %d, threadId: %d\n", resourceNo, threadID);
    resourceNo++;
    printf("Mutex unlock, rescourceNo: %d, threadId: %d\n", resourceNo,
           threadID);
    pthread_mutex_unlock(&mymutex);
    sleep(1);
  }
  return nullptr;
}

int main() {
  pthread_mutexattr_t mutex_attr;
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
  pthread_mutex_init(&mymutex, &mutex_attr);

  pthread_t threadID[5];
  for (int i = 0; i < 5; ++i) {
    pthread_create(&threadID[i], NULL, work_thread, NULL);
  }

  for (int i = 0; i < 5; ++i) {
    pthread_join(threadID[i], NULL);
  }

  pthread_mutex_destroy(&mymutex);
  pthread_mutexattr_destroy(&mutex_attr);

  return 0;
}