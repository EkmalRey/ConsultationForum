#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>
#include <cstdlib>

#include "userdata.h"
#include "forum.h"
#include "formatting.h"

using namespace std;

void clearScreen();
void menu_welcome(userList &Luser, postList &Lpost, userAdr &usrData);
void menu_signIn(userList &Luser, postList &Lpost, userAdr &usrData);
void menu_signUp(userList &Luser, postList &Lpost, userAdr &usrData);
void menu_main(userList &Luser, postList &Lpost, userAdr &usrData, string genre, int n);
void menu_detail(userList &Luser, postList &Lpost, userAdr &usrData, postAdr Ppost, string tag, int n);
void menu_createPost(userList &Luser, postList &Lpost, userAdr &usrData);
void menu_replyPost(userList &Luser, replyList &Lreply, userAdr &usrData);
void menu_search(userList &Luser, postList &Lpost, userAdr &usrData, string tag);
void menu_deleteReply(userList &Luser, postList &Lpost, userAdr &usrData, postAdr Ppost);
void menu_profile(userList &Luser, postList &Lpost, userAdr &usrData);
void menu_pemenuhanSpesifikasi(userList Luser, postList Lpost, userAdr usrData);
void menu_debug(userList &Luser, postList &Lpost, userAdr &usrData);
#endif // MENU_H
