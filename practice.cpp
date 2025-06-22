```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "animal.h"
#include "crop.h"
#include "worker.h"
#include "market.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addAnimal();
    void viewAnimals();
    void removeAnimal();
    void plantWheat();
    void plantCorn();
    void harvestCrops();
    void animalCaretakerTasks();
    void fieldWorkerTasks();
    void stimulateNewDay();
    void checkStock();
    void goToMarket();
    void performMarketAction();

private:
    void updateStatusBar();
    void appendOutput(const QString &message);

    QTextEdit *outputText;
    QLineEdit *animalNameInput;
    QComboBox *animalTypeCombo;
    QComboBox *removeAnimalCombo;
    QComboBox *caretakerAnimalCombo;
    QComboBox *marketActionCombo;
    QComboBox *marketStockCombo;
    QLineEdit *marketQuantityInput;

    Animal *animals[10];
    int animalCount = 0;
    Crop *wheat;
    Crop *corn;
    AnimalManager animalManager;
    WorkerManager workerManager;
    Market market;
    double balance = 10.00;
    int wheatStock = 0;
    int cornStock = 0;
};

#endif // MAINWINDOW_H
```

---

#### 2. `mainwindow.cpp`
Implements the GUI layout, button connections, and game logic. The `performMarketAction` function is completed with proper stock updates.

