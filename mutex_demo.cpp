#include <bits/stdc++.h>
#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t locked;
int g_var = 0;

void *func_without_lock(void *var){
    g_var = 1;
    int *id = (int *)var;
    cout<<"Thread id: "<<*id<<endl;
    for (int i = 0; i<6; i++){
        cout<<"Global var value is "<<g_var++<<endl;
        sleep(3);
    }
    cout<<"Finished ..."<<endl;
    return nullptr;
}

void *func_with_lock(void *var){
    pthread_mutex_lock(&locked);
    g_var = 1;
    int *id = (int *)var;
    cout<<"Thread id: "<<*id<<endl;
    for (int i = 0; i<6; i++){
        cout<<"Global var value is "<<g_var++<<endl;
        sleep(2);
    }
    cout<<"Finished ..."<<endl;
    pthread_mutex_unlock(&locked);
    return nullptr;
}

int main(){
    cout<<"Main Thread begins.. "<<endl;
    pthread_t t_id3, t_id4;
    g_var = 0;
    cout<<"#######################################################################"<<endl;
    cout<<"                       Without mutex func: "<<endl;
    cout<<"#######################################################################"<<endl;
    pthread_create(&t_id3, NULL, func_without_lock, (void *)&t_id3);
    pthread_create(&t_id4, NULL, func_without_lock, (void *)&t_id4);
    pthread_join(t_id3, NULL); //blocks calling thread until thread with identifier equal to 1st arg terminates
    pthread_join(t_id4, NULL);

    pthread_t t_id1, t_id2;
    if(pthread_mutex_init(&locked, NULL) != 0){
        cout<<"Mutex creation failed "<<endl;
        exit(1);
    }
    g_var = 0;
    cout<<"#######################################################################"<<endl;
    cout<<"                          With mutex func: "<<endl;
    cout<<"#######################################################################"<<endl;
    pthread_create(&t_id1, NULL, func_with_lock, (void *)&t_id1);
    pthread_create(&t_id2, NULL, func_with_lock, (void *)&t_id2);
    pthread_join(t_id1, NULL); //blocks calling thread until thread with identifier equal to 1st arg terminates
    pthread_join(t_id2, NULL);
    cout<<"Main thread ends.. "<<endl;   
    //pthread_exit(NULL);   //Makes sure that main terminates after terminating all threads
    return 0;
}



/* Output: 
    Main Thread begins..
    #######################################################################
                        Without mutex func:
    #######################################################################
    Thread id: Thread id: 3
    Global var value is 1
    2
    Global var value is 2
    Global var value is Global var value is 4
    3
    Global var value is Global var value is 6
    5
    Global var value is 7
    Global var value is 8
    Global var value is 9 
    Global var value is 10
    Global var value is 11
    Global var value is 12
    Finished ...
    Finished ...
    #######################################################################
                            With mutex func:
    #######################################################################
    Thread id: 4
    Global var value is 1
    Global var value is 2
    Global var value is 3
    Global var value is 4
    Global var value is 5
    Global var value is 6
    Finished ...
    Thread id: 5
    Global var value is 1
    Global var value is 2
    Global var value is 3
    Global var value is 4
    Global var value is 5
    Global var value is 6
    Finished ...
    Main thread ends..
*/