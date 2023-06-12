#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_image.h>


struct Cowboy { //struktura gracza
    float PosX = 30.0f;
    float PosY = 220.0f; //startowe pozycje
    int width = 83;
    int height = 87;
    float initialPosX = 30.0f;
    float targetPosX = 30.0f; //target i initial sa zeby po skoku cofal sie na miejsce
    float Speed = 1.5f;
    bool isJumping = false; //flaga zeby sprawdzac czy skacze czy nie
    float jumpVelocity = 25.0f; //wysokosc skoku
};

struct Tumbleweed { //struktura biegacza, jednej z przeszkod
    ALLEGRO_BITMAP * image;
    float posX = 800.0f;
    float posY = 300.0f;
    int width = 25;
    int height = 25;
    int interwal = 500;
    bool draw = false;
    float StartX = 741.0f;
    float StartY = 300.0f; //jak przetoczy sie przez ekran, zeby znowu spawnowal sie poza ekranem
    int currentFrame = 0;
    int FrameCount = 0;
    int FrameDelay = 15;};

struct Skull { //struktura czaszki, drugiej z przeszkod
    ALLEGRO_BITMAP * image;
    float posX = 741.0f;
    float posY = 320.0f;
    int width = 40;
    int height = 29;
    bool isActive = false;};

bool collisionDetect(float PosX, float PosY, int cowboywidth, int cowboyheight,
                     int posX, float posY, float tumblewidth, float tumbleheight) {
    if (PosX <= posX + tumblewidth && PosX + cowboywidth >= posX &&
        PosY <= posY + tumbleheight && PosY + cowboyheight >= posY) {
        return true;} // bylo zdrzenie

    return false;} //nie bylo zderzenia

void resetGame(Cowboy& gracz, Tumbleweed& tumbleweedObstacle, Skull& skullObstacle, int&  score) { //przywraca poczatkowe wartosci gry
    bool isGameOver = false;
    score = 0;
    gracz.PosX = 30.0f;
    gracz.PosY = 220.0f;
    gracz.isJumping = false;
    gracz.jumpVelocity = 25.0f;
    tumbleweedObstacle.draw = false;
    tumbleweedObstacle.posX = tumbleweedObstacle.StartX;
    tumbleweedObstacle.posY = tumbleweedObstacle.StartY;
    tumbleweedObstacle.currentFrame = 0;
    tumbleweedObstacle.FrameCount = 0;
    skullObstacle.isActive = false;}



const int NUM_COWBOY_IMAGES = 5;
const int NUM_TUMBLEWEED_IMAGES = 3; //ilosci obrazkow w animacji