<xaiArtifact artifact_id="3e7328fe-d49a-4801-89b1-7af2d00686ff" artifact_version_id="10b09991-fdab-4249-98a1-cc49afe5d20d" title="mainwindow.cpp" contentType="text/x-c++src">
```cpp
#include "mainwindow.h"
#include <QLabel>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    srand(time(0));
    wheat = new Wheat();
    corn = new Corn();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Title
    QLabel *title = new QLabel("Digital Farm Management System", this);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(title, 0, Qt::AlignCenter);

    // Output area
    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    // Animal Management
    QHBoxLayout *animalLayout = new QHBoxLayout();
    animalNameInput = new QLineEdit(this);
    animalNameInput->setPlaceholderText("Animal Name");
    animalTypeCombo = new QComboBox(this);
    animalTypeCombo->addItems({"Cow", "Chicken"});
    QPushButton *addAnimalBtn = new QPushButton("Add Animal", this);
    QPushButton *viewAnimalsBtn = new QPushButton("View Animals", this);
    removeAnimalCombo = new QComboBox(this);
    QPushButton *removeAnimalBtn = new QPushButton("Remove Animal", this);
    animalLayout->addWidget(animalNameInput);
    animalLayout->addWidget(animalTypeCombo);
    animalLayout->addWidget(addAnimalBtn);
    animalLayout->addWidget(viewAnimalsBtn);
    animalLayout->addWidget(removeAnimalCombo);
    animalLayout->addWidget(removeAnimalBtn);
    mainLayout->addLayout(animalLayout);

    // Crop Management
    QHBoxLayout *cropLayout = new QHBoxLayout();
    QPushButton *plantWheatBtn = new QPushButton("Plant Wheat", this);
    QPushButton *plantCornBtn = new QPushButton("Plant Corn", this);
    QPushButton *harvestBtn = new QPushButton("Harvest Crops", this);
    cropLayout->addWidget(plantWheatBtn);
    cropLayout->addWidget(plantCornBtn);
    cropLayout->addWidget(harvestBtn);
    mainLayout->addLayout(cropLayout);

    // Worker Management
    QHBoxLayout *workerLayout = new QHBoxLayout();
    caretakerAnimalCombo = new QComboBox(this);
    QPushButton *caretakerBtn = new QPushButton("Animal Caretaker", this);
    QPushButton *fieldWorkerBtn = new QPushButton("Field Worker", this);
    workerLayout->addWidget(caretakerAnimalCombo);
    workerLayout->addWidget(caretakerBtn);
    workerLayout->addWidget(fieldWorkerBtn);
    mainLayout->addLayout(workerLayout);

    // Other Actions
    QHBoxLayout *otherLayout = new QHBoxLayout();
    QPushButton *newDayBtn = new QPushButton("New Day", this);
    QPushButton *checkStockBtn = new QPushButton("Check Stock", this);
    QPushButton *marketBtn = new QPushButton("Go to Market", this);
    otherLayout->addWidget(newDayBtn);
    otherLayout->addWidget(checkStockBtn);
    otherLayout->addWidget(marketBtn);
    mainLayout->addLayout(otherLayout);

    // Market Controls
    QHBoxLayout *marketLayout = new QHBoxLayout();
    marketActionCombo = new QComboBox(this);
    marketActionCombo->addItems({"Buy", "Sell"});
    marketStockCombo = new QComboBox(this);
    marketStockCombo->addItems({"Corn", "Wheat", "Milk", "Eggs"});
    marketQuantityInput = new QLineEdit(this);
    marketQuantityInput->setPlaceholderText("Quantity");
    QPushButton *marketActionBtn = new QPushButton("Perform Market Action", this);
    marketLayout->addWidget(marketActionCombo);
    marketLayout->addWidget(marketStockCombo);
    marketLayout->addWidget(marketQuantityInput);
    marketLayout->addWidget(marketActionBtn);
    mainLayout->addLayout(marketLayout);

    // Status Bar
    QLabel *statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("font-size: 16px;");
    mainLayout->addWidget(statusLabel);
    updateStatusBar();

    // Connect buttons to slots
    connect(addAnimalBtn, &QPushButton::clicked, this, &MainWindow::addAnimal);
    connect(viewAnimalsBtn, &QPushButton::clicked, this, &MainWindow::viewAnimals);
    connect(removeAnimalBtn, &QPushButton::clicked, this, &MainWindow::removeAnimal);
    connect(plantWheatBtn, &QPushButton::clicked, this, &MainWindow::plantWheat);
    connect(plantCornBtn, &QPushButton::clicked, this, &MainWindow::plantCorn);
    connect(harvestBtn, &QPushButton::clicked, this, &MainWindow::harvestCrops);
    connect(caretakerBtn, &QPushButton::clicked, this, &MainWindow::animalCaretakerTasks);
    connect(fieldWorkerBtn, &QPushButton::clicked, this, &MainWindow::fieldWorkerTasks);
    connect(newDayBtn, &QPushButton::clicked, this, &MainWindow::stimulateNewDay);
    connect(checkStockBtn, &QPushButton::clicked, this, &MainWindow::checkStock);
    connect(marketBtn, &QPushButton::clicked, this, &MainWindow::goToMarket);
    connect(marketActionBtn, &QPushButton::clicked, this, &MainWindow::performMarketAction);

    setWindowTitle("Digital Farm Management System");
    resize(800, 600);
}

MainWindow::~MainWindow() {
    for (int i = 0; i < animalCount; i++) {
        delete animals[i];
    }
    delete wheat;
    delete corn;
}

void MainWindow::appendOutput(const QString &message) {
    outputText->append(message);
}

void MainWindow::updateStatusBar() {
    QString status = QString("Balance: $%1 | Stock: Milk: %2L, Eggs: %3, Wheat: %4, Corn: %5")
        .arg(balance, 0, 'f', 2)
        .arg(Cow::getMilkCapacity())
        .arg(Chicken::getTotalEggs())
        .arg(wheatStock)
        .arg(cornStock);
    findChild<QLabel*>()->setText(status);
}

void MainWindow::addAnimal() {
    QString name = animalNameInput->text();
    QString type = animalTypeCombo->currentText();
    if (name.isEmpty()) {
        appendOutput("Please enter an animal name.");
        return;
    }
    if (animalCount >= 10) {
        appendOutput("Maximum animal limit reached.");
        return;
    }
    Animal *newAnimal = animalManager.createAnimal(type == "Cow" ? 1 : 2, name.toStdString());
    if (newAnimal) {
        animals[animalCount++] = newAnimal;
        appendOutput(QString("%1 added.").arg(name));
        removeAnimalCombo->addItem(name);
        caretakerAnimalCombo->addItem(name);
        animalNameInput->clear();
    }
}

void MainWindow::viewAnimals() {
    appendOutput("Available Animals: " + QString::number(animalCount));
    for (int i = 0; i < animalCount; i++) {
        appendOutput(QString("%1. %2").arg(i).arg(QString::fromStdString(animals[i]->getName())));
    }
}

void MainWindow::removeAnimal() {
    if (animalCount == 0) {
        appendOutput("No animals to remove.");
        return;
    }
    int index = removeAnimalCombo->currentIndex();
    if (index >= 0 && index < animalCount) {
        QString name = QString::fromStdString(animals[index]->getName());
        animalManager.removeAnimal(animalCount, animals, index);
        appendOutput(name + " removed from the farm.");
        removeAnimalCombo->removeItem(index);
        caretakerAnimalCombo->removeItem(index);
        updateStatusBar();
    }
}

void MainWindow::plantWheat() {
    wheat->grow(this);
    updateStatusBar();
}

void MainWindow::plantCorn() {
    corn->grow(this);
    updateStatusBar();
}

void MainWindow::harvestCrops() {
    harvestCrops(wheat, wheatStock, "Wheat", this);
    harvestCrops(corn, cornStock, "Corn", this);
    updateStatusBar();
}

void MainWindow::animalCaretakerTasks() {
    if (animalCount == 0) {
        appendOutput("No animals added yet.");
        return;
    }
    int index = caretakerAnimalCombo->currentIndex();
    if (index >= 0 && index < animalCount) {
        workerManager.animalCaretakerTasks(animalManager, animalCount, animals, index, this);
        updateStatusBar();
    }
}

void MainWindow::fieldWorkerTasks() {
    workerManager.fieldWorkerTasks(wheat, corn, wheatStock, cornStock, this);
    updateStatusBar();
}

void MainWindow::stimulateNewDay() {
    stimulateNewDay(animalCount, animals, wheat, corn, this);
    updateStatusBar();
}

void MainWindow::checkStock() {
    market.showAvailableStock(Cow::getMilkCapacity(), Chicken::getTotalEggs(), wheatStock, cornStock, this);
}

void MainWindow::goToMarket() {
    appendOutput("Welcome to THE MARKET...");
    appendOutput(QString("Current Balance: $%1").arg(balance, 0, 'f', 2));
}

void MainWindow::performMarketAction() {
    QString action = marketActionCombo->currentText();
    QString stockType = marketStockCombo->currentText();
    bool ok;
    int quantity = marketQuantityInput->text().toInt(&ok);
    if (!ok || quantity <= 0) {
        appendOutput("Invalid quantity.");
        return;
    }

    int index = 0;
    if (stockType == "Corn") index = 1;
    else if (stockType == "Wheat") index = 4;
    else if (stockType == "Milk") index = 3;
    else if (stockType == "Eggs") index = 2;

    int randomCornStock = market.getStock(), randomWheatStock = market.getStock();
    int randomMilkStock = market.getStock(), randomEggStock = market.getStock();
    double cornUnit = market.getUnit(), wheatUnit = market.getUnit();
    double milkUnit = market.getUnit(), eggUnit = market.getUnit();

    if (action == "Buy") {
        appendOutput(QString("Available: Corn: %1 ($%2/2), Wheat: %3 ($%4/2), Milk: %5 ($%6/2), Eggs: %7 ($%8/2)")
            .arg(randomCornStock).arg(cornUnit, 0, 'f', 2)
            .arg(randomWheatStock).arg(wheatUnit, 0, 'f', 2)
            .arg(randomMilkStock).arg(milkUnit, 0, 'f', 2)
            .arg(randomEggStock).arg(eggUnit, 0, 'f', 2));
        if (index == 1 && !market.checkQuantity(quantity, randomCornStock, this)) {
            double value = market.getValue(quantity, cornUnit);
            market.buyStock(balance, cornStock, quantity, value, this);
        } else if (index == 4 && !market.checkQuantity(quantity, randomWheatStock, this)) {
            double value = market.getValue(quantity, wheatUnit);
            market.buyStock(balance, wheatStock, quantity, value, this);
        } else if (index == 3 && !market.checkQuantity(quantity, randomMilkStock, this)) {
            double value = market.getValue(quantity, milkUnit);
            market.buyStock(balance, Cow::milkCapacity, quantity, value, this);
            Cow::addMilk(quantity);
        } else if (index == 2 && !market.checkQuantity(quantity, randomEggStock, this)) {
            double value = market.getValue(quantity, eggUnit);
            market.buyStock(balance, Chicken::totalEggs, quantity, value, this);
            Chicken::addEgg(quantity);
        }
    } else if (action == "Sell") {
        if (index == 1 && !market.checkQuantity(quantity, cornStock, this)) {
            double value = market.getValue(quantity, cornUnit);
            market.sellStock(balance, cornStock, quantity, value, this);
        } else if (index == 4 && !market.checkQuantity(quantity, wheatStock, this)) {
            double value = market.getValue(quantity, wheatUnit);
            market.sellStock(balance, wheatStock, quantity, value, this);
        } else if (index == 3 && !market.checkQuantity(quantity, Cow::getMilkCapacity(), this)) {
            double value = market.getValue(quantity, milkUnit);
            market.sellStock(balance, Cow::milkCapacity, quantity, value, this);
            Cow::removeMilk(quantity);
        } else if (index == 2 && !market.checkQuantity(quantity, Chicken::getTotalEggs(), this)) {
            double value = market.getValue(quantity, eggUnit);
            market.sellStock(balance, Chicken::totalEggs, quantity, value, this);
            Chicken::removeEgg(quantity);
        }
    }
    updateStatusBar();
}
```

