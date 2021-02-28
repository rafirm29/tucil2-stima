#include <fstream>
#include "DirectedGraph.hpp"

void FileToGraph (Graph *G, string filename, bool *valid) {
    ifstream file(filename);
    if (file.fail()) {
        (*valid) = false;
    } else {
        string lines;
        bool firstNode;
        bool isHead = true;

        // Process each line from textfile
        while (getline(file, lines, '\n')) {
            string delimiter = " ,.";

            size_t pos = 0;
            string course;

            addrNode Pmain;
            firstNode = true;
            string mainCourse;

            // Parse word with delimiter as the separator
            while ((pos = lines.find_first_of(delimiter)) != string::npos) {
                course = lines.substr(0, pos);
                
                /***** GRAPH MAKING PROCESS *****/

                if (firstNode) {                            // Check for the first node on every line
                    if (isHead)                             // First ever node will be head of graph
                    {
                        CreateGraph(G, course);             // Create graph with the first course as the head
                        isHead = false;
                    }
                    else
                    {
                        if (SearchNode(*G, course) == NULL)
                        {
                            InsertNode(G, course, &Pmain);  // Insert node if it has not yet existed      
                        }                    
                    }
                    firstNode = false;                      // Stop checking for first node
                    mainCourse = course;                    // Setting the first code from the line as the mainCourse
                }

                // Process the prerequisite for the current mainCourse
                else {
                    addrNode dummy;
                    if (SearchNode(*G, course) == NULL)
                    {
                        InsertNode(G, course, &dummy);      // Insert node if it has not yet existed
                    }    
                    InsertEdge(G, course, mainCourse);      // Connect the edge from the current course to the current mainCourse
                }
                

                /***** END OF PROCESSING LINE *****/

                lines.erase(0, pos + 2);
            }
        }
    }
}

int main() {
    Graph G;
    string input;
    cout << "Silakan masukkan nama file!" << endl;
    cout << "Contoh : test123.txt" << endl;
    cout << "Nama input file : ";
    cin >> input;
    string testfile = "../test/";
    testfile += input;

    bool valid = true;
    FileToGraph(&G, testfile, &valid);
    
    if (valid) {
        int smt = 1;
        while (First(G) != NULL) {
            cout << "Semester " << smt << ":" << endl;

            // Set P to always be the head of graph
            addrNode P = First(G);

            // Create array of addrNode that will be deleted
            addrNode* delArr = new addrNode[50];
            int idx = 0;

            // Getting and showing the courses that has 0 predecessor
            while (P != NULL) {
                if (JmlMasuk(P) == 0) {  
                    cout << "\t- " << Course(P) << endl;
                    delArr[idx] = P;
                    idx++;
                }
                P = Next(P);
            }

            // Deleting all the nodes that has 0 predecessor
            for (int i = 0; i < idx; i++)
            {
                DeleteNode(&G, Course(delArr[i]));
            }
            
            smt++; // Increment semester
        }
    } else {
        cout << "File not found!" << endl;
    }

    return 0;
}