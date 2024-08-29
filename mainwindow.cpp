#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "SearchAlgorithms.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include <QQueue>
#include <QStack>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , root(nullptr)
    , currentNode(nullptr)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    connect(timer, &QTimer::timeout, this, &MainWindow::processNextNode);

    connect(ui->executeAlgorithmButton, &QPushButton::clicked, this, &MainWindow::executeAlgorithmButton);
    connect(ui->generateRandomTreeButton, &QPushButton::clicked, this, &MainWindow::generateRandomTreeButton);
    connect(ui->addNodeButton, &QPushButton::clicked, this, &MainWindow::addNodeButton);
}

MainWindow::~MainWindow()
{
    delete ui;
    deleteTree(root); // Correctly call deleteTree
}

void MainWindow::deleteTree(Node* node)
{
    if (!node) return;
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

void MainWindow::executeAlgorithmButton()
{
    QString selectedAlgorithm = ui->algorithmComboBox->currentText();

    if (selectedAlgorithm == "BFS") {
        runBFS();
    } else if (selectedAlgorithm == "DFS") {
        runDFS();
    } else if (selectedAlgorithm == "UCS") {
        runUCS();
    } else if (selectedAlgorithm == "A*") {
        runAStar();
    } else if (selectedAlgorithm == "Best-First Search") {
        runBestFirstSearch();
    } else if (selectedAlgorithm == "IDS") {
        runIDS();
    } else if (selectedAlgorithm == "Backtracking") {
        runBacktracking();
    }
}

void MainWindow::generateRandomTreeButton()
{
    if (root) {
        deleteTree(root); // Correctly call deleteTree
        root = nullptr;
    }
    root = createRandomTree(3, 3);  // Create a tree with depth 3 and up to 3 children per node
    if (root) {
        visualizeCurrentState();
    } else {
        ui->statusbar->showMessage("Failed to create a random tree.");
    }
}

Node* MainWindow::createRandomTree(int depth, int maxChildren)
{
    if (depth == 0) return nullptr;

    int value = rand() % 100;
    Node* node = new Node(value);

    int goalValue = ui->goalSpinBox->value();


    if (value == goalValue || (depth == 1 && rand() % 2 == 0)) {
        node->value = goalValue;
    }

    int numChildren = rand() % maxChildren + 1;

    for (int i = 0; i < numChildren; ++i) {
        Node* child = createRandomTree(depth - 1, maxChildren);
        if (child) {
            node->children.push_back(child);
        }
    }

    return node;
}



void MainWindow::addNodeButton()
{
    int parentValue = ui->parentValueSpinBox->value();
    int childValue = ui->childValueSpinBox->value();


    Node* parentNode = findNodeByValue(root, parentValue);
    if (!parentNode) {
        parentNode = new Node(parentValue);
        if (root == nullptr) {
            root = parentNode;
        }

    }


    Node* newNode = new Node(childValue);
    parentNode->children.push_back(newNode);


    visualizeCurrentState();
}


Node* MainWindow::findNodeByValue(Node* node, int value)
{
    if (!node) return nullptr;
    if (node->value == value) return node;
    for (Node* child : node->children) {
        Node* found = findNodeByValue(child, value);
        if (found) return found;
    }
    return nullptr;
}




void MainWindow::processNextNode()
{
    if (bfsQueue.isEmpty()) {
        timer->stop();
        ui->statusbar->showMessage("Queue is empty. Search ended.");
        return;
    }

    currentNode = bfsQueue.dequeue();
    visitedNodes.append(currentNode);
    ui->statusbar->showMessage(QString("Visited: %1").arg(currentNode->value));
    visualizeCurrentState();

    int goalValue = ui->goalSpinBox->value();
    if (currentNode->value == goalValue) {
        timer->stop();
        ui->statusbar->showMessage(QString("Goal Found: %1").arg(currentNode->value));
        displayPath();
        return;
    }

    for (Node* child : currentNode->children) {
        bfsQueue.enqueue(child);
    }

    if (bfsQueue.isEmpty()) {
        timer->stop();
        ui->statusbar->showMessage("Search completed without finding the goal.");
    }
}




void MainWindow::displayPath()
{
    QString path = "Path to goal: ";
    for (Node* node : visitedNodes) {
        path += QString::number(node->value) + " -> ";
    }
    path.chop(4);
    ui->statusbar->showMessage(path);
}





void MainWindow::runBFS()
{
    if (!root) return;
    bfsQueue.clear();
    visitedNodes.clear();
    currentNode = root;
    bfsQueue.enqueue(root);
    ui->statusbar->showMessage("Run BFS...");
    connect(timer, &QTimer::timeout, this, &MainWindow::processNextNode);
    timer->start(1000);
}




void MainWindow::runDFS()
{
    if (root == nullptr) return;
    dfsStack.clear(); // Clear the stack before starting
    dfsStack.push(root);
    connect(timer, &QTimer::timeout, this, &MainWindow::processNextNodeDFS);
    timer->start(1000);
}




void MainWindow::processNextNodeDFS()
{
    if (dfsStack.isEmpty()) {
        timer->stop();
        return;
    }
    currentNode = dfsStack.pop();
    ui->statusbar->showMessage(QString("Visited: %1").arg(currentNode->value));
    visualizeCurrentState();

    for (Node* child : currentNode->children) {
        dfsStack.push(child);
    }

    if (bfsQueue.isEmpty() || dfsStack.isEmpty()) {
        timer->stop();
        disconnect(timer, &QTimer::timeout, this, &MainWindow::processNextNode);
        disconnect(timer, &QTimer::timeout, this, &MainWindow::processNextNodeDFS);
        return;
    }

}

void MainWindow::runUCS()
{
    // Implement UCS algorithm logic
    SearchAlgorithms::UCS(root);
    visualizeCurrentState();
}

void MainWindow::runAStar()
{
    // Implement A* algorithm logic
    SearchAlgorithms::AStar(root);
    visualizeCurrentState();
}

void MainWindow::runBestFirstSearch()
{
    int goalValue = ui->goalSpinBox->value(); // Assuming you have a UI element for goal value
    SearchAlgorithms::BestFirstSearch(root, goalValue); // Pass the goal value
    visualizeCurrentState();
}


void MainWindow::runIDS()
{
    // Implement IDS algorithm logic with a default depth or configurable depth
    SearchAlgorithms::IDS(root, 3);
    visualizeCurrentState();
}

void MainWindow::runBacktracking()
{
    // Implement Backtracking algorithm logic
    bool found = SearchAlgorithms::Backtracking(root, ui->goalSpinBox->value());
    visualizeCurrentState();
    ui->statusbar->showMessage(found ? "Goal Found!" : "Goal Not Found");
}

void MainWindow::visualizeCurrentState()
{
    int goalValue = ui->goalSpinBox->value();
    std::ofstream file("current_graph.dot");
    if (!file) {
        ui->statusbar->showMessage("Failed to open file for visualization.");
        return;
    }

    file << "digraph G {\n";

    std::function<void(Node*)> traverse = [&](Node* node) {
        std::string color;
        if (node == currentNode) {
            color = "yellow";
        } else if (node->value == goalValue) {
            color = "red";
        } else {
            color = "lightgray";
        }

        file << "  " << node->value << " [style=filled, fillcolor=" << color << "];\n";
        for (Node* child : node->children) {
            file << "  " << node->value << " -> " << child->value << ";\n";
            traverse(child);
        }
    };

    traverse(root);
    file << "}\n";
    file.close();
    system("dot -Tpng current_graph.dot -o current_graph.png");

    QPixmap pixmap("current_graph.png");
    ui->graphLabel->setPixmap(pixmap);
}
