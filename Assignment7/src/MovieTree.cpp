#include "MovieTree.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

MovieTree::MovieTree()
{
    root=NULL;
}


void MovieTree::findMovie(string title)
{
    MovieNode *foundMovie=root;
    int flag=0;
    while (foundMovie!=NULL)
    {
        if (foundMovie->title>title)
            foundMovie=foundMovie->leftChild;
        else if (foundMovie->title<title)
            foundMovie=foundMovie->rightChild;
        else
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            flag=1;
            break;
        }
    }
    if (flag==0)
        cout<<"Movie not found."<<endl;

}

void MovieTree::rentMovie(string title)
{
    MovieNode *foundMovie=root;
    int flag=0;
    while (foundMovie!=NULL)
    {
        if (foundMovie->title>title)
            foundMovie=foundMovie->leftChild;
        else if (foundMovie->title<title)
            foundMovie=foundMovie->rightChild;
        else
        {
            if (foundMovie->quantity==0)
                cout<<"Movie out of stock."<<endl;
            else
            {
                cout<<"Movie has been rented."<<endl;
                cout << "Movie Info:" << endl;
                cout << "===========" << endl;
                cout << "Ranking:" << foundMovie->ranking << endl;
                cout << "Title:" << foundMovie->title << endl;
                cout << "Year:" << foundMovie->year << endl;
                foundMovie->quantity=foundMovie->quantity-1;
                cout << "Quantity:" << foundMovie->quantity << endl;
            }
            flag=1;
            break;
        }
    }
    if (flag==0)
        cout<<"Movie not found."<<endl;

}

void MovieTree::printMovieInventory(MovieNode* node)
{
    if (node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;

    if (node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    MovieNode *node=root;
    printMovieInventory(node);
}

MovieTree::~MovieTree()
{
    //dtor
    DeleteAll(root);
}

void MovieTree::addMovieNode(int ranking,string title, int year,int quantity)
{
    MovieNode *temp=root;
    MovieNode *node=new MovieNode;
    node->parent=NULL;
    node->leftChild=NULL;
    node->rightChild=NULL;
    node=new MovieNode(ranking,title,year,quantity);
    MovieNode *p=NULL;
    while (temp!=NULL)
    {
        p=temp;
        if (node->title<temp->title)
            temp=temp->leftChild;
        else
            temp=temp->rightChild;
    }
    if (p==NULL)
        root=node;
    else if (node->title<p->title)
    {
        p->leftChild=node;
        node->parent=p;
    }
    else
    {
        p->rightChild=node;
        node->parent=p;
    }
}


void MovieTree::deleteMovieNode(string title)
{
    MovieNode *node=root;
    int flag=0;
    while (node!=NULL)
    {
        if (node->title>title)
        {
            node=node->leftChild;
        }
        else if (node->title<title)
        {
            node=node->rightChild;
        }
        else
        {

            if (node->leftChild==NULL&&node->rightChild==NULL)//no child
            {
                if (node->parent->leftChild==node)
                    node->parent->leftChild=NULL;
                else
                    node->parent->rightChild=NULL;
                delete node;
            }
            else if (node->leftChild!=NULL&&node->rightChild!=NULL)//two children
            {
                MovieNode *minimum;
                while (node->leftChild!=NULL)
                {
                    minimum=minimum->leftChild;
                }
                if (minimum==node->rightChild)
                {
                    node->parent->leftChild=minimum;
                    minimum->parent=node->parent;
                }
                else
                {
                    minimum->parent->leftChild=minimum->rightChild;
                    minimum->parent=node->parent;
                    minimum->rightChild->parent=minimum->parent;
                    node->parent->leftChild=minimum;
                    minimum->leftChild=node->leftChild;
                    minimum->rightChild=node->rightChild;
                    node->rightChild->parent=minimum;
                    node->leftChild->parent=minimum;
                }
                delete node;

            }
            else//one child
            {
                MovieNode*x=node->leftChild;
                node->parent->leftChild=x;
                x->parent=node->parent;
                delete node;
            }
        }
    }
    if (flag==0)
        cout<<"Movie not found."<<endl;
}

void MovieTree::countMovieNodes(MovieNode*node, int *c)
{

    if (node->leftChild!=NULL)
    {
        countMovieNodes(node->leftChild, c);
    }
    *c=*c+1;
    if (node->rightChild!=NULL)
    {
        countMovieNodes(node->rightChild, c);
    }

}
void MovieTree::DeleteAll(MovieNode *node)
{
    if (node->leftChild!=NULL)
    {
        DeleteAll(node->leftChild);
    }
    if (node->rightChild!=NULL)
    {
        DeleteAll(node->rightChild);
    }
    cout<<"Deleting "<<node->title<<endl;
    delete node;

}

int MovieTree::countMovieNodes()
{
    if (root!=NULL)
    {
        int *c=new int;
        countMovieNodes(root, c);
        return *c;
    }
    else
    {
        return 0;
    }
}
