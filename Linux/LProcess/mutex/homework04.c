#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int status = 0;
void *thread_func_t1(void *arg)
{
    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock t1 A");

    printf("A-->");

    ret = pthread_cond_signal(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal");

    status = 1;

    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock t1 A");

    ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock t1 C");

    while (2 != status)
    {
        ret = pthread_cond_wait(&cond, &lock);
        THREAD_ERROR_CHECK(ret, "pthread_cond_wait B");
    }

    printf("C\n");

    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock t1 C");

    pthread_exit(NULL);
}

void *thread_func_t2(void *arg)
{
    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock t2 B");
    while (1 != status)
    {
        ret = pthread_cond_wait(&cond, &lock);
        THREAD_ERROR_CHECK(ret, "pthread_cond_wait A");
    }
    printf("B-->");
    status = 2;

    ret = pthread_cond_signal(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal_B");

    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock t2 B");

    pthread_exit(NULL);
}

/*Usage: */
int main(int argc, char *argv[])
{
    int ret = pthread_mutex_init(&lock, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    ret = pthread_cond_init(&cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init A");

    pthread_t thread_t1, thread_t2;

    ret = pthread_create(&thread_t1, NULL, thread_func_t1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create t1");

    ret = pthread_create(&thread_t2, NULL, thread_func_t2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create t2");

    ret = pthread_join(thread_t1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join t1");

    ret = pthread_join(thread_t2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join t2");

    ret = pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret, "mutex destroy");

    ret = pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy condA");

    return 0;
}
