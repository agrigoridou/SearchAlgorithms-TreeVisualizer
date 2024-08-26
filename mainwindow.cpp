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

    connect(ui->executeAlgorithmButton, &QPushButton::clicked, this, &MainWindow::on_executeAlgorithmButton_clicked);
    connect(ui->generateRandomTreeButton, &QPushButton::clicked, this, &MainWindow::on_generateRandomTreeButton_clicked);
    connect(ui->addNodeButton, &QPushButton::clicked, this, &MainWindow::on_addNodeButton_clicked);
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

void MainWindow::on_executeAlgorithmButton_clicked()
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

void MainWindow::on_generateRandomTreeButton_clicked()
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

    int numChildren = rand() % maxChildren + 1;

    for (int i = 0; i < numChildren; ++i) {
        Node* child = createRandomTree(depth - 1, maxChildren);
        if (child) {
            node->children.push_back(child);
        }
    }

    return node;
}

void MainWindow::on_addNodeButton_clicked()
{
    int parentValue = ui->parentValueSpinBox->value();
    int childValue = ui->childValueSpinBox->value();

    Node* parentNode = findNodeByValue(root, parentValue);
    if (parentNode) {
        parentNode->addChild(childValue);
        visualizeCurrentState();
    } else {
        ui->statusbar->showMessage("Parent node not found!");
    }
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

void MainWindow::runBFS()
{
    if (root == nullptr) return;
    bfsQueue.clear(); // Clear the queue before starting
    currentNode = root;
    bfsQueue.enqueue(root);
    timer->start(1000);
}

void MainWindow::processNextNode()
{
    if (bfsQueue.isEmpty()) {
        timer->stop();
        return;
    }
    currentNode = bfsQueue.dequeue();
    ui->statusbar->showMessage(QString("Visited: %1").arg(currentNode->value));
    visualizeCurrentState();

    for (Node* child : currentNode->children) {
        bfsQueue.enqueue(child);
    }
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
    std::ofstream file("current_graph.dot");
    if (!file) {
        ui->statusbar->showMessage("Failed to open file for visualization.");
        return;
    }

    file << "digraph G {\n";

    std::function<void(Node*)> traverse = [&](Node* node) {
        std::string color = (node == currentNode) ? "yellow" : "lightgray";
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
