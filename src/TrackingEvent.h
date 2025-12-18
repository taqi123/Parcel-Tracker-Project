#ifndef TRACKING_EVENT_H
#define TRACKING_EVENT_H

#include <string>
using namespace std;

class TrackingEvent {
public:
    string description;
    string timestamp;
    TrackingEvent* next;

    TrackingEvent(string desc, string time) {
        description = desc;
        timestamp = time;
        next = nullptr;
    }
};

#endif
