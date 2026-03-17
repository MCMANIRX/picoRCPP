#include <queue>
#include <optional>
template <typename T, int SIZE>

class FIFO {

    std::queue<T> buffer;

    enum status {
        EMPTY,
        NOT_EMPTY,
        FULL
    };

    public:
        
        status insert_fifo(T datum) {

            status s = get_status();

            if(s==FIFO::FULL)
                return s;

            buffer.push(datum);

            return s;
        }

        std::optional<T> pop_fifo() {
            if(buffer.empty())
                return std::nullopt;

            T value = buffer.pop();
            return value;
        }

        FIFO(){}
        ~FIFO(){}

};