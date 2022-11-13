#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <vector>


using namespace std;

void hacer_ping(string ip){
    string command = "ping -q -c2 192.168.10.100 | awk 'NR==4 {print $1, $4}' > resultado_ping.txt";
    system (command.c_str());
  

    string line;
    ifstream myfile("resultado_ping.txt");
    if (myfile.is_open()){
        getline(myfile,line);
        myfile.close();
    }
    else{
        cout << "Unable to open file";
    }
}


void leer_archivo(string archivo){
    string line;
    vector<string> ips;
    int i = 1;


    ifstream myfile(archivo);
    if (myfile.is_open()){
        while (getline(myfile,line)){
            ips.push_back(line);
            i++;
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file";
    }

    thread threads[ips.size()];

    for (i=0; i < ips.size(); i++) {
         threads[i] = thread(hacer_ping, ips[i]);
    }


    for (i=0; i< ips.size(); i++) {
        threads[i].join();
    }

}

int main(int argc, char** args) {
    string archivoip = args[0];
    leer_archivo(archivoip);
}
