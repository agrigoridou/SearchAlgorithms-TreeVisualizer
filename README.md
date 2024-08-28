# SearchAlgorithms-TreeVisualizer

![image](https://github.com/user-attachments/assets/1f703302-8e28-4f7f-8945-22090ef32970)


Tree Visualizer creates and visualizes trees and supports various search algorithms such as BFS, DFS, UCS, A*, Best-First Search, IDS, and Backtracking. It provides the ability to generate random trees, add nodes, and visualize the current state of the tree.

## Requirements

- Qt 5 or Qt 6
- C++ Compiler
- Graphviz (for tree visualization)

## Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/agrigoridou/TreeVisualizer.git
    cd TreeVisualizer
    ```

2. **Set up the Qt Project:**

    Open the project in Qt Creator or run the following to generate the Makefile:

    ```sh
    qmake
    ```

3. **Install the required packages:**

    Install Graphviz if you haven't already. It depends on your system:

    - **For Ubuntu/Debian:**

        ```sh
        sudo apt-get install graphviz
        ```

    - **For macOS (Homebrew):**

        ```sh
        brew install graphviz
        ```

4. **Build the project:**

    ```sh
    make
    ```

5. **Run the application:**

    ```sh
    ./TreeVisualizer
    ```

## Usage

- **Generate Random Tree:** Click the "Generate Random Tree" button to create a random tree with a depth of 3 and up to 3 children per node.

- **Add Node:** Enter the values for the parent node and the new node, then click the "Add Node" button.

- **Execute Algorithm:** Select an algorithm from the dropdown menu and click the "Execute Algorithm" button to start the search.

- **Visualize Tree:** The tree's state is visualized in the application's graphical interface and saved as a PNG file.
