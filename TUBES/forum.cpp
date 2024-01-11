#include "forum.h"

void post_create_list(postList &L){
    L.first = NULL;
}

postAdr post_create_element(content x, string title, string tag){
    postAdr p = new post;
    p->isi = x;
    p->title = title;
    p->tag = tag;
    reply_create_list(p->replies);
    p->next = NULL;
    return p;
}

void post_load_sample(postList &Lpost, userList Luser){
    content x;
    postAdr P;
    replyAdr R;
    string title, tag;

    x.text = "Obat murah untuk sakit perut apa ya dok? sudah 3 hari saya sakit perut";
    x.OP = user_search_username(Luser, "user1");
    title = "Apa Obat Sakit Perut Murah?";
    tag = "perut";
    P = post_create_element(x, title, tag);
    post_insert(Lpost, P);
    x.text = R"(Jika Anda mengalami sakit perut ringan, beberapa opsi obat yang mungkin membantu termasuk:

1. **Antasida**: Untuk meredakan rasa terbakar lambung.
2. **Anti-diare (jika diperlukan)**: Contohnya loperamide.
3. **Anti-mual (jika diperlukan)**: Seperti dimenhydrinate atau ondansetron.
4. **Obat penghilang rasa nyeri**: Misalnya parasetamol atau ibuprofen (hindari jika ada masalah lambung/usus)
5. **Minuman hangat**: Teh herbal atau kaldu.

Namun, penting untuk konsultasi dengan dokter sebelum mengonsumsi obat dan jika gejala berlanjut.)";
    x.OP = user_search_username(Luser, "doctor1");
    R = reply_create_element(x);
    reply_insert(P->replies, R);
    x.text = R"(Kalau perut sakit, bisa coba:

1. **Minum obat antasida**, seperti tablet rasa mint.
2. **Obat anti-diare** yang ada di warung obat.
3. **Obat anti-mual**, cari yang bikin nyaman perut.
4. **Obat pereda sakit**, yang biasa dipakai aja.
5. **Minum teh hangat**, enak dan bisa bantu.

Tapi kalau tetap bingung atau nggak membaik, mending tanya dokter ya.)";
    x.OP = user_search_username(Luser, "user5");
    R = reply_create_element(x);
    reply_insert(P->replies, R);

    x.text = "Apakah diet vegetarian mendukung produksi protein pada tubuh?";
    x.OP = user_search_username(Luser, "user2");
    title = "Protein Pada Diet Vegetarian";
    tag = "vegetarian";
    P = post_create_element(x, title, tag);
    post_insert(Lpost, P);
}

bool post_empty(postList &L){
    return (L.first == NULL);
}

void post_insert(postList &L, postAdr P){
    if (post_empty(L)){
        L.first = P;
    }else{
        P->next = L.first;
        L.first = P;
    }
}

void post_print(postList &L, int width, int n, string tag, postAdr (&postArr)[5]){
    if (!post_empty(L)){
        if (tag == "general"){
            postAdr P = L.first;
            int postCount = 1;
            int postNumber = n + 1;
            int arrNum = 0;

            while (P != NULL && postNumber <= n+5){
                if (postCount > n){
                    string title = P->title;
                    string username = P->isi.OP->info.username;

                    printTableMain(width, to_string(postCount), title, username);
                    postArr[arrNum] = P;
                    arrNum++;
                    postNumber++;
                }
                P = P->next;
                postCount++;
            }
        } else {
            postAdr P = L.first;
            int postCount = 1;
            int postNumber = n + 1;
            int arrNum = 0;

            while (P != NULL && postNumber <= n+5){
                    if (P->tag == tag){
                        if (postCount > n){
                            string title = P->title;
                            string username = P->isi.OP->info.username;

                            printTableMain(width, to_string(postCount), title, username);
                            postArr[arrNum] = P;
                            arrNum++;
                            postNumber++;
                        }
                        postCount++;
                    }
                    P = P->next;
            }
        }
    }
}

int post_count_threads(postList L, string tag){
    int n = 0;
    if (!post_empty(L)){
        postAdr P = L.first;
        while (P != NULL){
            if (tag == "general"){
                n++;
            }else{
                if (tag == P->tag){
                    n++;
                }
            }
            P = P->next;
        }
    }
    return n;
}

void post_delete_first(postList &L){
    postAdr P;
    if (!post_empty(L)){
        P = L.first;
        if (L.first->next == NULL){
            L.first = NULL;
        } else {
            L.first = L.first->next;
        }
        delete P;
    }
}

void post_delete_after(postList &L, postAdr &prec){
    postAdr P;
    if (!post_empty(L)){
        P = prec->next;
        prec->next = P->next;
        delete P;
    }
}

void post_delete(postList &L, postAdr &P){
    if (!post_empty(L)){
        while (!reply_empty(P->replies)){
            reply_delete_first(P->replies);
        }
        if (P == L.first){
            post_delete_first(L);
        } else {
            postAdr prec = L.first;
            while (prec->next != P){
                prec = prec->next;
            }
            post_delete_after(L, prec);
        }
    }
}
// =================================================================================================================================================================================================

void reply_create_list(replyList &L){
    L.first = NULL;
    L.last = NULL;
}
replyAdr reply_create_element(content x){
    replyAdr r = new reply;
    r->isi = x;
    r->next = NULL;
    return r;
}

bool reply_empty(replyList &L){
    return (L.first == NULL && L.last == NULL);
}
void reply_insert(replyList &L, replyAdr R){
    if (reply_empty(L)){
        L.first = R;
        L.last = R;
        R->next = R;
    }else{
        L.last->next = R;
        L.last = R;
        R->next = L.first;
    }
}

void reply_delete_first(replyList &L){
    replyAdr R;
    if (!reply_empty(L)){
        R = L.first;
        if (L.first == L.last){
            L.first = NULL;
            L.last = NULL;
        }else{
            L.first = L.first->next;
            L.last->next = L.first;
        }
        delete R;
    }
}

void reply_delete_after(replyList &L, replyAdr prec){
    replyAdr R;
    if (!reply_empty(L)){
        R = prec->next;
        prec->next = R->next;
        if (R == L.last){
            L.last = prec;
        }
        delete R;
    }
}

void reply_delete(replyList &L, userAdr usrData, int pos, string user){
    replyAdr R = L.first;
    if (pos == 1){
        if (user == "poster" || (user == "replier" && L.first->isi.OP == usrData)){
            reply_delete_first(L);
        } else {
            do {
                R = R->next;
            } while (R->next->isi.OP != usrData);
            reply_delete_after(L, R);
        }
    } else {
        int n;
        if (user == "poster"){
            n = 0;
        }else{
            n = 1;
        }
        while (R != NULL && n < pos){
            if (user == "poster"){
                n++;
            } else if (user == "replier" && R->isi.OP == usrData) {
                n++;
            }
            R = R->next;
        }
        reply_delete_after(L, R);
    }
    if (reply_empty(L)){
        reply_create_list(L);
    }

}


int reply_count_threads(replyList &Lreply){
    int n = 0;
    if (Lreply.first != NULL){
        replyAdr Preply = Lreply.first;
        do {
            n++;
            Preply = Preply->next;
        } while (Preply != Lreply.first);
    }
    return n;
}

