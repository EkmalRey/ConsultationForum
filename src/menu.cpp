#include "../include/menu.h"

using namespace std;
int terminalWidth = 50;
int maxTerminalWidth = 120;

void menu_welcome(userList &Luser, postList &Lpost, userAdr &usrData){
    clearScreen();
    int tries = 0;
    char choice;

    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Welcome To HaloDek!");
    fillLines(terminalWidth, '=');

    if (usrData == NULL){
        cout << " 1. Sign In"<< endl;
        cout << " 2. Sign Up"<< endl;
        cout << " 3. Continue AS Guest"<< endl;
        cout << " 0. Exit" << endl;

        bool run = true;
        while (run){
            cout << " Input : "; cin >> choice;
            switch (choice){
                case '0':
                    cout << " Quitting Program..." << endl;
                    exit(0);
                case '1':
                    run = false;
                    menu_signIn(Luser, Lpost, usrData);
                    break;
                case '2':
                    run = false;
                    menu_signUp(Luser, Lpost, usrData);
                    break;
                case '3':
                    run = false;
                    menu_main(Luser, Lpost, usrData, "general", 0);
                    break;
                default:
                    tries++;
                    cout << " Invalid input, Try Again! " << tries << " out of 10 tries!" << endl;
                    if (tries == 10){
                        cout << " Maximum tries reached! Quitting Program..." << endl;
                        run = false;
                        exit(0);
                    }
                    break;
            }
        }
    } else if (usrData == user_search_username(Luser, "doctor5")) {
        cout << "DEBUG MODE" << endl;
        pressAnyKeyToContinue();
        menu_debug(Luser, Lpost, usrData);
    } else {
        cout << " 1. Sign Out"<< endl;
        cout << " 2. See Profile"<< endl;
        cout << " 3. Go To Forum" << endl;
        cout << " 4. Find User" << endl;
        cout << " 5. PEMENUHAN SPESIFIKASI (UNTUK TUBES)" << endl;
        cout << " 0. Exit" << endl;

        bool run = true;
        while (run){
            cout << " Input : "; cin >> choice;
            switch (choice){
                case '0':
                    cout << " Quitting Program..." << endl;
                    exit(0);
                case '1':
                    run = false;
                    usrData = NULL;
                    cout << " Successfully Signed Out!" << endl;
                    menu_welcome(Luser, Lpost, usrData);
                    break;
                case '2':
                    run = false;
                    menu_profile(Luser, Lpost, usrData);
                    break;
                case '3':
                    run = false;
                    menu_main(Luser, Lpost, usrData, "general", 0);
                    break;
                case '4': {
                    run = false;
                    string username;
                    userAdr U;

                    cout << " Username to find : "; cin >> username;
                    U = user_search_username(Luser, username);
                    clearScreen();
                    if (U != NULL){
                        menu_profile(Luser, Lpost, U);
                    } else {
                        fillLines(terminalWidth, '=');
                        headerCentre(terminalWidth, "404 USER NOT FOUND!");
                        fillLines(terminalWidth, '=');
                        pressAnyKeyToContinue();
                        menu_welcome(Luser, Lpost, usrData);
                    }
                    break;
                }
                case '5':
                    run = false;
                    menu_pemenuhanSpesifikasi(Luser, Lpost, usrData);
                    break;
                default:
                    tries++;
                    cout << " Invalid input, Try Again! " << tries << " out of 10 tries!" << endl;
                    if (tries == 10){
                        cout << " Maximum tries reached! Quitting Program..." << endl;
                        run = false;
                        exit(0);
                    }
                    break;
            }
        }
    }
}

