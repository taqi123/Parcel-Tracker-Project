#include "DeliveryManager.h"
#include <iostream>
using namespace std;

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

bool DeliveryManager::parcelExists(int id) {
    Parcel* temp = head;
    while (temp != nullptr) {
        if (temp->parcelID == id)
            return true;
        temp = temp->next;
    }
    return false;
}

void DeliveryManager::addParcel(int id, string sender, string receiver, string address) {
    if (parcelExists(id)) {
        cout << "Parcel with ID " << id << " already exists!\n";
        return;
    }

    Parcel* newParcel = new Parcel(id, sender, receiver, address, "Booked");

    if (head == nullptr) {
        head = tail = newParcel;
    } else {
        tail->next = newParcel;
        tail = newParcel;
    }

    cout << "Parcel added successfully!\n";
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
        cout << "\nStatus: " << temp->status << "\n";
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

void DeliveryManager::updateParcelStatus(int id) {
    Parcel* temp = head;
    while (temp != nullptr && temp->parcelID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Parcel not found.\n";
        return;
    }

    if (temp->status == "Booked")
        temp->status = "In Progress";
    else if (temp->status == "In Progress")
        temp->status = "Delivered";

    cout << "Parcel status updated successfully.\n";
}

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
