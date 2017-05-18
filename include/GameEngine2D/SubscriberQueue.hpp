#ifndef SUBSCRIBER_QUEUE
#define SUBSCRIBER_QUEUE
#include <map>

template <class QueueType>
class SubscriberQueue {
    public:
        SubscriberQueue() {};

        // Add a subscriber.
        void registerSubscriber(int subscriberID) {
            if (subscribers.count(subscriberID) == 0) {
                subscribers[subscriberID] = false;
            }
        }

        // Clear the queue when all subscribers are done with it.
        void done(int subscriberID) {
            // If this subscriber has not told us before...
            if (subscribers.count(subscriberID) > 0 && !subscribers[subscriberID]) {
                subscribers[subscriberID] = true;
                ++numSubscribersDone;
            }
            // If all systems are done...
            if (numSubscribersDone == subscribers.size()) {
                // Mark all subscribers as false
                for (std::map<int, bool>::iterator subscriber = subscribers.begin(); subscriber != subscribers.end(); ++subscriber) {
                    subscriber -> second = false;
                }
                numSubscribersDone = 0;
                // Clear the queue.
                queue.clear();
            }
        }

        void push_back(auto element) {
            if (subscribers.size() != 0) {
                queue.push_back(element);
            }
        }

        auto front() {
            return queue.front();
        }

        auto back() {
            return queue.back();
        }

        auto& operator[](int index) {
            return queue[index];
        }

        int size() {
            return queue.size();
        }
    private:
        QueueType queue;
        std::map<int, bool> subscribers;
        int numSubscribersDone = 0;
};

#endif
