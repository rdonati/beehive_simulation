#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"


LinkedList* createLinkedList() {
  LinkedList* ll;
  ll = (LinkedList *)malloc( sizeof( LinkedList ));
  ll->head = 0;
  ll->tail = 0;
  return( ll );
}

Node* createNewLLNode( int data ) {
  Node* newnode = (Node*)malloc( sizeof( Node ));
  newnode->data = data;
  newnode->next = 0;
  newnode->prev = 0;
  return( newnode );
}

void insertInLinkedList( LinkedList* ll, int data ) {
  Node* newnode = createNewLLNode( data );

  if ( ll->head == 0 ) { // first item
    ll->head = newnode;
    ll->tail = newnode;
  } else {
    newnode->next = ll->head;
    ll->head->prev = newnode;
    ll->head = newnode;
  }
}

void printNodeData( Node* n ) {
  printf( "%d ", n->data );
}

void printLinkedList( LinkedList* ll ) {
  Node* current;
  if ( ll->head != 0 ) {
    printf( "Data: " );
    current = ll->head;
    while( current != 0 ) {
      printNodeData( current );
      current = current->next;
    }
    printf( "\n" );
  }
}

/*
    remove the value from the LinkedList if it exists (just the first occurrence).
    Returns true if successful, false if not
    */
bool recursiveRemove(Node* head,int value){
     if(head == 0){
            return false;
       }
        if(head->data == value){

            head->next->prev = head->prev;
            head->prev->next = head->next;
            return true;
        }
        else{
            return recursiveRemove(head->next,value);
        }
}

bool removeInt( LinkedList* ll, int value ) {
    if(ll->head == 0){
        return false;
    }
   if((ll->head)->data == value){
       if(ll->head->next == 0){
           ll->head=0;
           ll->tail=0;
           return true;
       }
       else{
       (ll->head)->next->prev = 0;
        ll->head=(ll->head)->next;
       }
        return true;
    }
    else{
        return recursiveRemove((ll->head),value);
    }
}

