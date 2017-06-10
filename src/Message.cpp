#include "Message.h"

Message::Message(int sender, int receiver, int time, vector<int> const& shorstestPathCost):_sender(sender), _receiver(receiver), _time(time), _shortestPathCost(shorstestPathCost){
}

int Message::getSender() const{
    return _sender;
}

int Message::getReceiver() const{
    return _receiver;
}

int Message::getTime() const{
    return _time;
}

int Message::getShortestPathCost(int i) const{
    return _shortestPathCost[i];
}

void Message::report() const{
    cout << "Time : " << _time << "  From : " << _sender << "  To : "<< _receiver << endl;
    for(size_t i = 0, s = _shortestPathCost.size(); i < s; ++i){
    cout << setw(6);
        if(i != _sender)
            if(_shortestPathCost[i] == INT_MAX)
                cout << "inf";
            else
                cout << _shortestPathCost[i];
        else
            cout << 0;
        cout << ' ';
    }
    cout << endl << endl;
}