---

#### 3. `animal.h`
Defines `Animal`, `Cow`, `Chicken`, and `AnimalManager` classes, with static variables declared.

<xaiArtifact artifact_id="c52c32cb-2852-4630-aafc-9131f4d694ee" artifact_version_id="49d43705-637a-47a2-a412-336c86004f2b" title="animal.h" contentType="text/x-c++hdr">
```cpp
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <cstdlib>
#include <ctime>
#include "mainwindow.h"

class Animal {
protected:
    std::string name;
    int health;
    bool fedToday;

public:
    Animal() {}
    Animal(std::string n) : name(n), health(100), fedToday(false) {}
    virtual void feed(MainWindow *window) = 0;
    virtual void newDay(MainWindow *window) = 0;
    virtual void checkHealth(MainWindow *window) = 0;
    virtual void produce(MainWindow *window) = 0;
    std::string getName() { return name; }
    virtual ~Animal() {}
};

class Cow : public Animal {
    bool milkProduced;
    static int milkCapacity;

public:
    Cow() {}
    Cow(std::string n) : Animal(n), milkProduced(false) {}

    void feed(MainWindow *window) override {
        fedToday = true;
        window->appendOutput(QString("%1 has been fed today.").arg(QString::fromStdString(name)));
        if (health < 100 && health > 0) {
            health += rand() % 12 + 4;
        }
        if (health > 100) health = 100;
        window->appendOutput(QString("Fed cow %1 with hay.").arg(QString::fromStdString(name)));
    }

    void newDay(MainWindow *window) override {
        if (health != 0) {
            if (!fedToday) {
                int drop = rand() % 9 + 7;
                health -= drop;
                window->appendOutput(QString("%1 was not fed today. Health decreased by %2.").arg(QString::fromStdString(name)).arg(drop));
            } else {
                window->appendOutput(QString("%1 was well-fed today. Health remains stable.").arg(QString::fromStdString(name)));
            }
        }
        fedToday = false;
        if (health == 0) {
            window->appendOutput(QString("%1 died. Cause of death: Starvation.").arg(QString::fromStdString(name)));
        } else if (health < 50) {
            window->appendOutput(QString("%1 Health is unstable. Please feed.").arg(QString::fromStdString(name)));
        }
        if (health < 0) health = 0;
        milkProduced = false;
    }

    void produce(MainWindow *window) override {
        if (health > 55 && !milkProduced) {
            int random = rand() % 4 + 2;
            milkCapacity += random;
            window->appendOutput("Cow is producing milk...");
            window->appendOutput(QString("%1 produced %2 liters of milk.").arg(QString::fromStdString(name)).arg(random));
            milkProduced = true;
        } else if (health < 55) {
            window->appendOutput("Health not stable. Cannot produce milk.");
        } else {
            window->appendOutput(QString("%1 already produced milk.").arg(QString::fromStdString(name)));
        }
    }

    void checkHealth(MainWindow *window) override {
        window->appendOutput(QString("%1 has health: %2 /100").arg(QString::fromStdString(name)).arg(health));
        if (health < 50) {
            window->appendOutput(QString("%1 health is unstable. Please feed.").arg(QString::fromStdString(name)));
        }
    }

    static int getMilkCapacity() { return milkCapacity; }
    static void addMilk(int qty) { milkCapacity += qty; }
    static void removeMilk(int qty) { milkCapacity = std::max(0, milkCapacity - qty); }
};

class Chicken : public Animal {
    static int totalEggs;
    bool eggsLaid;

public:
    Chicken() {}
    Chicken(std::string n) : Animal(n), eggsLaid(false) {}

    void feed(MainWindow *window) override {
        fedToday = true;
        window->appendOutput(QString("%1 has been fed today.").arg(QString::fromStdString(name)));
        if (health < 100 && health > 0) {
            health += rand() % 12 + 4;
        }
        if (health > 100) health = 100;
        window->appendOutput(QString("Chicken %1 has been fed with grains.").arg(QString::fromStdString(name)));
    }

    void newDay(MainWindow *window) override {
        if (health != 0) {
            if (!fedToday) {
                int drop = rand() % 9 + 7;
                health -= drop;
                window->appendOutput(QString("%1 was not fed today. Health decreased by %2.").arg(QString::fromStdString(name)).arg(drop));
            } else {
                window->appendOutput(QString("%1 was well-fed today. Health remains stable.").arg(QString::fromStdString(name)));
            }
        }
        fedToday = false;
        if (health == 0) {
            window->appendOutput(QString("%1 died. Cause of death: Starvation.").arg(QString::fromStdString(name)));
        } else if (health < 50) {
            window->appendOutput(QString("%1 Health is unstable. Please feed.").arg(QString::fromStdString(name)));
        }
        if (health < 0) health = 0;
        eggsLaid = false;
    }

    void produce(MainWindow *window) override {
        if (health > 55 && !eggsLaid) {
            int random = rand() % 5 + 1;
            totalEggs += random;
            window->appendOutput("Chicken is laying eggs...");
            window->appendOutput(QString("%1 eggs laid.").arg(random));
            eggsLaid = true;
        } else if (health < 55) {
            window->appendOutput("Health not stable. Cannot lay eggs.");
        } else {
            window->appendOutput(QString("%1 already laid eggs.").arg(QString::fromStdString(name)));
        }
    }

    void checkHealth(MainWindow *window) override {
        window->appendOutput(QString("%1 has health: %2 /100").arg(QString::fromStdString(name)).arg(health));
        if (health < 50) {
            window->appendOutput(QString("%1 health is unstable. Please feed.").arg(QString::fromStdString(name)));
        }
    }

    static int getTotalEggs() { return totalEggs; }
    static void addEgg(int qty) { totalEggs += qty; }
    static void removeEgg(int qty) { totalEggs = std::max(0, totalEggs - qty); }
};

class AnimalManager {
public:
    void removeAnimal(int &animalCount, Animal *animals[], int removeIndex) {
        if (removeIndex >= 0 && removeIndex < animalCount) {
            delete animals[removeIndex];
            for (int i = removeIndex; i < animalCount - 1; i++) {
                animals[i] = animals[i + 1];
            }
            animalCount--;
        }
    }

    Animal *createAnimal(int index, const std::string &name) {
        if (index == 1) return new Cow(name);
        else if (index == 2) return new Chicken(name);
        return nullptr;
    }
};

#endif // ANIMAL_H
```