void menu_signIn(userList &Luser, postList &Lpost, userAdr &usrData){
    string inputUsername, inputPassword;
    int tries = 0;
    userAdr adr;

    clearScreen();
    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Sign In");
    fillLines(terminalWidth, '=');

    while (true){
        cout << " Username : "; cin >> inputUsername;
        adr = user_search_username(Luser, inputUsername);
        if (adr != NULL){
            break;
        }else{
            cout << " Username Not Found! " << tries+1 << " out of 3 Attempts!" << endl;
            tries++;
            if (tries == 3){
                cout << " You have reached the max attempt!";
                pressAnyKeyToContinue();
                menu_welcome(Luser, Lpost, usrData);
                break;
            }
        }
    }

    tries = 0;
    while (true){
        cout << " Password : "; cin >> inputPassword;

        if (adr->info.password == inputPassword){
            cout << " Welcome Back, " << adr->info.name << "!" << endl;
            usrData = adr;
            pressAnyKeyToContinue();
            menu_main(Luser, Lpost, usrData, "general", 0);
        }else{
            cout << " Incorrect Password! " << tries+1 << " out of 3 Attempts!" << endl;
            tries++;
            if (tries == 3){
                cout << " You have reached the max attempt!";
                pressAnyKeyToContinue();
                menu_welcome(Luser, Lpost, usrData);
                break;
            }
        }
    }
}

void menu_signUp(userList &Luser, postList &Lpost, userAdr &usrData){
    userInfo x;
    userAdr P;
    string a;

    clearScreen();
    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Sign Up");
    fillLines(terminalWidth, '=');

    while (true){
        cout << " Create a Username : "; cin >> x.username;
        P = user_search_username(Luser, x.username);
        if (P != NULL){
            cout << " That username already Existed! Try another one!";
        }else{
            break;
        }
    }

    cout << " Create a Password : "; cin >> x.password;
    cin.ignore(1, '\n');
    x.name = inputParagraph(" What's your name : ");
    cout << " How old are you : "; cin >> x.age;
    cout << " Are you a doctor or patient (Please insert 'doctor' or 'patient') : "; cin >> a;
    if (a == "doctor" || a == "Doctor"){
        x.roles = 1;
    }else{
        x.roles = 0;
    }

    if (user_empty(Luser)){
        x.id = 1001;
    }else{
        x.id = Luser.first->info.id + 1;
    }

    P = user_create_element(x);
    user_insert(Luser, P);
    usrData = P;

    cout << " Successfully Signed Up! Welcome, " << x.name << "!" << endl;
    pressAnyKeyToContinue();

    menu_main(Luser, Lpost, usrData, "general", 0);
}

void menu_main(userList &Luser, postList &Lpost, userAdr &usrData, string tag, int n){
    bool stopProgram = false;
    do {
        clearScreen();
        int postTotal = 0;
        int tries = 0;
        char choice;
        postAdr postArr[5] = {NULL, NULL, NULL, NULL, NULL};

        fillLines(terminalWidth, '=');
        headerCentre(terminalWidth, "FORUM HALO DEK");
        fillLines(terminalWidth, '=');

        if (!post_empty(Lpost)){
            postTotal = post_count_threads(Lpost, tag);
            cout << " Showing " << n+1 << " - ";
            if (postTotal < n+5){
                cout << postTotal;
            }else{
                cout << n+5;
            }
            cout <<" Post out of " << postTotal << " : (Sorted by Newest)" << endl;
            fillLines(terminalWidth, '-');
            printTableMain(terminalWidth, "No", "Title", "Author");
            fillLines(terminalWidth, '-');
            post_print(Lpost, terminalWidth, n, tag, postArr);
            fillLines(terminalWidth, '-');
        } else {
            fillLines(terminalWidth, '-');
            printTableMain(terminalWidth, "No", "Title", "Author");
            fillLines(terminalWidth, '-');
            headerBorder(terminalWidth, "center", "THIS FORUM IS CURRENTLY EMPTY");
            fillLines(terminalWidth, '-');
            cout << " L. Load sample post" << endl;
        }

        if (n != 0){cout << " 6. Previous Page" << endl;}
        if (n+5 < postTotal){cout << " 7. Next Page" << endl;}
        cout << " 8. Create a post" << endl;
        cout << " 9. Search" << endl;
        cout << " 0. Back to main menu" << endl;

        bool run = true;
        while (run){
            cout << " Input : "; cin >> choice;
            switch (choice){
                case '0':
                    run = false;
                    stopProgram = true;
                    menu_welcome(Luser, Lpost, usrData);
                case '1':
                    run = false;
                    stopProgram = true;
                    menu_detail(Luser, Lpost, usrData, postArr[0], tag, n);
                    break;
                case '2':
                    run = false;
                    stopProgram = true;
                    menu_detail(Luser, Lpost, usrData, postArr[1], tag, n);
                    break;
                case '3':
                    run = false;
                    stopProgram = true;
                    menu_detail(Luser, Lpost, usrData, postArr[2], tag, n);
                    break;
                case '4':
                    run = false;
                    stopProgram = true;
                    menu_detail(Luser, Lpost, usrData, postArr[3], tag, n);
                    break;
                case '5':
                    run = false;
                    stopProgram = true;
                    menu_detail(Luser, Lpost, usrData, postArr[4], tag, n);
                    break;
                case '6':
                    run = false;
                    stopProgram = true;
                    menu_main(Luser, Lpost, usrData, tag, n-5);
                    break;
                case '7':
                    run = false;
                    stopProgram = true;
                    menu_main(Luser, Lpost, usrData, tag, n+5);
                    break;
                case '8':
                    run = false;
                    menu_createPost(Luser, Lpost, usrData);
                    break;
                case '9':
                    run = false;
                    stopProgram = true;
                    menu_search(Luser, Lpost, usrData, tag);
                    break;
                case 'L':
                case 'l':
                    run = false;
                    stopProgram = true;
                    post_load_sample(Lpost, Luser);
                    clearScreen();
                    cout << "SAMPLE POST LOADED" << endl;
                    pressAnyKeyToContinue();
                    menu_main(Luser, Lpost, usrData, tag, n);
                    break;
                default:
                    cout << " Invalid input, Try Again!" << endl;
                    tries++;
                    if (tries == 10){
                        cout << " Maximum tries reached! Quitting Program..." << endl;
                        exit(0);
                    }
                    break;
            }
        }
    } while (!stopProgram);
}

