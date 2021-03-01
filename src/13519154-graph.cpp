#include "13519154-graph.hpp"

void CreateGraph(Graph *G, string c) {
    addrNode P;
    P = AlokNode(c);
    First(*G) = P;
}

addrNode AlokNode(string c) {
    addrNode P;
    P = (Node*) malloc(sizeof(Node));
    if (P != NULL) {
        Course(P) = c;
        JmlMasuk(P) = 0;
        Trail(P) = NULL;
        Next(P) = NULL;
    }
    return P;
}

void DealokNode(addrNode P) {
    free(P);
}

addrSucc AlokSucc(addrNode P) {
    addrSucc Ps;
    Ps = (SuccNode*) malloc (sizeof(SuccNode));
    if (Ps != NULL) {
        Succ(Ps) = P;
        NextTrail(Ps) = NULL;
    }
    return Ps;
}

void DealokSucc(addrSucc Ps) {
    free(Ps);
}

addrNode SearchNode(Graph G, string c) {
    addrNode P;
    P = First(G);
    while (P != NULL && Course(P) != c) {
        P = Next(P);
    }
    return P;
}

addrSucc SearchEdge(Graph G, string prec, string succ) {
    addrNode P;
    P = SearchNode(G, prec);

    if (P != NULL) {
        addrSucc Ps;
        Ps = Trail(P);
        while (Ps != NULL && Course(Succ(Ps)) != succ) {
            Ps = NextTrail(Ps);
        }
        return Ps;
    }

    return NULL;
}

void InsertNode(Graph *G, string c, addrNode *P) {
    (*P) = AlokNode(c);
    if ((*P) != NULL) {
        addrNode Pn;
        Pn = First(*G);
        while (Next(Pn) != NULL) {
            Pn = Next(Pn);
        }
        Next(Pn) = (*P);
    }
}

void DeleteNode(Graph *G, string c) {
    addrNode Pdel, P;
    Pdel = SearchNode((*G), c);
    P = First((*G));

    if (P != NULL) {
        if (Pdel == First((*G))) {
            First(*G) = Next(P);
        } else {
            while (Next(P) != Pdel) {
                P = Next(P);
            }
            Next(P) = Next(Pdel);
        }
        DeleteAllEdges(G, Pdel);
    }
}

void InsertEdge(Graph *G, string prec, string succ) {
    addrSucc Q;
    Q = SearchEdge((*G), prec, succ);
    if (Q == NULL) {
        addrNode Pr, Ps;
        Pr = SearchNode((*G), prec);
        Ps = SearchNode((*G), succ);

        // if (Pr == NULL) {
        //     InsertNode(G, prec, &Pr);
        // }
        // if (Ps == NULL) {
        //     InsertNode(G, succ, &Ps);
        // }

        addrSucc Tr;
        Tr = Trail(Pr);
        if (Tr != NULL) {
            while (NextTrail(Tr) != NULL) {
                Tr = NextTrail(Tr);
            }
            NextTrail(Tr) = AlokSucc(Ps);
        } else {
            Trail(Pr) = AlokSucc(Ps);
        }

        JmlMasuk(Ps)++;
    }
}

void DeleteAllEdges(Graph *G, addrNode P) {
    addrSucc Ps;
    Ps = Trail(P);
    while (Ps != NULL) {
        JmlMasuk(Succ(Ps)) -= 1;
        Ps = NextTrail(Ps);
    }
    Trail(P) = NULL;
}

void PrintGraph(Graph G) { // FOR DEBUGGING PURPOSES
    // Print each node and their successor node(s)
    addrNode P = First(G);
    while (P != NULL) {
        cout << "Course " << Course(P) << " is directed to ";

        addrSucc Ps;
        Ps = Trail(P);
        if (Ps == NULL) {
            cout << "none." << endl;
        }

        while (Ps != NULL) {
            cout << Course(Succ(Ps));
            if (NextTrail(Ps) != NULL) {
                cout << ", ";
            } else {
                cout << "." << endl;
            }
            Ps = NextTrail(Ps);
        }
        
        P = Next(P);
    }

    // Print each node and their number of predecessor(s)
    P = First(G);
    while (P != NULL) {
        cout << Course(P) << ": " << JmlMasuk(P) << endl;
        P = Next(P);
    }
}