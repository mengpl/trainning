#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void sizoffunc(char str[100])
{
    printf("******sizoffunc***********\n");
    printf("sizeof(str) = %d\n",sizeof(str));
}

void test_sizeof()
{
    // test sizeof
    printf("*******sizeof test********** \n");
    int i;
    int a[100];
    int * p;
    char str[] = "Hello";
    char *pStr = str;

    void *pM = malloc(100);

    printf("sizeof(i) = %d\n",sizeof(i)); // 32位机器和64位机int都是占用4个字节
    printf("sizeof(a) = %d\n",sizeof(a)); // a代表数组大小 4 * 100 = 400
    printf("sizeof(a[100] = %d\n",sizeof(a[100])); // 只是数组的第101个，虽然没有值，但是占位是有的，4个字节
    printf("sizeof(p) = %d\n",sizeof(p)); // 指针32位4 ,64位是8个字节
    printf("sizeof(&a) = %d\n",sizeof(&a)); // 引用也是指针 32位是4,64位是8个字节
    printf("sizeof(a[0]) = %d\n",sizeof(a[0])); // 和a[100]一样
    printf("sizeof(void*) = %d\n",sizeof(void*)); // 指针，64位占位是8个字节
    printf("sizeof(str) = %d\n",sizeof(str)); // str代表整个字符数组，答案是6，结尾是'\0'
    printf("sizoof(pStr) = %d\n",sizeof(pStr)); //指针，32位是4,64位是8个字节
    printf("sizoof(pM) = %d\n",sizeof(pM)); // 还是指针，32位4,64位是8个字节

    char strTest[100];
    sizoffunc(strTest); // 引用传递，32位是4,64位是8个字节
}

void test_strlen()
{
    printf("*******test_strlen test********** \n");
    char c1[10] = {'m','o','b','i','l'};
    char c2[20] = {'A','N','S','I','\0','C','+','+'};
    char c3[6] = {'I','S','O','C','+','+'};

    printf("strlen(c1) = %d\n",strlen(c1)); // 5
    printf("strlen(c2) = %d\n",strlen(c2)); // 4
    printf("strlen(c3) = %d\n",strlen(c3)); // 6

    printf("c2 = %s\n",c2); // AISI

    printf("c2[8] = %d\n",c2[8]); // 0

}

void get_memory1(char * p)
{
    p = (char *)malloc(100);
}

char * get_memory2()
{
    char p[] = "hello world";
    fprintf(stderr, "p = %s\n", p);
    return p;
}

void get_memory3(char ** p,int num)
{
    *p = (char *)malloc(num);
}

void test_memory()
{
    printf("*******test_memory test********** \n");
    // char *str1 = NULL;
    // get_memory1(str1);
    // strcpy(str1,"hello world");
    // printf("str1 = %s\n",str1); // str1没被赋值，core在strcpy这行

    // char *str2 = NULL;
    // str2 = get_memory2();
    // printf("str2 = %s\n",str2);  //p是个临时变量，出了函数被释放，得到的p的指针，已经不是执行原来的位置了，所以是乱码


    // char *str3 = NULL;
    // get_memory3(&str3,100);
    // strcpy(str3,"hello world");
    // printf("str3 = %s\n",str3); // 正确打印出hello world，有内存泄漏

    char * str4 = (char *)malloc(100);
    strcpy(str4,"hello world");
    free(str4);
    if(str4 != NULL)
    {
        strcpy(str4,"hello world");
        printf("str4 = %s\n", str4); // 正确打印出了 hello world,不可取，str4是野指针
    }

}

void test_trans()
{
    using namespace std;
    printf("*******test_trans test********** \n");
    double d = 100.25;

    int x = d;

    int * pInt = (int *)&d;

    cout << x << endl; // 100 直接转换
    cout << *pInt << endl; // 转换了地址，值不是100
}

