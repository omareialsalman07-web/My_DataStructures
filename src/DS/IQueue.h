template<class T>
class IQueue
{
public:
    virtual ~IQueue() = default;

    virtual void push(const T& value) = 0;
    virtual void pop() = 0;

    virtual T& front() = 0;
    virtual const T& front() const = 0;

    virtual T& back() = 0;
    virtual const T& back() const = 0;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
};