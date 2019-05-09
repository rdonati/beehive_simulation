#include "gate.h"

Gate::Gate()
{

}
bool Gate::getState(){
    return state;
}
void Gate::setState(bool b){
    state = b;
}