void menu_detail(userList &Luser, postList &Lpost, userAdr &usrData, postAdr Ppost, string tag, int n){
    clearScreen();
    bool stopProgram = false;
    if (Ppost == NULL){
        fillLines(terminalWidth, '=');
        headerCentre(terminalWidth, "404 POST NOT FOUND!");
        fillLines(terminalWidth, '=');
        pressAnyKeyToContinue();
        menu_main(Luser, Lpost, usrData, tag, n);
    }else{
        do{
            clearScreen();
            int tries = 0;
            char choice;
            string title = Ppost->title;
            string by = "By : " + Ppost->isi.OP->info.name;
            string nReply = to_string(reply_count_threads(Ppost->replies)) + " Replied to this post!";

            int postTerminalWidth = max(int(max(Ppost->isi.text.length(), Ppost->title.length()) + 2), terminalWidth);
            if (postTerminalWidth > 100){
                postTerminalWidth = 100;
            }
            fillLines(postTerminalWidth, '=');
            headerBorder(postTerminalWidth, "center", title);
            headerBorder(postTerminalWidth, "center", by);
            headerBorder(postTerminalWidth, "left", "");
            printParagraphBordered(postTerminalWidth, "left", Ppost->isi.text);
            headerBorder(postTerminalWidth, "left", "");
            printParagraphBordered(postTerminalWidth, "right", nReply);
            fillLines(postTerminalWidth, '=');

            if (Ppost->replies.first == NULL){
                cout << " Be the first one to reply!" << endl;
                cout << endl;
            } else {
                replyAdr Preply = Ppost->replies.first;
                do {
                    string replyBy = Preply->isi.OP->info.name + " replied : ";
                    istringstream iss(Preply->isi.text);
                    string line;
                    int lineWidth = 0;

                    while (getline(iss, line)){
                        lineWidth = max(lineWidth, int(line.length()));
                    }
                    int replyTerminalWidth = max(lineWidth, postTerminalWidth) + 2;
                    if (replyTerminalWidth > maxTerminalWidth){
                        replyTerminalWidth = maxTerminalWidth;
                    }

                    headerCentre(postTerminalWidth, "|");
                    headerCentre(postTerminalWidth, "|");
                    headerCentre(postTerminalWidth, "|");
                    fillLines(replyTerminalWidth, '=');
                    printParagraphBordered(replyTerminalWidth, "left", replyBy);
                    headerBorder(replyTerminalWidth, "left", "");
                    printParagraphBordered(replyTerminalWidth, "left", Preply->isi.text);
                    headerBorder(replyTerminalWidth, "left", "");
                    fillLines(replyTerminalWidth, '=');
                    Preply = Preply->next;
                } while (Preply != Ppost->replies.first);
                cout << endl;
            }

            cout << " Options : " << endl;
            cout << " 1. Reply to this post" << endl;
            cout << " 2. Delete a reply from this post" << endl;
            if (Ppost->isi.OP == usrData){
                cout << " 3. Delete this post" << endl;
            }
            if (!reply_empty(Ppost->replies)){
                cout << " 4. See detail of the replier" << endl;
            }
            cout << " 0. Back to main menu" << endl;

            bool run = true;
            while (run){
                cout << " Input : "; cin >> choice;
                switch (choice){
                    case '0':
                        run = false;
                        stopProgram = true;
                        menu_main(Luser, Lpost, usrData, tag, n);
                    case '1':
                        run = false;
                        menu_replyPost(Luser, Ppost->replies, usrData);
                        break;
                    case '2':
                        run = false;
                        menu_deleteReply(Luser, Lpost, usrData, Ppost);
                        break;
                    case '3':
                        if (Ppost->isi.OP == usrData){
                            run = false;
                            stopProgram = false;
                            post_delete(Lpost, Ppost);
                            cout << " Post Deleted!" << endl;
                            pressAnyKeyToContinue();
                            menu_main(Luser, Lpost, usrData, tag, n);
                        } else {
                            cout << " You can't delete this post!" << endl;
                        }
                        break;
                    case '4':{
                        run = false;
                        clearScreen();
                        if (!reply_empty(Ppost->replies)){
                            replyAdr Preply = Ppost->replies.first;
                            do {
                                userAdr OP = Preply->isi.OP;
                                int profileTerminalWidth = max(terminalWidth, int(OP->info.name.length()));
                                fillLines(profileTerminalWidth, '-');
                                cout << setw(profileTerminalWidth/2) << left << " |Username : ";
                                cout << setw(profileTerminalWidth/2) << right << OP->info.username << "|" << endl;
                                cout << setw(profileTerminalWidth/2) << left << " |Full Name : ";
                                cout << setw(profileTerminalWidth/2) << right << OP->info.name << "|" << endl;
                                cout << setw(profileTerminalWidth/2) << left << " |Age : ";
                                cout << setw(profileTerminalWidth/2) << right << OP->info.age << "|" << endl;
                                cout << setw(profileTerminalWidth/2) << left << " |Roles : ";
                                if (OP->info.roles == 0){
                                    cout << setw(profileTerminalWidth/2) << right << "Patient" << "|" << endl;
                                }else if (OP->info.roles == 1){
                                    cout << setw(profileTerminalWidth/2) << right << "Doctor" << "|" << endl;
                                }
                                fillLines(profileTerminalWidth, '-');
                                cout << endl << endl;
                                Preply = Preply->next;
                            } while (Preply != Ppost->replies.first);
                        }
                        pressAnyKeyToContinue();
                        break;
                    }
                    default:
                        cout << " Invalid input, Try Again!" << endl;
                        tries++;
                        if (tries == 10){
                            cout << " Maximum tries reached! Quitting Program..." << endl;
                            exit(0);
                        }
                        break;
                }
            }
        } while (!stopProgram);
    }
}

