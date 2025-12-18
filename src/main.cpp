#include <iostream>
#include "DeliveryManager.h"
using namespace std;

int main() {
    DeliveryManager manager;
    int choice;

    do {
        cout << "\n--- Parcel Delivery System ---\n";
        cout << "1. Add Parcel\n";
        cout << "2. Update Parcel Status\n";
        cout << "3. Display All Parcels\n";
        cout << "4. Search Parcel by ID\n";
        cout << "5. Delete Parcel\n";

        cout << "6. View Tracking History\n";
        cout << "7. Exit\n";
        
        cin >> choice;

        int id;
        string sender, receiver, address;

        switch (choice) {
        case 1:
            cout << "Parcel ID: ";
            cin >> id;
            cin.ignore();
            cout << "Sender Name: ";
            getline(cin, sender);
            cout << "Receiver Name: ";
            getline(cin, receiver);
            cout << "Delivery Address: ";
            getline(cin, address);
            manager.addParcel(id, sender, receiver, address);
            break;

        case 2:
            cout << "Enter Parcel ID: ";
            cin >> id;
            manager.updateParcelStatus(id);
            break;

        case 3:
            manager.displayParcels();
            break;

        case 4:
            cout << "Enter Parcel ID: ";
            cin >> id;
            manager.searchParcelByID(id);
            break;

        case 5:
            cout << "Enter Parcel ID: ";
            cin >> id;
            manager.deleteParcel(id);
            break;

        case 6:
            cout << "Enter Parcel ID: ";
            cin >> id;
            manager.showTrackingHistory(id);
            break;
            
        case 7:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
