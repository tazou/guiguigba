#include <hel2.h>
#include "gfx/ResourceData.h"

#define TEXT_LAYER 1
#define SCREEN_LAYER 3
#define SOLPEACH 113
#define SOL 113
#define SOLTORTUE 110
#define SOLMONSTRE 110
#define MAXDROITE 220
#define XPEACH 2

// Prototypes
void app_init();
void FAT_initSpritePalette();
void app_showImgBackground();
void app_showImgGameCover();
void app_writeSomeText(char* text, u8 xTEXT, u8 yTEXT);
void hidePerso();
void showPerso();
void deplace();
void app_showFirstScreen();
void animePersonage();
void discoursChampi();
void app_showImgNiveau1();
void app_showImgNiveau2();
void app_showImgIntroChampi();

THandle tabUsbKey[5];
THandle tabMonstre[5];
THandle tabTortue[5];
u8 x=2;
u8 y=70;
u8 yPeach;
u8 xPeach;
u8 jump;
bool unSurDeux = 0;
bool jumpBreak = 0;
u8 xMonstre = 30;
bool level1complete = 0;
u8 nbMonstres = 0;
u8 xUsbKey = 2;
u8 yUsbKey = 2;

int main(){
  app_init();
  initPeach();
  initChamp1();
  initTortue();
  initMonstre();
  initUsbKey();

  //Couverture du jeu
  app_showImgGameCover();
  app_writeSomeText("Princesse Morgane",6,2);
  app_writeSomeText("au pays des geeks !",5,5);
  app_writeSomeText("[PRESS START]",8,13);
  animePersonage();//Cette fonction fait la boucle sur la gestion clavier.

  //Screen avec le champi et discours
  FAT_reinitScreen();
  app_showImgIntroChampi();
  showPerso();
  movePeach(XPEACH,SOLPEACH);
  yPeach = SOLPEACH;
  xPeach = XPEACH;
  bool textOK = 0;
  for(;;){
    hel_PadCapture();
    if (hel_PadQuery()->Pressed.Right){
      xPeach++;
      if(xPeach>=175) {
        //discoursChampi();
        app_writeSomeText("Bonjour Morgane, je suis ",2,4);
        app_writeSomeText("un gentil petit champi",2,5);
        app_writeSomeText("et je vais te raconter",2,6);
        app_writeSomeText("une histoire.",2,7);
        app_writeSomeText("Tu viens d'etre catapulte",2,8);
        app_writeSomeText("dans un mode magique...",2,9);
        app_writeSomeText("Le monde des geeks !",2,10);
        app_writeSomeText("Ta mission si tu l'acceptes",2,11);
        app_writeSomeText("est d'aller delivrer ton",2,12);
        app_writeSomeText("geek d'amour :)",2,13);
        app_writeSomeText("[PRESS A]",5,16);

        for(;;) {
          hel_PadCapture();
          if (hel_PadQuery()->Pressed.A || hel_PadQuery()->Pressed.B) {
              break;
          }
          hel_SwiVBlankIntrWait();
        }
        FAT_reinitScreen();
        app_writeSomeText("Il est actuellement",1,4);
        app_writeSomeText("prisonnier dans une boucle",2,5);
        app_writeSomeText("infinie.",2,6);
        app_writeSomeText("Pour cela tu devras eviter",2,7);
        app_writeSomeText("des petits monstres et",2,8);
        app_writeSomeText("les pluies de clefs usb.",2,9);
        app_writeSomeText("Appuie sur START pour ",2,14);
        app_writeSomeText("demarrer ta quete!",2,15);
        textOK = 1;
      }else {
        xPeach+=4;
        movePeach(xPeach,yPeach);
      }
    }
    if (hel_PadQuery()->Pressed.Start){
      break;
    }
    hel_SwiVBlankIntrWait();
  }

  //Niveau 1 : il faut éviter les monstres
  FAT_reinitScreen();
  app_showImgNiveau1();

  //peach au sol
  showPerso();
  movePeach(XPEACH,SOLPEACH);
  yPeach = SOLPEACH;
  xPeach = XPEACH;

  //tortue
  u8 xTortue = MAXDROITE;
  u8 xTortue1 = MAXDROITE;
  u8 xTortueBis = MAXDROITE;
  u8 xTortueVole = MAXDROITE;

  //monstre
  xMonstre = MAXDROITE;
  u8 xMonstre3 = MAXDROITE;
  u8 xMonstre1 = MAXDROITE;
  u8 xMonstre2 = MAXDROITE;
  bool declencheM1 = 0;
  bool declencheM0 = 0;
  bool declencheM2 = 0;
  bool declencheT1 = 0;
  bool declencheT0 = 1;
  bool dTortue = 0;

  for (;;) {
        hel_PadCapture();
        if (hel_PadQuery()->Pressed.A || hel_PadQuery()->Pressed.B){
          jump = 1;
          if(jumpBreak == 0){
            jumpPeach();
            jumpBreak = 1;
          }
        }
        if (hel_PadQuery()->Pressed.Right){
            xPeach+=4;
            movePeach(xPeach,yPeach);
          //jump peach
          if (jump == 1){
            if(jumpBreak == 0){
              jumpPeach();
              jumpBreak = 1;
            }
          }
        }
        if (hel_PadQuery()->Pressed.Left){
          if(xPeach > 2){
            xPeach-=4;
            movePeach(xPeach,yPeach);
          }
        }

        //Avance monstre
        if(nbMonstres == 0 || nbMonstres == 2 || nbMonstres == 4){
          showMonstre();
          moveMonstre(xMonstre,SOLMONSTRE);
          xMonstre--;
          if(xMonstre == 0){
            nbMonstres++;
            hideMonstre();
          }
        }

        //Avance tortue
        if(nbMonstres == 1){//1
          showTortue();
          moveTortue(xTortue,SOLTORTUE);
          xTortue--;
          if(xTortue == 0){
            nbMonstres++;
            hideTortue();
          }
        }

        //Monstre et Tortue
        if(nbMonstres == 3){//3
          showMonstre();
          moveMonstre(xMonstre,SOLMONSTRE);
          xMonstre--;
          if(xMonstre <= 120){
            dTortue = 1;
            showTortue();
          }
          if(dTortue == 1){
            moveTortue(MAXDROITE,SOLTORTUE);
            moveTortue(xTortueBis,SOLTORTUE);
            xTortueBis--;
          }
          if(xMonstre == 0){
            hideMonstre();
          }
          if(xTortueBis == 0){
            hideTortue();
            nbMonstres++;
          }
        }

        //Tortue volante
        if(nbMonstres == 5){
          if(declencheT0 == 1){
            showTortue();
            moveTortue(xTortueVole,SOLTORTUE - 35);
            xTortueVole--;
          }
          if(xTortueVole <= 90){
            declencheM1 = 1;
          }
          if(xTortueVole == 0){
            hideTortue();
            showTortue1();
            declencheT1 = 1;
            declencheT0 = 0;
          }
          if(declencheT1 == 1){
            moveTortue1(xTortue1,SOLTORTUE);
            xTortue1--;
          }
          if(xTortue1 == 0){//stop la T1
            declencheT1 = 0;
          }
          if(declencheM1 == 1){
            showMonstre1();
            moveMonstre1(xMonstre1,SOLMONSTRE);
            xMonstre1--;
          }
          if(xMonstre1 == 0){//stop monstre 1
            declencheM1 = 0;
          }
          if(xMonstre1 <= 30){
            declencheM0 = 1;
          }
          if(declencheM0 == 1){
            showMonstre();
            moveMonstre(xMonstre3,SOLMONSTRE);
            xMonstre3--;
          }
          if(xMonstre3 == 0){
            declencheM0 = 0;
          }
          if(xMonstre3 <= 90){
            declencheM2 = 1;
          }
          if(declencheM2 == 1){
            showMonstre2();
            moveMonstre2(xMonstre2,SOLMONSTRE);
            xMonstre2--;
          }
          if(xMonstre2 == 2){//stop tout
            hideMonstre1();
            hideMonstre2();
            hideMonstre();
            hideTortue();
            hideTortue1();
            break;
          }
        }

        //Fait redescendre peach
        if(yPeach < SOLPEACH){
          if(unSurDeux == 0) {
            yPeach += 1;
            movePeach(xPeach,yPeach);
            unSurDeux = 1;
          }else{
            unSurDeux = 0;
          }
        }else{
          jumpBreak = 0;
        }

        //Test collision peach et monstre -> blink de peach
        if( xPeach+16 >= xMonstre && (xPeach - xMonstre) < 10 && yPeach >= SOLMONSTRE - 16 ||
            xPeach+16 >= xMonstre2 && (xPeach - xMonstre2) < 10 && yPeach >= SOLMONSTRE - 16 ||
            xPeach+16 >= xMonstre1 && (xPeach - xMonstre1) < 10 && yPeach >= SOLMONSTRE - 16 ||
            xPeach+16 >= xTortue1 && (xPeach - xTortue1) < 10 && yPeach >= SOLMONSTRE - 16){
          //clignote peach
          hidePerso();
          hel_SwiVBlankIntrWait();
          showPerso();
        }

        // Wait for Vertical Blank
        hel_SwiVBlankIntrWait();
    }

  //Texte fin de niveau 1
  FAT_reinitScreen();
  app_showImgNiveau1FIN();
  hideALL();
  for(;;){
    hel_PadCapture();
    if (hel_PadQuery()->Pressed.Start){
      break;
    }
  }

  //Niveau 2
  FAT_reinitScreen();
  hideALL();
  app_showImgNiveau2();
  showPerso();
  showUsbKey();
  showUsbKey1();
  u8 xUsbKey2 = xUsbKey + 170;
  u8 yUsbKey2 = yUsbKey;
  u8 xUsbKey3 = 100;
  u8 yUsbKey3 = 2;
  u8 xUsbKey4 = 80;
  u8 yUsbKey4 = 2;
  u8 xUsbKey5 = 60;
  u8 yUsbKey5 = 2;
  u8 xUsbKey6 = 140;
  u8 yUsbKey6 = 2;
  u8 nbCle = 1;
  u8 cptNiv2 = 0;
  int gestionCleUsb[5];
  gestionCleUsb[0]=1;gestionCleUsb[1]=0;gestionCleUsb[2]=0;gestionCleUsb[3]=0;gestionCleUsb[4]=0;
  xPeach = 2;
  yPeach = SOLPEACH;
  movePeach(xPeach,yPeach);

  for(;;){
    hel_PadCapture();
    if (hel_PadQuery()->Pressed.Right){
      xPeach += 5;
      movePeach(xPeach,yPeach);
    }
    if (hel_PadQuery()->Pressed.Left){
      xPeach -= 5;
      movePeach(xPeach,yPeach);
    }
    //il pleut des clé usb
    moveUsbKey(xUsbKey,yUsbKey);
    moveUsbKey1(xUsbKey+20,yUsbKey-5);

    //premier jeu de 2 clés
    if(gestionCleUsb[0] == 1){
      yUsbKey++;
      if(yUsbKey > 125){
        yUsbKey = 2;
        gestionCleUsb[1] = 1;
        gestionCleUsb[0] = 0;
        hideUsbKey();
        hideUsbKey1();
      }
    }

    //seconde clé
    if(gestionCleUsb[1] == 1){
      showUsbKey2();
      yUsbKey2++;
      moveUsbKey2(xUsbKey2,yUsbKey2);
      if(yUsbKey2 > 125){
        yUsbKey2 = 2;
        gestionCleUsb[2] = 1;
      }
    }

    //Troisème clé
    if(gestionCleUsb[2] == 1){
      showUsbKey3();
      yUsbKey3++;
      moveUsbKey3(xUsbKey3,yUsbKey3);
      if(yUsbKey3 > 125){
        yUsbKey3 = 2;
        gestionCleUsb[3] = 1;
      }
    }

    //quatrième clé
    if(gestionCleUsb[3] == 1){
      showUsbKey4();
      yUsbKey4++;
      moveUsbKey4(xUsbKey4,yUsbKey4-10);
      if(yUsbKey4 > 125){
        yUsbKey4 = 2;
        gestionCleUsb[4] = 1;

        //on relance les 2 première clés
        yUsbKey = 2;
        showUsbKey();
        showUsbKey1();
        gestionCleUsb[0] = 1;
      }
    }

    //cinquième clé
    if(gestionCleUsb[4] == 1){
      showUsbKey5();
      yUsbKey5++;
      moveUsbKey5(xUsbKey5,yUsbKey5+5);
      if(yUsbKey5 > 125){
        yUsbKey5 = 2;
        gestionCleUsb[5] = 1;
      }
    }

    //dernière clé
    if(gestionCleUsb[5] == 1){
      showUsbKey6();
      yUsbKey6++;
      moveUsbKey6(xUsbKey6,yUsbKey6-15);
      if(yUsbKey6 > 125){
        yUsbKey6 = 2;
        cptNiv2++;
      }
      if(cptNiv2 == 2){
        break;
      }
    }

    //Test collision peach et monstre -> blink de peach
    //if(xPeach+16 >= xMonstre && temporisation < 30){
    if( xUsbKey < xPeach && xPeach < xUsbKey + 11 && yPeach <= yUsbKey + 10 ||
        xUsbKey2 < xPeach && xPeach < xUsbKey2 + 11 && yPeach <= yUsbKey2 + 10 ||
        xUsbKey3 < xPeach && xPeach < xUsbKey3 + 11 && yPeach <= yUsbKey3 + 10 ||
        xUsbKey4 < xPeach && xPeach < xUsbKey4 + 11 && yPeach <= yUsbKey4 + 10 ||
        xUsbKey5 < xPeach && xPeach < xUsbKey5 + 11 && yPeach <= yUsbKey5 + 10 ||
        xUsbKey6 < xPeach && xPeach < xUsbKey6 + 11 && yPeach <= yUsbKey6 + 10
      ){
      //clignote peach
      hidePerso();
      hel_SwiVBlankIntrWait();
      showPerso();
    }


    hel_SwiVBlankIntrWait();
  }//fin niveau 2

  //Texte indiquant que le niveau est validé
  FAT_reinitScreen();
  hideALL();
  app_showImgNiveau2Valide();
  for(;;){
    hel_PadCapture();
    if (hel_PadQuery()->Pressed.Start){
      break;
    }
    hel_SwiVBlankIntrWait();
  }


  //final du jeu
  FAT_reinitScreen();
  hideALL();
  app_showImgNiveauFinal();
  xPeach = 2;
  yPeach = SOLPEACH;
  showPerso();
  movePeach(xPeach,yPeach);
  for(;;){
    hel_PadCapture();
    if (hel_PadQuery()->Pressed.Right){
      xPeach += 5;
      movePeach(xPeach,yPeach);
    }
    if(xPeach >= 195){
      break;
    }
    hel_SwiVBlankIntrWait();
  }

  //fin
  FAT_reinitScreen();
  hideALL();
  app_showImgTexteFinal();
  for(;;){}

  return 0;

} //fin du main