char * strcpy(char * strDest,const char * strSrc)
{
    // judget NULL
    if(NULL == strSrc || NULL == strDest)
    {
        return NULL;
    }

    // 
    if(strSrc == strDest)
    {
        return strDest;
    }

    char * tempStr = strDest;
    while((*strDest++ = *strSrc++)!= '\0')
        NULL;

    return tempStr;
}

void test_strcpy()
{
    char strDest[10];
    char strSrc[10] = {'n','i','h','a','o'};

    printf("strSrc = %s\n", strSrc);
    strcpy(strDest,strSrc);

    printf("strDest = %s\n", strDest);
}

void test_bubbleSort()
{
    // int a[10] = {2,1,4,6,5,3,8,15,7,11};
    int a[10] = {3,2,4,6,5,1,8,15,7,11};

    /**
     * 1.两两比较，把最大的值交换到最后
     * 2.每次外层循环，可以排好一个数字，内层循环可以少一些循环
     * 3.外层循环，可以通过判断内层循环是否有数据交换，来判断是否排好了序列
     */
    int temp = 0;
    int flag;
    for(int j = 0; j < 10 ; ++j)
    {
        flag = 0;
        for(int i = 0; i < (9-j) ; ++i)
        {
            if(a[i] > a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                flag = 1;
            }
        }

        for(int i = 0; i < 10; ++i)
        {
            printf("%d ",a[i]);
            if(i == 9)
                printf("\n");
        }
        if(0 == flag)
            break;
    } 
}

void test_chose()
{
    /*
    1.先取出一个数字，遍历整个数组，比较，得到最大值的位置
    2.这个数字和最大值交换
     */
    int a[10] = {2,1,4,6,5,3,8,15,6,11};
    int temp;
    int index = 0;
    int chose;

    for(int i = 0; i < 9 ; ++i)
    {
        chose = a[i];
        for(int j = i+1; j < 10; ++j)
        {            
            if(chose > a[j])
            {
                index = j;
                chose = a[j];
            }
        }

        if(chose != a[i])
        {
            temp = a[i];
            a[i] = a[index];
            a[index] = temp;
        }

        
        for(int i = 0; i < 10; ++i)
        {
            printf("%d ",a[i]);
            if(i == 9)
                printf("n");
        }

    }
}

struct CNode
{
    CNode * next;
    CNode * pre;
    int value;
};

