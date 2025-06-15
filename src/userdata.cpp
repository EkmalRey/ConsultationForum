#include <iostream>
#include "../include/userdata.h"

void user_create_list(userList &L){
    L.first = NULL;
    L.last = NULL;
}

userAdr user_create_element(userInfo x){
    userAdr P = new userElement;
    P->info = x;
    P->next = NULL;
    return P;
}

void user_load_sample(userList &L){
    userInfo x;
    userAdr P;

    for (int i=1;i<=5;i++){
        string a = std::to_string(i);
        x.username = "user"+ a;
        x.password = a;
        x.name = "User " + a;
        if (user_empty(L)){
            x.id = 1001;
        }else{
            x.id = L.first->info.id + 1;
        }
        x.age = 20+i;
        x.roles = 0;
        P = user_create_element(x);
        user_insert(L, P);
    }

    for (int i=1;i<=5;i++){
        string a = std::to_string(i);
        x.username = "doctor"+ a;
        x.password = a;
        x.name = "Doctor " + a;
        if (user_empty(L)){
            x.id = 1001;
        }else{
            x.id = L.first->info.id + 1;
        }
        x.age = 30+i;
        x.roles = 1;
        P = user_create_element(x);
        user_insert(L, P);
    }
}

bool user_empty(userList &L){
    return (L.first == NULL && L.last == NULL);
}

void user_insert(userList &L, userAdr P){
    if (user_empty(L)){
        L.first = P;
        L.last = P;
        P->next = P;
    }else{
        L.last->next = P;
        L.last = P;
        P->next = L.first;
    }
}

userAdr user_search_username(userList L, string username){
    userAdr P = L.first;
    do{
        if (P->info.username == username){
            return P;
        }
        P = P->next;
    } while (P != L.first);
    return NULL;
}