void hideALL(){
  hidePerso();
  hideChamp1();
  hideTortue();
  hideMonstre();
  hideUsbKey();
  hideUsbKey1();
  hideUsbKey2();
  hideUsbKey3();
  hideUsbKey4();
  hideUsbKey5();
  hideUsbKey6();
  hideMonstre1();
  hideMonstre2();
}

//fait sauter le perso
void jumpPeach(){
  yPeach -= 30;
  movePeach(xPeach,yPeach);
  jump = 0;
}

void discoursChampi(){
    app_writeSomeText("Bonjour Morgane, je suis ",2,4);
    app_writeSomeText("un gentil petit champi",2,5);
    app_writeSomeText("et je vais te raconter",2,6);
    app_writeSomeText("une histoire.",2,7);
    app_writeSomeText("Tu viens d'etre catapulte",2,8);
    app_writeSomeText("dans un mode magique...",2,9);
    app_writeSomeText("Le monde des geeks !",2,10);
    app_writeSomeText("Ta mission si tu l'acceptes",2,11);
    app_writeSomeText("est d'aller delivrer ton",2,12);
    app_writeSomeText("geek d'amour :)",2,13);
    app_writeSomeText("[PRESS A]",5,16);

    for(;;) {
      hel_PadCapture();
            if (hel_PadQuery()->Pressed.A || hel_PadQuery()->Pressed.B) {
                break;
            }
            hel_SwiVBlankIntrWait();
    }
    FAT_reinitScreen();
    app_writeSomeText("Il est actuellement",1,4);
    app_writeSomeText("prisonnier dans une boucle",2,5);
    app_writeSomeText("infinie.",2,6);
    app_writeSomeText("Pour cela tu devras eviter",2,7);
    app_writeSomeText("des petits monstres et",2,8);
    app_writeSomeText("les pluies de clefs usb.",2,9);
    app_writeSomeText("Appuie sur START pour ",2,14);
    app_writeSomeText("demarrer ta quete!",2,15);
}