void menu_createPost(userList &Luser, postList &Lpost, userAdr &usrData){
    clearScreen();
    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Create A Post");
    fillLines(terminalWidth, '=');

    content x;
    string title, tag;
    postAdr Ppost;

    if (usrData != NULL){
        x.OP = usrData;
        cin.ignore(1, '\n');
        title = inputParagraph(" Title : ");
        x.text = inputParagraph(" Message : ");
        cout << " Tag (lowercase) : "; cin >> tag;
        Ppost = post_create_element(x, title, tag);
        post_insert(Lpost, Ppost);
        cout << endl << " Post Successfully Created!" << endl;
    } else {
        cout << " You need to sign in before creating a post!" << endl;
    }

    pressAnyKeyToContinue();
}

void menu_replyPost(userList &Luser, replyList &Lreply, userAdr &usrData){
clearScreen();
    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Reply to a post");
    fillLines(terminalWidth, '=');

    content x;
    string title, tag;
    replyAdr Preply;

    if (usrData != NULL){
        x.OP = usrData;
        cin.ignore(1, '\n');
        x.text = inputParagraph(" Message : ");
        Preply = reply_create_element(x);
        reply_insert(Lreply, Preply);
        cout << endl << " Successfully Replied To The Post!" << endl;
    } else {
        cout << " You need to sign in before replying to a post!" << endl;
    }
    pressAnyKeyToContinue();
}

