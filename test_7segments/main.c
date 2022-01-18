 //arduino 4 digits 7 segments + 4DP (dp = digital point)

// int : declaration d'une variable (nbre entier)
// stockage de l'information dans l'arduino

int delai_latence=10;
int potar=A0; // entrée analogique A0 (branchée au centre du potar)

int digit1 = 2; //Afficheur le plus à gauche - chiffre 1000
int digit2 = 3; //Afficheur centre gauche - chiffre 100
int digit3 = 4; //Afficheur centre droit - chiffre 10
int digit4 = 5; //Afficheur le plus à droite - chiffre 1

int segA = 6;
int segB = 7;
int segC = 8;
int segD = 9;
int segE = 10;
int segF = 11;
int segG = 12;
int dp = 13;//dp = digital point

//void = fonction, contient le programme
//setup : configuration
void setup()
{                
 pinMode(segA, OUTPUT);
 pinMode(segB, OUTPUT);
 pinMode(segC, OUTPUT);
 pinMode(segD, OUTPUT);
 pinMode(segE, OUTPUT);
 pinMode(segF, OUTPUT);
 pinMode(segG, OUTPUT);
 pinMode(dp, OUTPUT);

pinMode(digit1, OUTPUT);
pinMode(digit2, OUTPUT);
pinMode(digit3, OUTPUT);
pinMode(digit4, OUTPUT);

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);
//on commence par tout éteindre
}


void afficheDigit(int num)
// == égalité entre 2 variables , signifie "est égal à"
{
 if (num==0)
   {
   digitalWrite(segA, LOW); //allumer a
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, LOW);
   digitalWrite(segF, LOW);
   digitalWrite(segG, HIGH); //éteindre g
   digitalWrite(dp, HIGH);
   }

 if (num==1)
   {
   digitalWrite(segA, HIGH);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, HIGH);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, HIGH);
   digitalWrite(segG, HIGH);
   digitalWrite(dp, HIGH);
   }

 if (num==2)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, LOW);
   digitalWrite(segC, HIGH);
   digitalWrite(segD, LOW);
   digitalWrite(segE, LOW);
   digitalWrite(segF, HIGH);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==3)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, HIGH);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==4)
   {
   digitalWrite(segA, HIGH);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, HIGH);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, LOW);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==5)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, HIGH);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, LOW);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==6)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, HIGH);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, LOW);
   digitalWrite(segF, LOW);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==7)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, HIGH);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, HIGH);
   digitalWrite(segG, HIGH);
   digitalWrite(dp, HIGH);
   }

 if (num==8)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, LOW);
   digitalWrite(segF, LOW);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }

 if (num==9)
   {
   digitalWrite(segA, LOW);
   digitalWrite(segB, LOW);
   digitalWrite(segC, LOW);
   digitalWrite(segD, LOW);
   digitalWrite(segE, HIGH);
   digitalWrite(segF, LOW);
   digitalWrite(segG, LOW);
   digitalWrite(dp, HIGH);
   }
}


void affiche4digits(int num)
{
    int nb;
    // arduino calcule des entiers

    //affiche le chiffre des 1000
    nb=num/1000;
    digitalWrite(digit4, LOW);
    digitalWrite(digit1, HIGH);
    afficheDigit(nb);

    delay(delai_latence);

    //affiche le chiffre des 100
    num=num-nb*1000;
    nb=num/100;
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, HIGH);
    afficheDigit(nb);

    delay(delai_latence);  

    //affiche le chiffre des 10
    num=num-nb*100;
    nb=num/10;
    digitalWrite(digit2, LOW);
    digitalWrite(digit3, HIGH);
    afficheDigit(nb);

    delay(delai_latence);  

    //affiche le chiffre des 1
    num=num-nb*10;
    nb=num;
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, HIGH);
    afficheDigit(nb);

    delay(delai_latence);  
}

void loop()
{
    affiche4digits(2017);

    delai_latence=1+(analogRead(potar)/2);
}