void animePersonage(){
  u8 x=100;
  u8 y=60;
  for(;;) {
    hel_PadCapture();
          if (hel_PadQuery()->Pressed.Start) {
              break;
          }
    x++;
    showPerso();
    movePeach(x,y);
    if (x >= 150) {
      x==100;
    }
    hel_SwiVBlankIntrWait();
  }
}

//void app_showFirstScreen() {

//}

/**
 * \brief Méthode qui permet de réinitialiser le BG SCREEN_LAYER proprement.
 *
 * <b>NE PAS TOUCHER !  </b>
 */
void FAT_reinitScreen() {
    if (ham_bg[SCREEN_LAYER].ti) {
        ham_DeInitTileSet(ham_bg[SCREEN_LAYER].ti);
        ham_DeInitMapSet(ham_bg[SCREEN_LAYER].mi);
        FAT_forceClearTextLayer();
    }
}

/**
 * \brief Méthode à réfactorer : effacer l'écran texte en affichant des espaces partout.
 *
 * Performance warning ! Afficher du texte via HAM est lent !
 */
void FAT_forceClearTextLayer() {
    if (ham_bg[TEXT_LAYER].ti) {

        ham_DeInitTileSet(ham_bg[TEXT_LAYER].ti);
        ham_DeInitMapSet(ham_bg[TEXT_LAYER].mi);

        ham_bg[TEXT_LAYER].ti = ham_InitTileSet((void*) ResData(RES_TEXT_RAW), RES_TEXT_RAW_SIZE16, 1, 1);
        ham_bg[TEXT_LAYER].mi = ham_InitMapEmptySet((u8) 1024, 0);
    }

}

