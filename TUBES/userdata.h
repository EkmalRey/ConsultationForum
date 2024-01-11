#ifndef USERDATA_H
#define USERDATA_H

using namespace std;

typedef struct userElement *userAdr;

struct userInfo{
    string username, password, name;
    int id, age, roles;
};

struct userElement{
    userInfo info;
    userAdr next;

};

struct userList{
    userAdr first;
    userAdr last;
};

void user_create_list(userList &L);
userAdr user_create_element(userInfo x);
void user_load_sample(userList &L);
bool user_empty(userList &L);
void user_insert(userList &L, userAdr P);
userAdr user_search_username(userList L, string username);
#endif // USERDATA_H
