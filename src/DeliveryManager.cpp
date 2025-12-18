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