/**
 * \brief La palette pour les sprites est différente: cette fonction la charge au bon endroit.
 */
void FAT_initSpritePalette() {
    hel_PalObjLoad16(ResData16(RES_SPRITES_PAL), 0);
}

//Gestion de Peach
/**
 * ID technique HAM pour le cursor de taille 1.
 */
THandle peach_obj;
void initPeach() {
    peach_obj = hel_ObjCreate(ResData(RES_PEACH_RAW), // Pointer to source graphic
                                                          OBJ_SHAPE_VERTICAL,       // Obj Shape
                                                          2,                      // Obj Size, 1 means 16x16 pixels, if Shape is set to SQUARE
                                                          OBJ_MODE_SEMITRANSPARENT,        // Obj Mode
                                                          COLORS_16,              // Use 16 color mode
                                                          0,                      // Palette number. Only neccessary in 16 color mode
                                                          FALSE,                  // Don't use mosaic
                                                          FALSE,                  // Don't flip the sprite horizontally
                                                          FALSE,                  // Don't flip the object vertically
                                                          1,                      // Priority against background. 0=higest
                                                          FALSE,                  // Don't make the object double-sized
                                                          100,                    // Destination horzintal screen coordinate in pixels
                                                          70                      // Destination vertical screen coordinate in pixels
                                                          );

    hel_ObjSetVisible(peach_obj, 0);
}

