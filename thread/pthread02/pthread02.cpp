/*
 * pthread02.cpp
 *
 *  Created on: 2014��10��27��
 *      Author: mengpl
 */


#include "pthread.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node
{
     int n_number;
     struct node *n_next;
} *head = NULL;

/*[thread_func]*/

static void cleanup_handler(void *arg)
{
     log_info("Cleanup handler of second thread./n");
     free(arg);
     (void)pthread_mutex_unlock(&mtx);
}

static void *thread_func(void *arg)
{
     struct node *p = NULL;
     pthread_cleanup_push(cleanup_handler, p);
     while (1)
     {
         //���mutex��Ҫ��������֤pthread_cond_wait�Ĳ�����
         pthread_mutex_lock(&mtx);
         while (head == NULL)
         {
         //���whileҪ�ر�˵��һ�£�����pthread_cond_wait���ܺ����ƣ�Ϊ��
         //����Ҫ��һ��while (head == NULL)�أ���Ϊpthread_cond_wait�����
         //�̿��ܻᱻ���⻽�ѣ�������ʱ��head != NULL������������Ҫ�������
         //���ʱ��Ӧ�����̼߳�������pthread_cond_wait
         // pthread_cond_wait���Ƚ��֮ǰ��pthread_mutex_lock������mtx��
         //Ȼ�������ڵȴ����������ߣ�ֱ���ٴα����ѣ������������ǵȴ�����������
         //�������ѣ����Ѻ󣬸ý��̻���������pthread_mutex_lock(&mtx);���ٶ�ȡ��Դ
         //����������ǱȽ������/*block-->unlock-->wait() return-->lock*/

         pthread_cond_wait(&cond, &mtx);
         p = head;
         head = head->n_next;
         log_info("Got %d from front of queue/n", p->n_number);
         free(p);
          }
          pthread_mutex_unlock(&mtx); //�ٽ������ݲ�����ϣ��ͷŻ�����
     }
     pthread_cleanup_pop(0);
     return NULL;
}

int main(void)
{

     pthread_t tid;
     int i;
     struct node *p;
     //���̻߳�һֱ�ȴ���Դ�����������ߺ������ߣ���������������߿����Ƕ�������ߣ���
     //������֧����ͨ�ĵ��������ߣ����ģ����Ȼ�򵥣����Ǻ�ǿ��
     pthread_create(&tid, NULL, thread_func, NULL);
     sleep(1);
     for (i = 0; i < 10; i++)
     {
         p = (struct node*)malloc(sizeof(struct node));
         p->n_number = i;
         pthread_mutex_lock(&mtx); //��Ҫ����head����ٽ���Դ���ȼ�����
         p->n_next = head;
         head = p;
         pthread_cond_signal(&cond);
         pthread_mutex_unlock(&mtx); //����
         sleep(1);
     }

     log_info("thread 1 wanna end the line.So cancel thread 2./n");
     //����pthread_cancel����һ������˵�������Ǵ��ⲿ��ֹ���̣߳����̻߳��������ȡ���㣬�˳�
     //�̣߳��������ǵĴ���������ȡ����϶�����pthread_cond_wait()�ˡ�
     pthread_cancel(tid);
     pthread_join(tid, NULL);
     log_info("All done -- exiting/n");
     return 0;
}




