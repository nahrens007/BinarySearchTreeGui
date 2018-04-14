/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 *
 * This class is the "About" window - it gives information about the project.
 */

#include "bst_about_window.h"
#include <QTextEdit>

BST_About_Window::BST_About_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("About BST Visualization");
    window->setFixedSize(QSize(350, 300));

    QVBoxLayout *specifierLayout = new QVBoxLayout();
    specifierLayout->addWidget(new QLabel("Date:"));
    specifierLayout->addWidget(new QLabel("Funding:"));
    specifierLayout->addWidget(new QLabel("Programmer:"));

    labelLayout = new QVBoxLayout;
    labelLayout->addWidget(new QLabel("Summer 2017"));
    labelLayout->addWidget(new QLabel("Ashland University Computer Science Department"));
    labelLayout->addWidget(new QLabel("Nathan Ahrens (nahrens@ashland.edu)"));

    QVBoxLayout *textAreaLayout = new QVBoxLayout();
    QTextEdit *txtEdit = new QTextEdit("The Binary Search Tree Visualization program was developed by "
                                       "Nathan Ahrens who, at the time, was an Ashland University sophomore. Started as "
                                       "a fun project, the Binary Search Tree Visualization program was brought to the attention of "
                                       "Dr. Iyad Ajwa, who helped turn it into a grant-funded project. The project now has the purpose of "
                                       "helping the faculty of Ashland University better describe and display what a Binary Search Tree is to "
                                       "freshman and sophomore students.<br/>"
                                       "For more information, view the project on GitHub:<br/>"
                                       "<i>https://github.com/redninja2/BinarySearchTreeGui</i>"
                                       "<br/><br/>"
                                       "<b>What about depthfirst traversal?</b><br/>"
                                       "The depthfirst traversal algorithm is the same as the preorder traversal.");
    txtEdit->setStyleSheet("background-color: white; color: black;");
    txtEdit->setReadOnly(true);
    textAreaLayout->addWidget(txtEdit);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(specifierLayout);
    containerLayout->addLayout(labelLayout);

    QVBoxLayout *vContainerLayout = new QVBoxLayout();
    vContainerLayout->addLayout(containerLayout);
    vContainerLayout->addLayout(textAreaLayout);

    container = new QWidget;
    container->setLayout(vContainerLayout);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(container);
    // mainLayout->addLayout(buttonLayout); // layout for ok/close button

    centralWidget = new QWidget(window);
    centralWidget->setLayout(mainLayout);

    window->setCentralWidget(centralWidget);
}

BST_About_Window::~BST_About_Window()
{
    delete labelLayout;
    delete containerLayout;
    delete container;
    delete mainLayout;
    delete centralWidget;
    delete window;
}

void BST_About_Window::show()
{
    window->setVisible(true);
    window->activateWindow();
    return;
}

void BST_About_Window::close()
{
    window->close();
    return;
}
