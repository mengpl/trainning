 #include <iostream> 
 #include <pthread.h> 
 #include <string.h> 
using namespace std;

 static pthread_mutex_t m_cMutex = PTHREAD_MUTEX_INITIALIZER; 

 static int __number = 0;  
 static pthread_t __thread_id = 0;

void * timeout_monitor(void * args)
{
    cout << "\n==[NOTIFICATION_FILE]==> ====    ********timeout_monitor begin ******** ========" << endl;
    
    // sleep(5);
    pthread_mutex_lock(&m_cMutex);
    __number++;
    cout << "\n ====    ********thread __number ******** ========" << __number << endl;
    pthread_mutex_unlock(&m_cMutex);

    cout << "\n==[NOTIFICATION_FILE]==> ====    ********timeout_monitor end ******** ========" << endl;
}

 void start_daemon_thread()
 {
    cout << "\n==[NOTIFICATION_FILE]==> ====    ********before __thread_id = %lu******** ========" << __thread_id <<endl;

    if(__thread_id <= 0)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&__thread_id,NULL,timeout_monitor,NULL);
    }
    cout << "\n==[NOTIFICATION_FILE]==> ====    ********after __thread_id = %lu******** ========" << __thread_id <<endl;
 }

void add_number()
{
    pthread_mutex_t m_cMutex;
    pthread_mutex_lock(&m_cMutex);
    __number++;
    cout << "\n ====    ********main __number ******** ========" << __number << endl;
    pthread_mutex_unlock(&m_cMutex);

}

int main() 
{ 
    // start a daemon thread
    cout << "\n ====    ********start_daemon_thread******** ========" << endl;
    start_daemon_thread();

    add_number();

    sleep(5);

    return 0; 
}