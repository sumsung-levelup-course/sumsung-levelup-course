struct Node {
    int value;
    Node* prev;
    Node* next;
    Node() {
        value = 0;
        next = prev = 0;
    }
    Node(int i, Node* ptr) {
        value = i;
        next = ptr;
        prev = ptr->prev;
        ptr->prev = ptr->prev->next = this;
    }
};
 
struct Dll {
    Node* head;
    Node* tail;
 
    Dll() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
 
    void insert_node(int i, Node* ptr) {
        new Node(i, ptr);
    }
};
 
Dll *list = new Dll();
 
void init()
{
    list->head->next = list->tail;
    list->tail->prev = list->head;
}
 
void mergenums(int n, int * arr)
{
    if (list->head->next == list->tail)
    {
        for (int i = 0; i < n; i++)
        {
            list->insert_node(arr[i], list->tail);
        }
    }
    else
    {
        Node* ptr = list->head->next;
        bool ismerged = false;
 
        while (1)
        {
            if (ptr->value > arr[0])
            {
                ismerged = true;
                for (int i = 0; i < n; i++)
                {
                    list->insert_node(arr[i], ptr);
                }
                break;
            }
 
            ptr = ptr->next;
            if (ptr->next == list->tail)
                break;
        }
 
        if (!ismerged)
        {
            for (int i = 0; i < n; i++)
            {
                list->insert_node(arr[i], list->tail);
            }
        }
    }
}
 
int findkth(int kth)
{
    int cnt = kth;
    int v = 0;
    Node* ptr;
    if (kth > 0)
    {
        ptr = list->head->next;
        cnt--;
    }
    else
    {
        ptr = list->tail->prev;
        cnt++;
    }
    while (cnt)
    {
        if (kth > 0)
        {
            ptr = ptr->next;
            v = ptr->value;
            cnt--;
        }
        else
        {
            ptr = ptr->prev;
            v = ptr->value;
            cnt++;
        }
    }
 
    return v;
}