---

#### 4. `crop.h`
Defines `Crop`, `Wheat`, and `Corn` classes.

<xaiArtifact artifact_id="9efa9700-299a-4d7b-859a-0d174ec58864" artifact_version_id="0d6f327c-fe60-4aaa-bade-d76779c5c553" title="crop.h" contentType="text/x-c++hdr">
```cpp
#ifndef CROP_H
#define CROP_H

#include <string>
#include "mainwindow.h"

class Crop {
protected:
    std::string name;
    int daysToHarvest;
    bool isWatered;

public:
    Crop(std::string n = "") : name(n), isWatered(false), daysToHarvest(-1) {}
    virtual void grow(MainWindow *window) = 0;
    virtual void water(MainWindow *window) = 0;
    virtual void newDay(MainWindow *window) = 0;
    virtual int harvestYield() = 0;
    int getDaysToHarvest() { return daysToHarvest; }
    void setDaysToHarvest(int days) { daysToHarvest = days; }
    bool getIsWatered() { return isWatered; }

    virtual void checkStatus(MainWindow *window) {
        if (daysToHarvest != -1) {
            window->appendOutput(QString("%1 Status: %2 (%3 days remaining)")
                .arg(QString::fromStdString(name))
                .arg(daysToHarvest > 0 ? "Growing" : "Ready to harvest")
                .arg(daysToHarvest));
        } else {
            window->appendOutput(QString("%1 Status: not planted yet.").arg(QString::fromStdString(name)));
        }
    }

    virtual ~Crop() {}
};

class Wheat : public Crop {
public:
    Wheat() : Crop("Wheat") {}
    void grow(MainWindow *window) override {
        daysToHarvest = 3;
        window->appendOutput("Planted wheat seeds.");
    }
    int harvestYield() override {
        if (isWatered || daysToHarvest == 0) {
            return rand() % 26 + 10;
        } else {
            return 0;
        }
    }
    void water(MainWindow *window) override {
        if (daysToHarvest != -1) {
            isWatered = true;
            window->appendOutput(QString("Watering %1...").arg(QString::fromStdString(name)));
        } else {
            window->appendOutput(QString("%1 not planted yet.").arg(QString::fromStdString(name)));
        }
    }
    void newDay(MainWindow *window) override {
        if (daysToHarvest != 0 && daysToHarvest != -1) {
            if (daysToHarvest <= 2 && !isWatered) {
                window->appendOutput(QString("%1 needs to be watered").arg(QString::fromStdString(name)));
            } else if (daysToHarvest > 0) {
                daysToHarvest--;
                if (daysToHarvest > 0) {
                    window->appendOutput(QString("%1 is growing. Days left to harvest: %2")
                        .arg(QString::fromStdString(name)).arg(daysToHarvest));
                }
            }
        }
        if (daysToHarvest == 0) {
            window->appendOutput(QString("%1 is ready to harvest").arg(QString::fromStdString(name)));
        }
        isWatered = false;
    }
};

class Corn : public Crop {
public:
    Corn() : Crop("Corn") {}
    void grow(MainWindow *window) override {
        daysToHarvest = 4;
        window->appendOutput("Corn planted.");
    }
    int harvestYield() override {
        if (isWatered || daysToHarvest == 0) {
            return rand() % 26 + 10;
        } else {
            return 0;
        }
    }
    void water(MainWindow *window) override {
        if (daysToHarvest != -1) {
            isWatered = true;
            window->appendOutput(QString("Watering %1...").arg(QString::fromStdString(name)));
        } else {
            window->appendOutput(QString("%1 not planted yet.").arg(QString::fromStdString(name)));
        }
    }
    void newDay(MainWindow *window) override {
        if (daysToHarvest != 0 && daysToHarvest != -1) {
            if (daysToHarvest <= 2 && !isWatered) {
                window->appendOutput(QString("%1 needs to be watered").arg(QString::fromStdString(name)));
            } else if (daysToHarvest > 0) {
                daysToHarvest--;
                if (daysToHarvest > 0) {
                    window->appendOutput(QString("%1 is growing. Days left to harvest: %2")
                        .arg(QString::fromStdString(name)).arg(daysToHarvest));
                }
            }
        }
        if (daysToHarvest == 0) {
            window->appendOutput(QString("%1 is ready to harvest").arg(QString::fromStdString(name)));
        }
        isWatered = false;
    }
};

#endif // CROP_H
```