void hidePerso() {
  hel_ObjSetVisible(peach_obj, 0);
}

void showPerso() {
  hel_ObjSetVisible(peach_obj, 1);
}

void movePeach(u8 x, u8 y) {
    hel_ObjSetXY(peach_obj, x, y);
}

//Gestion des champi
THandle champ1_obj;
void initChamp1() {
    champ1_obj = hel_ObjCreate(ResData(RES_CHAMP1_RAW), // Pointer to source graphic
                                                          OBJ_SHAPE_SQUARE,       // Obj Shape
                                                          1,                      // Obj Size, 1 means 16x16 pixels, if Shape is set to SQUARE
                                                          OBJ_MODE_SEMITRANSPARENT,        // Obj Mode
                                                          COLORS_16,              // Use 16 color mode
                                                          0,                      // Palette number. Only neccessary in 16 color mode
                                                          FALSE,                  // Don't use mosaic
                                                          FALSE,                  // Don't flip the sprite horizontally
                                                          FALSE,                  // Don't flip the object vertically
                                                          1,                      // Priority against background. 0=higest
                                                          FALSE,                  // Don't make the object double-sized
                                                          100,                    // Destination horzintal screen coordinate in pixels
                                                          70                      // Destination vertical screen coordinate in pixels
                                                          );

    hel_ObjSetVisible(champ1_obj, 0);
}
void hideChamp1() {
  hel_ObjSetVisible(champ1_obj, 0);
}

