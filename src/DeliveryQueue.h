#ifndef DELIVERY_QUEUE_H
#define DELIVERY_QUEUE_H

#include <iostream>
using namespace std;

class QNode {
public:
    int parcelID;
    QNode* next;

    QNode(int id) {
        parcelID = id;
        next = nullptr;
    }
};

class DeliveryQueue {
private:
    QNode* front;
    QNode* rear;

public:
    DeliveryQueue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int id) {
        QNode* node = new QNode(id);
        if (rear == nullptr) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
        cout << "Parcel added to delivery queue.\n";
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Delivery queue is empty.\n";
            return -1;
        }
        QNode* temp = front;
        int id = temp->parcelID;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return id;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Delivery queue is empty.\n";
            return;
        }
        QNode* temp = front;
        cout << "Delivery Queue: ";
        while (temp) {
            cout << temp->parcelID << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

#endif
