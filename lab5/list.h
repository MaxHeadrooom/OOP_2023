#include <memory>

template <class T, class Alloc = std::allocator<T>>
class List 
{
    private:
        struct Node 
        {
            T data;
            Node* next;

            explicit Node(const T& value) : data(value), next(nullptr) {}
        };

        using Alloc_traits = std::allocator_traits<Alloc>;
        using NodeAllocator = typename Alloc_traits::rebind_alloc<Node>;
        using Alloc_Item_traits = std::allocator_traits<NodeAllocator>;

        Node* head;
        int size;
        NodeAllocator allocator;

    public:
    class Iterator 
    {
        private:
            friend List;
            Node* current;

        public:
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            Iterator(Node* node) : current(node) {}

            reference operator*() const 
            {
                return current->data;
            }

            pointer operator->() const 
            {
                return &(current->data);
            }

            Iterator& operator++() 
            {
                current = current->next;
                return *this;
            }

            Iterator operator++(int) 
            {
                Iterator temp = *this;
                current = current->next;
                return temp;
            }

            bool operator==(const Iterator& other) const 
            {
                return this->current == other.current;
            }

            bool operator!=(const Iterator& other) const 
            {
                return this->current != other.current;
            }
    };

    class ConstIterator 
    {
        private:
            friend List;
            const Node* current;

        public:
            using value_type = T;
            using pointer = const T*;
            using reference = const T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            ConstIterator(const Node* node) : current(node) {}

            ConstIterator(const Iterator& it) : current(it.current) {}
            
            reference operator*() const 
            {
                return current->data;
            }

            pointer operator->() const 
            {
                return &(current->data);
            }

            ConstIterator& operator++() 
            {
                current = current->next;
                return *this;
            }

            ConstIterator operator++(int) 
            {
                ConstIterator temp = *this;
                current = current->next;
                return temp;
            }

            bool operator==(const ConstIterator& other) const 
            {
                return this->current == other.current;
            }

            bool operator!=(const ConstIterator& other) const 
            {
                return this->current != other.current;
            }
    };

    List() : head(nullptr), size(0) {}

    ~List() {
        while (head) 
        {
            Node* temp = head;
            head = head->next;

            Alloc_Item_traits::destroy(allocator, &(temp->data));
            Alloc_Item_traits::deallocate(allocator, temp, 1);
        }
        size = 0;
    }

    void push(const T& value) 
    {
        Node* newNode = Alloc_Item_traits::allocate(allocator, 1);
        Alloc_Item_traits::construct(allocator, newNode, value);

        newNode->next = head;
        head = newNode;
        size++;
    }

    void pop() 
    {
        if (head) 
        {
            size--;
            Node* temp = head;
            head = head->next;

            Alloc_Item_traits::deallocate(allocator, temp, 1);
            Alloc_Item_traits::destroy(allocator, &(temp->data));
        }
    }

    int getsize() const 
    {
        return size;
    }

    Iterator begin() 
    {
        return Iterator(head);
    }

    Iterator end() 
    {
        return Iterator(nullptr);
    }

    ConstIterator begin() const 
    {
        return ConstIterator(head);
    }

    ConstIterator end() const 
    {
        return ConstIterator(nullptr);
    }
};
