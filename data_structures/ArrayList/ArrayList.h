/******************************
*  Week 1 lab - exercise 1:   *
*   a simple ArrayList class  *
*******************************/

/*
* Class implementing an array based list.
*/
class ArrayList {
public:
    ArrayList();

    ~ArrayList();

    bool isEmpty();

    void display();

    void add(int);

    void removeAt(int);

private:
    int SIZE;        //size of the array that stores the list items
    int *list;        //array to store the list items
    int length;    //amount of elements in the list
};