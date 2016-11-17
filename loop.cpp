// Header Files
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <set>

using namespace std;

// Main Function
int main(int argc, char** argv) {

    // initialize variables
    ifstream fin;
    ofstream fout;
    string line;
    string token;
    string num;
    string temp;
    int counter = 0, length, length1, length2, loopCount = 0, repeatCount = 0, k, x, y, z, i, j;
    vector<string> trace;
    vector<string> new_trace;
    vector<string> test;
    set<string> all;
    set<string>::iterator itr;
    bool flag, rep, loop;
    float loops, repeats;

    // iterate through file
    for(int w = 1; w < 6; w++) {

        // clear pipe
        fin.clear();

        if(fin.good()){
            cout << "opened file" << endl;
        }
        else {
            cout << "didn't open file" << endl;
        }

        fin.open("/home/jay/ProjectData5/ArkData/unique_trace_06_0" + to_string(w) + "_2016.txt");

         // get each line in file
        while(getline(fin, line)) {

            all.insert(line);
        }

        fin.close();           
    }

    fout.open("/home/jay/ProjectData5/temp.txt");
    for(itr = all.begin(); itr != all.end(); itr++) {

        fout << (*itr) << endl;
    }
    fout.close();


    // clear pipe
    fin.clear();

    // open file for read
    fin.open("temp.txt");

    // get each line in file
    while(getline(fin, line)) {

        // convert line into stringstream
        stringstream ss(line);

        // push each item in line to trace vector
        while(getline(ss, token, '\t')) {
            trace.push_back(token);
        }

        // get length of trace vector
        length1 = trace.size();

        // loop through whole trace vector
        for(i = 0; i < length1; i++) {

            // convert each word in vector to stringstream
            istringstream ss(trace.at(i));

            // if this is the first item, split string on ':'
            if(i == 0) {
                getline(ss, token, ':');

                // push the first part to new_trace vector if it's not a '0'
                if(token != "0") {
                    new_trace.push_back(token);
                }
            }
            // if this is not the first item, split on ','
            else {
                getline(ss, token, ',');

                // push the first part to new_trace vector if it's not a '0'
                if(token != "0") {
                    new_trace.push_back(token);
                }
            }
        }

        // get length of new_trace
        length2 = new_trace.size();

        // look for repeats at end of string
        flag = false;
        rep = false;
        k = length2;

        try {
            while(flag == false) {
                if(new_trace.at(k-1) == new_trace.at(k-2)) {
                    //cout << new_trace.at(k-1) << endl;
                    new_trace.pop_back();
                    k--;
                    rep = true;
                }
                else {
                    flag = true;
                }
            }
        }
        catch(...) {
            //cout << "Repeat proplems at index " << counter << endl << endl;
        }

        if(rep == true) {
            repeatCount++;
            //cout << "Repeat at " << ' ' << counter << endl << endl;
        }




        // reset lenth after removing repeats
        length2 = new_trace.size();

        // copy new_trace vector to test vector
        for(y = 0; y < length2; y++) {
            test.push_back(new_trace.at(y));
        }









        // set loop flag
        loop = false;


        // iterate through all of new_trace
        for(x = 0; x < length2; x++) {

            // check against all items in test for loops
            for(z = 0; z < length2; z++) {

                // check against items in test vector
                if((new_trace.at(x) == test.at(z)) && (x != z)) {

                    // output "true"
                    loop = true;
                }
            }
        }


        // increment loop count
        if(loop == true) {
            loopCount++;

            //cout << "Index: " << counter << endl;

            // output new_trace vector for inspection
            //for(j = 0; j < length2; j++) {
                //cout <<  new_trace.at(j) << endl;
            //}
            //cout << endl;
        }







        // clear vectors for next time
        trace.clear();
        new_trace.clear();
        test.clear();
        counter++;    
    }
    // calculate percentage
    loops = (float(loopCount)/float(counter));
    repeats = (float(repeatCount)/float(counter));

    // output results
    cout << "Total Loops: " << loopCount << endl;
    cout << "Totla Repeats: " << repeatCount << endl;
    cout << "Total Traces: " << counter << endl;
    cout << "Total Loops percent: " << loops << endl;
    cout << "Total Repeats percent: " << repeats << endl;

    // endl program
    return 0;
}