void showChamp1() {
  hel_ObjSetVisible(champ1_obj, 1);
}

void moveChamp1(u8 x, u8 y) {
    hel_ObjSetXY(champ1_obj, x, y);
}

//Gestion de la tortue
THandle tortue_obj;
void initTortue() {
    tortue_obj = hel_ObjCreate(ResData(RES_TORTUE_RAW), // Pointer to source graphic
                                                          OBJ_SHAPE_VERTICAL,       // Obj Shape
                                                          2,                      // Obj Size, 1 means 16x16 pixels, if Shape is set to SQUARE
                                                          OBJ_MODE_SEMITRANSPARENT,        // Obj Mode
                                                          COLORS_16,              // Use 16 color mode
                                                          0,                      // Palette number. Only neccessary in 16 color mode
                                                          FALSE,                  // Don't use mosaic
                                                          FALSE,                  // Don't flip the sprite horizontally
                                                          FALSE,                  // Don't flip the object vertically
                                                          1,                      // Priority against background. 0=higest
                                                          FALSE,                  // Don't make the object double-sized
                                                          100,                    // Destination horzintal screen coordinate in pixels
                                                          70                      // Destination vertical screen coordinate in pixels
                                                          );

    hel_ObjSetVisible(tortue_obj, 0);
    //on clone la tortue
    tabTortue[0] = hel_ObjClone(tortue_obj,5,5);
}
void hideTortue() {
  hel_ObjSetVisible(tortue_obj, 0);
}

void showTortue() {
  hel_ObjSetVisible(tortue_obj, 1);
}

void moveTortue(u8 x, u8 y) {
    hel_ObjSetXY(tortue_obj, x, y);
}
void hideTortue1() {
  hel_ObjSetVisible(tabTortue[0], 0);
}

void showTortue1() {
  hel_ObjSetVisible(tabTortue[0], 1);
}

void moveTortue1(u8 x, u8 y) {
    hel_ObjSetXY(tabTortue[0], x, y);
}

//Gestion du monstre
THandle monstre_obj;
void initMonstre() {
    monstre_obj = hel_ObjCreate(ResData(RES_MONSTRE1_RAW), // Pointer to source graphic
                                                          OBJ_SHAPE_VERTICAL,       // Obj Shape
                                                          2,                      // Obj Size, 1 means 16x16 pixels, if Shape is set to SQUARE
                                                          OBJ_MODE_SEMITRANSPARENT,        // Obj Mode
                                                          COLORS_16,              // Use 16 color mode
                                                          0,                      // Palette number. Only neccessary in 16 color mode
                                                          FALSE,                  // Don't use mosaic
                                                          FALSE,                  // Don't flip the sprite horizontally
                                                          FALSE,                  // Don't flip the object vertically
                                                          1,                      // Priority against background. 0=higest
                                                          FALSE,                  // Don't make the object double-sized
                                                          100,                    // Destination horzintal screen coordinate in pixels
                                                          70                      // Destination vertical screen coordinate in pixels
                                                          );

    hel_ObjSetVisible(monstre_obj, 0);
    //on clone le monstre
    tabMonstre[0] = hel_ObjClone(monstre_obj,5,5);
    tabMonstre[1] = hel_ObjClone(monstre_obj,5,5);
}
void hideMonstre() {
  hel_ObjSetVisible(monstre_obj, 0);
}

void showMonstre() {
  hel_ObjSetVisible(monstre_obj, 1);
}

void moveMonstre(u8 x, u8 y) {
    hel_ObjSetXY(monstre_obj, x, y);
}
void hideMonstre1() {
  hel_ObjSetVisible(tabMonstre[0], 0);
}

void showMonstre1() {
  hel_ObjSetVisible(tabMonstre[0], 1);
}

void moveMonstre1(u8 x, u8 y) {
    hel_ObjSetXY(tabMonstre[0], x, y);
}
void hideMonstre2() {
  hel_ObjSetVisible(tabMonstre[1], 0);
}

void showMonstre2() {
  hel_ObjSetVisible(tabMonstre[1], 1);
}

void moveMonstre2(u8 x, u8 y) {
    hel_ObjSetXY(tabMonstre[1], x, y);
}

