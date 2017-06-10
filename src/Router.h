#ifndef _ROUTER_H_
#define _ROUTER_H_

#include <fstream>
#include <sstream>

#include "Message.h"

class Router{
    public:
        static void initialize(string);
        static void writeFile();
        static void run();
        Router(int);
        void broadcast();
        void receive(Message const&);
        void update();
    private:
        static string _outFileName;
        static int _routerNum;
        static vector<Router> _routerList;
        static bool _systemIsStable;
        static int _time;
        vector<vector<int> > _DV;
        vector<int> _neighbor;
        vector<Message> _messageList;
        vector<int> _shortestPath;
        int _ID;
        bool _isStable;
};
#endif
