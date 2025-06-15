#include "../include/menu.h"
#include "../include/userdata.h"
#include "../include/forum.h"
#include "../include/formatting.h"

using namespace std;

int main()
{
    userList userList;
    user_create_list(userList);
    user_load_sample(userList);
    userAdr usrData = NULL;
    postList postList;
    post_create_list(postList);

    menu_welcome(userList, postList, usrData);
    return 0;
}
