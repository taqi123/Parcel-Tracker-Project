#include "DeliveryManager.h"
#include <iostream>
using namespace std;

/* =========================
   Constructor / Destructor
   ========================= */

DeliveryManager::DeliveryManager() {
    head = tail = nullptr;
    loadFromFile();   
}

DeliveryManager::~DeliveryManager() {
    saveToFile();    
    while (head) {
        Parcel* temp = head;
        head = head->next;
        delete temp;
    }
}

/* =========================
   File Handling
   ========================= */

void DeliveryManager::loadFromFile() {
    head = FileHandler::loadParcels(tail);
}

void DeliveryManager::saveToFile() {
    FileHandler::saveParcels(head);
}

/* =========================
   Utility Functions
   ========================= */

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

/* =========================
   Parcel Operations
   ========================= */

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

    cout << "Parcel added successfully.\n";
}

void DeliveryManager::deleteParcel(int id) {
    if (!head) return;

    if (head->parcelID == id) {
        undo.save("DELETE", head);
        Parcel* del = head;
        head = head->next;
        delete del;
        cout << "Parcel deleted.\n";
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
        cout << "Parcel deleted.\n";
    }
}

void DeliveryManager::updateParcelStatus(int id) {
    Parcel* p = findParcel(id);
    if (!p) {
        cout << "Parcel not found.\n";
        return;
    }

    undo.save("UPDATE", p);

    if (p->status == "Booked") {
        p->status = "In Progress";
        p->addTrackingEvent("Status changed to In Progress", "Day 2");
    }
    else if (p->status == "In Progress") {
        p->status = "Delivered";
        p->addTrackingEvent("Parcel Delivered", "Day 3");
    }
    else {
        cout << "Parcel already delivered.\n";
        return;
    }

    cout << "Parcel status updated.\n";
}

void DeliveryManager::displayParcels() {
    if (!head) {
        cout << "No parcels available.\n";
        return;
    }

    Parcel* temp = head;
    while (temp) {
        cout << "\nParcel ID: " << temp->parcelID
             << "\nSender: " << temp->senderName
             << "\nReceiver: " << temp->receiverName
             << "\nAddress: " << temp->deliveryAddress
             << "\nStatus: " << temp->status << endl;
        cout << "-----------------------------";
        temp = temp->next;
    }
    cout << endl;
}

/* =========================
   Tracking History
   ========================= */

void DeliveryManager::showTrackingHistory(int id) {
    Parcel* p = findParcel(id);
    if (!p) {
        cout << "Parcel not found.\n";
        return;
    }

    cout << "\nTracking History for Parcel ID " << id << ":\n";
    TrackingEvent* e = p->historyHead;

    while (e) {
        cout << e->timestamp << " : " << e->description << endl;
        e = e->next;
    }
}

/* =========================
   Search Functions
   ========================= */

void DeliveryManager::searchBySender(string name) {
    Parcel* temp = head;
    bool found = false;

    while (temp) {
        if (temp->senderName == name) {
            cout << "Parcel ID: " << temp->parcelID << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "No parcels found for sender.\n";
}

void DeliveryManager::searchByStatus(string status) {
    Parcel* temp = head;
    bool found = false;

    while (temp) {
        if (temp->status == status) {
            cout << "Parcel ID: " << temp->parcelID << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "No parcels found with this status.\n";
}

/* =========================
   Queue Operations
   ========================= */

void DeliveryManager::enqueueParcel(int id) {
    if (!parcelExists(id)) {
        cout << "Parcel does not exist.\n";
        return;
    }
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

/* =========================
   Undo Operation
   ========================= */

void DeliveryManager::undoLastAction() {
    Parcel* snap = undo.getSnapshot();
    if (!snap) {
        cout << "Nothing to undo.\n";
        return;
    }

    if (undo.getAction() == "ADD") {
        deleteParcel(snap->parcelID);
    }
    else if (undo.getAction() == "DELETE") {
        addParcel(
            snap->parcelID,
            snap->senderName,
            snap->receiverName,
            snap->deliveryAddress
        );
    }
    else if (undo.getAction() == "UPDATE") {
        Parcel* p = findParcel(snap->parcelID);
        if (p)
            p->status = snap->status;
    }

    undo.clear();
    cout << "Undo completed.\n";
}