int main() {

    al_init();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY * display = al_create_display(741, 390);
    ALLEGRO_BITMAP * background = al_load_bitmap("tło.png");
    ALLEGRO_BITMAP * skull = al_load_bitmap("czaszka.png");
    ALLEGRO_FONT * font = al_create_builtin_font();

    Cowboy gracz;//inicjalizacja kowboja
    ALLEGRO_BITMAP * cowboy[NUM_COWBOY_IMAGES];
    cowboy[0] = al_load_bitmap("1v2.png");
    cowboy[1] = al_load_bitmap("2v2.png");
    cowboy[2] = al_load_bitmap("3v2.png");
    cowboy[3] = al_load_bitmap("4v2.png");
    cowboy[4] = al_load_bitmap("5v2.png");


    Tumbleweed tumbleweedObstacle;//inicjalizacja biegacza
    ALLEGRO_BITMAP * tumbleweed[NUM_TUMBLEWEED_IMAGES];
    tumbleweed[0] = al_load_bitmap("weed1.png");
    tumbleweed[1] = al_load_bitmap("weed2.png");
    tumbleweed[2] = al_load_bitmap("weed3.png");

    Skull skullObstacle;//inicjalizacja czaszki
    skullObstacle.image = skull;

    float backgroundPos = 0.0f;
    float backgroundSpeed = 0.9f;
    float tumbleweedSpeed = backgroundSpeed;//zeby biegacz toczyl sie z ta sama predkoscia co tlo
    float gravity = 0.5f; //zeby po skoku kowboj wrocil na ziemie

    int currentFrame = 0;
    int frameCount = 0;
    int frameDelay = 10;//to kontroluje szybkosc zmieniania sie klatek animacji kowboja

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER * tumbleweedTimer = al_create_timer(tumbleweedObstacle.interwal / 1000.0); //interwal do sekund


    ALLEGRO_EVENT_QUEUE * eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_timer_event_source(tumbleweedTimer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());


    al_start_timer(timer);
    al_start_timer(tumbleweedTimer);


    srand(time(NULL));

    int score = 0;
    bool startGame = false;


    while (!startGame) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);
        al_draw_bitmap(background, backgroundPos, 0, 0);
        al_draw_bitmap(background, backgroundPos + al_get_bitmap_width(background), 0, 0);
        al_draw_bitmap(cowboy[currentFrame], gracz.PosX, gracz.PosY, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), al_get_display_width(display) / 2,al_get_display_height(display) / 2,ALLEGRO_ALIGN_CENTER, "click space to start");
        al_flip_display();//zeby zanim gra sie zaczne obrazki sie wyswietlaly
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                startGame = true;}}}//gra sie zaczyna po nacisnieciu spacji

    while (startGame==true) {


        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, & event);
        bool isGameOver = false; // flaga czy przegrales

        if (event.type == ALLEGRO_EVENT_TIMER) {

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background, backgroundPos, 0, 0);
            al_draw_bitmap(background, backgroundPos + al_get_bitmap_width(background), 0, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 50, 10,ALLEGRO_ALIGN_RIGHT, "score: %d", score);
            al_draw_bitmap(cowboy[currentFrame], gracz.PosX, gracz.PosY, 0);

            if (gracz.isJumping) {//nowa pozycja w stosunku do skoku
                gracz.PosY -= gracz.jumpVelocity;
                gracz.PosX += gracz.Speed + 3.0f; //plus 3 rzeby skuteczniej omijal przeszkody
                gracz.jumpVelocity -= gravity;


                if (gracz.PosY >= 220.0f) {//sprawdza czy kowboj wyladowal
                    gracz.PosY = 220.0f;
                    gracz.isJumping = false;
                    gracz.targetPosX = gracz.initialPosX;}} //pozycja do ktorej kowboj ma sie cofnac jak nie bedzie skakac

            else {if (gracz.PosX > gracz.targetPosX) {//kowboj cofa sie do swojej poczatkowej pozycji zeby nie wykroczyl
                    gracz.PosX -= gracz.Speed;         //poza ekran po wielokrotnym skoku
                    if (gracz.PosX < gracz.targetPosX)
                        gracz.PosX = gracz.targetPosX;}}


            if (!skullObstacle.isActive) {
                skullObstacle.isActive = true;
                skullObstacle.posX = al_get_display_width(display) % rand();
                skullObstacle.posY = 320.0f;}

            if (skullObstacle.isActive) {//rysuje czaszke
                al_draw_bitmap(skullObstacle.image, skullObstacle.posX, skullObstacle.posY, 0);
                skullObstacle.posX -= backgroundSpeed;

                if (skullObstacle.posX <= -al_get_bitmap_width(skullObstacle.image)) {//dezaktywuje czaske kiedy znika z ekranu
                    skullObstacle.isActive = false;}}


            backgroundPos -= backgroundSpeed;

            if (backgroundPos <= -al_get_bitmap_width(background))//zapetlone tlo
                backgroundPos = 0.0f;


            if (frameCount >= frameDelay) {//animacja kowboja
                currentFrame = (currentFrame + 1) % NUM_COWBOY_IMAGES;
                frameCount = 0;}
            ++frameCount;

            if (tumbleweedObstacle.draw) {//rysuje biegacza i animuje zeby sie krecil
                al_draw_bitmap(tumbleweed[tumbleweedObstacle.currentFrame], tumbleweedObstacle.posX,
                               tumbleweedObstacle.posY, 0);
                ++tumbleweedObstacle.FrameCount;

                if (tumbleweedObstacle.FrameCount >= tumbleweedObstacle.FrameDelay) {
                    tumbleweedObstacle.currentFrame = (tumbleweedObstacle.currentFrame + 1) % NUM_TUMBLEWEED_IMAGES;
                    tumbleweedObstacle.FrameCount = 0;}
                tumbleweedObstacle.posX -= tumbleweedSpeed;//animuje biegacza zeby 'biegl' w lewo

                if (tumbleweedObstacle.draw) {
                    tumbleweedObstacle.posX -= tumbleweedSpeed;
                    if (tumbleweedObstacle.posX <= -al_get_bitmap_width(tumbleweed[0])) {//jesli biegacz przeleci przez ekran zeby znowu sie
                        tumbleweedObstacle.posX = tumbleweedObstacle.StartX;                    //ponownie wygenerowal w oryginalej pozycji
                        tumbleweedObstacle.posY = tumbleweedObstacle.StartY;}}}

            al_flip_display();}


        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            int width = al_get_display_width(display);
            int height = al_get_display_height(display);}


        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_UP) {
                if (!gracz.isJumping) {
                    gracz.isJumping = true;
                    gracz.jumpVelocity = 10.0f;}}} // mechnizm skakania


        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == tumbleweedTimer) {
            if (!tumbleweedObstacle.draw) {
                tumbleweedObstacle.draw = true;}}//generuje biegacza w odpowiednim momencie

        if (tumbleweedObstacle.draw && !gracz.isJumping) {
            if (collisionDetect(gracz.PosX, gracz.PosY, al_get_bitmap_width(cowboy[currentFrame]),
                                al_get_bitmap_height(cowboy[currentFrame]),
                                tumbleweedObstacle.posX, tumbleweedObstacle.posY, tumbleweedObstacle.width,
                                tumbleweedObstacle.height)) {
                isGameOver = true;}} //jesli jest zderzenie miedzy biegaczem a kowbojem wyjscie z petli i koniec gry

        else {score++;}//jesli przeskoczyl dostaje punkty

        if (skullObstacle.isActive && !gracz.isJumping) {
            if (collisionDetect(gracz.PosX, gracz.PosY, al_get_bitmap_width(cowboy[currentFrame]),
                                al_get_bitmap_height(cowboy[currentFrame]),
                                skullObstacle.posX, skullObstacle.posY, skullObstacle.width, skullObstacle.height)) {
                isGameOver = true;}}//jesli jest zderzenie miedzy czaszka a kowbojem wyjscie z petli i koniec gry
        else {score++;}


        if (isGameOver == true) {//kiedy gra sie konczy
            al_draw_text(font, al_map_rgb(255, 255, 255), al_get_display_width(display) / 2,
                         al_get_display_height(display) / 2-60,
                         ALLEGRO_ALIGN_CENTER, "YOU LOSE!");
            al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) / 2,
                          al_get_display_height(display) / 2 -30,
                          ALLEGRO_ALIGN_CENTER, "score: %d", score);
            al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) / 2,
                          al_get_display_height(display) / 2 ,
                          ALLEGRO_ALIGN_CENTER, "click SPACE to start over, ENTER to exit", score);
            al_flip_display();


            int highestScore = 0;
            FILE *file = fopen("highestscore.txt", "r");
            if (file == NULL){return 1;}//jesli nie da sie otworzyc pliku zeby zapisac return 1
            else if (file) {
                fscanf(file, "%d", &highestScore);//czyta obecny najwyzszy wnik
                fclose(file);}

            if (score > highestScore) {//jesli obecny jest wyzszy nadpisuje
                highestScore = score;
                file = fopen("highestscore.txt", "w");
                if (file) {
                    fprintf(file, "%d", highestScore);
                    fclose(file);}}


            while (true) {
                ALLEGRO_EVENT resumeEvent;
                al_wait_for_event(eventQueue, &resumeEvent);
                if (resumeEvent.type == ALLEGRO_EVENT_KEY_DOWN && resumeEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    resetGame( gracz, tumbleweedObstacle, skullObstacle, score);
                    break;}//jesli spacja resetuje wartosci do pierwotych i zaczyna gre od nowa
                else if (resumeEvent.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    return 0; //jesli enter zamyka gre
                }}}}

    al_destroy_bitmap(background);
    for (int i = 0; i < NUM_COWBOY_IMAGES; ++i)
        al_destroy_bitmap(cowboy[i]);
    for (int i = 0; i < NUM_TUMBLEWEED_IMAGES; ++i)
        al_destroy_bitmap(tumbleweed[i]);
    al_destroy_bitmap(skull);
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_timer(tumbleweedTimer);
    al_destroy_event_queue(eventQueue);
    return 0;}