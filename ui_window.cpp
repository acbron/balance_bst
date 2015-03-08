#include "ui_window.h"
#include <QtWidgets>

const int BASE_HEIGHT = 600;
const int BASE_WIDTH = 1200;
const int MAX_TOOLBAR_HEIGHT = 48;
const int MAX_LINE_EDIT_LENGTH = 128;
const int MAX_LINE_INPUT_LENGTH = 4;
const int MIN_LINE_INPUT_LENGTH = 1;

int WorksWidget::i = 0;

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    toolbar = new ToolBar(centralWidget);
    workspace = new WorksWidget(centralWidget);
    workspace->setMinimumSize(BASE_WIDTH, BASE_HEIGHT);

    vlayout->addWidget(toolbar);
    vlayout->addWidget(workspace);
    centralWidget->setLayout(vlayout);
    createStatusBar();

    /*
    UiNode *label = new UiNode(workspace, 100, 100);

    QPropertyAnimation *p = new QPropertyAnimation(label, "pos");
    p->setDuration(10000);
    p->setStartValue(QPoint(100, 100));
    p->setEndValue(QPoint(500, 500));
    p->start();
    */
    connect(toolbar, SIGNAL(sendPaintingSignal(const QString &)), workspace, SLOT(changeStatus(const QString &)));

}

MainWindow::~MainWindow()
{

}



void MainWindow::createActions()
{
    bstAction = new QAction(tr("&Binary Search Tree"), this);
    avlAction = new QAction(tr("&AVL Tree"), this);
    rbtAction = new QAction(tr("&Red Black Tree"), this);
    sbtAction = new QAction(tr("&Size Balanced Tree"), this);

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    selectMenu = menuBar()->addMenu(tr("&Select"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    selectMenu->addAction(bstAction);
    selectMenu->addAction(avlAction);
    selectMenu->addAction(rbtAction);
    selectMenu->addAction(sbtAction);

    helpMenu->addAction(aboutAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Status Bar"));
}

WorksWidget::WorksWidget()
{

}

WorksWidget::WorksWidget(QWidget *parent)
{
    setParent(parent);
}

WorksWidget::~WorksWidget()
{

}

void WorksWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach (Edge *edge, edges) {
        edge->paint(painter);
    }
}

void WorksWidget::changeStatus(const QString &str)
{
    label = new UiNode(this, 100, 100, str);
    label->show();
    /*
    i++;
    Edge *edge = NULL;
    edge = new Edge(i, i, i + 100, i + 100);
    edges << edge;
    update();
    QPropertyAnimation a(shape, "geometry");
    a.setDuration(10000);
    a.setStartValue(QRect(0, 0, 100, 100));
    a.setEndValue(QRect(100, 100, 100, 100));
    a.start();
    */
}

ToolBar::ToolBar()
{

}

ToolBar::ToolBar(QWidget *parent)
{
    setParent(parent);
    initialize();
}

ToolBar::~ToolBar()
{

}

void ToolBar::initSize()
{
    setMinimumSize(BASE_WIDTH, MAX_TOOLBAR_HEIGHT);
    setMaximumHeight(MAX_TOOLBAR_HEIGHT);
}

void ToolBar::initLayout()
{
    hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft);
    hlayout->addWidget(insertLine);
    hlayout->addWidget(insertButton);
    hlayout->addWidget(removeLine);
    hlayout->addWidget(removeButton);
    hlayout->addWidget(searchLine);
    hlayout->addWidget(searchButton);
    this->setLayout(hlayout);
}

void ToolBar::initElements()
{
    insertLine = new QLineEdit(this);
    removeLine = new QLineEdit(this);
    searchLine = new QLineEdit(this);
    insertLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);
    removeLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);
    searchLine->setFixedWidth(MAX_LINE_EDIT_LENGTH);
    insertLine->setInputMask(QString("9999"));
    removeLine->setInputMask(QString("9999"));
    searchLine->setInputMask(QString("9999"));
    insertLine->setPlaceholderText(tr("input..."));
    removeLine->setPlaceholderText(tr("input..."));
    searchLine->setPlaceholderText(tr("input..."));

    insertButton = new QPushButton(tr("insert"), this);
    removeButton = new QPushButton(tr("remove"), this);
    searchButton = new QPushButton(tr("search"), this);
    insertButton->setMaximumWidth(60);
    removeButton->setMaximumWidth(60);
    searchButton->setMaximumWidth(60);

    connect(insertButton, SIGNAL(clicked()), this, SLOT(emitPaintingSignal()));
}

void ToolBar::initialize()
{
    initSize();
    initElements();
    initLayout();
/*
 * Set Background
 *
    QPixmap pixmap = QPixmap(":/img/ToolBar.png").scaled(this->size());
    QPalette Pal(palette());
    Pal.setBrush(QPalette::Background, QBrush(pixmap));
    setAutoFillBackground(true);
    setPalette(Pal);
*/

}

void ToolBar::emitPaintingSignal()
{
    QString tmp = insertLine->text();
    emit sendPaintingSignal(tmp);
}