//Gestion de la clé usb
THandle usbkey_obj;
void initUsbKey() {
    usbkey_obj = hel_ObjCreate(ResData(RES_USBKEY_RAW), // Pointer to source graphic
                                                          OBJ_SHAPE_SQUARE,       // Obj Shape
                                                          1,                      // Obj Size, 1 means 16x16 pixels, if Shape is set to SQUARE
                                                          OBJ_MODE_SEMITRANSPARENT,        // Obj Mode
                                                          COLORS_16,              // Use 16 color mode
                                                          0,                      // Palette number. Only neccessary in 16 color mode
                                                          FALSE,                  // Don't use mosaic
                                                          FALSE,                  // Don't flip the sprite horizontally
                                                          FALSE,                  // Don't flip the object vertically
                                                          1,                      // Priority against background. 0=higest
                                                          FALSE,                  // Don't make the object double-sized
                                                          100,                    // Destination horzintal screen coordinate in pixels
                                                          70                      // Destination vertical screen coordinate in pixels
                                                          );

    hel_ObjSetVisible(usbkey_obj, 0);
    //on clone les cle usb
    tabUsbKey[0] = hel_ObjClone(usbkey_obj,5,5);
    tabUsbKey[1] = hel_ObjClone(usbkey_obj,5,5);
    tabUsbKey[2] = hel_ObjClone(usbkey_obj,5,5);
    tabUsbKey[3] = hel_ObjClone(usbkey_obj,5,5);
    tabUsbKey[4] = hel_ObjClone(usbkey_obj,5,5);
    tabUsbKey[5] = hel_ObjClone(usbkey_obj,5,5);

}
void hideUsbKey() {
  hel_ObjSetVisible(usbkey_obj, 0);
}

void showUsbKey() {
  hel_ObjSetVisible(usbkey_obj, 1);
}

void moveUsbKey(u8 x, u8 y) {
    hel_ObjSetXY(usbkey_obj, x, y);
}

void hideUsbKey1() {
  hel_ObjSetVisible(tabUsbKey[0], 0);
}

void showUsbKey1() {
  hel_ObjSetVisible(tabUsbKey[0], 1);
}
void moveUsbKey1(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[0], x, y);
}

void hideUsbKey2() {
  hel_ObjSetVisible(tabUsbKey[1], 0);
}

void showUsbKey2() {
  hel_ObjSetVisible(tabUsbKey[1], 1);
}
void moveUsbKey2(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[1], x, y);
}
void hideUsbKey3() {
  hel_ObjSetVisible(tabUsbKey[2], 0);
}
void showUsbKey3() {
  hel_ObjSetVisible(tabUsbKey[2], 1);
}
void moveUsbKey3(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[2], x, y);
}
void hideUsbKey4() {
  hel_ObjSetVisible(tabUsbKey[3], 0);
}
void showUsbKey4() {
  hel_ObjSetVisible(tabUsbKey[3], 1);
}
void moveUsbKey4(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[3], x, y);
}
void hideUsbKey5() {
  hel_ObjSetVisible(tabUsbKey[4], 0);
}
void showUsbKey5() {
  hel_ObjSetVisible(tabUsbKey[4], 1);
}
void moveUsbKey5(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[4], x, y);
}
void hideUsbKey6() {
  hel_ObjSetVisible(tabUsbKey[5], 0);
}
void showUsbKey6() {
  hel_ObjSetVisible(tabUsbKey[5], 1);
}
void moveUsbKey6(u8 x, u8 y) {
    hel_ObjSetXY(tabUsbKey[5], x, y);
}


// Implémentations des prototypes et fonctions utilitaires

// Procédure pour l'interruption système de synchro.
void VBLInterruptHandler(void) {
    hel_ObjTransmit();
    // acknowledge interrupt
    hel_IntrAcknowledge(INT_TYPE_VBL);
}

// app_init
// Initialise la stack système
// Initialise la palette principale
// Initialise le moteur de rendu de texte
//#define TEXT_LAYER 1
//#define SCREEN_LAYER 3


u8 ATTR_EWRAM ATTR_ALIGNED(4) g_BgTextSystemMemory[HEL_SUBSYSTEM_BGTEXT_REQUIREDMEMORY];
u16 ATTR_EWRAM g_CharLUT[256];
// attention, table ASCII uniquement sinon ça fout la grouille.
const unsigned char CHARORDER[] =
        " BCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn"\
    "opqrstuvwxyz0123456789,.-;:A#^+*@"\
    "!\"~$%&/()=?|\\<>[]{}¹²³°";

