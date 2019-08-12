typedef unsigned long long ulong;
 
struct Node {
 
    ulong data;
    Node* next;
 
    Node() {
        data = 0;
        next = 0;
    }
    Node(ulong i, Node* ptr) {
        data = i;
        next = 0;
        ptr->next = this;
    }
};
 
Node list[1789];
 
void init()
{
    for (int i = 0; i < 1789; i++)
    {
        list[i].data = 0;
        list[i].next = 0;
    }
}
 
int checkKey(ulong key)
{
    ulong tmp = key % 1789;
    Node* ptr = list + tmp;
    bool notChecked = true;
 
    while (1)
    {
        if (ptr->data == key)
        {
            notChecked = false;
            return 0;
        }
        else {
            if (ptr->next == 0)
            {
                new Node(key, ptr);
                return 1;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }
}
