#include "DeliveryManager.h"
#include <iostream>
using namespace std;

DeliveryManager::DeliveryManager() {
    head = tail = nullptr;
}

DeliveryManager::~DeliveryManager() {
    while (head) {
        Parcel* temp = head;
        head = head->next;
        delete temp;
    }
}

bool DeliveryManager::parcelExists(int id) {
    return findParcel(id) != nullptr;
}

Parcel* DeliveryManager::findParcel(int id) {
    Parcel* temp = head;
    while (temp) {
        if (temp->parcelID == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

/* ================= CORE ================= */

void DeliveryManager::addParcel(int id, string sender, string receiver, string address) {
    if (parcelExists(id)) {
        cout << "Parcel ID already exists.\n";
        return;
    }

    Parcel* p = new Parcel(id, sender, receiver, address, "Booked");
    p->addTrackingEvent("Parcel Booked", "Day 1");

    undo.save("ADD", p);

    if (!head) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    cout << "Parcel added.\n";
}

void DeliveryManager::deleteParcel(int id) {
    if (!head) return;

    if (head->parcelID == id) {
        undo.save("DELETE", head);
        Parcel* del = head;
        head = head->next;
        delete del;
        return;
    }

    Parcel* temp = head;
    while (temp->next && temp->next->parcelID != id)
        temp = temp->next;

    if (temp->next) {
        undo.save("DELETE", temp->next);
        Parcel* del = temp->next;
        temp->next = del->next;
        delete del;
    }
}

void DeliveryManager::updateParcelStatus(int id) {
    Parcel* p = findParcel(id);
    if (!p) return;

    undo.save("UPDATE", p);

    if (p->status == "Booked") {
        p->status = "In Progress";
        p->addTrackingEvent("In Progress", "Day 2");
    } else if (p->status == "In Progress") {
        p->status = "Delivered";
        p->addTrackingEvent("Delivered", "Day 3");
    }
}

/* ================= DISPLAY ================= */

void DeliveryManager::displayParcels() {
    Parcel* temp = head;
    while (temp) {
        cout << "\nID: " << temp->parcelID
             << "\nSender: " << temp->senderName
             << "\nReceiver: " << temp->receiverName
             << "\nStatus: " << temp->status << "\n";
        temp = temp->next;
    }
}

void DeliveryManager::showTrackingHistory(int id) {
    Parcel* p = findParcel(id);
    if (!p) return;

    TrackingEvent* e = p->historyHead;
    while (e) {
        cout << e->timestamp << " : " << e->description << endl;
        e = e->next;
    }
}

/* ================= SEARCH ================= */

void DeliveryManager::searchBySender(string name) {
    Parcel* temp = head;
    while (temp) {
        if (temp->senderName == name)
            cout << "Found Parcel ID: " << temp->parcelID << endl;
        temp = temp->next;
    }
}

void DeliveryManager::searchByStatus(string status) {
    Parcel* temp = head;
    while (temp) {
        if (temp->status == status)
            cout << "Parcel ID: " << temp->parcelID << endl;
        temp = temp->next;
    }
}

/* ================= QUEUE ================= */

void DeliveryManager::enqueueParcel(int id) {
    if (!parcelExists(id)) return;
    queue.enqueue(id);
}

void DeliveryManager::processDelivery() {
    int id = queue.dequeue();
    if (id != -1)
        updateParcelStatus(id);
}

void DeliveryManager::showQueue() {
    queue.displayQueue();
}

/* ================= UNDO ================= */

void DeliveryManager::undoLastAction() {
    Parcel* snap = undo.getSnapshot();
    if (!snap) {
        cout << "Nothing to undo.\n";
        return;
    }

    if (undo.getAction() == "ADD") {
        deleteParcel(snap->parcelID);
    } else if (undo.getAction() == "DELETE") {
        addParcel(snap->parcelID, snap->senderName, snap->receiverName, snap->deliveryAddress);
    } else if (undo.getAction() == "UPDATE") {
        Parcel* p = findParcel(snap->parcelID);
        if (p) p->status = snap->status;
    }

    undo.clear();
    cout << "Undo completed.\n";
}
