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
            // чтобы не было ситуаций когда Node<int> = 42; мне надо только Node<int> node(42);
        };

    using Alloc_traits = std::allocator_traits<Alloc>;
    using NodeAllocator = typename Alloc_traits::rebind_alloc<Node>;
    using Alloc_Item_traits = std::allocator_traits<NodeAllocator>;

    Node* head;
    int size;
    NodeAllocator allocator;

    class Iterator
    {
        private:
            friend List;
            Node* current;

        public:
            using value_type = T; //data
            using pointer = T*; // * on current
            using reference = T&; // & on elements
            using difference_type = std::ptrdiff_t; // diff between next and last
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

    public:

        List(): head(nullptr), size(0) {}

        ~List()
        {
            while (head) 
            {
                Node* temp = head;
                head = head->next;

                // Destroy the data and deallocate the node
                Alloc_Item_traits::destroy(allocator, &(temp->data));
                Alloc_Item_traits::deallocate(allocator, temp, 1);
            }
            size = 0;
        }

        void push(const T& value)
        {
            //alloc for 1 element
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

                // Deallocate the node before destroying the data
                Alloc_Item_traits::deallocate(allocator, temp, 1);
                // Destroy the data after deallocation
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
};