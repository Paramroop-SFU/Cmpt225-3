// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Paramroop Parmar>
// St.# : <psp10@sfu.ca>
// Email: <301555338>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not #include any other files!
//
#include "Announcement.h"
#include "JingleNet_announcer.h"
#include "Queue_base.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class Queue : public Queue_base<T>
{
private:
    // Define the internal structure of your queue and any necessary private members here
    struct node
    {
        T data;
        node *next;
    };

    node *head;
    node *tail;
    int count;

public:
    // Constructor to initialize the queue
    Queue()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Destructor to clean up any allocated resources
    ~Queue()
    {
        while (head != nullptr)
        {
            node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Implement the size() function to return the number of items in the queue
    int size() const override
    {
        return count;
    }

    // Implement the enqueue() function to add an item to the back of the queue
    void enqueue(const T &item) override
    {
        node *newnode = new node{item, nullptr};
        if (tail == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
        count++;
    }

    // Implement the front() function to return a constant reference to the front item
    const T &front() const override
    {
        if (head == nullptr)
        {
            throw runtime_error("front: queue is empty");
        }
        return head->data;
    }

    // Implement the dequeue() function to remove the front item from the queue
    void dequeue() override
    {
        if (head == nullptr)
        {
            throw runtime_error("dequeue: queue is empty");
        }
        node *temp = head;
        head = head->next;
        delete temp;
        count--;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    void print()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        printf("\n");
    }
};
// end of class

struct all_five
{
    Queue<Announcement> Santa;
    Queue<Announcement> reindeer;
    Queue<Announcement> elf1;
    Queue<Announcement> elf2;
    Queue<Announcement> snowman;
};

string get_type(string &s) // returns the type
{
    string type;
    int i = 0;
    while (s[i] != ' ')
    {
        type += s[i];
        i++;
    }
    s.erase(0, i + 1);
    return type;
}

void Announcment_fun(all_five &order, string &s)
{
    int num = stoi(s);

    while (num > 0)
    {
        if (order.Santa.size() != 0)
        {
            jnet.announce(order.Santa.front());
            order.Santa.dequeue();
        }
        else if (order.reindeer.size() != 0)
        {
            jnet.announce(order.reindeer.front());
            order.reindeer.dequeue();
        }
        else if (order.elf2.size() != 0)
        {
            jnet.announce(order.elf2.front());
            order.elf2.dequeue();
        }
        else if (order.elf1.size() != 0)
        {
            jnet.announce(order.elf1.front());
            order.elf1.dequeue();
        }
        else if (order.snowman.size() != 0)
        {
            jnet.announce(order.snowman.front());
            order.snowman.dequeue();
        }

        num--;
    }
}

void Remove_all(all_five &order, string &s)
{
    int size = order.reindeer.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.reindeer.front());
        if (a3.get_sender_name() == s)
        {

        }
        else
        {
            order.reindeer.enqueue(a3);     
        }
        order.reindeer.dequeue();
    }
    size = order.Santa.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.Santa.front());
        if (a3.get_sender_name() != s)
        {
            order.Santa.enqueue(a3);
        }
        order.Santa.dequeue();
    }
    size = order.elf1.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.elf1.front());
        if (a3.get_sender_name() != s)
        {
            order.elf1.enqueue(a3);
        }
         order.elf1.dequeue();
    }
    size = order.elf2.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.elf2.front());
        if (a3.get_sender_name() != s)
        {
            order.elf2.enqueue(a3);
        }
      
        order.elf2.dequeue();
    }
    size = order.snowman.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.snowman.front());
        if (a3.get_sender_name() != s)
        {
            order.snowman.enqueue(a3);
        }
        order.snowman.dequeue();
    }
}



void Promote(all_five &order, string &s)
{
    int size = order.reindeer.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.reindeer.front());
        if (a3.get_sender_name() == s)
        {
            Announcement a1(a3.get_sender_name(), Rank::SANTA, a3.get_text());
            order.Santa.enqueue(a1);      
        }
        else
        {
            order.reindeer.enqueue(a3);
        }
        order.reindeer.dequeue();
    }

    size = order.elf1.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.elf1.front());
        if (a3.get_sender_name() == s)
        {
            Announcement a1(a3.get_sender_name(), Rank::ELF2, a3.get_text());
            order.reindeer.enqueue(a1);
        }
        else
        {
            order.elf1.enqueue(a3);
            
        }
        order.elf1.dequeue();
    }
    size = order.elf2.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.elf2.front());
        if (a3.get_sender_name() == s)
        {
            Announcement a1(a3.get_sender_name(), Rank::REINDEER, a3.get_text());
            order.elf1.enqueue(a1);
            
        }
        else
        {
            order.elf2.enqueue(a3);
            
        }
        order.elf2.dequeue();
    }
    size = order.snowman.size();
    for (int i = 0; i < size; i++) // do this 3 more times
    {
        Announcement a3(order.snowman.front());
        if (a3.get_sender_name() == s)
        {
            Announcement a1(a3.get_sender_name(), Rank::ELF1, a3.get_text());
            order.elf1.enqueue(a1);
            
        }
        else
        {
            order.snowman.enqueue(a3);
            
        }
        order.snowman.dequeue();
    }
}







int main(int argc, char *argv[])
{
    all_five order; // declare the 5 queues

    if (argc != 2) // check
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) // check if file opened
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    string line;

    while (getline(file, line))
    {
        // what type of command it is
        string cases = get_type(line); 
        if (cases == "SEND")
        {
            Announcement store(line);
            Rank ranks = store.get_rank(); // int form
            switch (ranks)
            {
            case Rank::SNOWMAN:
                order.snowman.enqueue(line);
                break;
            case Rank::ELF1:
                order.elf1.enqueue(line);
                break;
            case Rank::ELF2:
                order.elf2.enqueue(line);
                break;
            case Rank::REINDEER:
                order.reindeer.enqueue(line);
                break;
            case Rank::SANTA:
                order.Santa.enqueue(line);
                break;

            default:
                assert(false);
            }
        }
        else if (cases == "REMOVE_ALL")
        {
            Remove_all(order, line);
        }
        else if (cases == "PROMOTE_ANNOUNCEMENTS")
        {
            Promote(order, line);
        }
        else if (cases == "ANNOUNCE")
        {
            Announcment_fun(order, line);
        }
    } // end of brackets for while loop
    file.close(); // Close the file when done
    return 0;
}