u8 ATTR_EWRAM ATTR_ALIGNED(4) g_ObjSystemBuffer[HEL_SUBSYSTEM_OBJ_REQUIREDMEMORY];

// Reserve memory for the Map-System. This buffer
// is used to manage internal states of the Map-System.
// You can achieve a little performance increase when you
// store it in IWRAM, but keep in mind, IWRAM is very limited!
// The recommended memory location is EWRAM.
u8 ATTR_EWRAM ATTR_ALIGNED(4) g_MapSystemBuffer[HEL_SUBSYSTEM_MAP_REQUIREDMEMORY];

void app_init() {
    // HAM !
    ham_Init();
    hel_SysSetPrefetch(FALSE);

    hel_BgSetMode(0);

    hel_MapInit(g_MapSystemBuffer);
    hel_BgTextInit((void*) g_BgTextSystemMemory);
    hel_ObjInit(g_ObjSystemBuffer);

    hel_PadInit();
    hel_PadSetRepeatDelay(PAD_BUTTON_R | PAD_BUTTON_L | PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_UP | PAD_BUTTON_DOWN | PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_START, 1);
    hel_PadSetRepeatRate(PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_UP | PAD_BUTTON_DOWN, 3);
    hel_PadSetRepeatRate(PAD_BUTTON_R | PAD_BUTTON_L | PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_START, 0);

    // initialisation des palettes.
    hel_PalBgLoad256(ResData16(RES_SCREEN_PAL));
    FAT_initSpritePalette();

    // Initialize the tileset and an empty
    ham_bg[TEXT_LAYER].ti = ham_InitTileSet((void*) ResData(RES_TEXT_RAW), RES_TEXT_RAW_SIZE16, 1, 1);
    ham_bg[TEXT_LAYER].mi = ham_InitMapEmptySet((u8) 640, 0);

    hel_BgTextCreate(
            TEXT_LAYER, // BgNo
            1, // Width of one character specified in tiles
            1, // Height of one character specified in tiles
            //ResData(RES_CHARSET8X8_MAP), // Pointer to character map
            ResData(RES_TEXT_MAP),
            CHARORDER, // Pointer to array that reflects the order of characters on source graphic
            g_CharLUT, // Pointer to buffer that receives the generated lookup table
            BGTEXT_FLAGS_GENERATELUT); // Flags that control creation and print behaviour

    ham_InitBg(TEXT_LAYER, TRUE, 0, FALSE);

    hel_IntrStartHandler(INT_TYPE_VBL, (void*) &VBLInterruptHandler);
}


void app_showImgBackground() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_IMGBACKGROUND_RAW), RES_IMGBACKGROUND_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_IMGBACKGROUND_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgGameCover() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_IMGGAMECOVER_RAW), RES_IMGGAMECOVER_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_IMGGAMECOVER_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgIntroChampi() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_INTRO_RAW), RES_INTRO_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_INTRO_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgNiveau1() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_NIV1_RAW), RES_NIV1_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_NIV1_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgNiveau1FIN() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_NIV1FIN_RAW), RES_NIV1FIN_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_NIV1FIN_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgNiveau2() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_NIV2_RAW), RES_NIV2_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_NIV2_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgNiveauFinal() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_NIVFINAL_RAW), RES_NIVFINAL_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_NIVFINAL_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgNiveau2Valide() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_NIV2FIN_RAW), RES_NIV2FIN_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_NIV2FIN_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_showImgTexteFinal() {

    ham_bg[SCREEN_LAYER].ti = ham_InitTileSet((void*)ResData(RES_TEXTEFINAL_RAW), RES_TEXTEFINAL_RAW_SIZE16, 1, 1);
    // Create a map for background
    hel_MapCreate(SCREEN_LAYER,        // Background number
                  32,   // width in tiles
                  20,   // height in tiles
                  ResData(RES_TEXTEFINAL_MAP),   // Pointer to source MapData
                  sizeof(u16),                  // DataTypeSize of one element from Source MapData
                  MAP_FLAGS_DEFAULT);           // Flags to control map behaviour

    ham_InitBg(SCREEN_LAYER, 1, 3, FALSE);

}

void app_writeSomeText(char* text, u8 xTEXT, u8 yTEXT) {
  hel_BgTextPrintF(TEXT_LAYER, xTEXT, yTEXT, 0, text);
}
