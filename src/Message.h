#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <vector>
#include <iomanip>
#include <climits>
#include <iostream>
using namespace std;

class Message{
    public:
        Message(int sender, int receiver, int time, vector<int> const& shortestPathCost);
        int getSender() const;
        int getReceiver() const;
        int getTime() const;
        int getShortestPathCost(int i) const;
        void report() const;
    private:
        int _sender;
        int _receiver;
        int _time;
        vector<int> _shortestPathCost;
};
#endif
