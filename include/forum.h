#ifndef FORUM_H
#define FORUM_H

#include <iostream>
#include "userdata.h"
#include "formatting.h"

using namespace std;

typedef struct post *postAdr;
typedef struct reply *replyAdr;


struct content{
    string text;
    userAdr OP;
};

struct replyList{
    replyAdr first, last;
};
struct reply{
    content isi;
    replyAdr next;
};

struct postList{
    postAdr first;
};
struct post{
    content isi;
    string title, tag;
    replyList replies;
    postAdr next;
};



void post_create_list(postList &L);
postAdr post_create_element(content x, string title, string tag);
void post_load_sample(postList &L, userList Luser);
bool post_empty(postList &L);
void post_insert(postList &L, postAdr P);
void post_print(postList &L, int width, int n, string tag, postAdr (&postArr)[5]);
void post_delete_first(postList &L);
void post_delete_after(postList &L, postAdr &prec);
void post_delete(postList &L, postAdr &P);

void reply_create_list(replyList &L);
replyAdr reply_create_element(content x);
void reply_load_sample(replyList &L);
bool reply_empty(replyList &L);
void reply_insert(replyList &L, replyAdr R);
void reply_delete_first(replyList &L);
void reply_delete_after(replyList &L, replyAdr prec);
void reply_delete(replyList &L, userAdr usrData, int pos, string user);
int post_count_threads(postList L, string tag);
int reply_count_threads(replyList &Lreply);
#endif // FORUM_H
