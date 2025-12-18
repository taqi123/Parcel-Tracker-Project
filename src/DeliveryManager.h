#ifndef DELIVERY_MANAGER_H
#define DELIVERY_MANAGER_H

#include "Parcel.h"
#include "DeliveryQueue.h"
#include "UndoStack.h"

class DeliveryManager {
private:
    Parcel* head;
    Parcel* tail;

    DeliveryQueue queue;
    UndoStack undo;

public:
    DeliveryManager();
    ~DeliveryManager();

    // Core
    bool parcelExists(int id);
    Parcel* findParcel(int id);

    void addParcel(int id, string sender, string receiver, string address);
    void deleteParcel(int id);
    void updateParcelStatus(int id);
    void displayParcels();

    // Tracking
    void showTrackingHistory(int id);

    // Search (Phase 3)
    void searchBySender(string name);
    void searchByStatus(string status);

    // Queue (Phase 4)
    void enqueueParcel(int id);
    void processDelivery();
    void showQueue();

    // Undo (Phase 5)
    void undoLastAction();
};

#endif
