#include "Router.h"

int main(int argc, char** argv){
    Router::initialize(argv[1]);
    Router::run();
    return 0;
}
