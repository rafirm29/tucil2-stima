#ifndef DirGRAPH_H
#define DirGRAPH_H

#include <string>
#include <iostream>
using namespace std;

typedef struct taddrNode *addrNode;
typedef struct taddrSucc *addrSucc;
typedef struct taddrNode {
    string course;
    int jmlMasuk;
    addrSucc trail;
    addrNode next;
} Node;

typedef struct taddrSucc {
    addrNode succ;
    addrSucc nextTrail;
} SuccNode;

typedef struct {
    addrNode first;
} Graph;

#define Course(N) (N)->course
#define JmlMasuk(N) (N)->jmlMasuk
#define Trail(N) (N)->trail
#define Next(N) (N)->next
#define Succ(T) (T)->succ
#define NextTrail(T) (T)->nextTrail
#define First(G) (G).first

void CreateGraph(Graph *G, string c);
/* I.S. Graf sembarang
F.S. First dari Graf menuju pada node dengan nilai course adalah c */

addrNode AlokNode(string c);
/* Mengembalikan address node yang telah dialokasi
dengan nama node berupa nama dari course tersebut.
Jika alokasi tidak berhasil maka mengembalikan NULL */

void DealokNode(addrNode P);
/* I.S. P terdefinisi
F.S. P telah didealokasi */

addrSucc AlokSucc(addrNode P);
/* Mengembalikan address successor node yang telah
dialokasi menuju P sebagai successor node-nya.
Jika alokasi tidak berhasil maka mengembalikan NULL */

void DealokSucc(addrSucc Ps);
/* I.S. Ps terdefinisi
F.S. Ps telah didealokasi */

addrNode SearchNode(Graph G, string c);
/* Mengembalikan address dari node yang merepresentasikan
course c. JIka tidak ada maka akan mengembalikan NULL */

addrSucc SearchEdge(Graph G, string prec, string succ);
/* Mengembalikan address dari successor node yang
menghubungkan node dengan course prec dan succ.
JIka tidak ada maka akan mengembalikan NULL */

void InsertNode(Graph *G, string c, addrNode *P);
/* Menambahkan Node dengan course c pada list utama graf */

void DeleteNode(Graph *G, string c);
/* Menghapus node dengan course c pada graf */

void InsertEdge(Graph *G, string prec, string succ);
/* Menambahkan edge yang menghubungkan node dengan course prec
dan node dengan course succ. Successor node ditambahkan pada trail
prec menuju node succ */

void DeleteAllEdges(Graph *G, addrNode P);
/* Menghapus seluruh edges yang dimiliki oleh node P */

void PrintGraph(Graph G);
/* Menampilkan informasi graf berupa setiap node menunjuk ke node
mana serta jumlah predecessor yang dimiliki oleh masing-masing node */

#endif