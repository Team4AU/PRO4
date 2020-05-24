//
// Created by dani on 4/14/20.
//

#ifndef MQTT_THREADSAFEQUEUE_H
#define MQTT_THREADSAFEQUEUE_H

#include <mutex>
#include <queue>

template<typename T>
class threadSafeQueue {
    std::queue<T> queue;
    std::mutex m;
public:
    bool dequeue(T& element){
        std::lock_guard<std::mutex> lock(m);
        if(queue.empty()){
            return false;
        }
        element = queue.front();
        queue.pop();
        return true;
    };
    void enqueue(T element){
        std::lock_guard<std::mutex> lock(m);
        queue.push(element);
    };
private:

};
#endif //MQTT_THREADSAFEQUEUE_H