---

#### 5. `worker.h`
Defines `Worker`, `AnimalCaretaker`, `FieldWorker`, `WorkerManager`, and utility functions.

<xaiArtifact artifact_id="97240460-7b30-4735-b751-e8d9e2ea095a" artifact_version_id="265ca344-dd1d-4dba-b73d-83b92567f826" title="worker.h" contentType="text/x-c++hdr">
```cpp
#ifndef WORKER_H
#define WORKER_H

#include "animal.h"
#include "crop.h"

class Worker {
public:
    virtual void performTask(MainWindow *window) {}
};

class AnimalCaretaker : public Worker {
public:
    void performTask(MainWindow *window, Animal *animal) {
        window->appendOutput(QString("Feeding and checking %1...").arg(QString::fromStdString(animal->getName())));
        animal->feed(window);
        animal->checkHealth(window);
        animal->produce(window);
    }
};

class FieldWorker : public Worker {
public:
    void performTask(MainWindow *window, Crop *crop) {
        if (!crop->getIsWatered()) {
            crop->water(window);
        }
        crop->checkStatus(window);
    }
};

class WorkerManager {
    AnimalCaretaker caretaker;
    FieldWorker fieldWorker;

public:
    void animalCaretakerTasks(AnimalManager &animalManager, int animalCount, Animal *animals[], int index, MainWindow *window) {
        if (animalCount == 0) {
            window->appendOutput("No animals added yet.");
            return;
        }
        if (index >= 0 && index < animalCount) {
            caretaker.performTask(window, animals[index]);
        }
    }

    void fieldWorkerTasks(Crop *wheat, Crop *corn, int &wheatStock, int &cornStock, MainWindow *window) {
        fieldWorker.performTask(window, wheat);
        fieldWorker.performTask(window, corn);
    }
};

void harvestCrops(Crop *crop, int &stock, const std::string &name, MainWindow *window) {
    if (crop->getDaysToHarvest() == 0) {
        int yield = crop->harvestYield();
        stock += yield;
        window->appendOutput(QString("%1 harvested! Yield: %2 units.").arg(QString::fromStdString(name)).arg(yield));
        crop->setDaysToHarvest(-1);
    } else {
        crop->checkStatus(window);
    }
}

void stimulateNewDay(int &animalCount, Animal *animals[], Crop *wheat, Crop *corn, MainWindow *window) {
    window->appendOutput("A new day has begun...");
    for (int i = 0; i < animalCount; i++) {
        animals[i]->newDay(window);
    }
    wheat->newDay(window);
    corn->newDay(window);
}

#endif // WORKER_H
```