void menu_search(userList &Luser, postList &Lpost, userAdr &usrData, string tag){
    clearScreen();

    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "SEARCH A POST");
    fillLines(terminalWidth, '=');

    cout << " Current tag : " << tag << endl;
    cout << " Tag to search for : "; cin >> tag;
    menu_main(Luser, Lpost, usrData, tag, 0);
}

void menu_deleteReply(userList &Luser, postList &Lpost, userAdr &usrData, postAdr Ppost){
    clearScreen();
    if (reply_empty(Ppost->replies)){
        cout << " There is no reply you can delete in this post!" << endl;
        pressAnyKeyToContinue();
    }else{
        replyAdr Preply = Ppost->replies.first;
        int n = 1;
        int choice;

        fillLines(terminalWidth, '=');
        headerCentre(terminalWidth, "DELETE A REPLY");
        fillLines(terminalWidth, '=');

        do{
            if (Preply->isi.OP == usrData || Ppost->isi.OP == usrData){
                string msg = Preply->isi.text;
                if (int(msg.length()) > terminalWidth-15){
                    msg = msg.substr(0, terminalWidth-25) + "...";
                }
                printTableMain(terminalWidth, to_string(n), msg, Preply->isi.OP->info.username);
                n++;
            }
            Preply = Preply->next;
        } while (Preply != Ppost->replies.first);
        cout << " Select which reply to delete : "; cin >> choice;
        if (choice >= n || choice == 0){
            cout << " Reply doesnt exist! returning..." << endl;
            pressAnyKeyToContinue();
        } else {
            if (Ppost->isi.OP == usrData){
                reply_delete(Ppost->replies, usrData, choice, "poster");
            } else {
                reply_delete(Ppost->replies, usrData, choice, "replier");
            }
            cout << " Reply deleted!" << endl;
            pressAnyKeyToContinue();
        }
    }
}

void menu_profile(userList &Luser, postList &Lpost, userAdr &usrData){
    clearScreen();
    int profileTerminalWidth = max(terminalWidth, int(usrData->info.name.length()));
    fillLines(profileTerminalWidth, '=');
    headerCentre(profileTerminalWidth, "Profile");
    fillLines(profileTerminalWidth, '=');
    cout << setw(profileTerminalWidth/2) << left << " |Username : ";
    cout << setw(profileTerminalWidth/2) << right << usrData->info.username << "|" << endl;
    cout << setw(profileTerminalWidth/2) << left << " |Full Name : ";
    cout << setw(profileTerminalWidth/2) << right << usrData->info.name << "|" << endl;
    cout << setw(profileTerminalWidth/2) << left << " |Age : ";
    cout << setw(profileTerminalWidth/2) << right << usrData->info.age << "|" << endl;
    cout << setw(profileTerminalWidth/2) << left << " |Roles : ";
    if (usrData->info.roles == 0){
        cout << setw(profileTerminalWidth/2) << right << "Patient" << "|" << endl;
    }else if (usrData->info.roles == 1){
        cout << setw(profileTerminalWidth/2) << right << "Doctor" << "|" << endl;
    }
    fillLines(profileTerminalWidth, '=');

    pressAnyKeyToContinue();
    menu_welcome(Luser, Lpost, usrData);
}

