#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <cstdlib>

using namespace std;

queue<int> buffer;
mutex mtx;

// Sensor de tráfico (productor)
void sensor(int id){

    for(int i=0; i<5; i++){

        int dato = rand()%100;

        mtx.lock();
        buffer.push(dato);
        cout<<"Sensor "<<id<<" detecto trafico: "<<dato<<endl;
        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Analizador de tráfico (consumidor)
void analizador(){

    for(int i=0; i<10; i++){

        mtx.lock();

        if(!buffer.empty()){
            int dato = buffer.front();
            buffer.pop();

            cout<<"Sistema analizo dato: "<<dato<<endl;
        }

        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(700));
    }
}

int main(){

    thread sensor1(sensor,1);
    thread sensor2(sensor,2);
    thread sistema(analizador);

    sensor1.join();
    sensor2.join();
    sistema.join();

    cout<<"Simulacion terminada"<<endl;

    return 0;
}

