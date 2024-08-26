#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QTimer>
#include <QStack>
#include "Node.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateRandomTreeButton_clicked();
    void on_addNodeButton_clicked();
    void on_executeAlgorithmButton_clicked();
    void processNextNode(); // This will handle BFS and DFS processing
    void processNextNodeDFS(); // Add if using DFS

private:

    Ui::MainWindow *ui;
    Node* root;
    Node* currentNode;
    QTimer* timer;
    QQueue<Node*> bfsQueue; // For BFS
    QStack<Node*> dfsStack; // For DFS


    Node* createRandomTree(int depth, int maxChildren);
    Node* findNodeByValue(Node* node, int value);
    void runDFS(); // Start DFS traversal
    void runBFS();
    void runUCS(); // Placeholder for UCS
    void runAStar(); // Placeholder for A*
    void runBestFirstSearch(); // Placeholder for Best-First Search
    void runIDS(); // Placeholder for IDS
    void runBacktracking(); // Placeholder for Backtracking
    void visualizeCurrentState();
    void deleteTree(Node* node);
};

#endif // MAINWINDOW_H
