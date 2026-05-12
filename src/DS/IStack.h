template<class T>
class IStack
{
public:
    virtual ~IStack() = default;

    virtual void push(const T& value) = 0;
    virtual void pop() = 0;

    virtual T& top() = 0;
    virtual const T& top() const = 0;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
};