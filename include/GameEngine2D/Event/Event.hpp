#ifndef EVENT_H
#define EVENT_H

enum eventID {
    inputEvent = 0
};

class Event {
    public:
        Event(eventID evID);
        eventID evID;
};

#endif
