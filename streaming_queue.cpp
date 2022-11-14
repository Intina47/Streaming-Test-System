
/** ## HEADER FILES ## */
#include <iostream>
// include other header files here if required
#include <string>
#include <fstream>
using namespace std;
/** ## CONSTANTS ## */ 
#define FRAME_DATA_SIZE  500 // the number of chars / bytes in a frame


/** ## STRUCT DEFINITION(S) ## */
// a data structure to record details of a movie frame to be placed on the streaming queue
struct MovieFrame {
    double movieID; // the ID of the movie that the frame belongs to
    int sequenceNumber; // the sequence number of the frame within the movie
    char frameData[FRAME_DATA_SIZE]; // the actual data for the frame, as an array of bytes / chars
    MovieFrame* next; // points to next frame in the queue
};


/** ## CLASS DEFINITION ## */
// a class to implement the data structure for the streaming queue
class StreamingQueue
{
private:
    MovieFrame* head; // points to item at head of the queue
    MovieFrame* tail; // points to item at tail of the queue

public:
    StreamingQueue(); // constructor, initialise the queue to be empty
    ~StreamingQueue();  // destructor, free up any resources that are still in use by the queue
    void addFrame(double id, int seqNum, char data[], bool placeAtFront); // adds a new frame to the queue using the data provided
    MovieFrame* removeFrame();  // remove and return (a pointer to) the next frame from the queue for processing
    void displayQueue(); // outputs the entire queue of Tickets to cout
    void dumpQueue(std::string fileName); // outputs the entire queue of Tickets to a specified file on disk
    void recalibrateQueue(); // recalibrates the queue, to sort frames in order of sequence number
};



/** ## IMPLEMENTATION OF THE METHODS DECLARED IN THE StreamingQueue CLASS ## */
// add your method implementations here
StreamingQueue :: StreamingQueue()
{
    head = NULL;
    tail = NULL;
}

StreamingQueue :: ~StreamingQueue()
{
    MovieFrame* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

void StreamingQueue :: addFrame(double id, int seqNum, char data[], bool placeAtFront)
{
    MovieFrame* newFrame = new MovieFrame;
    newFrame->movieID = id;
    newFrame->sequenceNumber = seqNum;
    strcpy(newFrame->frameData, data);
    newFrame->next = NULL;
    
    if (placeAtFront)
    {
        newFrame->next = head;
        head = newFrame;
    }
    else
    {
        if (tail == NULL)
        {
            head = newFrame;
            tail = newFrame;
        }
        else
        {
            tail->next = newFrame;
            tail = newFrame;
        }
    }
}

MovieFrame* StreamingQueue :: removeFrame()
{
    MovieFrame* tmp;
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        tmp = head;
        head = head->next;
        return head;
    }
}

void StreamingQueue :: displayQueue()
{
    MovieFrame* tmp = head;
    if(tmp == NULL)
    {
        cout << "Nothing to display, The queue is empty"<<endl; 
    }else
    {
    while (tmp != NULL)
    {
        cout << "Movie ID: " << tmp->movieID << " Sequence Number: " << tmp->sequenceNumber << " Frame Data: " << tmp->frameData << endl;
        tmp = tmp->next;
    }
 }   
}

void StreamingQueue:: dumpQueue(std::string fileName)
{

  MovieFrame* tmp = head;
  std::ofstream file;
  file.open(fileName,std::ios::app);
if(!file.is_open())
  {
    cout << "Error: File could not be opened!" << endl;
  }else
  {
      cout << "Dump to " << fileName << " was successful"<<endl;
  }
   while (tmp != NULL)
  {
      file << "New addition" <<endl;
      file <<"--------------"<<endl;
    file << "Movie ID: " << tmp->movieID << " Sequence Number: " << tmp->sequenceNumber << " Frame Data: " << tmp->frameData << endl;
    tmp = tmp->next;
  }
 file.close();
}
void StreamingQueue::recalibrateQueue()
{
    cout << "Not implemented :.["<<endl;
}
int display_menu()
{
    int userSelection;
    cout << "This is the RamsFlix International Streaming Test System.\n"<<endl;
    cout << "----------------------------------------"<<endl;
    cout << "Please select one of the choices below:"<<endl;
    cout << "1.Add a frame to the queue.\n2.Remove a frame from the queue.\n3.Display the queue.\n4.Dump the queue.\n5.Recalibrate the queue.\n6.Exit."<<endl;
    cout << "----------------------------------------"<<endl;
    cout << "Enter your choice: ";
    cin >> userSelection;
    cout << endl;

    //input validation
    while(!cin.good())
    {
        cout << "Ooops!! Invalid choice.\n Ensure you choice appears on the menu"<<endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    cout << "This is the RamsFlix International Streaming Test System.\n"<<endl;
    cout << "----------------------------------------"<<endl;
    cout << "Please select one of the choices below:"<<endl;
    cout << "1.Add a frame to the queue.\n2.Remove a frame from the queue.\n3.Display the queue.\n4.Dump the queue.\n5.Recalibrate the queue.\n6.Exit."<<endl;
    cout << "----------------------------------------"<<endl;
    cout << "Enter your choice: ";
    cin >> userSelection;
    cout << endl;

    }
return userSelection;
}
int main()
{
  StreamingQueue queue;
  int userSelection;
  userSelection = display_menu();
  while (userSelection != 6)
  {
    switch (userSelection)
    {
      case 1:
      {
          double id;
          int seqNum;
          char data[FRAME_DATA_SIZE];
               cout << "Enter the movie ID: ";
                cin >> id;
              while(!cin.good())
              {
                  cout << "Error encountered in your input, please try again"<<endl;
                  cin.clear();
                  cin.ignore(INT_MAX, '\n');
                  cout << "Enter the movie ID: ";
                   cin >> id;
              }
               cout << "Enter the sequence number: ";
                cin >> seqNum;
          while(!cin.good())
          {
              cout << "Error encountered in your input, please try again"<<endl;
              cin.clear();
              cin.ignore(INT_MAX, '\n');
              cout << "Enter the sequence number: ";
               cin >> seqNum;
          }
          cout << "Enter the frame data: ";
         cin >> data;
        cout << endl;
         queue.addFrame(id, seqNum, data, false);
        cout << "Added to queue"<<endl;
        break;
          
      }
      case 2:
      {
        MovieFrame* tmp = queue.removeFrame();
        if (tmp == NULL)
        {
          cout << "The queue is empty." << endl;
        }
        else
        {
            cout <<"Adding next frame on line to queue..."<<endl;
          cout << "Movie ID: " << tmp->movieID << " Sequence Number: " << tmp->sequenceNumber << " Frame Data: " << tmp->frameData <<" is next in line"<< endl;
        }
        break;
      }
      case 3:
      {
        queue.displayQueue();
        break;
      }
      case 4:
      {
        string fileName;
        cout << "Enter the file name: ";
        cin >> fileName;
        queue.dumpQueue(fileName);
        break;
      }
      case 5:
      {
        cout << "recalibrating..."<<endl;
        queue.recalibrateQueue();
          cout << "recalibration complete"<<endl;
        break;
      }
      default:
      {
        cout << "Ooops!! Invalid choice.\n Ensure you choice appears on the menu" << endl;
        break;
      }
    }
    userSelection = display_menu();
    
}
cout << "Exiting System..."<<endl;
  return 0;
}

