#include "mainwindow.h"
#include "ui_mainwindow.h"

// Aika kellossa muuttuu sekunnin (tuhannen millisekunnin) välein, arvo on vakio
const int TIMER_INTERVAL_MS = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Lisää Minesweeper-ikonin ikkunan otsikkorivin alkuun
    setWindowIcon(QIcon(":/icons/bomb.png"));

    // Ikkunan otsikko
    setWindowTitle("C++ Minesweeper");

    ui->horizontalSlider->setMinimum(3);
    ui->horizontalSlider->setMaximum(12);
    timer_ = new QTimer(this);

    /* Yhdistää ajastinosoittimen itse luotuun onSecTimeriin, joka varmistaa,
     * että ajastin noudattaa oikeaa ajan rakennetta realistisesti, kuten että
     * 60 sekuntia = 1 minuutti yms.
     */
    connect(timer_, &QTimer::timeout, this, &MainWindow::onSecTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Go to slotilla autogeneroitu slottifunktio, joka huolehtii siitä, että
 * siemenluku otetaan talteen arvon näyttämiseksi spinBoxissa. Ottaa vastaan
 * parametrina spinBoxin kokonaisluvun, ei palauta arvoa.
 */
void MainWindow::on_seedValueSpinBox_valueChanged(int arg1)
{

    // Annetaan arvo siemenluvulle
    seedValue_ = arg1;
}

/* Funktiossa käydään läpi koordinaatteja for-loopeilla. Jos "klikkaussignaali
 * havaitaan jonkin ruudun kohdalla", se avataan käyttämällä openSquare-
 * funktiota. Ei ota vastaan parametreja eikä palauta arvoa. For-loopeissa
 * muuttujat positiivisia kokonaislukuja, jotta pääsee eroon varoituksesta,
 * että intin kanssa oltaisiin vertaamassa kahta erityyppistä muuttujaa
 * (graphicalBoardin koko ei voi olla negatiivinen).
 */
void MainWindow::handleSquareClicks()
{
    for (unsigned y = 0; y < graphicalBoard_.size(); y++)
    {
        for (unsigned x = 0; x < graphicalBoard_.size(); x++)
        {
            if (graphicalBoard_.at(y).at(x) == sender())
            {
                openSquare(x, y);
            }
        }
    }

}

/* Funktio huolehtii siitä, että ajastin toimii oikean ajastimen tavoin: minuu-
 * tit kasvavat yhdellä, kun sekuntteja tulee lisää 60. Minuutin vaihduttua
 * sekunnit nollataan. Funktio ei ota vastaan parametreja eikä palauta arvoa.
 */
void MainWindow::onSecTimer()
{
    // lcdNumbereissa näkyvät arvot muuttujiksi
    int seconds = ui->lcdNumberSec->intValue();
    int minutes = ui->lcdNumberMin->intValue();

    seconds++;

    /* Minuutin tullessa täyteen sekunnit nollataan ja minuutteja kasvatetaan
     * yhdellä (uusi minuutti alkaa).
     */
    if (seconds == 60)
    {
        seconds = 0;
        minutes++;
    }

    // Näytetään molemmat aika-arvot GUI:n näytöissä
    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
}

/* Slottifunktio, joka käsittelee Uuden pelin aloittamisen klikkaussignaalia.
 * Ei ota vastaan parametreja eikä palauta arvoa. Jos peli on jo aloitettu,
 * poistaa vanhan ajastimen ja luo uuden, nollaten samalla aika-arvot.
 */
void MainWindow::on_newGamePushButton_clicked()
{
    // Boolean tarkistaa onko peli jo aloitettu
    static bool isGameAlreadyStarted = false;

    board_ = std::make_shared<GameBoard>(GameBoard());

    // Lauta luodaan pohjakoodin init-funktion avulla
    board_->init(seedValue_, boardSize_);

    // Tyhjennetään lauta, jotta peli voidaan aloittaa uudelleen eri lautakoolla
    clearBoard();

    // Lauta tuodaan näkyviin graafiseen käyttöliittymiin (GUI)
    initButtons();

    /* Ajastin aloitetaan ja sekunnin vaihtumisväliksi (interval) asetetaan
     * vakio 1000 millisekuntia eli sekuntti vaihtuu luonnollisesti (arvo kasvaa
     * kerran sekunnissa).
     */
    timer_->start(TIMER_INTERVAL_MS);

    // Jos peli on jo aloitettu, näytöt nollataan eli aika alkaa alusta
    if (isGameAlreadyStarted)
    {
        ui->lcdNumberSec->display(0);
        ui->lcdNumberMin->display(0);
    }

    // Peli on joka tapauksessa alkanut tähän päästessä
    isGameAlreadyStarted = true;

}


/* Täyttää ruudukon (=vektori vektorissa) pelilautaosoittimen avulla.
 * Lisää aina uuden ruudun kohdalle klikattavan napin (QPushButton).
 * Ei ota vastaan parametreja eikä palauta arvoa.
 */
void MainWindow::initButtons()
{

    // Luodaan uusi osoitin QT:n mukana tulevaan centralwidget -widgettiin
    QWidget* central = ui->centralwidget;
    this->resize((3*MARGIN_SIZE)+(BUTTON_SIZE*board_->getSize()),
                 (3*MARGIN_SIZE)+(BUTTON_SIZE*board_->getSize()));

    graphicalBoard_.clear();

    // Pelilauta täytetään sisäkkäisillä silmukoilla
    for(int y = 0; y < board_->getSize(); y++)
    {
        /* Vektoria laajennetaan niin kauan, että koko vastaa pelaajan
         * haluamaa laudan kokoa
         */
        graphicalBoard_.push_back({});

        for (int x = 0; x < board_->getSize(); x++)
        {
            // Täytetään pelilauta QT:n pushButtoneilla
            QPushButton* clickableSquare = new QPushButton("", this);

            /* Yksittäisen ruudun koko asetetaan vakioksi, ja sekä korkeuteen
             * että leveyteen käytetään napin kokovakiota (saadaan aikaan neliö)
             */
            clickableSquare->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
            clickableSquare->setGeometry(MARGIN_SIZE+(x*BUTTON_SIZE),
                                    MARGIN_SIZE+(y*BUTTON_SIZE),
                                    BUTTON_SIZE,
                                    BUTTON_SIZE);

            // Ruutuun asetetaan oletuskuvaksi closedSquare.png
            addButtonIcon(clickableSquare, ":/icons/closedSquare.png");

            /* Tämä tarvitaan napin tuomiseksi esiin, kun tuominen tehdään
             * rakentajan ulkopuolella
             */
            clickableSquare->show();

            graphicalBoard_.at(y).push_back(clickableSquare);

            /* handleSquareClicks-funktio laitetaan vastaamaan napin klikkausta
             * seuraavasta aktiviteetista (funktion toiminta selittetty
             * tarkemmin ennen itse funktiota)
             */
            connect(clickableSquare, &QPushButton::clicked,
                    this, &MainWindow::handleSquareClicks);

        }

    }

    // Asetetaan kaikki em. osaksi centralwidgettiä.
    setCentralWidget(central);

}


/* Ruudunavausfunktio. Funktiota kutsutaan handleSquareClicksistä. openSquaren
 * tehtävänä on nimensä mukaisesti tarkoitus avata itse ruutu. Ottaa paramet-
 * reina koordinaatit, muttei palauta arvoa.
 */
void MainWindow::openSquare(unsigned x, unsigned y)
{
    // Uusi nappiosoitin, joka osoittaa (x, y) -sijainnin nappiin
    QPushButton* coordsOfButton = graphicalBoard_.at(y).at(x);
    Square tile = board_->getSquare(x, y);

    // SEURAAVAT EHDOT TARKISTETAAN ENNEN RUUDUN AVAAMISTA

    /* Poistaa lipun, jos ruudussa on jo lippu ja sitä klikataan
     * Set flagin ollessa rastitettuna.
     */
    if (tile.hasFlag() and isFlagActive_ and not tile.isOpen())
    {
        tile.removeFlag();
        addButtonIcon(coordsOfButton, ":/icons/closedSquare.png");
        board_->setSquare(tile, x, y);
    }

    // Ruudun oltava kiinni, jotta siihen voi lisätä lipun tässä else iffissä
    else if (isFlagActive_ and not tile.isOpen())
    {
        tile.addFlag();
        addButtonIcon(coordsOfButton, ":/icons/flagged.png");
        board_->setSquare(tile, x, y);
    }

    // Peli loppuu, jos klikataan miinaa
    else if (tile.hasMine())
    {
        // Ruutu avautuu
        board_->openSquare(x, y);

        // Ajastin pysähtyy
        timer_->stop();

        // Ruutun kuvaksi vaihdetaan bomb.png
        addButtonIcon(coordsOfButton, ":/icons/bomb.png");

        // Peli loppuu itse luodusssa gameOver-funktiossa
        gameOver();
    }

    // Itse ruudun avaaminen, mikäli mikään em. ehdoista ei täyttynyt
    else
    {
        int adjacent = tile.countAdjacent();
        board_->openSquare(x, y);

        /* Jos jokin viereisistä ruuduista sisältää miinan, käytetään sen
         * numeroa vastaavaa kuvaa ruudun kuvana suljetun kuvan tilalla.
         */
        if (adjacent != 0)
        {
            addButtonIcon(coordsOfButton, formFileName(adjacent));
        }

        else
        {
            for (unsigned y = 0; y < graphicalBoard_.size(); y++)
            {
                for (unsigned x = 0; x < graphicalBoard_.size(); x++)
                {
                    tile = board_->getSquare(x, y);
                    if (tile.isOpen() and not tile.hasMine())
                    {
                        adjacent = tile.countAdjacent();
                        addButtonIcon(graphicalBoard_.at(y).at(x),
                                      formFileName(adjacent));
                    }
                }
            }
        }

    }

    if (board_->isGameOver())
    {
        gameOver(true);
    }

//    qDebug() << x << y;
}

/* Funktion tehtävänä on huolehtia pelin lopettamisesta. Ottaa parametrina
 * booleanin, jota käytetään
 */
void MainWindow::gameOver(bool isGameWon)
{
    QMessageBox::StandardButton reply;

    // Jos peli hävitään
    if (!isGameWon)
    {
        reply = QMessageBox::question(this, "You lost", "New game?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
        {
            this->close();
        }

        else
        {
            on_newGamePushButton_clicked();
        }
    }

    // Muuten peli voitetaan
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "You won", "New game?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
        {
            this->close();
        }

        else
        {
            on_newGamePushButton_clicked();
        }
    }


}

/* Funktio huolehtii kuvien lisäämisistä nappeihin. Ottaa parametreina
 * itse napin sekä polun (käytettävä kuvatiedosto vaihtuu tilanteen mukaan eri
 * paikoissa, joissa tätä funktiota kutsutaan). Ei palauta arvoa.
 */
void MainWindow::addButtonIcon(QPushButton* button, QString path)
{
    QPixmap pixmap(path);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}

/* Funktiota käytetään pelilaudan tyhjentämiseen silloin, kun uusi peli aloi-
 * tetaan, jotta lauta voidaan luoda uudelleen erikokoisena. Ei ota vastaan
 * parametreja eikä palauta arvoa.
 */
void MainWindow::clearBoard()
{
    /* Käydään koordinaatteja läpi sisäkkäisissä silmukoissa niin kauan kun
     * laudalla riittää nappeja.
     */
    for(unsigned y = 0; y < graphicalBoard_.size(); y++)
    {
        for (unsigned x = 0; x < graphicalBoard_.size(); x++)
        {
            // Luodaan uusi osoitin, joka osoittaa (X, Y) sijainnin nappiin
            QPushButton* graphicalBoardPointer = graphicalBoard_.at(y).at(x);

            delete graphicalBoardPointer;

        }

    }
    graphicalBoard_.clear();
}

/* Funktion ideana on käsitellä kuvatiedostojen nimiä. Kuvatiedostot löytyvät
 * aina icons-kansiosta, jonka takia polku alkoitetaan sieltä. Tämän jälkeen
 * polkuun lisätään ruudun numeroa vastaava kuva, jotta siinä voidaan käyttää
 * kuvaa tekstimuotoisen numeron sijasta. Ottaa viereisten määrän parametrina
 * ja palauttaa stringin, joka sisältää polun.
 */
QString MainWindow::formFileName(int adjacent)
{
    QString fileName = ":/icons/";
    std::string adjacentString;
    fileName += QString::number(adjacent) + ".png";
    return fileName;
}

void MainWindow::on_setFlagCheckBox_stateChanged(int)
{
    isFlagActive_ = not isFlagActive_;
    static int i = 0;
    qDebug() << "Checkboxin tilaa vaihdettu onnistuneesti!" << i;
    i++;
}

/* Slottifunktio, joka huolehtii siitä, että slideria liikuttamalla numerot
 * ilmestyvät näytölle. Ottaa vastaan sliderin arvon ja näyttää sen GUI:ssa.
 * Ei palauta arvoa.
 */
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    boardSize_ = position;
    ui->lcdNumberSize->display(position);
}
