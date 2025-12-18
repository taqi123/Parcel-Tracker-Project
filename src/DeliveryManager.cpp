#include "DeliveryManager.h"
#include <iostream>
using namespace std;

/* =========================
   Constructor & Destructor
   ========================= */

DeliveryManager::DeliveryManager() {
    head = tail = nullptr;
}

DeliveryManager::~DeliveryManager() {
    Parcel* curr = head;
    while (curr != nullptr) {
        Parcel* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
}

/* =========================
   Utility Functions
   ========================= */

bool DeliveryManager::parcelExists(int id) {
    Parcel* temp = head;
    while (temp != nullptr) {
        if (temp->parcelID == id)
            return true;
        temp = temp->next;
    }
    return false;
}

/* =========================
   Core Parcel Operations
   ========================= */

void DeliveryManager::addParcel(int id, string sender, string receiver, string address) {
    if (parcelExists(id)) {
        cout << "Parcel with ID " << id << " already exists.\n";
        return;
    }

    Parcel* newParcel = new Parcel(id, sender, receiver, address, "Booked");

    // 🔥 Tracking history (Phase 2)
    newParcel->addTrackingEvent("Parcel Booked", "Day 1");

    if (head == nullptr) {
        head = tail = newParcel;
    } else {
        tail->next = newParcel;
        tail = newParcel;
    }

    cout << "Parcel added successfully.\n";
}

void DeliveryManager::displayParcels() {
    if (head == nullptr) {
        cout << "No parcels available.\n";
        return;
    }

    Parcel* temp = head;
    while (temp != nullptr) {
        cout << "\nParcel ID: " << temp->parcelID;
        cout << "\nSender: " << temp->senderName;
        cout << "\nReceiver: " << temp->receiverName;
        cout << "\nAddress: " << temp->deliveryAddress;
        cout << "\nStatus: " << temp->status << endl;
        cout << "-----------------------------";
        temp = temp->next;
    }
    cout << endl;
}

void DeliveryManager::searchParcelByID(int id) {
    Parcel* temp = head;
    while (temp != nullptr) {
        if (temp->parcelID == id) {
            cout << "\nParcel Found!\n";
            cout << "Sender: " << temp->senderName << endl;
            cout << "Receiver: " << temp->receiverName << endl;
            cout << "Address: " << temp->deliveryAddress << endl;
            cout << "Status: " << temp->status << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Parcel not found.\n";
}

/* =========================
   Update Status (with tracking)
   ========================= */

void DeliveryManager::updateParcelStatus(int id) {
    Parcel* temp = head;

    while (temp != nullptr && temp->parcelID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Parcel not found.\n";
        return;
    }

    if (temp->status == "Booked") {
        temp->status = "In Progress";
        temp->addTrackingEvent("Status changed to In Progress", "Day 2");
    }
    else if (temp->status == "In Progress") {
        temp->status = "Delivered";
        temp->addTrackingEvent("Parcel Delivered", "Day 3");
    }
    else {
        cout << "Parcel already delivered.\n";
        return;
    }

    cout << "Parcel status updated successfully.\n";
}

/* =========================
   Delete Parcel
   ========================= */

void DeliveryManager::deleteParcel(int id) {
    if (!head) {
        cout << "No parcels to delete.\n";
        return;
    }

    if (head->parcelID == id) {
        Parcel* del = head;
        head = head->next;
        if (del == tail)
            tail = nullptr;
        delete del;
        cout << "Parcel deleted successfully.\n";
        return;
    }

    Parcel* temp = head;
    while (temp->next && temp->next->parcelID != id)
        temp = temp->next;

    if (!temp->next) {
        cout << "Parcel not found.\n";
        return;
    }

    Parcel* del = temp->next;
    temp->next = del->next;
    if (del == tail)
        tail = temp;
    delete del;

    cout << "Parcel deleted successfully.\n";
}

/* =========================
   Tracking History Display
   ========================= */

void DeliveryManager::showTrackingHistory(int id) {
    Parcel* temp = head;

    while (temp && temp->parcelID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Parcel not found.\n";
        return;
    }

    cout << "\nTracking History for Parcel ID " << id << ":\n";

    TrackingEvent* event = temp->historyHead;
    if (!event) {
        cout << "No tracking events available.\n";
        return;
    }

    while (event) {
        cout << "- " << event->timestamp
             << " : " << event->description << endl;
        event = event->next;
    }
}