CNode * cross_link(CNode *pHead1,CNode* pHead2)
{

    if(pHead1 == NULL || pHead2 == NULL)
    {
        return NULL;
    }

    CNode * p1 = pHead1;
    CNode * p2 = pHead2;

    int count1 = 0;
    while(p1->next != NULL)
    {
        p1 = p1->next;
        count1++;
    }

    int count2 = 0;
    while(p2->next != NULL)
    {
        p2 = p2->next;
        count2++;
    }

    if(p1 != p2)
    {
        //尾节点不同，说明一定不想交
        return NULL;
    }

    p1 = pHead1;
    p2 = pHead2;

    if(count1 > count2)
    {

        // 把长的追一段
        for(int i = 0; i < count1-count2; ++i)
        {
            p1 = p1->next; 
        }
    }
    else
    {
        // 把长的追一段
        for(int i = 0; i < count2-count1; ++i)
        {
            p2 = p2->next; 
        }
    }

    while(p1->next != NULL && p2->next != NULL)
    {
        if(p1 == p2)
        {
            return p1;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    return NULL;
}

bool cycle_link(CNode * pHead)
{
    CNode * pSlow = pHead;
    CNode * pFast = pHead;

    while(NULL != pFast && NULL != pFast->next)
    {
        pSlow = pSlow->next;
        pFast = pFast->next->next;

        if(pSlow == pFast)
            return true;
    }

    return false;
}

void test_link()
{
    // 判断两个链表是否有焦点

    CNode * pLink1 = new CNode();
    pLink1->value = 100;
    pLink1->pre = NULL;


    CNode * pCur = new CNode();
    pLink1->next = pCur;
    pCur->pre = pLink1;

    for(int i = 0;i < 10; ++i)
    {
        pCur->value = i;
        CNode * pNext = new CNode();
        pCur->next = pNext;
        pNext->pre = pCur;

        pCur = pNext;     
    }

    CNode * pIter = new CNode();
    pIter = pLink1;
    while(pIter->next != NULL)
    {
        printf("%d ",pIter->value);
        pIter = pIter->next;
    }
    printf("\n");

    CNode * pLink2 = new CNode;
    pLink2->pre = NULL;
    pLink2->value = 80;
    pLink2->next = pLink1->next;
    pLink2->next->pre = pLink2;

    CNode * pLink = cross_link(pLink1,pLink2);

    if(NULL != pLink)
        printf("pLink->value = %d\n", pLink->value);

    bool bCycle = cycle_link(pLink1);

    if(bCycle)
        printf("this link is a cycle link! \n");
    else
        printf("this link is not a cycle link!\n");

    pIter->next = pLink1;

    bCycle = cycle_link(pLink1);

    if(bCycle)
        printf("this link is a cycle link! \n");
    else
        printf("this link is not a cycle link!\n");

}

// void Qsort(int a[], int low, int high)
// {
//     if(low >= high)
//     {
//         return;
//     }
//     int first = low;
//     int last = high;
//     int key = a[first];/*用字表的第一个记录作为枢轴*/
 
//     while(first < last)
//     {
//         while(first < last && a[last] >= key)
//         {
//             --last;
//         }
 
//         a[first] = a[last];/*将比第一个小的移到低端*/
 
//         while(first < last && a[first] <= key)
//         {
//             ++first;
//         }
         
//         a[last] = a[first];    
//         /*将比第一个大的移到高端*/
//     }
//     a[first] = key;/*枢轴记录到位*/
//     Qsort(a, low, first-1);
//     Qsort(a, first+1, high);
// }

void test_fast()
{
    /*
    1.先取一个数，把小的移到左边，大的移到右边
    2.递归下
     */
    // int a[10] = {2,1,4,6,5,3,8,15,6,11};
    
    // int guard = a[0];
    // for(int i = 1; j = 9; i < 9 ; ++i)
    // {
    //     if(a[i] > guard)
    //     {
            
    //     }

    //     for(int i = 0; i < 10; ++i)
    //     {
    //         printf("%d ",a[i]);
    //         if(i == 9)
    //             printf("n");
    //     }

    // }
}

struct Student 
{
    int num;
    char name[20];
    float score;
};

/*//使用二进制写入
void write_to_binary_file()
{
    struct Student stdu;
    stdu.num = 111;
    sprintf(stdu.name,20,"%s","shine");
    stdu.score = 80.0f;
    fstream binary_file("test1.dat",ios::out|ios::binary|ios::app); //此处省略文件是否打开失败的判断
    binary_file.write((char *)&stdu,sizeof(struct Student));//二进制写入的方式
    binary_file.close();
} 
//文本格式写入
void write_to_text_file()
{
    struct Student stdu;
    stdu.num = 111;
    sprintf(stdu.name,20,"%s","shine");
    stdu.score = 80.0f;
    FILE *fp = fopen("test2.dat","a+");   //此处省略文件是否打开失败的判断
    fprintf(fp,"%d%s%f",stdu.num,stdu.name,stdu.score); //将数据转换成字符串（字符串的格式可以自己定义）
    fclose(fp);
} 

void write_test()
{
    write_to_binary_file();
    write_to_text_file();
}
*/
int main(int argc,char** argv)
{
    
    // test_sizeof();

    // test_strlen();

    // test_memory();
    
    // test_trans();
    
    // test_class();
    
    // test_strcpy();
    
    // test_bubbleSort();
    
    // test_chose();
    
    // test_link();

    return 0;
}