void menu_pemenuhanSpesifikasi(userList Luser, postList Lpost, userAdr usrData){
    clearScreen();
    char choice;

    fillLines(terminalWidth, '=');
    headerCentre(terminalWidth, "Pemenuhan Spesifikasi");
    fillLines(terminalWidth, '=');

    cout << " 1. SHOW ALL PARENTS" << endl;
    cout << " 2. SHOW ALL PARENT & CHILD" << endl;
    cout << " 0. Back to main menu" << endl;

    bool run = true;
    while (run){
        cout << " Input : "; cin >> choice;
        switch (choice){
            case '0':
                run = false;
                menu_welcome(Luser, Lpost, usrData);
                break;
            case '1':
                run = false;
                clearScreen();
                if (post_empty(Lpost)){
                    cout << " DETECTED 0 POST, LOADING SOME SAMPLE POST!" << endl;
                    post_load_sample(Lpost, Luser);
                }
                if (!post_empty(Lpost)){
                    fillLines(terminalWidth, '-');
                    printTableMain(terminalWidth, "No", "Title", "Author");
                    fillLines(terminalWidth, '-');
                    postAdr postArr[5] = {NULL, NULL, NULL, NULL, NULL};
                    int n = 0;
                    int postTotal = post_count_threads(Lpost, "general");
                    while (n < postTotal){
                        post_print(Lpost, terminalWidth, n, "general", postArr);
                        n = n + 5;
                    }
                    fillLines(terminalWidth, '-');
                    pressAnyKeyToContinue();
                    menu_pemenuhanSpesifikasi(Luser, Lpost, usrData);
                }
                break;
            case '2': {
                run = false;
                clearScreen();
                if (post_empty(Lpost)){
                    cout << " DETECTED 0 POST, LOADING SOME SAMPLE POST!" << endl;
                    post_load_sample(Lpost, Luser);
                }
                postAdr Ppost = Lpost.first;
                while (Ppost != NULL){
                    string title = Ppost->title;
                    string by = "By : " + Ppost->isi.OP->info.name;
                    string nReply = to_string(reply_count_threads(Ppost->replies)) + " Replied to this post!";
                    int postTerminalWidth = max(int(max(Ppost->isi.text.length(), Ppost->title.length()) + 2), terminalWidth);
                    if (postTerminalWidth > 100){
                        postTerminalWidth = 100;
                    }
                    fillLines(postTerminalWidth, '=');
                    headerBorder(postTerminalWidth, "center", title);
                    headerBorder(postTerminalWidth, "center", by);
                    headerBorder(postTerminalWidth, "left", "");
                    printParagraphBordered(postTerminalWidth, "left", Ppost->isi.text);
                    headerBorder(postTerminalWidth, "left", "");
                    printParagraphBordered(postTerminalWidth, "right", nReply);
                    fillLines(postTerminalWidth, '=');

                    if (Ppost->replies.first == NULL){
                    } else {
                        replyAdr Preply = Ppost->replies.first;
                        do {
                            string replyBy = Preply->isi.OP->info.name + " replied : ";
                            istringstream iss(Preply->isi.text);
                            string line;
                            int lineWidth = 0;

                            while (getline(iss, line)){
                                lineWidth = max(lineWidth, int(line.length()));
                            }
                            int replyTerminalWidth = max(lineWidth, postTerminalWidth) + 2;
                            if (replyTerminalWidth > maxTerminalWidth){
                                replyTerminalWidth = maxTerminalWidth;
                            }

                            headerCentre(postTerminalWidth, "|");
                            headerCentre(postTerminalWidth, "|");
                            headerCentre(postTerminalWidth, "|");
                            fillLines(replyTerminalWidth, '=');
                            printParagraphBordered(replyTerminalWidth, "left", replyBy);
                            headerBorder(replyTerminalWidth, "left", "");
                            printParagraphBordered(replyTerminalWidth, "left", Preply->isi.text);
                            headerBorder(replyTerminalWidth, "left", "");
                            fillLines(replyTerminalWidth, '=');
                            Preply = Preply->next;
                        } while (Preply != Ppost->replies.first);
                    }
                    cout << endl;
                    fillLines(150, '*');
                    fillLines(150, '*');
                    fillLines(150, '*');
                    cout << endl;
                    Ppost = Ppost->next;
                }
                pressAnyKeyToContinue();
                menu_pemenuhanSpesifikasi(Luser, Lpost, usrData);
                break;
            }
            default:
                cout << "INVALID INPUT, TRY AGAIN!" << endl;
                break;
        }
    }
}

void menu_debug(userList &Luser, postList &Lpost, userAdr &usrData){
    postAdr Ppost = Lpost.first;
    if (Ppost->replies.first != NULL){
        replyAdr Preply = Ppost->replies.first;
        do {
            cout << Preply->isi.text << endl;
            Preply = Preply->next;
        } while (Preply != Ppost->replies.first && Preply != NULL);
    }
    pressAnyKeyToContinue();
    usrData = NULL;
    menu_welcome(Luser, Lpost, usrData);
}
