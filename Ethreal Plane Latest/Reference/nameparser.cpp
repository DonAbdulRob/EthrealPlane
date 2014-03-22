/* This program will format a file of text names seperated by a space */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    string thefile, tmp;
    
    bool store = true;
    bool skip1 = true;
    bool skip2 = true;
    bool skip3 = true;
    int currentPosition = 0;
    int count = 0;
    string x;
    
    
    cout << "Parsing\n\n";
    
    /* Algorithm:
    1. Read up to a a space. Once at the space delete 2 and then new line.
       After doing the above 4 times ^, we then read up to an endline. 
       Skip ahead of it, then repeat the process.
    */
    
    ifstream myfile("C:\\Users\\donny\\Desktop\\monsterlist3.txt");
    
    while (!myfile.eof()) {
        getline(myfile, tmp);
        if ((tmp != "\n") && (tmp != " ") && (tmp != "\t") )
           thefile += tmp + "\n";
    }

    myfile.close();
    
    cout << "cake";
    
    ofstream genfile("C:\\Users\\donny\\Desktop\\GenList.txt");
    
    /* First read whole file and remove all <td> </td> <tr> and </tr> */
    while (x != "9") {
        store = true;
        skip1 = false;
        skip2 = false;
        
        /* Skip td tr */
        x = thefile.substr(currentPosition,4);
        if ((x == "<td>") || (x == "<tr>")) {
            count++;
            store = false;
            skip1 = true;
        }
        else
            currentPosition++;
        
        /* skip /td /tr */
        x = thefile.substr(currentPosition,5);
        if ((x == "</td>") || (x == "</tr>")) {
            count++;
            store = false;
            skip2 = true;
        }
        
        if (store == true) {
           x = thefile.substr(currentPosition,1);
           if (x != "<")
              genfile << x;
        }
            
        if (skip1 == true)
           currentPosition += 3;
        if (skip2 == true)
           currentPosition += 4;
    }

    cout << "Complete!";
    system("pause");   
    
}