---

#### 6. `market.h`
Defines the `Market` class.

<xaiArtifact artifact_id="9affffcb-be21-4105-9137-9b8d140fe288" artifact_version_id="f8613895-7ef9-4f11-a064-b1b75c8d8e8f" title="market.h" contentType="text/x-c++hdr">
```cpp
#ifndef MARKET_H
#define MARKET_H

#include "animal.h"

class Market {
public:
    bool checkQuantity(int &quantity, const int &stock, MainWindow *window) {
        if (quantity > stock) {
            window->appendOutput("Error! Cannot process, Stock seems to be low.");
            return true;
        }
        return false;
    }

    void showAvailableStock(int milkStock, int eggStock, int &wheatStock, int &cornStock, MainWindow *window) {
        window->appendOutput("Currently Available Stocks");
        window->appendOutput(QString("1. Corn: %1 Units").arg(cornStock));
        window->appendOutput(QString("2. Eggs: %1 Units").arg(eggStock));
        window->appendOutput(QString("3. Milk: %1 Liters").arg(milkStock));
        window->appendOutput(QString("4. Wheat: %1 Units").arg(wheatStock));
    }

    void buyStock(double &balance, int &stock, int &quantity, double &value, MainWindow *window) {
        if (value > balance) {
            window->appendOutput("Not enough balance to buy.");
        } else if (balance > 0) {
            stock += quantity;
            balance -= value;
            window->appendOutput(QString("Purchased %1 units/liters for $%2").arg(quantity).arg(value, 0, 'f', 2));
        }
    }

    void sellStock(double &balance, int &stock, int &quantity, double &value, MainWindow *window) {
        stock -= quantity;
        balance += value;
        window->appendOutput(QString("%1 units/liters sold. $%2 earned!!").arg(quantity).arg(value, 0, 'f', 2));
    }

    double getValue(int &quantity, double &stock) {
        return (quantity * stock) / 2;
    }

    int getStock() {
        return rand() % 35 + 20;
    }

    double getUnit() {
        return (rand() % 3 + 1.0) / 2;
    }
};

#endif // MARKET_H
```

---

#### 7. `main.cpp`
Initializes the Qt application and static variables.

<xaiArtifact artifact_id="7e901b16-5b68-40a9-8a4e-b4ac2fa507be" artifact_version_id="e788beed-102a-41a5-ba1e-d320d6d1863e" title="main.cpp" contentType="text/x-c++src">
```cpp
#include "mainwindow.h"
#include <QApplication>

int Cow::milkCapacity = 0;
int Chicken::totalEggs = 0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
