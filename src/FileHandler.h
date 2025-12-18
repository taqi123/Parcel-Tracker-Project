#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <fstream>
#include <sstream>
#include "Parcel.h"

class FileHandler {
public:
    static void saveParcels(Parcel* head) {
        ofstream out("data/parcels.txt");
        Parcel* p = head;

        while (p) {
            out << p->parcelID << "|"
                << p->senderName << "|"
                << p->receiverName << "|"
                << p->deliveryAddress << "|"
                << p->status;

            // save tracking history
            TrackingEvent* e = p->historyHead;
            out << "|";
            while (e) {
                out << e->timestamp << "," << e->description;
                if (e->next) out << "#";
                e = e->next;
            }
            out << "\n";
            p = p->next;
        }
        out.close();
    }

    static Parcel* loadParcels(Parcel*& tail) {
        ifstream in("data/parcels.txt");
        if (!in) return nullptr;

        Parcel* head = nullptr;
        tail = nullptr;
        string line;

        while (getline(in, line)) {
            stringstream ss(line);
            string id, s, r, a, st, history;

            getline(ss, id, '|');
            getline(ss, s, '|');
            getline(ss, r, '|');
            getline(ss, a, '|');
            getline(ss, st, '|');
            getline(ss, history);

            Parcel* p = new Parcel(stoi(id), s, r, a, st);

            // restore tracking history
            stringstream hs(history);
            string event;
            while (getline(hs, event, '#')) {
                stringstream es(event);
                string time, desc;
                getline(es, time, ',');
                getline(es, desc);
                p->addTrackingEvent(desc, time);
            }

            if (!head) {
                head = tail = p;
            } else {
                tail->next = p;
                tail = p;
            }
        }
        in.close();
        return head;
    }
};

#endif
