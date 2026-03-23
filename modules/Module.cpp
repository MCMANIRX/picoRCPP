#include "inc/Module.h"

/*
T Module::pop_fifo() {
    if(out_buffer)
        return out_buffer.pop_fifo();
    else return std::nullopt;

}

FIFO::status Module::insert_fifo(T datum) {
    if(out_buffer)
        return out_buffer->insert_fifo(datum);
    else return std::nullopt;

}*/

bool Module::isEnabled() const {
    return this->enabled;
}

void Module::setEnabled(bool on) {

    this->enabled = on;
}



Module::~Module()
{
}